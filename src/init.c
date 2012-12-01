#include "lpc214x.h"

/* Function is called from crt.s. It initializes cpu clock, MAM settings and fast GPIO */
void Initialize(void)  {
#define PLOCK 0x400

	SCS |= 0x03; // We will use the fast interface...

	// Setting Multiplier and Divider values
	PLLCFG = PLL_CONF;

	PLLFEED = 0xAA;
	PLLFEED = 0x55;

	// Enabling the PLL */
	PLLCON = 0x1;

	PLLFEED = 0xAA;
	PLLFEED = 0x55;

	// Wait for the PLL to lock to set frequency
	while (!(PLLSTAT & PLOCK)) ;

	// Connect the PLL as the clock source
	PLLCON = 0x3;

	PLLFEED = 0xAA;
	PLLFEED = 0x55;

	// Enabling MAM and setting number of clocks used for Flash memory fetch (4 cclks in this case)
	MAMCR = 0x2;
	MAMTIM = 0x4;

	// Setting peripheral Clock (pclk) to System Clock (cclk)
	VPBDIV = 0x1;
}
