# MCU and clock
MCU = atmega328p
F_CPU = 16000000UL

# Toolchain
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os \
         -std=gnu11 \
         -Wall -Wextra

# Serial port for Arduino Uno (adjust to your system)
PORT = /dev/ttyACM0
BAUD = 115200

# File names
TARGET = mood_cue
SRC = $(TARGET).c
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# Convert ELF to HEX
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Build ELF
$(ELF): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<


# Upload HEX to Arduino
flash: $(HEX)
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX)

# Clean build files
clean:
	rm -f $(ELF) $(HEX)

.PHONY: flash clean
