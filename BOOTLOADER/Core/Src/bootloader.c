#include "main.h"

void Ascii_To_Hex( char* source, uint8_t* destination, uint8_t count)
{
	uint8_t i;

	for(i=0; i<count;i++)
	{

		if(source[i] <= '9' && source[i] >= '0' )
		{
			destination[i] = source[i]-0x30;
			continue;
		}

		else if (source[i] >= 'A' && source[i]<='F')
		{
			destination[i] = source[i] - 0x41 + 10;
			continue;
		}
		destination[i] = source[i];
	}
}

//Функция, осуществляющая запись 32-битного слова во Flash-память по определенному адресу.

void flash_write(const uint32_t *src, uint32_t dst, uint32_t size)
{
    // Unlock flash
    HAL_FLASH_Unlock();


    // Program the flash 4 bytes at a time.
    for (int i=0; i<size/4; i++) {
        if (HAL_FLASH_Program(TYPEPROGRAM_WORD, dst, *src) != HAL_OK) {
            // error occurred during flash write
            HAL_FLASH_Lock(); // lock the flash
            Error_Handler();
        }
        src += 1;
        dst += 4;
    }

    // lock the flash
    HAL_FLASH_Lock();
}

void flash_erase(uint32_t flashSector) {
	HAL_StatusTypeDef status = HAL_FLASH_Unlock();
	  		if (status != HAL_OK) {
	  			Error_Handler();
	  		}

	  		FLASH_EraseInitTypeDef erase_init;
	  		erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
	  		erase_init.Banks = FLASH_BANK_1;
	  		erase_init.Sector = flashSector;
	  		erase_init.NbSectors = 1; // erase sectors 3-7
	  		erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	  		uint32_t sector_error=0;

	  		status = HAL_FLASHEx_Erase(&erase_init, &sector_error);
	  		if (status != HAL_OK) {
	  			Error_Handler();
	  		} else {
	  		}

	  		status = HAL_FLASH_Lock();
	  		if (status != HAL_OK) {
	  			Error_Handler();
	  		}
}

void startApplicationByAddress(uint32_t address) {
	uint32_t appJumpAddress;
	  	  void (*GoToApp)(void);
	  	  appJumpAddress = *((volatile uint32_t*)(address + 4));
	  	  GoToApp = (void (*)(void))appJumpAddress;
	  	  HAL_DeInit();
	  	  __disable_irq();
	  	  __set_MSP(*((volatile uint32_t*)address));
	  	  GoToApp();
}

void programFlash(uint8_t flashSector, const char data[][BUFFER_SIZE],size_t rows) {
	uint16_t baseAddress = 0x0000;
	uint16_t offsetAddress = 0x0000;
	volatile uint32_t address = 0x00000000;
	uint8_t buffer[BUFFER_SIZE] = {0};
	uint8_t dataBuffer[BUFFER_SIZE] = {0};
	uint8_t bufferForCrc[BUFFER_SIZE] = {0};
	flash_erase(flashSector);
	  	for (size_t i = 0;i<rows;i++) {
	  		uint8_t *pointerToSource;
	  		Ascii_To_Hex((char*)&data[i], buffer, BUFFER_SIZE);
	  		size_t dataLength = 0;
	  		dataLength = 16 * buffer[1] + buffer[2]; // определяем объем данных в байтах
	  		uint8_t datatype = buffer[8] + 16*buffer[7];//Определяем тип данных
	  		//Заполняем буфер для вычисления CRC
	  		pointerToSource = &buffer[1]; // ставим указатель на 2 элемент массива (исключаем символ ':')

	  		for (size_t i = 0;i<dataLength+5;i++) {
	  			 bufferForCrc[i] = 16*(*pointerToSource) + *(pointerToSource+1);
	  			 pointerToSource +=2; // инкрементируем указатель
	  		}
	  		uint8_t crcCalculate = softCheckCRC(bufferForCrc, dataLength + 4);
	  		uint8_t crcReceive =  bufferForCrc[dataLength + 4];

	  		//Если вычисленный и принятый CRC не совпадают, тогда ошибка

	  		if (crcCalculate != crcReceive) {
	  			Error_Handler();
	  		}
	  		switch (datatype) {

	  		case BASE_ADDRESS :
	  			baseAddress = (uint16_t)buffer[12] + 16*((uint16_t)buffer[11]) + 256*((uint16_t)buffer[10]) + 4096*((uint16_t)buffer[9]);
	  			address = ((uint32_t)baseAddress<<16);
	  			break;
	  		case DATA :
	  			offsetAddress = (uint16_t)buffer[6] + 16*((uint16_t)buffer[5]) + 256*((uint16_t)buffer[4]) + 4096*((uint16_t)buffer[3]);
	  			address = ((uint32_t)baseAddress<<16) +(uint32_t) offsetAddress;
	  			pointerToSource = &buffer[9];
	  			uint32_t programData = 0;
	  			uint8_t shift = 0;
	  			uint8_t count = 0;
	  			//�?нициализация буфера данных
	  			for (size_t i = 0;i<dataLength;i++) {
	  				dataBuffer[i] = 16*(*pointerToSource) + *(pointerToSource+1);
	  				pointerToSource +=2; // инкрементируем указатель

	  				//Формируем 32-разрядные данные для записи во Flash
	  				if ((i+1) %4 != 0) {
	  					programData += ((uint32_t)(dataBuffer[i]))<<(8*shift);
	  					shift++;
	  				} else {
	  					programData += ((uint32_t)(dataBuffer[i]))<<(8*shift);
	  					flash_write(&programData, address + (count)*4, 4);
	  					programData = 0;
	  					shift = 0;
	  					count++;
	  				}
	  			}
	  		case LASTDATA:
	  		  	break;
	  			}
	  		}
}

uint8_t softCheckCRC(const uint8_t* data, size_t size) {
	uint8_t result = 0x00;
	for(size_t i = 0; i<size;i++) {
		result += data[i];
	}
	result = ~result + 0x01;

	return result;
}
