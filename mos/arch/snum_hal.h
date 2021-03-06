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

//
// Board serial number (aka 8-byte address) driver
//

#ifndef _DEV_SNUM_HAL_H_
#define _DEV_SNUM_HAL_H_

// let the platform define the chip it uses
#include <platform.h>

// #ifndef SNUM_CHIP
// #define SNUM_CHIP SNUM_DS2411
// #endif

#if SNUM_CHIP == SNUM_DS2411

#include <ds2411/ds2411.h>
#define serialNumberRead(buf) ds2411Get(buf) 
#define serialNumberMatches(snum) ds2411SnumMatches(snum)
#define serialNumberInit() ds2411Init()

#elif SNUM_CHIP == SNUM_DS2401

#include <ds2401/ds2401.h>
#define serialNumberRead(buf) ds2401Get(buf) 
#define serialNumberMatches(snum) ds2401SnumMatches(snum)
#define serialNumberInit() ds2401Init()

#else

#warning Serial number chip not defined for this platform!

#define SERIAL_NUMBER_SIZE 8
#define serialNumberRead(buf) (*(buf) = 0)
#define serialNumberMatches(snum) (1)
#define serialNumberInit()

#endif

#endif
