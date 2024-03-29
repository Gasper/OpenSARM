/***********************************************************************
 *
 *  lpc214x.h:  Header file for Philips LPC214x series
 *
 ***********************************************************************/

#ifndef __lpc214x_h
#define __lpc214x_h

/* External Memory Controller (EMC) */
#define BCFG0          (*((volatile unsigned long *) 0xFFE00000))
#define BCFG1          (*((volatile unsigned long *) 0xFFE00004))
#define BCFG2          (*((volatile unsigned long *) 0xFFE00008))
#define BCFG3          (*((volatile unsigned long *) 0xFFE0000C))

/* Vectored Interrupt Controller (VIC) */
#define VICIRQStatus   (*((volatile unsigned long *) 0xFFFFF000))
#define VICFIQStatus   (*((volatile unsigned long *) 0xFFFFF004))
#define VICRawIntr     (*((volatile unsigned long *) 0xFFFFF008))
#define VICIntSelect   (*((volatile unsigned long *) 0xFFFFF00C))
#define VICIntEnable   (*((volatile unsigned long *) 0xFFFFF010))
#define VICIntEnClr    (*((volatile unsigned long *) 0xFFFFF014))
#define VICSoftInt     (*((volatile unsigned long *) 0xFFFFF018))
#define VICSoftIntClr  (*((volatile unsigned long *) 0xFFFFF01C))
#define VICProtection  (*((volatile unsigned long *) 0xFFFFF020))
#define VICVectAddr    (*((volatile unsigned long *) 0xFFFFF030))
#define VICDefVectAddr (*((volatile unsigned long *) 0xFFFFF034))
#define VICVectAddr0   (*((volatile unsigned long *) 0xFFFFF100))
#define VICVectAddr1   (*((volatile unsigned long *) 0xFFFFF104))
#define VICVectAddr2   (*((volatile unsigned long *) 0xFFFFF108))
#define VICVectAddr3   (*((volatile unsigned long *) 0xFFFFF10C))
#define VICVectAddr4   (*((volatile unsigned long *) 0xFFFFF110))
#define VICVectAddr5   (*((volatile unsigned long *) 0xFFFFF114))
#define VICVectAddr6   (*((volatile unsigned long *) 0xFFFFF118))
#define VICVectAddr7   (*((volatile unsigned long *) 0xFFFFF11C))
#define VICVectAddr8   (*((volatile unsigned long *) 0xFFFFF120))
#define VICVectAddr9   (*((volatile unsigned long *) 0xFFFFF124))
#define VICVectAddr10  (*((volatile unsigned long *) 0xFFFFF128))
#define VICVectAddr11  (*((volatile unsigned long *) 0xFFFFF12C))
#define VICVectAddr12  (*((volatile unsigned long *) 0xFFFFF130))
#define VICVectAddr13  (*((volatile unsigned long *) 0xFFFFF134))
#define VICVectAddr14  (*((volatile unsigned long *) 0xFFFFF138))
#define VICVectAddr15  (*((volatile unsigned long *) 0xFFFFF13C))
#define VICVectCntl0   (*((volatile unsigned long *) 0xFFFFF200))
#define VICVectCntl1   (*((volatile unsigned long *) 0xFFFFF204))
#define VICVectCntl2   (*((volatile unsigned long *) 0xFFFFF208))
#define VICVectCntl3   (*((volatile unsigned long *) 0xFFFFF20C))
#define VICVectCntl4   (*((volatile unsigned long *) 0xFFFFF210))
#define VICVectCntl5   (*((volatile unsigned long *) 0xFFFFF214))
#define VICVectCntl6   (*((volatile unsigned long *) 0xFFFFF218))
#define VICVectCntl7   (*((volatile unsigned long *) 0xFFFFF21C))
#define VICVectCntl8   (*((volatile unsigned long *) 0xFFFFF220))
#define VICVectCntl9   (*((volatile unsigned long *) 0xFFFFF224))
#define VICVectCntl10  (*((volatile unsigned long *) 0xFFFFF228))
#define VICVectCntl11  (*((volatile unsigned long *) 0xFFFFF22C))
#define VICVectCntl12  (*((volatile unsigned long *) 0xFFFFF230))
#define VICVectCntl13  (*((volatile unsigned long *) 0xFFFFF234))
#define VICVectCntl14  (*((volatile unsigned long *) 0xFFFFF238))
#define VICVectCntl15  (*((volatile unsigned long *) 0xFFFFF23C))

/* Pin Connect Block */
#define PINSEL0        (*((volatile unsigned long *) 0xE002C000))
#define PINSEL1        (*((volatile unsigned long *) 0xE002C004))
#define PINSEL2        (*((volatile unsigned long *) 0xE002C014))

/* General Purpose Input/Output (GPIO) */
#define IOPIN          (*((volatile unsigned long *) 0xE0028000))
#define IOSET          (*((volatile unsigned long *) 0xE0028004))
#define IODIR          (*((volatile unsigned long *) 0xE0028008))
#define IOCLR          (*((volatile unsigned long *) 0xE002800C))

