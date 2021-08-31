/*
 * bootloader.h
 *
 *  Created on: Aug 31, 2021
 *      Author: nikit
 */

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#include <inttypes.h>
#include <string.h>

#define APP_START_ADDRESS 0x0800C000
#define BUFFER_SIZE 64 // Размер буфера (число символов) под строку прошивки.


/*Возможные типы данных:
 * 00 — cодержит данные
 * 01 — последняя запись в файле
 * 02 — дополнительный адрес сегмента
 * 04 — запись содержит дополнительный адрес, необходимы для вычисления полного адреса
 * 05 — адрес начала приложения, а именно функции main(только для MDK-ARM)*/
const enum {
	DATA=0x00,
	LASTDATA=0x01,
	BASE_ADDRESS=0x04,
	OFFSET_ADDRESS = 0x02,
	START_APPLICATION = 0x05
} dataType;




void Ascii_To_Hex( char* source, uint8_t* destination, uint8_t count);
void flash_write(const uint32_t *src, uint32_t dst, uint32_t size);
void flash_erase(uint32_t flashSector);
void startApplicationByAddress(uint32_t address);
void programFlash(uint8_t flashSector, const char data[][BUFFER_SIZE],size_t rows);

uint8_t softCheckCRC(const uint8_t* data, size_t size);



#endif /* INC_BOOTLOADER_H_ */
