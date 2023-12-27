//
// Created by user on 23.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_FLASHMEMORY_H
#define STM32_CONTROLLER_GRAPHICS_FLASHMEMORY_H

#include <stdint.h>
#include "stm32f103x6.h"
#include "stm32f1xx_hal_flash_ex.h"

#define FLASH_BANK_SIZE     (FLASH_BANK1_END-FLASH_BASE+1)

#define SETTINGS_ADDRESS 0x08007e00

static uint32_t GetPage(uint32_t Addr) {
    uint32_t page = 0;

    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE)) {
        /* Bank 1 */
        page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
    } else {
        /* Bank 2 */
        page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
    }

    return page;
}

/**
  * @brief  Gets the bank of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
static uint32_t GetBank(uint32_t Addr) {
    return FLASH_BANK_1;
}

uint32_t Flash_Write_Data(uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords) {
    int sofar = 0;

    /* Unlock the Flash to enable the flash control register access *************/
    HAL_FLASH_Unlock();


    uint32_t PAGEError;
    static FLASH_EraseInitTypeDef EraseInitStruct;

    /* Erase the user Flash area*/
    uint32_t StartPage = GetPage(StartPageAddress);
    uint32_t EndPageAdress = StartPageAddress + numberofwords * 4;
    uint32_t EndPage = GetPage(EndPageAdress);

    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = StartPage;
    EraseInitStruct.NbPages = ((EndPage - StartPage) / FLASH_PAGE_SIZE) + 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) {
        /*Error occurred while page erase.*/
        return HAL_FLASH_GetError();
    }

    /* Program the user Flash area word by word*/
    while (sofar < numberofwords) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartPageAddress, Data[sofar]) == HAL_OK) {
            StartPageAddress += 4;  // use StartPageAddress += 2 for half word and 8 for double word
            sofar++;
        } else {
            /* Error occurred while writing data in Flash memory*/
            return HAL_FLASH_GetError();
        }
    }

    /* Lock the Flash to disable the flash control register access (recommended
       to protect the FLASH memory against possible unwanted operation) *********/
    HAL_FLASH_Lock();

    return 0;
}

void Flash_Read_Data(uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords) {
    while (1) {

        *RxBuf = *(__IO uint32_t *) StartPageAddress;
        StartPageAddress += 4;
        RxBuf++;
        if (!(numberofwords--)) break;
    }
}

void ReadSettings() {
    int32_t data[3];

    data[0] = *(__IO uint32_t *) (SETTINGS_ADDRESS);
    data[1] = *(__IO uint32_t *) (SETTINGS_ADDRESS + 4);
    data[2] = *(__IO uint32_t *) (SETTINGS_ADDRESS + 8);

    //Flash_Read_Data(0x08007e00, data, 3);
}

/*
void WriteSettings() {
    uint64_t data[] = {firstElementData, secondElementData, thirdElementData};

    HAL_StatusTypeDef status = HAL_FLASH_Unlock();

    if (status == HAL_ERROR) DrawText("ERROR UNLOCK", 11, colorRed, &Font24, 0, 0);
    if (status == HAL_OK) DrawText("OK UNLOCK", 9, colorGreen, &Font24, 0, 0);

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, SETTINGS_ADDRESS, data[0]);

    if (status == HAL_ERROR) DrawText("ERROR WRITE1", 11, colorRed, &Font24, 0, 30);
    if (status == HAL_OK) DrawText("OK WRITE1", 9, colorGreen, &Font24, 0, 30);

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, SETTINGS_ADDRESS + 4, data[1]);

    if (status == HAL_ERROR) DrawText("ERROR WRITE2", 11, colorRed, &Font24, 0, 60);
    if (status == HAL_OK) DrawText("OK WRITE2", 9, colorGreen, &Font24, 0, 60);

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, SETTINGS_ADDRESS + 8, data[2]);

    if (status == HAL_ERROR) { DrawText("ERROR WRITE3", 11, colorRed, &Font24, 0, 90); }
    if (status == HAL_OK) DrawText("OK WRITE3", 9, colorGreen, &Font24, 0, 90);

    HAL_FLASH_Lock();

    if (status == HAL_ERROR) DrawText("ERROR LOCK", 10, colorRed, &Font24, 0, 120);
    if (status == HAL_OK) DrawText("OK LOCK", 7, colorGreen, &Font24, 0, 120);
}
*/

#endif //STM32_CONTROLLER_GRAPHICS_FLASHMEMORY_H