#define IOPIN0         (*((volatile unsigned long *) 0xE0028000))
#define IOSET0         (*((volatile unsigned long *) 0xE0028004))
#define IODIR0         (*((volatile unsigned long *) 0xE0028008))
#define IOCLR0         (*((volatile unsigned long *) 0xE002800C))
#define IOPIN1         (*((volatile unsigned long *) 0xE0028010))
#define IOSET1         (*((volatile unsigned long *) 0xE0028014))
#define IODIR1         (*((volatile unsigned long *) 0xE0028018))
#define IOCLR1         (*((volatile unsigned long *) 0xE002801C))
#define IOPIN2         (*((volatile unsigned long *) 0xE0028020))
#define IOSET2         (*((volatile unsigned long *) 0xE0028024))
#define IODIR2         (*((volatile unsigned long *) 0xE0028028))
#define IOCLR2         (*((volatile unsigned long *) 0xE002802C))
#define IOPIN3         (*((volatile unsigned long *) 0xE0028030))
#define IOSET3         (*((volatile unsigned long *) 0xE0028034))
#define IODIR3         (*((volatile unsigned long *) 0xE0028038))
#define IOCLR3         (*((volatile unsigned long *) 0xE002803C))

/* Fast I/O setup */
#define FIO_BASE_ADDR		0x3FFFC000
#define FIO0DIR        (*((volatile unsigned long *) 0x3FFFC000))
#define FIO0MASK       (*((volatile unsigned long *) 0x3FFFC010))
#define FIO0PIN        (*((volatile unsigned long *) 0x3FFFC014))
#define FIO0SET        (*((volatile unsigned long *) 0x3FFFC018))
#define FIO0CLR        (*((volatile unsigned long *) 0x3FFFC01C))
#define FIO1DIR        (*((volatile unsigned long *) 0x3FFFC020))
#define FIO1MASK       (*((volatile unsigned long *) 0x3FFFC030))
#define FIO1PIN        (*((volatile unsigned long *) 0x3FFFC034))
#define FIO1SET        (*((volatile unsigned long *) 0x3FFFC038))
#define FIO1CLR        (*((volatile unsigned long *) 0x3FFFC03C))

/* Memory Accelerator Module (MAM) */
#define MAMCR          (*((volatile unsigned long *) 0xE01FC000))
#define MAMTIM         (*((volatile unsigned long *) 0xE01FC004))
#define MAMMAP         (*((volatile unsigned long *) 0xE01FC040))

/* Phase Locked Loop (PLL) */
#define PLLCON         (*((volatile unsigned long *) 0xE01FC080))
#define PLLCFG         (*((volatile unsigned long *) 0xE01FC084))
#define PLLSTAT        (*((volatile unsigned long *) 0xE01FC088))
#define PLLFEED        (*((volatile unsigned long *) 0xE01FC08C))

/* PLL48 Registers */
#define PLL48CON       (*((volatile unsigned long *) 0xE01FC0A0))
#define PLL48CFG       (*((volatile unsigned long *) 0xE01FC0A4))
#define PLL48STAT      (*((volatile unsigned long *) 0xE01FC0A8))
#define PLL48FEED      (*((volatile unsigned long *) 0xE01FC0AC))

/* Power Control */
#define PCON           (*((volatile unsigned long *) 0xE01FC0C0))
#define PCONP          (*((volatile unsigned long *) 0xE01FC0C4))

/* VPB Divider */
#define VPBDIV         (*((volatile unsigned long *) 0xE01FC100))

/* External Interrupts */
#define EXTINT         (*((volatile unsigned long *) 0xE01FC140))
#define EXTWAKE        (*((volatile unsigned long *) 0xE01FC144))
#define EXTMODE        (*((volatile unsigned long *) 0xE01FC148))
#define EXTPOLAR       (*((volatile unsigned long *) 0xE01FC14C))

/* Reset */
#define RSIR           (*((volatile unsigned long *) 0xE01FC180))

/* System Controls and Status */
#define SCS            (*((volatile unsigned long *) 0xE01FC1A0))

/* Timer 0 */
#define TIMER0_IR      (*((volatile unsigned long *) 0xE0004000))
#define TIMER0_TCR     (*((volatile unsigned long *) 0xE0004004))
#define TIMER0_TC      (*((volatile unsigned long *) 0xE0004008))
#define TIMER0_PR      (*((volatile unsigned long *) 0xE000400C))
#define TIMER0_PC      (*((volatile unsigned long *) 0xE0004010))
#define TIMER0_MCR     (*((volatile unsigned long *) 0xE0004014))
#define TIMER0_MR0     (*((volatile unsigned long *) 0xE0004018))
#define TIMER0_MR1     (*((volatile unsigned long *) 0xE000401C))
#define TIMER0_MR2     (*((volatile unsigned long *) 0xE0004020))
#define TIMER0_MR3     (*((volatile unsigned long *) 0xE0004024))
#define TIMER0_CCR     (*((volatile unsigned long *) 0xE0004028))
#define TIMER0_CR0     (*((volatile unsigned long *) 0xE000402C))
#define TIMER0_CR1     (*((volatile unsigned long *) 0xE0004030))
#define TIMER0_CR2     (*((volatile unsigned long *) 0xE0004034))
#define TIMER0_CR3     (*((volatile unsigned long *) 0xE0004038))
#define TIMER0_EMR     (*((volatile unsigned long *) 0xE000403C))
#define TIMER0_CTCR    (*((volatile unsigned long *) 0xE0004070))

#define T0IR           (*((volatile unsigned long *) 0xE0004000))
#define T0TCR          (*((volatile unsigned long *) 0xE0004004))
#define T0TC           (*((volatile unsigned long *) 0xE0004008))
#define T0PR           (*((volatile unsigned long *) 0xE000400C))
#define T0PC           (*((volatile unsigned long *) 0xE0004010))
#define T0MCR          (*((volatile unsigned long *) 0xE0004014))
#define T0MR0          (*((volatile unsigned long *) 0xE0004018))
#define T0MR1          (*((volatile unsigned long *) 0xE000401C))
#define T0MR2          (*((volatile unsigned long *) 0xE0004020))
#define T0MR3          (*((volatile unsigned long *) 0xE0004024))
#define T0CCR          (*((volatile unsigned long *) 0xE0004028))
#define T0CR0          (*((volatile unsigned long *) 0xE000402C))
#define T0CR1          (*((volatile unsigned long *) 0xE0004030))
#define T0CR2          (*((volatile unsigned long *) 0xE0004034))
#define T0CR3          (*((volatile unsigned long *) 0xE0004038))
#define T0EMR          (*((volatile unsigned long *) 0xE000403C))
#define T0CTCR         (*((volatile unsigned long *) 0xE0004070))

