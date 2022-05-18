#include <stdint.h>
#include "main.h"
#include "error.h"


#define BYTE_BUFLEN 	 1
#define LINE_BUFLEN 	 1024
#define CARRIAGE_RETURN  13 /* carriage return char \r */
#define LINE_FEED 		 10 /* linefeed char \n		   */

typedef struct
{
	uint8_t byte_buffer_rx[BYTE_BUFLEN];	// Store the rx byte from the USART2
	char line_rx_buffer[LINE_BUFLEN];		// Buffer to hold all the bytes from rx USART2
	int msglen;
	volatile int char_counter;				// Counter for line_rx_buffer
	char command_execute_flag;				/* Set = whole transmission is received, ready for processing \
											   Reset = still receiving*/
}input_vars;

extern input_vars input;

void FL_UART_Init();
void FL_Parser();
