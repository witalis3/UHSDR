/**
 * @brief PCF8574 arduino library
 * @author SkyWodd <skywodd@gmail.com>
 * @version 2.0
 * @link http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This class is designed to allow user to use PCF8574 gpio expander like any standard arduino pins.\n
 * This class provided standards arduino functions like pinMode, digitalWrite, digitalRead, ...\n
 * This new version is fully optimized and documented.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section license_sec License
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 *
 * @section other_sec Others notes and compatibility warning
 * Compatible with arduino 1.0.x and >=0023\n
 * Retro-compatible with the previous library version
 */
#ifndef PCF8574_RF_H
#define PCF8574_RF_H
#include "stm32f7xx_hal.h"
#include "i2c.h"
#include "main.h"

/** Comment this define to disable interrupt support */
// #define PCF8574_RF_INTERRUPT_SUPPORT

/* Retro-compatibility with arduino 0023 and previous version */
#if ARDUINO >= 100
#include "Arduino.h"
#define I2CWRITE(x) Wire.write(x)
#define I2CREAD() Wire.read()
#else
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define LOW 0
#define HIGH 1
#endif

/**
 * @brief PCF8574 Arduino class
 */

	/**
	 * Start the I2C controller and store the PCF8574 chip address
	 */
	void PCF8574_RF_begin(uint8_t address);

	/**
	 * Set the direction of a pin (OUTPUT, INPUT or INPUT_PULLUP)
	 * 
	 * @param pin The pin to set
	 * @param mode The new mode of the pin
	 * @remarks INPUT_PULLUP does physicaly the same thing as INPUT (no software pull-up resistors available) but is REQUIRED if you use external pull-up resistor
	 */
	void PCF8574_RF_pinMode(uint8_t pin, uint8_t mode);

	/**
	 * Set the state of a pin (HIGH or LOW)
	 * 
	 * @param pin The pin to set
	 * @param value The new state of the pin
	 * @remarks Software pull-up resistors are not available on the PCF8574
	 */
	void PCF8574_RF_digitalWrite(uint8_t pin, uint8_t value);

	/**
	 * Read the state of a pin
	 * 
	 * @param pin The pin to read back
	 * @return
	 */
	uint8_t PCF8574_RF_digitalRead(uint8_t pin);

	/**
	 * Set the state of all pins in one go
	 * 
	 * @param value The new value of all pins (1 bit = 1 pin, '1' = HIGH, '0' = LOW)
	 */
	void PCF8574_RF_write(uint8_t value);

	/**
	 * Read the state of all pins in one go
	 * 
	 * @return The current value of all pins (1 bit = 1 pin, '1' = HIGH, '0' = LOW)
	 */
	uint8_t PCF8574_RF_read();

	/**
	 * Exactly like write(0x00), set all pins to LOW
	 */
	void PCF8574_RF_clear();

	/**
	 * Exactly like write(0xFF), set all pins to HIGH
	 */
	void PCF8574_RF_set();


	/**
	 * Mark a pin as "pulled up"
	 * 
	 * @warning DO NOTHING - FOR RETRO COMPATIBILITY PURPOSE ONLY
	 * @deprecated
	 * @param pin Pin the mark as "pulled up"
	 */
	void PCF8574_RF_pullUp(uint8_t pin);

	/**
	 * Mark a pin as "pulled down"
	 * 
	 * @warning DO NOTHING - FOR RETRO COMPATIBILITY PURPOSE ONLY
	 * @deprecated
	 * @param pin Pin the mark as "pulled down"
	 */
	void PCF8574_RF_pullDown(uint8_t pin);

	/** 
	 * Read GPIO states and store them in _PIN variable
	 *
	 * @remarks Before reading current GPIO states, current _PIN variable value is moved to _oldPIN variable
	 */
	void PCF8574_RF_readGPIO();

	/** 
	 * Write value of _PORT variable to the GPIO
	 * 
	 * @remarks Only pin marked as OUTPUT are set, for INPUT pins their value are unchanged
	 * @warning To work properly (and avoid any states conflicts) readGPIO() MUST be called before call this function !
	 */
	void PCF8574_RF_updateGPIO();

#endif
