#ifndef _SHIFTR_H
#define _SHIFTR_H

/* includes */

#ifdef USING_WPI
#include <wiringPi.h>
#else
#include <bcm2835.h>
#endif /* #ifdef USING_WPI */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* definitions */

#define DEF_NUM_PINS    8
#define SR_NO_PIN       255
#define SR_HIGH         1
#define SR_LOW          0

/* structures */

struct shiftRegister {
        struct srPins {
                /* the essential pins */
                uint8_t data,
                        clock,
                        updateOutput;

                /* the "extra" pins */
                uint8_t reset,
                        enable;
        } pins;

        /* the number of outputs */
        uint8_t outputs;

        /* this may be useful for someone at some point */
        bool isEnabled; 
};

/* functions */

struct shiftRegister initShiftRegister(uint8_t pinN, uint8_t data, uint8_t clock, uint8_t updateOutput, 
                uint8_t reset, uint8_t outputEnable, bool enable);
void srUpdateOutput(struct shiftRegister sr);
void srWriteBit(struct shiftRegister sr, bool bit);
void srEnable(struct shiftRegister sr);
void srDisable(struct shiftRegister sr);
void srReset(struct shiftRegister sr);
void srWriteData(struct shiftRegister, bool *data);
bool *srNumberToBinaryArray(uint64_t num, uint8_t bits);
void srWriteValue(struct shiftRegister sr, uint64_t val);

void srWritePin(uint8_t pin, bool out);
void srDelay(size_t t);
void srSetPinAsOutput(uint8_t pin);
void srClose(void);
void srInitGpioControl(void);

#endif /* #ifndef _SHIFTR_H */
