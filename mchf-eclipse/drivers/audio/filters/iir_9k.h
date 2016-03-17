/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014                            **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:                                                                     **
**  Description:                                                                   **
**  Last Modified:                                                                 **
**  Licence:		CC BY-NC-SA 3.0                                                **
************************************************************************************/

#ifndef __IIR_9K
#define __IIR_9K
//
// alternative filter designed with MATLAB fdatools by DD4WH 2016-02-18
// 24k sampling rate, Lattice ARMA structure
// 8th order IIR Elliptic lowpass LPF
// Fpass 9000Hz
// Astop 60dB
// coefficients in reverse order than that spit out by MATLAB
//
//

#define IIR_9k_numStages 8

const float IIR_9k_LPF_pkCoeffs[] =
{
		0.144843368057163,
		0.0311176821163535,
		0.671835107699585,
		0.499495871489971,
		0.971603001167062,
		0.651162915986589,
		0.998310568870827,
		0.698395145953468
};

const float IIR_9k_LPF_pvCoeffs[] =
{
		0.157182890700946,
		0.510999353559437,
		0.454077934277190,
		-0.0776493551890845,
		-0.180998321432113,
		0.00575759072640292,
		0.0249744575699347,
		0.000197356170009044,
		-0.000725804365039828
};


#endif