/* Timer 1 */
#define TIMER1_IR      (*((volatile unsigned long *) 0xE0008000))
#define TIMER1_TCR     (*((volatile unsigned long *) 0xE0008004))
#define TIMER1_TC      (*((volatile unsigned long *) 0xE0008008))
#define TIMER1_PR      (*((volatile unsigned long *) 0xE000800C))
#define TIMER1_PC      (*((volatile unsigned long *) 0xE0008010))
#define TIMER1_MCR     (*((volatile unsigned long *) 0xE0008014))
#define TIMER1_MR0     (*((volatile unsigned long *) 0xE0008018))
#define TIMER1_MR1     (*((volatile unsigned long *) 0xE000801C))
#define TIMER1_MR2     (*((volatile unsigned long *) 0xE0008020))
#define TIMER1_MR3     (*((volatile unsigned long *) 0xE0008024))
#define TIMER1_CCR     (*((volatile unsigned long *) 0xE0008028))
#define TIMER1_CR0     (*((volatile unsigned long *) 0xE000802C))
#define TIMER1_CR1     (*((volatile unsigned long *) 0xE0008030))
#define TIMER1_CR2     (*((volatile unsigned long *) 0xE0008034))
#define TIMER1_CR3     (*((volatile unsigned long *) 0xE0008038))
#define TIMER1_EMR     (*((volatile unsigned long *) 0xE000803C))
#define TIMER1_CTCR    (*((volatile unsigned long *) 0xE0008070))

#define T1IR           (*((volatile unsigned long *) 0xE0008000))
#define T1TCR          (*((volatile unsigned long *) 0xE0008004))
#define T1TC           (*((volatile unsigned long *) 0xE0008008))
#define T1PR           (*((volatile unsigned long *) 0xE000800C))
#define T1PC           (*((volatile unsigned long *) 0xE0008010))
#define T1MCR          (*((volatile unsigned long *) 0xE0008014))
#define T1MR0          (*((volatile unsigned long *) 0xE0008018))
#define T1MR1          (*((volatile unsigned long *) 0xE000801C))
#define T1MR2          (*((volatile unsigned long *) 0xE0008020))
#define T1MR3          (*((volatile unsigned long *) 0xE0008024))
#define T1CCR          (*((volatile unsigned long *) 0xE0008028))
#define T1CR0          (*((volatile unsigned long *) 0xE000802C))
#define T1CR1          (*((volatile unsigned long *) 0xE0008030))
#define T1CR2          (*((volatile unsigned long *) 0xE0008034))
#define T1CR3          (*((volatile unsigned long *) 0xE0008038))
#define T1EMR          (*((volatile unsigned long *) 0xE000803C))
#define T1CTCR         (*((volatile unsigned long *) 0xE0008070))

/* Pulse Width Modulator (PWM) */
#define PWM_IR         (*((volatile unsigned long *) 0xE0014000))
#define PWM_TCR        (*((volatile unsigned long *) 0xE0014004))
#define PWM_TC         (*((volatile unsigned long *) 0xE0014008))
#define PWM_PR         (*((volatile unsigned long *) 0xE001400C))
#define PWM_PC         (*((volatile unsigned long *) 0xE0014010))
#define PWM_MCR        (*((volatile unsigned long *) 0xE0014014))
#define PWM_MR0        (*((volatile unsigned long *) 0xE0014018))
#define PWM_MR1        (*((volatile unsigned long *) 0xE001401C))
#define PWM_MR2        (*((volatile unsigned long *) 0xE0014020))
#define PWM_MR3        (*((volatile unsigned long *) 0xE0014024))
#define PWM_MR4        (*((volatile unsigned long *) 0xE0014040))
#define PWM_MR5        (*((volatile unsigned long *) 0xE0014044))
#define PWM_MR6        (*((volatile unsigned long *) 0xE0014048))
#define PWM_CCR        (*((volatile unsigned long *) 0xE0014028))
#define PWM_CR0        (*((volatile unsigned long *) 0xE001402C))
#define PWM_CR1        (*((volatile unsigned long *) 0xE0014030))
#define PWM_CR2        (*((volatile unsigned long *) 0xE0014034))
#define PWM_CR3        (*((volatile unsigned long *) 0xE0014038))
#define PWM_EMR        (*((volatile unsigned long *) 0xE001403C))
#define PWM_PCR        (*((volatile unsigned long *) 0xE001404C))
#define PWM_LER        (*((volatile unsigned long *) 0xE0014050))

