#include <shiftr.h>

struct shiftRegister initShiftRegister(uint8_t pinN, uint8_t data, uint8_t clock, uint8_t updateOutput, 
		uint8_t reset, uint8_t outputEnable, bool enable) {
	struct shiftRegister sr;
	sr.outputs = pinN;
	sr.pins.data = data;
	sr.pins.clock = clock;
	sr.pins.updateOutput = updateOutput;
	sr.pins.reset = reset;
	sr.pins.enable = outputEnable;

	srSetPinAsOutput(sr.pins.data);
	srSetPinAsOutput(sr.pins.clock);
	srSetPinAsOutput(sr.pins.updateOutput);

	if(sr.pins.reset != SR_NO_PIN) {
		srSetPinAsOutput(sr.pins.reset);
		srWritePin(sr.pins.reset, SR_HIGH);
	}

	if(sr.pins.enable != SR_NO_PIN) {
		srSetPinAsOutput(sr.pins.enable);
		if(enable)
			srEnable(sr);
		else
			srDisable(sr);
	}
	else
		sr.isEnabled = true;

	return sr;
}

void srUpdateOutput(struct shiftRegister sr) {
	srMicroDelay(1);
	srWritePin(sr.pins.updateOutput, SR_HIGH);
	srMicroDelay(1);
	srWritePin(sr.pins.updateOutput, SR_LOW);
}

void srWriteBit(struct shiftRegister sr, bool bit) {
	srWritePin(sr.pins.data, bit ? SR_HIGH : SR_LOW); /* We put the bit into the data pin */

	srMicroDelay(1);

	srWritePin(sr.pins.clock, SR_HIGH); /* We pull the clock high */

	srMicroDelay(1);

	srWritePin(sr.pins.clock, SR_LOW); /* Now the bit should be written to the shift register */
}

void srEnable(struct shiftRegister sr) {
	srWritePin(sr.pins.enable, SR_LOW);

	sr.isEnabled = true;
}

void srDisable(struct shiftRegister sr) {
	srWritePin(sr.pins.enable, SR_HIGH);

	sr.isEnabled = false;
}

void srReset(struct shiftRegister sr) {
	srWritePin(sr.pins.reset, SR_LOW);

	srDelay(10);

	srWritePin(sr.pins.reset, SR_HIGH);
}

void srWriteData(struct shiftRegister sr, bool *data) {
	uint8_t i;

	for(i = 0; i < sr.outputs; i++) {
		srWriteBit(sr, *(data + i));
		srMicroDelay(1);
	}
}

bool *srNumberToBinaryArray(uint64_t num, uint8_t bits) {
	bool *array;
	uint8_t bit;

	array = (bool *)calloc(bits, sizeof(bool));

	for(bit = 0; bit < bits; bit++) {
		*(array + ((bits - 1) - bit)) = (num & (1 << bit)) ? true : false;
	}

	return array;
}

void srWriteValue(struct shiftRegister sr, uint64_t val) {
	bool *data;

       	data = srNumberToBinaryArray(val, sr.outputs);
	srWriteData(sr, data);

	free(data);
}
