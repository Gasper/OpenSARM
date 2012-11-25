#define UART_0 0
#define UART_1 1
#define DLAB 7

#define THRE 5
#define RDR 0

#define ONE_STOP_BIT 1
#define TWO_STOP_BITS 2

#define PARITY_ENABLE 1
#define PARITY_DISABLE 0
#define ODD_PARITY 0
#define EVEN_PARITY 1
#define FORCED_1_STICK_PARITY 2
#define FORCED_0_STICK_PARITY 3

void uart_init(unsigned char uart_number, unsigned int baud_rate, unsigned char number_of_bits, unsigned char stop_bits, unsigned char parity_enable, unsigned char parity);
unsigned char put_char(unsigned char uart_number, char c);
char get_char(unsigned char uart_number);
unsigned char putstring(unsigned char uart_number, char *string, unsigned int string_length);
unsigned char put_s(unsigned char uart_number, char *string);