#define PWMIR          (*((volatile unsigned long *) 0xE0014000))
#define PWMTCR         (*((volatile unsigned long *) 0xE0014004))
#define PWMTC          (*((volatile unsigned long *) 0xE0014008))
#define PWMPR          (*((volatile unsigned long *) 0xE001400C))
#define PWMPC          (*((volatile unsigned long *) 0xE0014010))
#define PWMMCR         (*((volatile unsigned long *) 0xE0014014))
#define PWMMR0         (*((volatile unsigned long *) 0xE0014018))
#define PWMMR1         (*((volatile unsigned long *) 0xE001401C))
#define PWMMR2         (*((volatile unsigned long *) 0xE0014020))
#define PWMMR3         (*((volatile unsigned long *) 0xE0014024))
#define PWMMR4         (*((volatile unsigned long *) 0xE0014040))
#define PWMMR5         (*((volatile unsigned long *) 0xE0014044))
#define PWMMR6         (*((volatile unsigned long *) 0xE0014048))
#define PWMCCR         (*((volatile unsigned long *) 0xE0014028))
#define PWMCR0         (*((volatile unsigned long *) 0xE001402C))
#define PWMCR1         (*((volatile unsigned long *) 0xE0014030))
#define PWMCR2         (*((volatile unsigned long *) 0xE0014034))
#define PWMCR3         (*((volatile unsigned long *) 0xE0014038))
#define PWMEMR         (*((volatile unsigned long *) 0xE001403C))
#define PWMPCR         (*((volatile unsigned long *) 0xE001404C))
#define PWMLER         (*((volatile unsigned long *) 0xE0014050))

/* Universal Asynchronous Receiver Transmitter 0 (UART0) */
#define UART0_RBR      (*((volatile unsigned long *) 0xE000C000))
#define UART0_THR      (*((volatile unsigned long *) 0xE000C000))
#define UART0_IER      (*((volatile unsigned long *) 0xE000C004))
#define UART0_IIR      (*((volatile unsigned long *) 0xE000C008))
#define UART0_FCR      (*((volatile unsigned long *) 0xE000C008))
#define UART0_LCR      (*((volatile unsigned long *) 0xE000C00C))
#define UART0_MCR      (*((volatile unsigned long *) 0xE000C010))
#define UART0_LSR      (*((volatile unsigned long *) 0xE000C014))
#define UART0_MSR      (*((volatile unsigned long *) 0xE000C018))
#define UART0_SCR      (*((volatile unsigned long *) 0xE000C01C))
#define UART0_ACR      (*((volatile unsigned long *) 0xE000C020))
#define UART0_FDR      (*((volatile unsigned long *) 0xE000C028))
#define UART0_TER      (*((volatile unsigned long *) 0xE000C030))
#define UART0_DLL      (*((volatile unsigned long *) 0xE000C000))
#define UART0_DLM      (*((volatile unsigned long *) 0xE000C004))

#define U0RBR          (*((volatile unsigned long *) 0xE000C000))
#define U0THR          (*((volatile unsigned long *) 0xE000C000))
#define U0IER          (*((volatile unsigned long *) 0xE000C004))
#define U0IIR          (*((volatile unsigned long *) 0xE000C008))
#define U0FCR          (*((volatile unsigned long *) 0xE000C008))
#define U0LCR          (*((volatile unsigned long *) 0xE000C00C))
#define U0MCR          (*((volatile unsigned long *) 0xE000C010))
#define U0LSR          (*((volatile unsigned long *) 0xE000C014))
#define U0MSR          (*((volatile unsigned long *) 0xE000C018))
#define U0SCR          (*((volatile unsigned long *) 0xE000C01C))
#define U0ACR          (*((volatile unsigned long *) 0xE000C020))
#define U0FDR          (*((volatile unsigned long *) 0xE000C028))
#define U0TER          (*((volatile unsigned long *) 0xE000C030))
#define U0DLL          (*((volatile unsigned long *) 0xE000C000))
#define U0DLM          (*((volatile unsigned long *) 0xE000C004))

/* Universal Asynchronous Receiver Transmitter 1 (UART1) */
#define UART1_RBR      (*((volatile unsigned long *) 0xE0010000))
#define UART1_THR      (*((volatile unsigned long *) 0xE0010000))
#define UART1_IER      (*((volatile unsigned long *) 0xE0010004))
#define UART1_IIR      (*((volatile unsigned long *) 0xE0010008))
#define UART1_FCR      (*((volatile unsigned long *) 0xE0010008))
#define UART1_LCR      (*((volatile unsigned long *) 0xE001000C))
#define UART1_MCR      (*((volatile unsigned long *) 0xE0010010))
#define UART1_LSR      (*((volatile unsigned long *) 0xE0010014))
#define UART1_MSR      (*((volatile unsigned long *) 0xE0010018))
#define UART1_SCR      (*((volatile unsigned long *) 0xE001001C))
#define UART1_ACR      (*((volatile unsigned long *) 0xE0010020))
#define UART1_FDR      (*((volatile unsigned long *) 0xE0010028))
#define UART1_TER      (*((volatile unsigned long *) 0xE0010030))
#define UART1_DLL      (*((volatile unsigned long *) 0xE0010000))
#define UART1_DLM      (*((volatile unsigned long *) 0xE0010004))

#define U1RBR          (*((volatile unsigned long *) 0xE0010000))
#define U1THR          (*((volatile unsigned long *) 0xE0010000))
#define U1IER          (*((volatile unsigned long *) 0xE0010004))
#define U1IIR          (*((volatile unsigned long *) 0xE0010008))
#define U1FCR          (*((volatile unsigned long *) 0xE0010008))
#define U1LCR          (*((volatile unsigned long *) 0xE001000C))
#define U1MCR          (*((volatile unsigned long *) 0xE0010010))
#define U1LSR          (*((volatile unsigned long *) 0xE0010014))
#define U1MSR          (*((volatile unsigned long *) 0xE0010018))
#define U1SCR          (*((volatile unsigned long *) 0xE001001C))
#define U1ACR          (*((volatile unsigned long *) 0xE0010020))
#define U1FDR          (*((volatile unsigned long *) 0xE0010028))
#define U1TER          (*((volatile unsigned long *) 0xE0010030))
#define U1DLL          (*((volatile unsigned long *) 0xE0010000))
#define U1DLM          (*((volatile unsigned long *) 0xE0010004))

