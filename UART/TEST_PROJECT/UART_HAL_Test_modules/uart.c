/*
 * uart.c
 *
 * Created: 23-10-2018 11:11:01 AM
 *  Author: New User
 */ 
#include "uart.h"
#include <avr/common.h>

/**
 *  Defines a pointer to the controller status register.
 */
static uint8_t volatile * const status = (uint8_t*)&SREG;

/**
 *  Defines a table of pointers to the uart control & status 0 registers on the microcontroller.
 */
static uint8_t volatile * const uartctlstat1[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UCSR0A
};

/**
 *  Defines a table of pointers to the uart control & status 1 registers on the microcontroller.
 */
static uint8_t volatile * const uartctlstat2[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UCSR0B
};

/**
 *  Defines a table of pointers to the uart control & status 2 registers on the microcontroller.
 */
static uint8_t volatile * const uartctlstat3[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UCSR0C
};


/**
 *  Defines a table of pointers to the uart receive buffer on the microcontroller.
 */
static uint8_t volatile * const uartrx[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UDR0
};

/**
 *  Defines a table of pointers to the uart transmit buffer on the microcontroller.
 */
static uint8_t volatile * const uarttx[NUM_UART_CHANNELS] =
{
  	(uint8_t*)&UDR0
};

void Uart_Init(UartConfig_t const * const Config)
{
	uint8_t i = 0;
	for(i = 0; i < NUM_UART_CHANNELS; i++) {
		
		/************************************************************************/
		/*  ENABLE / DISABLE uart                                                                    */
		/************************************************************************/

		if(Config[i].UartEnable == ENABLED) {
			
			*uartctlstat2[i] |= (REGBIT3 | REGBIT4);
		}
		else {
			*uartctlstat2[i] &= ~(REGBIT3 | REGBIT4);
		}
		
		/************************************************************************/
		/* Data length 8 bit / 9 bit                                                                     */
		/************************************************************************/
		
		if(Config[i].DataLength == BITS_EIGHT) {
			
			*uartctlstat3[i] &= ~(REGBIT0 | REGBIT1); //UCSR0C |= ((1 << UCSZ00) | (1 << UCSZ01));
			*uartctlstat2[i] &= ~REGBIT2;
			
			*uartctlstat3[i] |= (REGBIT0 | REGBIT1);
		}
		else if(Config[i].DataLength == BITS_NINE) {
			
			*uartctlstat3[i] |= (REGBIT0 | REGBIT1);
			*uartctlstat2[i] |= REGBIT2;
		}
		
		if(Config[i].IntEnable == ENABLED) {
			*status |= REGBIT7;			//Same as sei() or SREG |= (1 << 7); ==> SREG is found in <avr/common.h>
		}
		
		/************************************************************************/
		/* Baud rate set                                                                     */
		/************************************************************************/
		uint16_t UBRR0_value;
		
		if(Config[i].BaudRate >= 9600) {
			UBRR0_value = ((F_CPU / (4L * Config[i].BaudRate)) - 1)/2;
			*uartctlstat1[i] |= (REGBIT1);
		}
		else {
			UBRR0_value = ((F_CPU / (8L * Config[i].BaudRate)) - 1)/2 ;
			*uartctlstat1[i] &= ~(REGBIT1);
		}
		
		UBRR0H = UBRR0_value >> 8;
		UBRR0L = UBRR0_value;
	}
	
}


void Uart_ParitySet(UartChannel_t const Channel, UartConfig_t const * const Config)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Config[Channel].ParityType == ODD) {
		
		*uartctlstat3[number] |= (REGBIT4 | REGBIT5);
	}
	else if(Config[Channel].ParityType == EVEN) {
		
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
		*uartctlstat3[number] |= REGBIT5;
	}
	else {
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
	}
}

/************************************************************************/
/* I defined it                                                                     */
/************************************************************************/

