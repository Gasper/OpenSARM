/**
 * 2012 OpenSARM
 * Avtor: Matja¸ Tome <matjaz.tome@gmail.com>
 *
 */

#ifdef LM75_H_INCLUDED

#include "i2c.h"


/**
 * Configures i2c0 to work with LM75 sensor
 *
 * @param clk Desired i2c0 clock frequency in hertz
 */
void lm75_init(unsigned int clk)
{
	i2c0_init(clk);
}

/**
 * Returns raw data from sensor
 *
 * @param adr adress of sensor
 * @return Data from sensor
 */
signed int lm75_get_temp_raw(unsigned char adr)
{
	unsigned char a[2];
	i2c0_start(adr);
	i2c0_receive(a, 2);
	i2c0_stop();
	return ((a[0] << 8) | a[1]) >> 7;
}


/**
 * Returns data from sensor in celsius (whole part and decimal part)
 *
 * @param adr adress of sensor
 * @param *w pointer to variable, tha will hold whole part of temperature
 * @param *d pointer to a variable, the will hold decimal part of temperature
 */
void lm75_get_temp(unsigned char adr, signed char *w, signed char *d)
{
	signed int a = lm75_get_temp_raw(adr);

	if (a % 2)
		*d = 5;
	else
		*d = 0;

	*w = (a * 10) / 20;
}

#endif