/* I2C Interface 0 */
#define I2C_I2CONSET   (*((volatile unsigned long *) 0xE001C000))
#define I2C_I2STAT     (*((volatile unsigned long *) 0xE001C004))
#define I2C_I2DAT      (*((volatile unsigned long *) 0xE001C008))
#define I2C_I2ADR      (*((volatile unsigned long *) 0xE001C00C))
#define I2C_I2SCLH     (*((volatile unsigned long *) 0xE001C010))
#define I2C_I2SCLL     (*((volatile unsigned long *) 0xE001C014))
#define I2C_I2CONCLR   (*((volatile unsigned long *) 0xE001C018))

#define I2CONSET       (*((volatile unsigned long *) 0xE001C000))
#define I2STAT         (*((volatile unsigned long *) 0xE001C004))
#define I2DAT          (*((volatile unsigned long *) 0xE001C008))
#define I2ADR          (*((volatile unsigned long *) 0xE001C00C))
#define I2SCLH         (*((volatile unsigned long *) 0xE001C010))
#define I2SCLL         (*((volatile unsigned long *) 0xE001C014))
#define I2CONCLR       (*((volatile unsigned long *) 0xE001C018))

/* I2C Interface 1 */
#define I21CONSET      (*((volatile unsigned long *) 0xE005C000))
#define I21STAT        (*((volatile unsigned long *) 0xE005C004))
#define I21DAT         (*((volatile unsigned long *) 0xE005C008))
#define I21ADR         (*((volatile unsigned long *) 0xE005C00C))
#define I21SCLH        (*((volatile unsigned long *) 0xE005C010))
#define I21SCLL        (*((volatile unsigned long *) 0xE005C014))
#define I21CONCLR      (*((volatile unsigned long *) 0xE005C018))

/* SPI (Serial Peripheral Interface) */
#define SPI_SPCR       (*((volatile unsigned long *) 0xE0020000))
#define SPI_SPSR       (*((volatile unsigned long *) 0xE0020004))
#define SPI_SPDR       (*((volatile unsigned long *) 0xE0020008))
#define SPI_SPCCR      (*((volatile unsigned long *) 0xE002000C))
#define SPI_SPTCR      (*((volatile unsigned long *) 0xE0020010))
#define SPI_SPTSR      (*((volatile unsigned long *) 0xE0020014))
#define SPI_SPTOR      (*((volatile unsigned long *) 0xE0020018))
#define SPI_SPINT      (*((volatile unsigned long *) 0xE002001C))

#define S0SPCR         (*((volatile unsigned long *) 0xE0020000))
#define S0SPSR         (*((volatile unsigned long *) 0xE0020004))
#define S0SPDR         (*((volatile unsigned long *) 0xE0020008))
#define S0SPCCR        (*((volatile unsigned long *) 0xE002000C))
#define S0SPTCR        (*((volatile unsigned long *) 0xE0020010))
#define S0SPTSR        (*((volatile unsigned long *) 0xE0020014))
#define S0SPTOR        (*((volatile unsigned long *) 0xE0020018))
#define S0SPINT        (*((volatile unsigned long *) 0xE002001C))

/* SPI1 (Serial Peripheral Interface 1) */
#define S1SPCR         (*((volatile unsigned long *) 0xE0030000))
#define S1SPSR         (*((volatile unsigned long *) 0xE0030004))
#define S1SPDR         (*((volatile unsigned long *) 0xE0030008))
#define S1SPCCR        (*((volatile unsigned long *) 0xE003000C))
#define S1SPTCR        (*((volatile unsigned long *) 0xE0030010))
#define S1SPTSR        (*((volatile unsigned long *) 0xE0030014))
#define S1SPTOR        (*((volatile unsigned long *) 0xE0030018))
#define S1SPINT        (*((volatile unsigned long *) 0xE003001C))

/* SSP Controller */
#define SSPCR0         (*((volatile unsigned long *) 0xE0068000))
#define SSPCR1         (*((volatile unsigned long *) 0xE0068004))
#define SSPDR          (*((volatile unsigned long *) 0xE0068008))
#define SSPSR          (*((volatile unsigned long *) 0xE006800C))
#define SSPCPSR        (*((volatile unsigned long *) 0xE0068010))
#define SSPIMSC        (*((volatile unsigned long *) 0xE0068014))
#define SSPRIS         (*((volatile unsigned long *) 0xE0068018))
#define SSPMIS         (*((volatile unsigned long *) 0xE006801C))
#define SSPICR         (*((volatile unsigned long *) 0xE0068020))

