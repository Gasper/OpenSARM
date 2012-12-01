/**
 * 2012 OpenSARM
 * Avtor: Jernej Sorta <jernejsorta@gmail.com>
 *
 */

 #ifdef I2C_H_INCLUDED

 #include "lpc214x.h"
 #include "io.h"

char i2c_init(unsigned char i2c_number, unsigned int speed)
{

	if ((i2c_number > 1) || (speed > 400000) || (speed < ((CPU_FREQ * 1000) >> 17)))
        return -1;

	if (i2c_number == 1)
	{
		PINSEL0 |= (3 << 22) | (3 << 28);
		I21SCLH = (CPU_FREQ * 1000) / (2 * speed);
		I21SCLL = I21SCLH;
		I21CONCLR = 0xFF;
		I21CONSET = I2EN_BIT;
	}
	else
	{
		PINSEL0 &= ~((3 << 4) | (3 << 6));
		PINSEL0 |= (1 << 4) | (1 << 6);
		I2SCLH = (CPU_FREQ * 1000) / (2 * speed);
		I2SCLL = I2SCLH;
		I2CONCLR = 0xFF;
		I2CONSET = I2EN_BIT;
	}

	return 1;
}

char i2c_stop(unsigned char i2c_number)
{
	if (i2c_number > 1)
		return -1;

	if (i2c_number == 1)
	{
		I21CONCLR = SI_BIT;
		I21CONSET = STO_BIT;
	}
	else
	{
		I2CONCLR = SI_BIT;
		I2CONSET = STO_BIT;
	}

	return 1;
}

char i2c_start(unsigned char i2c_number, unsigned char slave_address, unsigned char rw)
{

	if ((i2c_number > 1) || ((slave_address >> 7) == 1) || (rw > 1))
		return -1;

	char status = 0;

	if (i2c_number == 1)
	{
		I21CONSET |= STA_BIT;
		while (!(I21CONSET & SI_BIT));

		I21CONCLR = STA_BIT | SI_BIT;
		I21DAT = ((slave_address << 1) + rw);
		while (!(I21CONSET & SI_BIT));

		I21CONCLR |= SI_BIT;
		status = I21STAT;
	}
	else
	{
		I2CONSET |= STA_BIT;
		while (!(I2CONSET & SI_BIT));

		I2CONCLR = STA_BIT | SI_BIT;
		I2DAT = ((slave_address << 1) + rw);
		while (!(I2CONSET & SI_BIT));

		I2CONCLR |= SI_BIT;
		status = I2STAT;
	}

	if (rw == 0)
	{
		if (status == 0x18)
		{
			//Začetek I2C povezave uspel!
			return 1;
		}
		else
		{
			i2c_stop(i2c_number);
			//Začetek I2C povezave ni uspel!
			return 0;
		}
	}
	else
	{
		if (status == 0x40)
		{
			//Začetek I2C povezave uspel!
			return 1;
		}
		else
		{
			i2c_stop(i2c_number);
			//Začetek I2C povezave ni uspel!
			return 0;
		}
	}
}



char i2c_send_byte(unsigned char i2c_number, char byte)
{
	if (i2c_number > 1)
		return -1;

	unsigned char status = 0;
	if (i2c_number == 1)
	{
		I21DAT = byte;
		I21CONCLR = SI_BIT;
		while (!(I21CONSET & SI_BIT));

		status = I21STAT;
	}
	else
	{
		I2DAT = byte;
		I2CONCLR = SI_BIT;
		while (!(I2CONSET & SI_BIT));

		status = I2STAT;
	}

	if (status == 0x28)
	{
		return 1;
	}
	else
	{
		i2c_stop(i2c_number);
		return 0;
	}
}

char i2c_receive_byte(unsigned char i2c_number, char *byte)
{
	if (i2c_number > 1)
		return -1;

	unsigned char status = 0;
	if (i2c_number == 1)
	{
		I21DAT = *byte;
		I21CONCLR = SI_BIT;
		while (!(I21CONSET & SI_BIT));

		status = I21STAT;
	}
	else
	{
		I2DAT = *byte;
		I2CONCLR = SI_BIT;
		while (!(I2CONSET & SI_BIT));

		status = I2STAT;
	}

	if (status == 0x50)
	{
		return 1;
	}
	else
	{
		i2c_stop(i2c_number);
		return 0;
	}
}

char i2c_send_string(unsigned char i2c_number, char *data, unsigned int string_length)
{
	if ((i2c_number > 1) || (string_length == 0))
		return -1;

	while (string_length--)
	{
		if (i2c_send_byte(i2c_number, *data++) == 0)
			return 0;
	}

	return 1;
}


char i2c_receive_string(unsigned char i2c_number, char *buff, unsigned int string_length)
{
	if ((i2c_number > 1) || (string_length == 0))
		return -1;

	char data = 0;
	while (string_length--)
	{
		if (i2c_receive_byte(i2c_number, &data) == 0)
			return 0;

		*buff++ = data;
	}
	return 1;
}

void i2c0_init(int mode)
{
	i2c_init(0, mode);
}

void i2c0_start(int addr)
{
	i2c_start(0, addr, 0);
}

void i2c0_stop()
{
	i2c_stop(0);
}

void i2c0_receive(char *buf, unsigned int count)
{
	i2c_receive_string(0, buf, count);
}

#endif
