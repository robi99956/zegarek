/*
 * mem_funs.h
 *
 *  Created on: 28 lip 2018
 *      Author: Robert
 */

#ifndef APPLICATION_USER_MEM_FUNS_H_
#define APPLICATION_USER_MEM_FUNS_H_

#include <stdint.h>

#define WREN 0x06
#define READ 0x03
#define WRITE 0x02
#define RDSR_L 0x05
#define RDSR_H 0x35
#define SECTOR_ERASE 0x20
#define CHIP_ERASE 0x60

#define SECTOR_CNT 2048
#define SECTOR_SIZE 4096

void mem_write( const uint8_t * buf, uint32_t sector, uint16_t len );
void mem_read( uint8_t * buf, uint32_t sector, uint16_t len );
int8_t mem_status( void );
void mem_register_SPI( SPI_HandleTypeDef * spi );

void mem_zepsuj_fs( void );

void mem_init( void );

#endif /* APPLICATION_USER_MEM_FUNS_H_ */