/* Real Time Clock */
#define RTC_ILR        (*((volatile unsigned long *) 0xE0024000))
#define RTC_CTC        (*((volatile unsigned long *) 0xE0024004))
#define RTC_CCR        (*((volatile unsigned long *) 0xE0024008))
#define RTC_CIIR       (*((volatile unsigned long *) 0xE002400C))
#define RTC_AMR        (*((volatile unsigned long *) 0xE0024010))
#define RTC_CTIME0     (*((volatile unsigned long *) 0xE0024014))
#define RTC_CTIME1     (*((volatile unsigned long *) 0xE0024018))
#define RTC_CTIME2     (*((volatile unsigned long *) 0xE002401C))
#define RTC_SEC        (*((volatile unsigned long *) 0xE0024020))
#define RTC_MIN        (*((volatile unsigned long *) 0xE0024024))
#define RTC_HOUR       (*((volatile unsigned long *) 0xE0024028))
#define RTC_DOM        (*((volatile unsigned long *) 0xE002402C))
#define RTC_DOW        (*((volatile unsigned long *) 0xE0024030))
#define RTC_DOY        (*((volatile unsigned long *) 0xE0024034))
#define RTC_MONTH      (*((volatile unsigned long *) 0xE0024038))
#define RTC_YEAR       (*((volatile unsigned long *) 0xE002403C))
#define RTC_ALSEC      (*((volatile unsigned long *) 0xE0024060))
#define RTC_ALMIN      (*((volatile unsigned long *) 0xE0024064))
#define RTC_ALHOUR     (*((volatile unsigned long *) 0xE0024068))
#define RTC_ALDOM      (*((volatile unsigned long *) 0xE002406C))
#define RTC_ALDOW      (*((volatile unsigned long *) 0xE0024070))
#define RTC_ALDOY      (*((volatile unsigned long *) 0xE0024074))
#define RTC_ALMON      (*((volatile unsigned long *) 0xE0024078))
#define RTC_ALYEAR     (*((volatile unsigned long *) 0xE002407C))
#define RTC_PREINT     (*((volatile unsigned long *) 0xE0024080))
#define RTC_PREFRAC    (*((volatile unsigned long *) 0xE0024084))

#define ILR            (*((volatile unsigned long *) 0xE0024000))
#define CTC            (*((volatile unsigned long *) 0xE0024004))
#define CCR            (*((volatile unsigned long *) 0xE0024008))
#define CIIR           (*((volatile unsigned long *) 0xE002400C))
#define AMR            (*((volatile unsigned long *) 0xE0024010))
#define CTIME0         (*((volatile unsigned long *) 0xE0024014))
#define CTIME1         (*((volatile unsigned long *) 0xE0024018))
#define CTIME2         (*((volatile unsigned long *) 0xE002401C))
#define SEC            (*((volatile unsigned long *) 0xE0024020))
#define MIN            (*((volatile unsigned long *) 0xE0024024))
#define HOUR           (*((volatile unsigned long *) 0xE0024028))
#define DOM            (*((volatile unsigned long *) 0xE002402C))
#define DOW            (*((volatile unsigned long *) 0xE0024030))
#define DOY            (*((volatile unsigned long *) 0xE0024034))
#define MONTH          (*((volatile unsigned long *) 0xE0024038))
#define YEAR           (*((volatile unsigned long *) 0xE002403C))
#define ALSEC          (*((volatile unsigned long *) 0xE0024060))
#define ALMIN          (*((volatile unsigned long *) 0xE0024064))
#define ALHOUR         (*((volatile unsigned long *) 0xE0024068))
#define ALDOM          (*((volatile unsigned long *) 0xE002406C))
#define ALDOW          (*((volatile unsigned long *) 0xE0024070))
#define ALDOY          (*((volatile unsigned long *) 0xE0024074))
#define ALMON          (*((volatile unsigned long *) 0xE0024078))
#define ALYEAR         (*((volatile unsigned long *) 0xE002407C))
#define PREINT         (*((volatile unsigned long *) 0xE0024080))
#define PREFRAC        (*((volatile unsigned long *) 0xE0024084))

/* A/D Converter */
#define ADCR           (*((volatile unsigned long *) 0xE0034000))
#define ADDR           (*((volatile unsigned long *) 0xE0034004))
#define AD1CR          (*((volatile unsigned long *) 0xE0060000))
#define AD1DR          (*((volatile unsigned long *) 0xE0060004))

/* D/A Converter */
#define DACR           (*((volatile unsigned long *) 0xE006C000))

/* USB Controller */
/* Device Interrupt Registers */
#define DEV_INT_STAT   (*((volatile unsigned long *) 0xE0090000))
#define DEV_INT_EN     (*((volatile unsigned long *) 0xE0090004))
#define DEV_INT_CLR    (*((volatile unsigned long *) 0xE0090008))
#define DEV_INT_SET    (*((volatile unsigned long *) 0xE009000C))
#define DEV_INT_PRIO   (*((volatile unsigned long *) 0xE009002C))

/* Endpoint Interrupt Registers */
#define EP_INT_STAT    (*((volatile unsigned long *) 0xE0090030))
#define EP_INT_EN      (*((volatile unsigned long *) 0xE0090034))
#define EP_INT_CLR     (*((volatile unsigned long *) 0xE0090038))
#define EP_INT_SET     (*((volatile unsigned long *) 0xE009003C))
#define EP_INT_PRIO    (*((volatile unsigned long *) 0xE0090040))

/* Endpoint Realization Registers */
#define REALIZE_EP     (*((volatile unsigned long *) 0xE0090044))
#define EP_INDEX       (*((volatile unsigned long *) 0xE0090048))
#define MAXPACKET_SIZE (*((volatile unsigned long *) 0xE009004C))

/* Command Reagisters */
#define CMD_CODE       (*((volatile unsigned long *) 0xE0090010))
#define CMD_DATA       (*((volatile unsigned long *) 0xE0090014))

/* Data Transfer Registers */
#define RX_DATA        (*((volatile unsigned long *) 0xE0090018))
#define TX_DATA        (*((volatile unsigned long *) 0xE009001C))
#define RX_PLENGTH     (*((volatile unsigned long *) 0xE0090020))
#define TX_PLENGTH     (*((volatile unsigned long *) 0xE0090024))
#define USB_CTRL       (*((volatile unsigned long *) 0xE0090028))

