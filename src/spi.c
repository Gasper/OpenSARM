/**
 * 2012 OpenSARM
 * Avtor: Jernej Sorta <jernejsorta@gmail.com>
 * 
 */

int spi_set_speed(unsigned char spi_number, unsigned int speed)
{
	if ((spi_number > 1) || (speed > ((CPU_FREQ * 1000) >> 3)) || ((((CPU_FREQ * 1000)) / speed) > 0xFF))
		return -1; //Če je hitrost večja kot f_cpu/8, ali pa premajhna
	
	unsigned int calculated_speed = 0;
	calculated_speed = (CPU_FREQ * 1000) / speed;

	if (((CPU_FREQ * 1000 * 10) / speed - (calculated_speed * 10)) > 5)
		calculated_speed++;

	if ((calculated_speed & 1) == 1)
		calculated_speed++;

	if (spi_number == 1)
	{
 		//Podpore za SPI1 še ni
		return -1;
	}
	else
	{
		S0SPCCR = calculated_speed;
		return ((CPU_FREQ * 1000) / S0SPCCR);
	}

}

char spi_init(unsigned char spi_number, unsigned int speed)
{
	if (spi_number > 1)
		return -1;
	
	if ((spi_set_speed(spi_number, speed) == -1) || (spi_set_mode(spi_number, 3, 0, 16) == -1))
		return -1;

	return 1;
}

char spi_set_mode(unsigned char spi_number, unsigned char mode, unsigned char msb_lsb_mode, unsigned char number_of_bits)
{
	if ((spi_number > 1) || (mode >= 4) || (msb_lsb_mode > 1) || (number_of_bits > 16) || (number_of_bits < 8))
		return -1;

	if(spi_number == 1)
	{
		//Trenutno še ni podpore za drugi SPI vmesnik
		return -1;
	}
	else
	{
		S0SPCR =	(mode << MODE) | //SPI način: CPOL, CPHA itd...
					(1 << MSTR) | //Nastavimo kot "kapetana" povezave
					(msb_lsb_mode << LSBF) | //Nastavimo, ali se prenaša najprej LSB(msb_lsb_mode = 1) ali MSB(msb_lsb_mode = 0)
					((number_of_bits > 8 ? 1 : 0) << BIT_ENABLE)| //Nastavimo, ali bomo prenašali 8 ali več bitov
					((number_of_bits == 16 ? 0 : number_of_bits) << BITS); //Nastavimo število bitov, ki jih bomo prenašali: 8<=št<=16

		/*Strojne nastavitve:*/
		PINSEL0 &= ~((0x03 << 8) | (0x03 << 10) | (0x03 << 12));
		PINSEL0 |= (1 << 8) | (1 << 10) | (1 << 12);
	}

	return 1;
}

char spi_enable_slave(unsigned char spi_number, unsigned char slave_number/*0-3*/)
{
	if ((slave_number > 3) || (spi_number > 1))
		return -1;

	if (spi_number == 1)
	{
		//Podpore za SPI1 še ni
		return -1;
	}
	else
	{
		switch (slave_number)
		{
			case 0:
				FIO0CLR |= 1 << 7;
				break;
			case 1:
			case 2:
			case 3:
				break;
		}
	
		return 1;
	}
}

char spi_disable_slave(unsigned char spi_number, unsigned char slave_number/*0-3*/)
{
	if ((slave_number > 3) || (spi_number > 1))
		return -1;

	if (spi_number == 1)
	{
		//Podpore za SPI1 še ni
		return -1;
	}
	else
	{
		switch (slave_number)
		{
			case 0:
				FIO0SET |= 1 << 7;
				break;
			case 1:
			case 2:
			case 3:
				break;
		}
	
		return 1;
	}
}

char spi_transmit_byte(unsigned char spi_number, unsigned char slave_number, char data)
{
	if ((spi_number > 1) || (slave_number > 3))
		return -1;

	char received_data = 0;
	if (spi_number == 1)
	{
		//Podpore za SPI1 še ni
		return -1;
	}
	else
	{
		received_data = S0SPDR;
		S0SPDR = data;
		spi_enable_slave(0, slave_number);
		while (((S0SPSR >> 7) & 1) != 1 );
		
		spi_disable_slave(0, slave_number);
		
		return received_data;
	}
}

int spi_transmit_data(unsigned char spi_number, unsigned char slave_number, int data)
{
	if ((spi_number > 1) || (slave_number > 3))
		return -1;

	int received_data;

	if (spi_number == 1)
	{
	   //Podpore za SPI1 še ni
	   return -1;
	}
	else
	{
		received_data = S0SPDR;
		spi_enable_slave(0, slave_number);
		S0SPDR = data;
		while (((S0SPSR >> 7) & 1) != 1);
		
		spi_disable_slave(0, slave_number);
	}

	return received_data;
}

int spi_receive_data(unsigned char spi_number, unsigned char slave_number)
{
	if ((spi_number > 1) || (slave_number > 3))
		return -1;

	if (spi_number == 1)
	{
	   //Podpore za SPI1 še ni
	   return -1;
	}
	else
	{
		spi_enable_slave(spi_number, slave_number);
		S0SPDR = '?';
		while (((S0SPSR >> 7) & 1) !=1);
		
		spi_disable_slave(spi_number, slave_number);
		
		return S0SPDR;
	}
}

char spi_send_array(unsigned char spi_number, unsigned char slave_number, int *data, unsigned int array_size)
{
	if ((spi_number >= 1) || (array_size == 0) || (slave_number > 3))
		return -1;

	while (array_size--)
		spi_transmit_data(spi_number, slave_number, *data++);

	return 1;
}

char spi_slave_init(unsigned char spi_number, unsigned char slave_number)
{
	if ((slave_number > 3) || (spi_number > 1))
		return -1;
	
	if (spi_number == 1)
	{
		//Podpore za SPI1 še ni
		return -1;
	}
	else
	{
		switch (slave_number)
		{
			case 0:
				FIO0DIR |= 1 << 7;
				break;
			case 1:
			case 2:
			case 3:
				break;
		}
		
		return 1;
	}
}
