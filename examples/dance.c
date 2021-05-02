#include <shiftr.h>

/* The pins we will be using */
#define DATA_PIN	RPI_GPIO_P1_11
#define CLOCK_PIN	RPI_GPIO_P1_15
#define LATCH_PIN	RPI_GPIO_P1_23
#define ENABLE_PIN	RPI_GPIO_P1_19

int main(void) {
	struct shiftRegister sr;
	int i;

	/* initializes the gpio control */
	srInitGpioControl();

	/* initializes the shift register pins */
	sr  = initShiftRegister(4,
			DATA_PIN, CLOCK_PIN, LATCH_PIN,
			SR_NO_PIN, ENABLE_PIN, true);


	/* This loop will be repeated 50 times */
	for(i = 0; i < 50; i++) {
		/* shifts the value 0xA to the shift register */
		srWriteValue(sr, 0xA);

		/* updates the shift register output */
		srUpdateOutput(sr);
		srDelay(100);

		/* shifts the value 0x5 to the shift register */
		srWriteValue(sr, 0x5);

		/* updates the shift register output */
		srUpdateOutput(sr);
		srDelay(100);
	}

	/* closes the gpio control */
	srClose();
}
