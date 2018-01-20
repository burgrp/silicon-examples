void initApplication() {
	target::RCC.AHBENR.setIOPBEN(true);
	target::GPIOB.MODER.setMODER(7, 1);

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
	target::GPIOB.ODR.setODR(7, led);
}