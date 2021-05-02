#include <shiftr.h>

/* The following functions are abstraction for cross 
 * compatibilities sake */
void srWritePin(uint8_t pin, bool out) {
#ifdef USING_WPI
	digitalWrite(pin, out);
#else
	bcm2835_gpio_write(pin, out);
#endif /* #ifdef USING_WPI */
}

void srDelay(size_t t) {
#ifdef USING_WPI
	delay(t);
#else
	bcm2835_delay(t);
#endif /* #ifdef USING_WPI */
}

void srSetPinAsOutput(uint8_t pin) {
#ifdef USING_WPI
	pinMode(pin, OUTPUT);
#else
	bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
#endif /* #ifdef USING_WPI */
}

void srInitGpioControl(void) {
#ifdef USING_WPI
	wiringPiSetup();
#else	
	if(!bcm2835_init())
		exit(1);
#endif /* #ifdef USING_WPI */
}

void srClose(void) {
#ifndef USING_WPI
	bcm2835_close();
#endif
}
