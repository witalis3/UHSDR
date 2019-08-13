/*
 * cat_PA.c
 *
 *  Created on: 13.08.2019
 *      Author: witek
 */
#include "cat_PA.h"

void cat_PA_send(uint8_t new_band_index )
{
    char* s = "OK";
    HAL_UART_Transmit(&huart6, (uint8_t*)s, strlen(s), 100);
}


