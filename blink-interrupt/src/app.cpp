target::gpio_b_f::Peripheral* LED_PORT = &target::GPIOB;
int LED_PIN = 7;

void initApplication() {
	target::RCC.AHBENR.setIOPBEN(true);
	
	LED_PORT->MODER.setMODER(LED_PIN, 1);

	target::RCC.APB1ENR.setTIM14EN(true);
	target::TIM14.ARR.setARR(0xFFFF);
	target::TIM14.PSC.setPSC(10);
	target::TIM14.DIER.setUIE(true);
	target::TIM14.CR1.setCEN(1);

	target::NVIC.ISER.setSETENA(1 << target::interrupts::External::TIM14);
}

void handleEvent() {
}

bool led = false;

void interruptHandlerTIM14() {
	led = !led;
	target::TIM14.SR.setUIF(0);
	LED_PORT->ODR.setODR(LED_PIN, led);
}