// Copyright (c) 2018 Rudá Moura <ruda.moura@gmail.com>
// License: The MIT License (MIT)
/*
 * na bazie powyższego
 *
 * mcp23008.h
 *
 *  Created on: 9 lip 2020
 *      Author: witek
 */

#ifndef MCP23008_H_
#define MCP23008_H_
#include "stm32f7xx_hal.h"
#include "i2c.h"
#include "main.h"

#include "uhsdr_board.h"
// Ports
#define MCP23017_PORTA          0x00    // dla świętego spokoju
#define MCP23017_PORTB          0x01    // dla świętego spokoju - brak portu w MCP23008
// Address (A0-A2)
#define MCP23008_ADDRESS_10     0x10
#define MCP23008_ADDRESS_11     0x11
#define MCP23008_ADDRESS_12     0x12
#define MCP23008_ADDRESS_13     0x13
#define MCP23008_ADDRESS_14     0x14
#define MCP23008_ADDRESS_15     0x15
#define MCP23008_ADDRESS_16     0x16
#define MCP23008_ADDRESS_17     0x17
// Default state: MCP23008_IODIR_ALL_INPUT
#define MCP23008_IODIR_ALL_OUTPUT   0x00
#define MCP23008_IODIR_ALL_INPUT    0xFF

// Registers
#define REGISTER_IODIR      0x00
#define REGISTER_IPOL       0x01
#define REGISTER_GPINTEN    0x02
#define REGISTER_DEFVAL     0x03
#define REGISTER_INTCON     0x08
#define REGISTER_IOCON      0x05
#define REGISTER_GPPU       0x06
#define REGISTER_INTF       0x07
#define REGISTER_INTCAP     0x08
#define REGISTER_GPIO       0x09
#define REGISTER_OLAT       0x0A
#define I2C_TIMEOUT     10

typedef struct
{
    I2C_HandleTypeDef*  hi2c;
    uint16_t            addr;
    uint8_t             gpio[2];
} MCP23008_HandleTypeDef;
extern MCP23008_HandleTypeDef hmcp;

void mcp23008_init(MCP23008_HandleTypeDef *hdev, I2C_HandleTypeDef *hi2c, uint16_t addr);
HAL_StatusTypeDef   mcp23008_read(MCP23008_HandleTypeDef *hdev, uint16_t reg, uint8_t *data);
HAL_StatusTypeDef   mcp23008_write(MCP23008_HandleTypeDef *hdev, uint16_t reg, uint8_t *data);
HAL_StatusTypeDef   mcp23008_iodir(MCP23008_HandleTypeDef *hdev, uint8_t port, uint8_t iodir);
//HAL_StatusTypeDef   mcp23008_iodir(MCP23008_HandleTypeDef *hdev, uint8_t iodir);
HAL_StatusTypeDef   mcp23008_ipol(MCP23008_HandleTypeDef *hdev, uint8_t port, uint8_t ipol);
HAL_StatusTypeDef   mcp23008_ggpu(MCP23008_HandleTypeDef *hdev, uint8_t port, uint8_t pu);
HAL_StatusTypeDef   mcp23008_read_gpio(MCP23008_HandleTypeDef *hdev, uint8_t port);
HAL_StatusTypeDef   mcp23008_write_gpio(MCP23008_HandleTypeDef *hdev, uint8_t port);

#endif /* MCP23008_H_ */
