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

// Values red from CSV file.
// Each line corresponds to a specific ADC channel
// Line format:
// chnum: val1, val2, ..., valn
// where chnum: channel number
// val1, ..., valn: values
// values may be separated with any symbol outside the interval '0'..'9'

#include "adc_hal.h"
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// where the valueas are red from
#define ADC_FILE_NAME "adcValues.txt"

// max count of values per each channel
#define ADC_VALUE_COUNT_FOR_CH 256

// indicates whether ADC value file was successfully red
static bool adcOk = false;

// array with cached values
static uint16_t values[PC_ADC_CHANNEL_COUNT][ADC_VALUE_COUNT_FOR_CH];

// currently cached values for each channel
static uint16_t valueCount[PC_ADC_CHANNEL_COUNT];

// current position for each channel of cached values
static uint16_t currPos[PC_ADC_CHANNEL_COUNT];

static uint8_t currChannel = 0;

// reads number from CSV file, updates isNewLine (true, when new line started)
static uint16_t readNum(int fd, bool *isNewLine, bool *isEOF);

void hplAdcInit() {
    memset(values, 0, sizeof(values));
    memset(valueCount, 0, sizeof(valueCount));
    memset(currPos, 0, sizeof(currPos));

    int fd = open(ADC_FILE_NAME, O_RDONLY);
    if (fd < 0) return;
    uint8_t chnum = 255;
    bool wasNewLine = false;
    bool isEOF = false;
    while (!isEOF)
    {
        bool isNewLine;
        uint16_t num = readNum(fd, &isNewLine, &isEOF);
        if (num != 0xffff) {
            if (wasNewLine || chnum == 255) {
                chnum = num;
                //PRINTF("chnum = %u\n", chnum);
                wasNewLine = false;
            } else {
                if (chnum < PC_ADC_CHANNEL_COUNT) {
                    values[chnum][valueCount[chnum]] = num;
                    //PRINTF("values[%u, %u] = %u\n", chnum, valueCount[chnum], num);
                    ++valueCount[chnum];
                }
            }
            if (isNewLine) {
                wasNewLine = true;
            }
        }
    }
    close(fd);
    adcOk = true;
}

static uint16_t readNum(int fd, bool *isNewLine, bool *isEOF) {
    *isNewLine = false;
    uint16_t n = 0xffff;
    bool numStarted = false;
    while (!*isEOF)
    {
        uint8_t c;
        //fgetc(f);
        int ret = read(fd, &c, 1);
        if (ret != 1) {
            *isEOF = true;
            break;
        }
        if (c >= '0' && c <= '9') {
            if (n != 0xffff) {
                n = n * 10;
            } else {
                n = 0;
            }
            n += (c - '0');
            numStarted = true;
        } else {
            if (c == '\n' || c == '\r') {
                *isNewLine = true;
            }
            if (numStarted) break; // separator after num
        }
    }
    return n;
}

uint16_t hplAdcGetVal() {
    uint16_t pos = currPos[currChannel]++;
    if (currPos[currChannel] >= valueCount[currChannel]) {
        currPos[currChannel] = 0;
    }
    return values[currChannel][pos];
}

void hplAdcSetChannel(uint8_t ch) {
    currChannel = ch;
}

uint8_t hplAdcGetChannel(void) {
    return currChannel;
}
