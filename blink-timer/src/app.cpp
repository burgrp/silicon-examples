target::gpio_b_f::Peripheral* LED_PORT = &target::GPIOB;
int LED_PIN = 7;

class ToggleTimer : public genericTimer::Timer {

	bool led = false;

	void onTimer() {
		led = !led;
		LED_PORT->ODR.setODR(LED_PIN, led);
		start(10);
	}

};

ToggleTimer timer;

void initApplication() {
	target::RCC.AHBENR.setIOPBEN(true);
	LED_PORT->MODER.setMODER(LED_PIN, 1);

	timer.start(10);
}

