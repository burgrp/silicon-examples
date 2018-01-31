target::gpio_b_f::Peripheral* LED_PORT = &target::GPIOB;
int LED_PIN = 7;

class TestEndopoint : public usbd::AbstractBulkEndpoint {
    
public:
    
    bool sendZLP = false;
    
    void init() {
        rxBufferSize = 64;
        txBufferSize = 64;
        AbstractBulkEndpoint::init();
    }

    void correctTransferIn() {
    }
    
    void correctTransferOut(unsigned char* data, int len) {
		
		if (len == 1 && data[0] == 0) {
			int state = LED_PORT->ODR.getODR(LED_PIN);
			send((unsigned char*)&state, 1);
		} 
		
		if (len == 2 && data[0] == 1) {
			LED_PORT->ODR.setODR(LED_PIN, data[1]);
		}
        statRx(usbd::EP_VALID);
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

	void init() {
		interfaces[0] = &interface;
		maxPower = 100;
		UsbConfiguration::init();
	}
};

class TestDevice : public usbd::UsbDevice {
public:

	TestConfiguration configuration;

	void init() {
		configurations[0] = &configuration;		
		UsbDevice::init();
	}
};

TestDevice testDevice;

void initApplication() {
	target::RCC.AHBENR.setIOPBEN(true);
	LED_PORT->MODER.setMODER(LED_PIN, 1);

	LED_PORT->ODR.setODR(LED_PIN, 1);

	testDevice.init();
}
