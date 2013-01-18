/*
 * Copyright (c) 2008-2012 the MansOS team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of  conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdbool.h>
#include "adc.h"
#include "digital.h"

//----------------------------------------------------------
// types
//----------------------------------------------------------

//----------------------------------------------------------
// internal variables
//----------------------------------------------------------
static bool adcIsOn;
static uint8_t adcChannel;
static uint16_t adcVal;

#define enableAdcPin(port, pin) \
    pinAsFunction(port, pin);   \
    pinAsInput(port, pin);

void adcOn(void) {
    hplAdcOn();
    adcIsOn = true;
}

void adcOff(void) {
    hplAdcOff();
    adcIsOn = false;
}

void adcInit(void)
{
    hplAdcInit();
    hplAdcOff();
    adcChannel = 1;

    // XXX: needed for lynx board to work without specific initialization
#if 0
    hplAdcUseSupplyRef();
    hplAdcOn();

#ifdef P6SEL
    enableAdcPin(6, 0);
    enableAdcPin(6, 1);
    enableAdcPin(6, 2);
    enableAdcPin(6, 3);
    enableAdcPin(6, 4);
    enableAdcPin(6, 5);
    enableAdcPin(6, 6);
    enableAdcPin(6, 7);
#endif
#endif
}

void adcSetChannel(uint8_t ch)
{
    hplAdcOff();
    hplAdcSetChannel(ch);
    adcChannel = ch;
    hplAdcOn();
}


uint16_t adcRead(uint8_t ch)
{
    uint16_t retval;

    //turn on if necessary
    if (!adcIsOn) {
        hplAdcOn();
    }

    if (ch != adcChannel) {
        adcSetChannel(ch);
    }

    // hplAdcEnableInterrupt();
    hplAdcStartConversion();

    if (hplAdcIntsUsed()) {
        // TODO - use callbacks
        while (hplAdcIsBusy()) {}
        retval = adcVal;
    } else {
        while (hplAdcIsBusy()) {}
        retval = hplAdcGetVal();
    }

    return retval;
}

uint16_t adcReadFast(void)
{
    hplAdcStartConversion();

    while (hplAdcIsBusy());

    return hplAdcGetVal();
}
