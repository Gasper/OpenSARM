#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include <lpc214x.h>
#include <io.h>

#define AA_BIT      (1<<2)
#define SI_BIT      (1<<3)
#define STO_BIT     (1<<4)
#define STA_BIT     (1<<5)
#define I2EN_BIT    (1<<6)

char i2c_init(unsigned char i2c_number, unsigned int speed);
char i2c_stop(unsigned char i2c_number);
char i2c_start(unsigned char i2c_number, unsigned char slave_address, unsigned char rw);
char i2c_send_byte(unsigned char i2c_number, char byte);
char i2c_receive_byte(unsigned char i2c_number, char *byte);
char i2c_send_string(unsigned char i2c_number, char *data, unsigned int string_length);
char i2c_receive_string(unsigned char i2c_number, char *buff, unsigned int string_length);

void i2c0_init(int mode);
void i2c0_start(int addr);
void i2c0_stop();
void i2c0_receive(char *buf, unsigned int count);

#ifdef ONLY_USED
#include "i2c.c"
#endif

#endif
