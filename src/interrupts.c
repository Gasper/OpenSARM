/**
 * 2012 OpenSARM
 * Avtor: Jernej Sorta <jernejsorta@gmail.com>
 * 
 */

#include "lpc214x.h"
#include "interrupts.h"

void set_interrupt(unsigned char interrupt, unsigned char set)
{
	if (set)
		VICIntEnable = (1 << interrupt);
	else
		VICIntEnClr = (1 << interrupt);
}

/*
 Funkcija nastavi željeno prekinitev kot hitro prekinitev
 Dobra praksa je, da je samo ena, zato je ta fja tako spisana
 */
void interrupt_fiq(unsigned char interrupt)
{
	VICIntSelect = (1 << interrupt);
	//V *.h datoteki je potrebno za to prekinitev popraviti iz "IRQ" v "FIQ"
}


unsigned char interrupt_fiq_status(unsigned char interrupt)
{
	if (interrupt > 15)
		interrupt = 15;

	return (VICFIQStatus >> interrupt) & 1;
}


unsigned char interrupt_irq_status(unsigned char interrupt)
{
	if (interrupt > 15)
		interrupt = 15;

	return (VICIRQStatus >> interrupt) & 1;
}


/*
V tej funkciji ročno nastavimo pomembnosti prekinitev, kar določa vrstni red izvajanja prekinitvenih rutin
v primeru večih zahtev po prekinitvi. Pomembnost pada z zaporedno številko. (0->najbolj pomembna, 15->najmanj pomembna)
*/
void interrupt_priorities(void)
{
	VICVectCntl0 = IRQslot_en + TIMER0;
	VICVectCntl1 = IRQslot_en + TIMER1;
	VICVectCntl2 = IRQslot_en + PWM;
	VICVectCntl3 = IRQslot_en + AD1;
	VICVectCntl4 = IRQslot_en + SPI0;
	VICVectCntl5 = IRQslot_en + SSP;
	VICVectCntl6 = IRQslot_en + I2C0;
	VICVectCntl7 = IRQslot_en + I2C1;
	VICVectCntl8 = IRQslot_en + RTC;
	VICVectCntl9 = IRQslot_en + UART0;
	VICVectCntl10 = IRQslot_en + UART1;
	VICVectCntl11 = IRQslot_en + AD0;
	VICVectCntl12 = IRQslot_en + PLL;
	VICVectCntl13 = IRQslot_en + BOD;
	VICVectCntl14 = IRQslot_en + EINT1;
	VICVectCntl15 = IRQslot_en + EINT2;
}

void interrupt_addresses(void)
{
	VICVectAddr0 = (unsigned int)TIMER0_ISR;
	VICVectAddr1 = (unsigned int)TIMER1_ISR;
	VICVectAddr2 = (unsigned int)PWM_ISR;
	VICVectAddr3 = (unsigned int)AD1_ISR;
	VICVectAddr4 = (unsigned int)SPI0_ISR;
	VICVectAddr5 = (unsigned int)SSP_ISR;
	VICVectAddr6 = (unsigned int)I2C0_ISR;
	VICVectAddr7 = (unsigned int)I2C1_ISR;
	VICVectAddr8 = (unsigned int)RTC_ISR;
	VICVectAddr9 = (unsigned int)UART0_ISR;
	VICVectAddr10 = (unsigned int)UART1_ISR;
	VICVectAddr11 = (unsigned int)AD0_ISR;
	VICVectAddr12 = (unsigned int)PLL_ISR;
	VICVectAddr13 = (unsigned int)BOD_ISR;
	VICVectAddr14 = (unsigned int)EINT1_ISR;
	VICVectAddr15 = (unsigned int)EINT2_ISR;
}

//prekinitvene rutine
void TIMER0_ISR(void)
{
	T0IR |= (1 << MR0_INT) | (1 << MR1_INT) | (1 << MR2_INT) | (1 << MR3_INT) | (1 << CR0_INT) | (1 << CR1_INT) | (1 << CR2_INT) | (1 << CR3_INT); //Potrebne zastavice
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void TIMER1_ISR(void)
{
	T1IR |= (1 << MR0_INT) | (1 << MR1_INT) | (1 << MR2_INT) | (1 << MR3_INT) | (1 << CR0_INT) | (1 << CR1_INT) | (1 << CR2_INT) | (1 << CR3_INT);
	VICVectAddr = 0xFF;
}

void PWM_ISR(void)
{
	PWMIR |= (1 << PWMMR0_INT) | (1 << PWMMR1_INT) | (1 << PWMMR2_INT) | (1 << PWMMR3_INT) | (1 << PWMMR4_INT) | (1 << PWMMR5_INT) | (1 << PWMMR6_INT); //Pobriše vse prekinitve
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void AD1_ISR(void)
{
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void SPI0_ISR(void)
{
	S0SPINT |= (1 << SPI_IF);
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void SSP_ISR(void)
{
	SSPICR |= (1 << RORIC) | (1 << RTIC); //Mja... Ne vem če je ravno pravilno... S tem pobrišem obe zastavici.
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void I2C0_ISR(void)
{	
	I2CONCLR |= (1 << SIC); 
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void I2C1_ISR(void)
{
	I21CONCLR |= (1 << SIC); //čudno ime registra...
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void RTC_ISR(void)
{
	ILR |= (1 << RTCCIF) | (1 << RTCALF);
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void UART0_ISR(void)
{
	unsigned int u0iir = U0IIR; //branje ragistra za pobrisanje prekinitve
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void UART1_ISR(void)
{
	unsigned int u1iir = U1IIR; //branje ragistra za pobrisanje prekinitve
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void AD0_ISR(void)
{
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void PLL_ISR(void)
{
	//?
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void BOD_ISR(void)
{
	//?
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void EINT1_ISR(void)
{
	EXTINT = 0x04;
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}

void EINT2_ISR(void)
{
	EXTINT = 0x02;
	VICVectAddr = 0xFF; //Vpišemo karkoli, da se posodobi tabela pomembnosti
}
