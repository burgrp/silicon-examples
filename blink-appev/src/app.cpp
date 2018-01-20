target::gpio_b_f::Peripheral* LED_PORT = &target::GPIOB;
int LED_PIN = 7;

class ToggleEvent : public applicationEvents::EventHandler {
	bool led = false;

	void onEvent() {
		led = !led;
		LED_PORT->ODR.setODR(LED_PIN, led);
	}

};

ToggleEvent toggleEvent;
int toggleEventId;

void initApplication() {
	target::RCC.AHBENR.setIOPBEN(true);

	LED_PORT->MODER.setMODER(LED_PIN, 1);

	target::RCC.APB1ENR.setTIM14EN(true);
	target::TIM14.ARR.setARR(0xFFFF);
	target::TIM14.PSC.setPSC(10);
	target::TIM14.DIER.setUIE(true);
	target::TIM14.CR1.setCEN(1);

	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::TIM14);

	toggleEventId = applicationEvents::createEventId();
	toggleEvent.handle(toggleEventId);
}

void interruptHandlerTIM14() {
	applicationEvents::schedule(toggleEventId);
	target::TIM14.SR.setUIF(0);
}
