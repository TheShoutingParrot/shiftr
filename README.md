# shiftr

shiftr is a simple raspberry pi library for controlling shift registers (such as the 74595). 


shiftr uses the bcm2835 library by default.

# Usage

## Prerequisites

Before using, compiling and possibly installing the shiftr library you need the bcm2835 library installed on your raspberry pi. The library can also be modified to use any another gpio controlling library simply by editing the [src/gpio-control.c](src/gpio-control.c) file.


To correctly use this library you also need at least one shift register. Most shift registers (should) work with this library.

## Compiling the library

To compile the library you simply must run `make` while in the shiftr directory. This will create the shared library file `libshiftr.so`.

### Installation

To install the library you simply have to run `make install`. This will copy the compiled `libshiftr.so` file to `PREFIX/lib/`.

To test if the library is working run `make examples`.

## Linking the library to a program

Linking the library to a program is extremely easy if you have installed the program to `/usr/local/lib/` or `/usr/lib/`. Just run `cc -lshiftr program.c` and the program will compile. The `program.c` filename should be replaced with the file that you want to compile.

### Without installing to PREFIX/lib

To link the library with a program (for example [examples/blink.c](examples/blink.c)) without installing the library you must compile your file like so: `cc -lshiftr -L /where/the/library/is/installed -l shiftr program.c`. The `/where/the/library/is/installed` path should be replaced with the path where the library is installed and the `program.c` should be replaced with the file you are compiling.


You may have to modify the `LD_LIBRARY_PATH` variable for the library loading to work properly.

# Your first shiftr program - blink.c

This program's source code can be found in [examples/blink.c](examples/blink.c)


This program is the simplest program for a shift register that there is. It "shifts" a 1 to the shift register.

First we include the shiftr header file:

```c
#include <shiftr.h>
```

Then we define the pins that we are using:

```c
#define DATA_PIN        RPI_GPIO_P1_11
#define CLOCK_PIN       RPI_GPIO_P1_15
#define LATCH_PIN       RPI_GPIO_P1_23
#define ENABLE_PIN      RPI_GPIO_P1_19
```

I will be using the 11th pin of the rpi as the data pin, the 15th as the clock pin, the 23rd as the latch/output update pin and the 19th pin as the enable pin. In this example we won't use the reset pin.

Then, we initialize the library and the shift register in the main function:

```c
int main(void) {
        struct shiftRegister sr;

        /* initializes the gpio control */
        srInitGpioControl();

        /* initializes the shift register pins */
        sr  = initShiftRegister(1,
                        DATA_PIN, CLOCK_PIN, LATCH_PIN,
                        SR_NO_PIN, ENABLE_PIN, true);
```

After this, we need to actually write the bit to the shift register and update the shift register's output:

```c
/* shifts a single bit (1) to the shift register */
srWriteBit(sr, 1);

/* Updates the output of the shift register */
srUpdateOutput(sr);
``` 

Then we can close the gpio control:

```c
srClose();
```

This example is included with the library and can be compiled simply by running `make examples` with the libraries [Makefile](Makefile).

# Using the library

First you must include the [`shiftr.h`](include/shiftr.h) header file. This can be like this: `#include <shiftr.h>`.

## Initializing shiftr

To initialize shiftr you must first initialize the gpio control through the shiftr library:

```c
srInitGpioControl();
```

After that you have to initialize the shiftr library and tell the program which gpio pins will this shift register be using and how many pins/outputs does the shift register have:

```c
struct shiftrRegister sr = initShiftRegister(pins, 
	data_pin, clock_pin, latch_pin
	reset_pin, enable_pin, enable);
```

This could look like this for example:

```c
sr = initShiftRegister(8, RPI_GPIO_P1_11, RPI_GPIO_P1_15, RPI_GPIO_P1_23,
	SR_NO_PIN, SR_NO_PIN, true)
```

In the above example we don't set the reset and enable pin, this can be done if (for example) the reset and enable pins are connected directly to ground or +5V. The data, clock and latch pin must be set.

**NOTE: The library uses the bcm2385 library by default so by default you must use the bcm2835 library pin numbering**

The `struct shiftRegister` structure is where the shift register's data is stored.

If the `enable` is set to false the output will be disabled and if it's set to true the output will be set to true. This will only work if the enable pin is connected to a gpio pin.

## Writing data to the shifr

**To show the data that has been written you must enable the output and to update the output you must you use the [srUpdateOutput](#srupdate) function.**

### Writing a single bit

Writing a single bit to the shift register is very easy:

```c
srWriteBit(struct shiftRegister, bool);
```

#### Examples

```c
srWriteBit(sr, 1);
```

The above example would write a 1 to the shift register.

```c
srWriteBit(sr, 1);
srUpdateOutput(sr);
```

This would write a 1 to the shift register and update the register's output.

### Writing data to the shift register

```c
srWriteValue(struct shiftRegister, uint64_t);
```

#### Examples

```c
srWriteValue(sr, 0xFF);
```

This would write 0xFF to the shift register `sr`.

```c
srWriteValue(sr, 0xFF);
srUpdateOutput(sr);
```

The above example would write 0xFF to the shift register **and** update the shift register's output.

## Output control functions

<a name="srupdate"></a>
### Updating the output 

To show the shift registers current value you must update the output:

```c
srUpdateOutput(struct shiftRegister);
```

#### Example
```c
srUpdateOutput(sr);
```

### Enabling the output of a shift register

```c
srEnable(struct shiftRegister);
```

#### Example


```c
srEnable(sr);
```

This would enable the output of the shift register `sr`.


### Disabling

```c
srDisable(struct shiftRegister);
```

#### Example

```c
srDisable(sr);
```

This would disable the output of the shift register `sr`.

## Misc

### Resetting the shift register

```c
srReset(struct shiftRegister);
```

#### Examples

Resetting the shift register:
```c
srReset(sr);
```


This resets the shift register and update's its output:
```c
srReset(sr);
srUpdateOutput(sr);
```


