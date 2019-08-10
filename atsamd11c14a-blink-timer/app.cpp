int LED_PIN = 23;

class ToggleTimer : public genericTimer::Timer {

	bool led = false;

	void onTimer() {
		led = !led;
		target::PORT.OUTTGL.setOUTTGL(1 << LED_PIN);
		start(10);
	}

};

ToggleTimer timer;

void initApplication() {
	target::PM.APBBMASK.setPORT_(1);
	target::PORT.DIR.setDIR(1 << LED_PIN);
	timer.start(10);
}

