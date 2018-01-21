target::gpio_b_f::Peripheral* LED_PORT = &target::GPIOB;
int LED_PIN = 7;

class TestEndopoint : public usbd::AbstractBulkEndpoint {
    
public:
    
    bool sendZLP = false;
    
    virtual void init() {
        rxBufferSize = 64;
        txBufferSize = 64;
        AbstractBulkEndpoint::init();
    }

    void correctTransferIn() {
        
//        int len = 0;
//        unsigned char buffer[txBufferSize];
//        while (len < sizeof(buffer) && transaction.read(&buffer[len])) {
//            len++;
//        }
//        
//        if (len || sendZLP) {
//            send(buffer, len);
//        }
//        
//        sendZLP = len == txBufferSize;
        send(0, 0);
    }
    
    void correctTransferOut(unsigned char* data, int len) {
        // we got data
        statRx(EP_VALID);
    }

};


class TestInterface : public usbd::UsbInterface {
public:


		TestEndopoint endpoint;

		void init() {
			endpoints[0] = &endpoint;
			UsbInterface::init();
		}


};

class TestConfiguration : public usbd::UsbConfiguration {
public:
	TestInterface interface;

	virtual void init() {
		interfaces[0] = &interface;
		maxPower = 100;
		UsbConfiguration::init();
	}
};

class TestDevice : public usbd::UsbDevice {
public:

	TestConfiguration configuration;

	virtual void init() {
		configurations[0] = &configuration;
		strVendor = "gogo inc.";
		UsbDevice::init();
	}
};

TestDevice testDevice;

void initApplication() {
	target::RCC.AHBENR.setIOPBEN(true);
	LED_PORT->MODER.setMODER(LED_PIN, 1);

	testDevice.init();

	LED_PORT->ODR.setODR(LED_PIN, 1);
}

extern "C" {

	void * memcpy(unsigned char* destination, unsigned char const* source, size_t num) {
		for (int c = 0; c < num; c++) {
			destination[c] = source[c];
		}
		return destination;
	}

	void __cxa_pure_virtual() {
		while (1);
	}

}