/* DMA Registers */
#define DMA_REQ_STAT   (*((volatile unsigned long *) 0xE0090050))
#define DMA_REQ_CLR    (*((volatile unsigned long *) 0xE0090054))
#define DMA_REQ_SET    (*((volatile unsigned long *) 0xE0090058))
#define UDCA_HEAD      (*((volatile unsigned long *) 0xE0090080))
#define EP_DMA_STAT    (*((volatile unsigned long *) 0xE0090084))
#define EP_DMA_EN      (*((volatile unsigned long *) 0xE0090088))
#define EP_DMA_DIS     (*((volatile unsigned long *) 0xE009008C))
#define DMA_INT_STAT   (*((volatile unsigned long *) 0xE0090090))
#define DMA_INT_EN     (*((volatile unsigned long *) 0xE0090094))
#define EOT_INT_STAT   (*((volatile unsigned long *) 0xE00900A0))
#define EOT_INT_CLR    (*((volatile unsigned long *) 0xE00900A4))
#define EOT_INT_SET    (*((volatile unsigned long *) 0xE00900A8))
#define NDD_REQ_INT_STAT (*((volatile unsigned long *) 0xE00900AC))
#define NDD_REQ_INT_CLR  (*((volatile unsigned long *) 0xE00900B0))
#define NDD_REQ_INT_SET  (*((volatile unsigned long *) 0xE00900B4))
#define SYS_ERR_INT_STAT (*((volatile unsigned long *) 0xE00900B8))
#define SYS_ERR_INT_CLR  (*((volatile unsigned long *) 0xE00900BC))
#define SYS_ERR_INT_SET  (*((volatile unsigned long *) 0xE00900C0))
#define MODULE_ID        (*((volatile unsigned long *) 0xE00900FC))

/* CAN Acceptance Filter RAM */
#define AFRAM          (*((volatile unsigned long *) 0xE0038000))

/* CAN Acceptance Filter */
#define AFMR           (*((volatile unsigned long *) 0xE003C000))
#define SFF_sa         (*((volatile unsigned long *) 0xE003C004))
#define SFF_GRP_sa     (*((volatile unsigned long *) 0xE003C008))
#define EFF_sa         (*((volatile unsigned long *) 0xE003C00C))
#define EFF_GRP_sa     (*((volatile unsigned long *) 0xE003C010))
#define ENDofTable     (*((volatile unsigned long *) 0xE003C014))
#define LUTerrAd       (*((volatile unsigned long *) 0xE003C018))
#define LUTerr         (*((volatile unsigned long *) 0xE003C01C))

/* CAN Central Registers */
#define CANTxSR        (*((volatile unsigned long *) 0xE0040000))
#define CANRxSR        (*((volatile unsigned long *) 0xE0040004))
#define CANMSR         (*((volatile unsigned long *) 0xE0040008))

/* CAN Controller 1 (CAN1) */
#define C1MOD          (*((volatile unsigned long *) 0xE0044000))
#define C1CMR          (*((volatile unsigned long *) 0xE0044004))
#define C1GSR          (*((volatile unsigned long *) 0xE0044008))
#define C1ICR          (*((volatile unsigned long *) 0xE004400C))
#define C1IER          (*((volatile unsigned long *) 0xE0044010))
#define C1BTR          (*((volatile unsigned long *) 0xE0044014))
#define C1EWL          (*((volatile unsigned long *) 0xE0044018))
#define C1SR           (*((volatile unsigned long *) 0xE004401C))
#define C1RFS          (*((volatile unsigned long *) 0xE0044020))
#define C1RID          (*((volatile unsigned long *) 0xE0044024))
#define C1RDA          (*((volatile unsigned long *) 0xE0044028))
#define C1RDB          (*((volatile unsigned long *) 0xE004402C))
#define C1TFI1         (*((volatile unsigned long *) 0xE0044030))
#define C1TID1         (*((volatile unsigned long *) 0xE0044034))
#define C1TDA1         (*((volatile unsigned long *) 0xE0044038))
#define C1TDB1         (*((volatile unsigned long *) 0xE004403C))
#define C1TFI2         (*((volatile unsigned long *) 0xE0044040))
#define C1TID2         (*((volatile unsigned long *) 0xE0044044))
#define C1TDA2         (*((volatile unsigned long *) 0xE0044048))
#define C1TDB2         (*((volatile unsigned long *) 0xE004404C))
#define C1TFI3         (*((volatile unsigned long *) 0xE0044050))
#define C1TID3         (*((volatile unsigned long *) 0xE0044054))
#define C1TDA3         (*((volatile unsigned long *) 0xE0044058))
#define C1TDB3         (*((volatile unsigned long *) 0xE004405C))

/* CAN Controller 2 (CAN2) */
#define C2MOD          (*((volatile unsigned long *) 0xE0048000))
#define C2CMR          (*((volatile unsigned long *) 0xE0048004))
#define C2GSR          (*((volatile unsigned long *) 0xE0048008))
#define C2ICR          (*((volatile unsigned long *) 0xE004800C))
#define C2IER          (*((volatile unsigned long *) 0xE0048010))
#define C2BTR          (*((volatile unsigned long *) 0xE0048014))
#define C2EWL          (*((volatile unsigned long *) 0xE0048018))
#define C2SR           (*((volatile unsigned long *) 0xE004801C))
#define C2RFS          (*((volatile unsigned long *) 0xE0048020))
#define C2RID          (*((volatile unsigned long *) 0xE0048024))
#define C2RDA          (*((volatile unsigned long *) 0xE0048028))
#define C2RDB          (*((volatile unsigned long *) 0xE004802C))
#define C2TFI1         (*((volatile unsigned long *) 0xE0048030))
#define C2TID1         (*((volatile unsigned long *) 0xE0048034))
#define C2TDA1         (*((volatile unsigned long *) 0xE0048038))
#define C2TDB1         (*((volatile unsigned long *) 0xE004803C))
#define C2TFI2         (*((volatile unsigned long *) 0xE0048040))
#define C2TID2         (*((volatile unsigned long *) 0xE0048044))
#define C2TDA2         (*((volatile unsigned long *) 0xE0048048))
#define C2TDB2         (*((volatile unsigned long *) 0xE004804C))
#define C2TFI3         (*((volatile unsigned long *) 0xE0048050))
#define C2TID3         (*((volatile unsigned long *) 0xE0048054))
#define C2TDA3         (*((volatile unsigned long *) 0xE0048058))
#define C2TDB3         (*((volatile unsigned long *) 0xE004805C))

