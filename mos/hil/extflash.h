/**
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
// External flash driver
//

#ifndef MANSOS_EXTFLASH_H
#define MANSOS_EXTFLASH_H

//
// List all supported external flash models here (before including extflash_hal.h)
//
#define FLASH_CHIP_M25P80 1
#define FLASH_CHIP_AT25DF 2

#include "extflash_hal.h"

//===========================================================
// Data types and constants
//===========================================================


//===========================================================
// Procedures
//===========================================================

// these functions/macros are defined in platform-specific part

#ifndef EXT_FLASH_SECTOR_SIZE
#warning External flash constants not defined for this platform!
#define EXT_FLASH_SECTOR_SIZE   0
#define EXT_FLASH_SECTOR_COUNT  0
#define EXT_FLASH_PAGE_SIZE     0
#endif

#define EXT_FLASH_SIZE \
    ((unsigned long)EXT_FLASH_SECTOR_SIZE * EXT_FLASH_SECTOR_COUNT)

// void extFlashInit(); // init flash (including SPI bus); for kernel only
// void extFlashSleep(); // enter low power mode
// void extFlashWake(); // wake up from low power mode
    // read len bytes from flash starting at address addr into buf
// void extFlashRead(uint32_t addr, uint8_t *buf, uint16_t len);
    // write len bytes from buf to flash starting at address addr
// void extFlashWrite(uint32_t addr, uint8_t *buf, uint16_t len);
// void extFlashBulkErase();  // erase whole flash memory
    // erase one sector at addr. Addr is not the sector number, rather an
    // address inside the sector
// void extFlashEraseSector(uint32_t addr);


#endif
