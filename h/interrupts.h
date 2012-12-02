
#ifndef INT_H_INCLUDED
#define INT_H_INCLUDED

#define WDT 0
#define ARMCore0 2
#define ARMCore1 3
#define TIMER0 4
#define TIMER1 5
#define UART0 6
#define UART1 7
#define PWM 8
#define I2C0 9
#define SPI0 10
#define SSP 11
#define PLL 12
#define RTC 13
#define EINT0 14
#define EINT1 15
#define EINT2 16
#define EINT3 17
#define AD0 18
#define I2C1 19
#define BOD 20
#define AD1 21
#define USB 22
#define IRQslot_en 0x20

#define PWMMR0_INT 0
#define PWMMR1_INT 1
#define PWMMR2_INT 2
#define PWMMR3_INT 3
#define PWMMR4_INT 8
#define PWMMR5_INT 9
#define PWMMR6_INT 10

#define MR0_INT 0
#define MR1_INT 1
#define MR2_INT 2
#define MR3_INT 3
#define CR0_INT 4
#define CR1_INT 5
#define CR2_INT 6
#define CR3_INT 7

#define RTCCIF 0
#define RTCALF 1

#define SPI_IF 7
#define RORIC 0
#define RTIC 1
#define SIC 3

void set_interrupt(unsigned char interrupt, unsigned char set);
void interrupt_fiq(unsigned char interrupt);
unsigned char interrupt_fiq_status(unsigned char interrupt);
unsigned char interrupt_irq_status(unsigned char interrupt);
void interrupt_priorities(void);
void interrupt_addresses(void);

/*
 To je tista zadevščina(prototipi prekinitvenih rutin), ki prevajalniku dopove, da ima opravka s prekinitvami
*/
void TIMER0_ISR (void)   __attribute__((interrupt("IRQ")));
void TIMER1_ISR (void)   __attribute__((interrupt("IRQ")));
void PWM_ISR (void)   __attribute__((interrupt("IRQ")));
void AD1_ISR (void)   __attribute__((interrupt("IRQ")));
void SPI0_ISR (void)   __attribute__((interrupt("IRQ")));
void SSP_ISR (void)   __attribute__((interrupt("IRQ")));
void I2C0_ISR (void)   __attribute__((interrupt("IRQ")));
void I2C1_ISR (void)   __attribute__((interrupt("IRQ")));
void RTC_ISR (void)   __attribute__((interrupt("IRQ")));
void UART0_ISR (void)   __attribute__((interrupt("IRQ")));
void UART1_ISR (void)   __attribute__((interrupt("IRQ")));
void AD0_ISR (void)   __attribute__((interrupt("IRQ")));
void PLL_ISR (void)   __attribute__((interrupt("IRQ")));
void BOD_ISR (void)   __attribute__((interrupt("IRQ")));
void EINT1_ISR (void)   __attribute__((interrupt("IRQ")));
void EINT2_ISR (void)   __attribute__((interrupt("IRQ")));

#ifdef ONLY_USED
#include "interrupts.c"
#endif

#endif
