/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * 
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * 
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 *
 * PCF8574(A) dla FPP
 */

/* Dependencies */
#include "PCF8574.h"
	/** Output pins values */
	volatile uint8_t _PORT = 0x0;

	/** Current input pins values */
	uint8_t _PIN = 0x0;

	/** Pins modes values (OUTPUT or INPUT) */
	volatile uint8_t _DDR = 0x0;

	/** PCF8574 I2C address */
	//uint8_t _address = 0x40;  // PCF8574 adres 0x20 X2
  uint8_t _address = 0x70;  // PCF8574A adres 0x38 X2 trzeba ciąc na płytce FPP - A0 do masy

void PCF8574_begin(uint8_t address) {

	/* Store the I2C address and init the Wire library */
	_address = address;
	PCF8574_readGPIO();
}

void PCF8574_pinMode(uint8_t pin, uint8_t mode) {

	/* Switch according mode */
	switch (mode) {
	case INPUT:
		_DDR &= ~(1 << pin);
		_PORT &= ~(1 << pin);
		break;

	case INPUT_PULLUP:
		_DDR &= ~(1 << pin);
		_PORT |= (1 << pin);
		break;

	case OUTPUT:
		_DDR |= (1 << pin);
		_PORT &= ~(1 << pin);
		break;

	default:
		break;
	}

	/* Update GPIO values */
	PCF8574_updateGPIO();
}

void PCF8574_digitalWrite(uint8_t pin, uint8_t value) {

	/* Set PORT bit value */
	if (value)
		_PORT |= (1 << pin);
	else
		_PORT &= ~(1 << pin);

	/* Update GPIO values */
	PCF8574_updateGPIO();
}

uint8_t PCF8574_digitalRead(uint8_t pin) {

	/* Read GPIO */
	PCF8574_readGPIO();

	/* Read and return the pin state */
	return (_PIN & (1 << pin)) ? HIGH : LOW;
}

void PCF8574_write(uint8_t value) {

	/* Store pins values and apply */
	_PORT = value;

	/* Update GPIO values */
	PCF8574_updateGPIO();
}

uint8_t PCF8574_read() {

	/* Read GPIO */
	PCF8574_readGPIO();

#ifdef PCF8574_INTERRUPT_SUPPORT
	/* Check for interrupt (manual detection) */
	//checkForInterrupt();
#endif

	/* Return current pins values */
	return _PIN;
}

void PCF8574_pullUp(uint8_t pin) {

	/* Same as pinMode(INPUT_PULLUP) */
	PCF8574_pinMode(pin, INPUT_PULLUP); // /!\ pinMode form THE LIBRARY
}

void PCF8574_pullDown(uint8_t pin) {

	/* Same as pinMode(INPUT) */
	PCF8574_pinMode(pin, INPUT); // /!\ pinMode form THE LIBRARY
}

void PCF8574_clear() {

	/* User friendly wrapper for write() */
	PCF8574_write(0x00);
}

void PCF8574_set() {

	/* User friendly wrapper for write() */
	PCF8574_write(0xFF);
}

void PCF8574_toggle(uint8_t pin) {

	/* Toggle pin state */
	_PORT ^= (1 << pin);

	/* Update GPIO values */
	PCF8574_updateGPIO();
}

void PCF8574_readGPIO() {
	/* Start request, wait for data and receive GPIO values as byte */
	HAL_I2C_Master_Receive(&hi2c1, _address, &_PIN, 1, 100);
	// ToDo sprawdzenie statusu operacji
}

void PCF8574_updateGPIO() {

	/* Read current GPIO states */
	//readGPIO(); // Experimental

	/* Compute new GPIO states */
	//uint8_t value = ((_PIN & ~_DDR) & ~(~_DDR & _PORT)) | _PORT; // Experimental
	uint8_t value = (_PIN & ~_DDR) | _PORT;
	/* Start communication and send GPIO values as byte */
	HAL_I2C_Master_Transmit(&hi2c1, _address, &value, 1, 100);
}
