
#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#define MODE    3
#define MSTR    5
#define LSBF    6
#define BIT_ENABLE   2
#define BITS    8


int spi_set_speed(unsigned char spi_number, unsigned int speed);
char spi_init(unsigned char spi_number, unsigned int speed);
char spi_set_mode(unsigned char spi_number, unsigned char mode, unsigned char msb_lsb_mode, unsigned char number_of_bits);
char spi_enable_slave(unsigned char spi_number, unsigned char slave_number/*0-3*/);
char spi_disable_slave(unsigned char spi_number, unsigned char slave_number/*0-3*/);
char spi_transmit_byte(unsigned char spi_number, unsigned char slave_number, char data);
int spi_transmit_data(unsigned char spi_number, unsigned char slave_number, int data);
int spi_receive_data(unsigned char spi_number, unsigned char slave_number);
char spi_send_array(unsigned char spi_number, unsigned char slave_number, int *data, unsigned int array_size);
char spi_slave_init(unsigned char spi_number, unsigned char slave_number);

#include "spi.c"
#endif
