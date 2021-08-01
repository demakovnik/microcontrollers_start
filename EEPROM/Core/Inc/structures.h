/*
 * structures.h
 *
 *  Created on: Aug 1, 2021
 *      Author: nikit
 */

#ifndef INC_STRUCTURES_H_
#define INC_STRUCTURES_H_
typedef struct Config_t {
  char phoneNumber[12];
  char str[255];
  uint32_t magicNumber;
} Config_t;

typedef union DevNVRAM {
  Config_t config;
  uint32_t data32[512];
} DevNVRAM;




#endif /* INC_STRUCTURES_H_ */
