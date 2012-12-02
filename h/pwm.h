
#ifndef PWM_H_INCLUDED
#define PWN_H_INCLUDED

//stanja števca
#define STOP_COUNTER 0x00
#define START_COUNTER 0x01
#define RESET_COUNTER 0x02

#define VHOD	0x00
#define IZHOD	0x01

#define PIN0	0x00
#define PIN1	0x01
#define PIN2	0x02
#define PIN3	0x03
#define PIN4	0x04
#define PIN5	0x05
#define PIN6	0x06
#define PIN7	0x07
#define PIN8	0x08
#define PIN9	0x09
#define PIN10	0x0A
#define PIN11	0x0B
#define PIN12	0x0C
#define PIN13	0x0D
#define PIN14	0x0E
#define PIN15	0x0F
#define PIN16	0x10
#define PIN17	0x11
#define PIN18	0x12
#define PIN19	0x13
#define PIN20	0x14
#define PIN21	0x15
#define PIN22	0x16
#define PIN23	0x17
#define PIN24	0x18
#define PIN25	0x19
#define PIN26	0x1A
#define PIN27	0x1B
#define PIN28	0x1C
#define PIN29	0x1D
#define PIN30	0x1E
#define PIN31	0x1F

#define COUNTER_ENABLE 0
#define PWM_ENABLE 3
#define COUNTER_RESET 1

#define PWM0 	0
#define PWM1 	1
#define PWM2 	2
#define PWM3 	3
#define PWM4 	4
#define PWM5 	5
#define PWM6 	6

#define VKLOP 	1
#define IZKLOP 	0

#define PWMMR0I	0
#define PWMMR0R 1
#define PWMMR0S 2
#define PWMMR1I 3
#define PWMMR1R 4
#define PWMMR1S 5
#define PWMMR2I 6
#define PWMMR2R 7
#define PWMMR2S 8
#define PWMMR3I 9
#define PWMMR3R 10
#define PWMMR3S 11
#define PWMMR4I 12
#define PWMMR4R 13
#define PWMMR4S 14
#define PWMMR5I 15
#define PWMMR5R 16
#define PWMMR5S 17
#define PWMMR6I 18
#define PWMMR6R 19
#define PWMMR6S 20

#define PWMENA1 9
#define PWMENA2 10
#define PWMENA3 11
#define PWMENA4 12
#define PWMENA5 13
#define PWMENA6 14

#define PWMSEL2	2
#define PWMSEL3	3
#define PWMSEL4	4
#define PWMSEL5	5
#define PWMSEL6	6

#define FUN_0	0
#define FUN_1	1
#define FUN_2	2
#define FUN_3	3

#define PREKINITEV	1
#define USTAVITEV	2
#define PONASTAVITEV	4

#define DELEZ 		100

#define PWMSEL2 	2
#define PWMSEL3 	3
#define PWMSEL4 	4
#define PWMSEL5 	5
#define PWMSEL6 	6

#define KANAL1_3_5	1
#define KANAL2_4_6	2



void Casovnik_Stanje(unsigned char stanje);
void PWM_NastaviFrekvenco(unsigned int frekvenca);
unsigned char PWM_NastaviKanal(unsigned char kanal/*od PWM1-PWM6*/, unsigned char prevajalno_razmerje/*od 0-100%*/, unsigned char vklop/*0 ali 1->vklop ali izklop posameznega kanala*/);
void PWM_PonastaviPrekinitev(unsigned char kanal);
void PWM_NastaviDogodek(unsigned char kanal, unsigned char dogodek);

#ifdef ONLY_USED
#include "pwm.c"
#endif

#endif