/* CAN Controller 3 (CAN3) */
#define C3MOD          (*((volatile unsigned long *) 0xE004C000))
#define C3CMR          (*((volatile unsigned long *) 0xE004C004))
#define C3GSR          (*((volatile unsigned long *) 0xE004C008))
#define C3ICR          (*((volatile unsigned long *) 0xE004C00C))
#define C3IER          (*((volatile unsigned long *) 0xE004C010))
#define C3BTR          (*((volatile unsigned long *) 0xE004C014))
#define C3EWL          (*((volatile unsigned long *) 0xE004C018))
#define C3SR           (*((volatile unsigned long *) 0xE004C01C))
#define C3RFS          (*((volatile unsigned long *) 0xE004C020))
#define C3RID          (*((volatile unsigned long *) 0xE004C024))
#define C3RDA          (*((volatile unsigned long *) 0xE004C028))
#define C3RDB          (*((volatile unsigned long *) 0xE004C02C))
#define C3TFI1         (*((volatile unsigned long *) 0xE004C030))
#define C3TID1         (*((volatile unsigned long *) 0xE004C034))
#define C3TDA1         (*((volatile unsigned long *) 0xE004C038))
#define C3TDB1         (*((volatile unsigned long *) 0xE004C03C))
#define C3TFI2         (*((volatile unsigned long *) 0xE004C040))
#define C3TID2         (*((volatile unsigned long *) 0xE004C044))
#define C3TDA2         (*((volatile unsigned long *) 0xE004C048))
#define C3TDB2         (*((volatile unsigned long *) 0xE004C04C))
#define C3TFI3         (*((volatile unsigned long *) 0xE004C050))
#define C3TID3         (*((volatile unsigned long *) 0xE004C054))
#define C3TDA3         (*((volatile unsigned long *) 0xE004C058))
#define C3TDB3         (*((volatile unsigned long *) 0xE004C05C))

/* CAN Controller 4 (CAN4) */
#define C4MOD          (*((volatile unsigned long *) 0xE0050000))
#define C4CMR          (*((volatile unsigned long *) 0xE0050004))
#define C4GSR          (*((volatile unsigned long *) 0xE0050008))
#define C4ICR          (*((volatile unsigned long *) 0xE005000C))
#define C4IER          (*((volatile unsigned long *) 0xE0050010))
#define C4BTR          (*((volatile unsigned long *) 0xE0050014))
#define C4EWL          (*((volatile unsigned long *) 0xE0050018))
#define C4SR           (*((volatile unsigned long *) 0xE005001C))
#define C4RFS          (*((volatile unsigned long *) 0xE0050020))
#define C4RID          (*((volatile unsigned long *) 0xE0050024))
#define C4RDA          (*((volatile unsigned long *) 0xE0050028))
#define C4RDB          (*((volatile unsigned long *) 0xE005002C))
#define C4TFI1         (*((volatile unsigned long *) 0xE0050030))
#define C4TID1         (*((volatile unsigned long *) 0xE0050034))
#define C4TDA1         (*((volatile unsigned long *) 0xE0050038))
#define C4TDB1         (*((volatile unsigned long *) 0xE005003C))
#define C4TFI2         (*((volatile unsigned long *) 0xE0050040))
#define C4TID2         (*((volatile unsigned long *) 0xE0050044))
#define C4TDA2         (*((volatile unsigned long *) 0xE0050048))
#define C4TDB2         (*((volatile unsigned long *) 0xE005004C))
#define C4TFI3         (*((volatile unsigned long *) 0xE0050050))
#define C4TID3         (*((volatile unsigned long *) 0xE0050054))
#define C4TDA3         (*((volatile unsigned long *) 0xE0050058))
#define C4TDB3         (*((volatile unsigned long *) 0xE005005C))

/* Watchdog */
#define WDMOD          (*((volatile unsigned long *) 0xE0000000))
#define WDTC           (*((volatile unsigned long *) 0xE0000004))
#define WDFEED         (*((volatile unsigned long *) 0xE0000008))
#define WDTV           (*((volatile unsigned long *) 0xE000000C))

#ifdef CPU_12MHZ
#define CPU_FREQ 12000
#define PLL_CONF 0x60 //P=8, M=1
#endif

#ifdef CPU_24MHZ
#define CPU_FREQ 24000
#define PLL_CONF 0x41 //P=4, M=2
#endif

#ifdef CPU_36MHZ
#define CPU_FREQ 36000
#define PLL_CONF 0x42 //P=4, M=3
#endif

#ifdef CPU_48MHZ
#define CPU_FREQ 48000
#define PLL_CONF 0x23 //P=2, M=4
#endif

#ifdef CPU_60MHZ
#define CPU_FREQ 60000
#define PLL_CONF 0x24 //P=2, M=5
#endif

#endif  // __LPC214x_H
