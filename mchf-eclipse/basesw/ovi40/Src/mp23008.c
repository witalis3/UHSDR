// Copyright (c) 2018 Rudá Moura <ruda.moura@gmail.com>
// License: The MIT License (MIT)
/*
 * na bazie powyższego
 *
 * mp23008.c
 *
 *  Created on: 9 lip 2020
 *      Author: witek
 */
#include <mcp23008.h>

void mcp23008_init(MCP23008_HandleTypeDef *hdev, I2C_HandleTypeDef *hi2c, uint16_t addr)
{
    hdev->hi2c = hi2c;
    hdev->addr = addr << 1;
}

HAL_StatusTypeDef mcp23008_read(MCP23008_HandleTypeDef *hdev, uint16_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Read(hdev->hi2c, hdev->addr, reg, 1, data, 1, I2C_TIMEOUT);
}

HAL_StatusTypeDef mcp23008_write(MCP23008_HandleTypeDef *hdev, uint16_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Write(hdev->hi2c, hdev->addr, reg, 1, data, 1, I2C_TIMEOUT);
}

HAL_StatusTypeDef mcp23008_iodir(MCP23008_HandleTypeDef *hdev, uint8_t port, uint8_t iodir)
//HAL_StatusTypeDef mcp23008_iodir(MCP23008_HandleTypeDef *hdev, uint8_t iodir)
{
    uint8_t data[1] = {iodir};
    return mcp23008_write(hdev, REGISTER_IODIR|port, data);
    //return mcp23008_write(hdev, REGISTER_IODIR, data);
}

HAL_StatusTypeDef mcp23008_ipol(MCP23008_HandleTypeDef *hdev, uint8_t port, uint8_t ipol)
{
    uint8_t data[1] = {ipol};
    return mcp23008_write(hdev, REGISTER_IPOL|port, data);
}

HAL_StatusTypeDef mcp23008_ggpu(MCP23008_HandleTypeDef *hdev, uint8_t port, uint8_t pu)
{
    uint8_t data[1] = {pu};
    return mcp23008_write(hdev, REGISTER_GPPU|port, data);
}

HAL_StatusTypeDef mcp23008_read_gpio(MCP23008_HandleTypeDef *hdev, uint8_t port)
{
    uint8_t data[1];
    HAL_StatusTypeDef status;
    status = mcp23008_read(hdev, REGISTER_GPIO|port, data);
    if (status == HAL_OK)
        hdev->gpio[port] = data[0];
    return status;
}

HAL_StatusTypeDef mcp23008_write_gpio(MCP23008_HandleTypeDef *hdev, uint8_t port)
{
    uint8_t data[1] = {hdev->gpio[port]};
    return mcp23008_write(hdev, REGISTER_GPIO|port, data);
}
