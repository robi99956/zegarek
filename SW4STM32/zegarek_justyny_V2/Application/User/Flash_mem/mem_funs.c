/*
 * mem_funs.c
 *
 *  Created on: 13 sie 2018
 *      Author: Robert
 */

#include "usbd_storage_if.h"
#include "mem_funs.h"

static SPI_HandleTypeDef * spi_handle;

void mem_register_SPI( SPI_HandleTypeDef * spi )
{
	spi_handle = spi;
}

void SPI_send_cmd( uint8_t cmd )
{
	HAL_SPI_Transmit(spi_handle, &cmd, 1, 100);
}

void SPI_set_cs( uint8_t stan )
{
	HAL_GPIO_WritePin( MEM_CS_GPIO_Port, MEM_CS_Pin, stan );
}

void SPI_read( uint8_t * buf, uint16_t cnt )
{
	HAL_SPI_Receive(spi_handle, buf, cnt, 100);
}

void SPI_write( uint8_t * buf, uint16_t cnt )
{
	HAL_SPI_Transmit(spi_handle, buf, cnt, 100);
}

void mem_write_enable( void )
{
	SPI_set_cs( 0 );
	SPI_send_cmd( WREN );
	SPI_set_cs( 1 );
}

void mem_wait_ready( void )
{
	while( mem_status() != USBD_OK );
}

void mem_sector_erase( uint8_t * addr )
{
	mem_write_enable();

	SPI_set_cs(0);
	SPI_send_cmd( SECTOR_ERASE );
	SPI_write(addr, 3);
	SPI_set_cs(1);

	mem_wait_ready();
}

void mem_write_page( const uint8_t * buf, uint8_t * addr )
{
	mem_write_enable();

	SPI_set_cs( 0 );
	SPI_send_cmd( WRITE );
	SPI_write(addr, 3);
	SPI_write( (uint8_t*)buf, 256);
	SPI_set_cs( 1 );

	mem_wait_ready();
}

int8_t mem_status( void )
{
	uint8_t status=98;

	SPI_set_cs( 0 );
	SPI_send_cmd( RDSR_L );
	SPI_read(&status, 1);
	SPI_set_cs( 1 );

	if( status & 0x01 ) return USBD_BUSY;

	return (USBD_OK);
}

uint8_t * mem_addr_resolve( uint32_t sector, uint16_t sector_size )
{
	static uint8_t addr[3];

	sector *= sector_size;

	for( uint8_t i=0; i<3; i++ )
	{
		addr[2-i] = sector % 256;
		sector /= 256;
	}

	return addr;
}

void mem_chip_erase( void )
{
	mem_write_enable();

	SPI_set_cs(0);

	SPI_send_cmd(CHIP_ERASE);

	SPI_set_cs( 1 );

	mem_wait_ready();
}

void mem_zepsuj_fs( void )
{
	for( uint16_t i=0; i<2048; i++ )
	{
		uint8_t * addr = mem_addr_resolve(i, 4096);
		mem_sector_erase(addr);
	}
}

void mem_read( uint8_t * buf, uint32_t sector, uint16_t len )
{
	uint8_t * addr = mem_addr_resolve(sector, SECTOR_SIZE);

	SPI_set_cs(0);

	SPI_send_cmd( READ );
	SPI_write(addr, 3);
	SPI_read(buf, len*SECTOR_SIZE);

	SPI_set_cs( 1 );
}

void mem_write( const uint8_t * buf, uint32_t sector, uint16_t len )
{
	uint8_t * addr = mem_addr_resolve(sector, SECTOR_SIZE);

	while( len-- )
	{
		mem_sector_erase(addr);

		for( uint8_t i=0; i<16; i++ )
		{
			mem_write_page(buf+256*i, addr);

			addr[1]++;
			if( addr[1] == 0 ) addr[0]++;
		}
	}
}

void mem_init( void )
{
	volatile uint8_t status = mem_status();

	if( status == 0 ) return;
}

