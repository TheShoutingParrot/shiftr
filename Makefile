CC		= gcc
CFLAGS		= -I $(INC_DIR)
LIBS		= -lbcm2835

INC_DIR 	= include
SRC_DIR		= src
OBJ_DIR 	= obj
EXAMPLES_DIR	= examples

PREFIX		= /usr/local

_DEPS		= shiftr.h
DEPS		= $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ		= gpio-control.o shiftr.o
OBJ		= $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: libshiftr.so

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

libshiftr.so: $(OBJ)
	$(CC) -fPIC -shared -o $@ $^ $(CFLAGS) $(LIBS) $(DEFINES)

examples: libshiftr.so
	$(CC) -L. -lshiftr $(CFLAGS) $(EXAMPLES_DIR)/blink.c -o $(EXAMPLES_DIR)/blink
	$(CC) -L. -lshiftr $(CFLAGS) $(EXAMPLES_DIR)/dance.c -o $(EXAMPLES_DIR)/dance

install: libshiftr.so clean
	mkdir -p $(PREFIX)/lib
	cp libshiftr.so $(PREFIX)/lib/libshiftr.so
	chmod +x $(PREFIX)/lib/libshiftr.so
	cp $(INC_DIR)/shiftr.h $(PREFIX)/include/shiftr.h

uninstall:
	rm -f $(PREFIX)/lib/libshiftr.so
	rm -f $(PREFIX)/include/shiftr.h

clean:
	rm -f $(OBJ_DIR)/*.o 

.PHONY: clean examples install uninstall
