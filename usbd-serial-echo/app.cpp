#include <ctype.h>

target::gpio_b_f::Peripheral* LED_PORT = &target::GPIOB;
int LED_PIN = 7;

class EchoUsbDevice : public usbdSerial::UsbSimpleSerialDevice {
public:

	void sendDataOut(unsigned char* data, int len) {
		LED_PORT->ODR.setODR(LED_PIN, !LED_PORT->ODR.getODR(LED_PIN));
		for (int c = 0; c < len; c++) {
			sendByteIn(toupper(data[c]));
		}

		dataSentOut();
	}

};

EchoUsbDevice echoUsbDevice;

void initApplication() {
	target::RCC.AHBENR.setIOPBEN(true);
	LED_PORT->MODER.setMODER(LED_PIN, 1);

	LED_PORT->ODR.setODR(LED_PIN, 1);

	echoUsbDevice.init();
}
