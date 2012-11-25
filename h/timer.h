
#define	COUNTER	0
#define TIMER	1
#define	COUNTER_RESET	1
#define	COUNTER_ENABLE	0
//counter_mode:
#define COUNT_ON_RISING_EDGE	1
#define COUNT_ON_FALLING_EDGE	2
#define COUNT_ON_BOTH_EDGES	3
#define	COUNT_INPUT_SELECT	2
//counter_clk_source:
#define	CAPn_0			0
#define	CAPn_1			1
#define	CAPn_2			2
#define	CAPn_3			3

#define TC0	0
#define TC1	1

#define MR0_IF 	0
#define MR1_IF 	1
#define MR2_IF 	2
#define MR3_IF 	3
#define CR0_IF 	4
#define CR1_IF 	5
#define CR2_IF 	6
#define CR3_IF 	7

#define MR0	0
#define MR1	1
#define MR2	2
#define MR3	3

#define CR0	0
#define CR1	1
#define CR2	2
#define CR3	3

#define CRx_0	0
#define CRx_1	1
#define CRx_2	2
#define CRx_3	3

#define INTERRUPT_ON_MATCH	1
#define RESET_ON_MATCH		2
#define STOP_ON_MATCH		4

#define CAPTURE_ON_RISING_EDGE	1
#define CAPTURE_ON_FALLING_EDGE	2
#define INTERRUPT_ON_CAPTURE	4


#define NO_RESET 0
#define RESET 	 1


#define FUN_0	0
#define FUN_1	1
#define FUN_2	2
#define FUN_3	3


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


unsigned char tc_init(unsigned char tc_number, unsigned char timer_counter, unsigned int frequency, unsigned char counter_clk_source, unsigned char counter_mode);
void tc_state(unsigned char TC_number, unsigned char state);
void delay_ms(unsigned char TC_number, unsigned int mili_sec, unsigned char reset);
char tc_get_interrupt_status(unsigned char TC_number, unsigned char flag_num);
char tc_set_match_register(unsigned char TC_number, unsigned char register_number, unsigned int value);
char tc_set_match_control(unsigned char TC_number, unsigned char register_number, unsigned char match_mode);
unsigned int tc_get_capture_value(unsigned char TC_number, unsigned char register_number);
char tc_set_capture_control(unsigned char TC_number, unsigned char register_number, unsigned char capture_mode);
char tc_io_capture_config(unsigned char TC_number, unsigned char register_number, unsigned char capture_pin_num);