void Uart_ParityChange(UartChannel_t const Channel, UartParity_t Parity)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Parity == ODD) {
		
		*uartctlstat3[number] |= (REGBIT4 | REGBIT5);
	}
	else if(Parity == EVEN) {
		
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
		*uartctlstat3[number] |= REGBIT5;
	}
	else {
		*uartctlstat3[number] &= ~(REGBIT4 | REGBIT5);
	}
}

void Uart_IsrModeSet(UartChannel_t const Channel, UartConfig_t const * const Config)
{

}

void Uart_BaudRateSet(UartChannel_t const Channel, UartConfig_t const * const Config)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	uint16_t UBRR0_value;
	
	if(Config[Channel].BaudRate >= 9600) {
		UBRR0_value = ((F_CPU / (4L * Config[Channel].BaudRate)) - 1)/2;
		*uartctlstat1[number] |= (REGBIT1);
	}
	else {
		UBRR0_value = ((F_CPU / (8L * Config[Channel].BaudRate)) - 1)/2 ;
		*uartctlstat1[number] &= ~(REGBIT1);
	}
	
	UBRR0H = UBRR0_value >> 8;
	UBRR0L = UBRR0_value;
}

/************************************************************************/
/* I created this                                                                     */
/************************************************************************/
void Uart_BaudRateChange(UartChannel_t const Channel, uint16_t Baudrate)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	uint16_t UBRR0_value;
	
	if(Baudrate >= 9600) {
		UBRR0_value = ((F_CPU / (4L * Baudrate)) - 1)/2;
		*uartctlstat1[number] |= (REGBIT1);
	}
	else {
		UBRR0_value = ((F_CPU / (8L * Baudrate)) - 1)/2 ;
		*uartctlstat1[number] &= ~(REGBIT1);
	}
	
	UBRR0H = UBRR0_value >> 8;
	UBRR0L = UBRR0_value;
}

uint8_t Uart_CharGet(UartChannel_t const Channel)
{
	uint8_t Temp;

	Temp = *uartrx[Channel];
	
	return Temp;
}

uint8_t Uart_IsDataPresent(UartChannel_t const Channel)
{
	// Mask for the uart receive interrupt flag
	// If interrupt flag is set, return true
	// Else, return false
	
	if((*uartctlstat1[Channel] & (1 << RX)) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void Uart_CharPut(UartChannel_t const Channel, char const Ch)
{
	char *ptr = &Ch;
	if (0x0a==Ch)
	{
		//Ch = 0x0d;
		*ptr = 0x0d;
	}

	// Send one byte to the UxTXREG of the specified channel
	*uarttx[Channel] = Ch;
	while(!(*uartctlstat1[UART_0] & (1 << TX)));

	// Mask for UCBUSY bit in UCAxSTAT register
	// If UCBUSY == 1, transmit is not completed
	// Wait for transmition to finish
	//    while((*uartstat[Channel] & REGBIT0) == 1);
}

uint8_t Uart_IsTransmitComplete(UartChannel_t const Channel)
{
	// Mask for the uart receive interrupt flag
	// If interrupt flag is set, return true
	// Else, return false
	
	if((*uartctlstat1[Channel] & (1 << TX)) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Uart_interruptTrigger(UartChannel_t Channel, Uart_interrupt Trigger)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Trigger == RECEIVE)
	{
		*uartctlstat2[number] |= (REGBIT7);
	}
	else if(Trigger == TRANSMIT)
	{
		*uartctlstat2[number] |= (REGBIT6);
	}
	else if(Trigger == DATA_READY)
	{
		*uartctlstat2[number] |= (REGBIT5);
	}
}

void Uart_interruptClear(UartChannel_t Channel, Uart_interrupt Trigger)
{
	uint8_t number = Channel % NUM_UART_CHANNELS;
	
	if(Trigger == RECEIVE)
	{
		*uartctlstat2[number] &= ~(REGBIT7);
	}
	else if(Trigger == TRANSMIT)
	{
		*uartctlstat2[number] &= ~(REGBIT6);
	}
	else if(Trigger == DATA_READY)
	{
		*uartctlstat2[number] &= ~(REGBIT5);
	}
}
