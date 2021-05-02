/* This simple example program shifts a single bit to a shift register */

#include <shiftr.h>

/* The pins we will be using */
#define DATA_PIN	RPI_GPIO_P1_11
#define CLOCK_PIN	RPI_GPIO_P1_15
#define LATCH_PIN	RPI_GPIO_P1_23
#define ENABLE_PIN	RPI_GPIO_P1_19

int main(void) {
	struct shiftRegister sr;

	/* initializes the gpio control */
	srInitGpioControl();

	/* initializes the shift register pins */
	sr  = initShiftRegister(1,
			DATA_PIN, CLOCK_PIN, LATCH_PIN,
			SR_NO_PIN, ENABLE_PIN, true);


	/* shifts a single bit (1) to the shift register */
	srWriteBit(sr, 1);

	/* Updates the output of the shift register */
	srUpdateOutput(sr);

	/* closes the gpio control */
	srClose();
}
