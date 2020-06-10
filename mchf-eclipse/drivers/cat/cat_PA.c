/*
 * cat_PA.c
 *
 *  Created on: 13.08.2019
 *      Author: witek
 */
#include "cat_PA.h"

void cat_PA_set_freq()
{
    uint32_t freq = RadioManagement_GetTXDialFrequency();
    uint8_t sendDMHz = 0;
    uint8_t sendMHz = 0;
    uint8_t sendkHz = 0;
    uint8_t sendHz = 0;
    uint8_t bufor[11];
    sendDMHz = (freq) / 1000000;
    sendDMHz = sendDMHz + (((sendDMHz / 10) * 6));
    sendMHz = ((freq) % 1000000) / 10000;
    sendMHz = sendMHz + (((sendMHz / 10) * 6));
    sendkHz = ((freq) % 10000) / 100;
    sendkHz = sendkHz + (((sendkHz / 10) * 6));
    sendHz = (((freq) % 100));
    sendHz = sendHz + (((sendHz / 10) * 6));
    bufor[10] = 0xFE;
    bufor[9] = 0xFE;
    bufor[8] = 0x1E;    // radio: Icom
    bufor[7] = 0xE0;    // controller
    bufor[6] = 0x05;    // command write operating frequency
    bufor[5] = sendHz;
    bufor[4] = sendkHz;
    bufor[3] = sendMHz;
    bufor[2] = sendDMHz;
    bufor[1] = 0x0;
    bufor[0] = 0xFD;
    //char* s = "OK";
    HAL_UART_Transmit(&huart6, (uint8_t*)bufor, strlen(bufor), 100);
    //printf(bufor);
}


