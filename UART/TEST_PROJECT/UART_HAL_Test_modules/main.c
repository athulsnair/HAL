/*
 * UART_HAL_Test.c
 *
 * Created: 17-10-2018 04:11:39 PM
 * Author : New User
 */ 

#include "uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

//#define F_CPU 16000000UL
// Serial baud rate
#define BAUD_RATE 9600

#define RX_BUFFER_SIZE 128
#define TX_BUFFER_SIZE 64

#define SERIAL_RX     USART_RX_vect
#define SERIAL_UDRE   USART_UDRE_vect

#define GRBL_PLATFORM "Atmega328p"

#define CPU_MAP_ATMEGA328P // Arduino Uno CPU

// Define realtime command special characters. These characters are 'picked-off' directly from the
// serial read data stream and are not passed to the grbl line execution parser. Select characters
// that do not and must not exist in the streamed g-code program. ASCII control characters may be
// used, if they are available per user setup. Also, extended ASCII codes (>127), which are never in
// g-code programs, maybe selected for interface programs.
// NOTE: If changed, manually update help message in report.c.
#define CMD_STATUS_REPORT '?'
#define CMD_FEED_HOLD '!'
#define CMD_CYCLE_START '~'
#define CMD_RESET 0x18 // ctrl-x.
#define CMD_SAFETY_DOOR '@'

// Define system executor bit map. Used internally by realtime protocol as realtime command flags,
// which notifies the main program to execute the specified realtime command asynchronously.
// NOTE: The system executor uses an unsigned 8-bit volatile variable (8 flag limit.) The default
// flags are always false, so the realtime protocol only needs to check for a non-zero value to
// know when there is a realtime command to execute.

#define EXEC_STATUS_REPORT  bit(0) // bitmask 00000001
#define EXEC_CYCLE_START    bit(1) // bitmask 00000010
#define EXEC_CYCLE_STOP     bit(2) // bitmask 00000100
#define EXEC_FEED_HOLD      bit(3) // bitmask 00001000
#define EXEC_RESET          bit(4) // bitmask 00010000
#define EXEC_SAFETY_DOOR    bit(5) // bitmask 00100000
#define EXEC_MOTION_CANCEL  bit(6) // bitmask 01000000

// Bit field and masking macros
#define bit(n) (1 << n)
#define bit_true_atomic(x,mask) {uint8_t sreg = SREG; cli(); (x) |= (mask); SREG = sreg; }
#define bit_false_atomic(x,mask) {uint8_t sreg = SREG; cli(); (x) &= ~(mask); SREG = sreg; }
#define bit_toggle_atomic(x,mask) {uint8_t sreg = SREG; cli(); (x) ^= (mask); SREG = sreg; }
#define bit_true(x,mask) (x) |= (mask)
#define bit_false(x,mask) (x) &= ~(mask)
#define bit_istrue(x,mask) ((x & mask) != 0)
#define bit_isfalse(x,mask) ((x & mask) == 0)

#define __ATTR_PROGMEM__ __attribute__((__progmem__))
#define PROGMEM __ATTR_PROGMEM__

# define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
#define GRBL_VERSION "0.9j"

#define __LPM(addr)         __LPM_enhanced__(addr)
#define pgm_read_byte_near(address_short) __LPM((uint16_t)(address_short))

#define SERIAL_NO_DATA 0xff

volatile uint8_t sys_probe_state;   // Probing state value.  Used to coordinate the probing cycle with stepper ISR.
volatile uint8_t sys_rt_exec_state;  // Global realtime executor bitflag variable for state management. See EXEC bitmasks.
volatile uint8_t sys_rt_exec_alarm;  // Global realtime executor bitflag variable for setting various alarms.


uint8_t serial_rx_buffer[RX_BUFFER_SIZE];
uint8_t serial_rx_buffer_head = 0;
volatile uint8_t serial_rx_buffer_tail = 0;

uint8_t serial_tx_buffer[TX_BUFFER_SIZE];
uint8_t serial_tx_buffer_head = 0;
volatile uint8_t serial_tx_buffer_tail = 0;

// Writes one byte to the TX serial buffer. Called by main program.
// TODO: Check if we can speed this up for writing strings, rather than single bytes.
void serial_write(uint8_t data) {
	
  // Calculate next head
  uint8_t next_head = serial_tx_buffer_head + 1;
  if (next_head == TX_BUFFER_SIZE) { next_head = 0; }

  // Wait until there is space in the buffer
  while (next_head == serial_tx_buffer_tail) { 
    // TODO: Restructure st_prep_buffer() calls to be executed here during a long print.    
    if (sys_rt_exec_state & EXEC_RESET) { return; } // Only check for abort to avoid an endless loop.
  }

  // Store data and advance head
  serial_tx_buffer[serial_tx_buffer_head] = data;
  //UDR0 = serial_tx_buffer[serial_tx_buffer_head];
  //loop_until_bit_is_set(UCSR0A, UDRE0);
  serial_tx_buffer_head = next_head;
  
  // Enable Data Register Empty Interrupt to make sure tx-streaming is running
  //UCSR0B |=  (1 << UDRIE0); 
  Uart_interruptTrigger(UART_0, DATA_READY);
  
}


// Data Register Empty Interrupt handler
ISR(SERIAL_UDRE)
{
  uint8_t tail = serial_tx_buffer_tail; // Temporary serial_tx_buffer_tail (to optimize for volatile)
  /*
  #ifdef ENABLE_XONXOFF
    if (flow_ctrl == SEND_XOFF) { 
      UDR0 = XOFF_CHAR; 
      flow_ctrl = XOFF_SENT; 
    } else if (flow_ctrl == SEND_XON) { 
      UDR0 = XON_CHAR; 
      flow_ctrl = XON_SENT; 
    } else
  #endif*/
  { 
    // Send a byte from the buffer	
    UDR0 = serial_tx_buffer[tail];
  
    // Update tail position
    tail++;
    if (tail == TX_BUFFER_SIZE) { tail = 0; }
  
    serial_tx_buffer_tail = tail;
  }
  
  // Turn off Data Register Empty Interrupt to stop tx-streaming if this concludes the transfer
  if (tail == serial_tx_buffer_head) { 
	  //UCSR0B &= ~(1 << UDRIE0);
	   Uart_interruptClear(UART_0, DATA_READY);
  }
}

uint8_t serial_read()
{
	uint8_t tail = serial_rx_buffer_tail; // Temporary serial_rx_buffer_tail (to optimize for volatile)
	
	if (serial_rx_buffer_head == tail) {
		return SERIAL_NO_DATA;
		} else {
		uint8_t data = serial_rx_buffer[tail];
		
		tail++;
		if (tail == RX_BUFFER_SIZE) { tail = 0; }
		serial_rx_buffer_tail = tail;
		return data;
		
	}
}

ISR(SERIAL_RX)
{
  uint8_t data = UDR0;
  uint8_t next_head;
  
  // Pick off realtime command characters directly from the serial stream. These characters are
  // not passed into the buffer, but these set system state flag bits for realtime execution.
  switch (data) {
    //case CMD_STATUS_REPORT: bit_true_atomic(sys_rt_exec_state, EXEC_STATUS_REPORT); break; // Set as true
   // case CMD_CYCLE_START:   bit_true_atomic(sys_rt_exec_state, EXEC_CYCLE_START); break; // Set as true
    //case CMD_FEED_HOLD:     bit_true_atomic(sys_rt_exec_state, EXEC_FEED_HOLD); break; // Set as true
    //case CMD_SAFETY_DOOR:   bit_true_atomic(sys_rt_exec_state, EXEC_SAFETY_DOOR); break; // Set as true
    //case CMD_RESET:         mc_reset(); break; // Call motion control reset routine.
    default: // Write character to buffer    
      next_head = serial_rx_buffer_head + 1;
      if (next_head == RX_BUFFER_SIZE) { next_head = 0; }
    
      // Write data to buffer unless it is full.
      if (next_head != serial_rx_buffer_tail) {
        serial_rx_buffer[serial_rx_buffer_head] = data;
        serial_rx_buffer_head = next_head;    
        /*
        #ifdef ENABLE_XONXOFF
          if ((serial_get_rx_buffer_count() >= RX_BUFFER_FULL) && flow_ctrl == XON_SENT) {
            flow_ctrl = SEND_XOFF;
            UCSR0B |=  (1 << UDRIE0); // Force TX
          } 
        #endif
        */
      }
      //TODO: else alarm on overflow?
  }
}


void serial_reset_read_buffer() 
{
  serial_rx_buffer_tail = serial_rx_buffer_head;
/*
  #ifdef ENABLE_XONXOFF
    flow_ctrl = XON_SENT;
  #endif
  */
}

void printString(const char *s)
{
	while (*s)
	serial_write(*s++);
}

// Print a string stored in PGM-memory
void printPgmString(const char *s)
{
	char c;
	while ((c = pgm_read_byte_near(s++)))
	serial_write(c);
}

// Welcome message
void report_init_message()
{
	printPgmString(PSTR("\r\nGrbl " GRBL_VERSION " ['$' for help]\r\n"));
}

int main(void)
{
    /*Initialize uart*/
	//serial_init();
	const UartConfig_t *UartConfig = Uart_ConfigGet();
	Uart_Init(UartConfig);
	Uart_interruptTrigger(UART_0, RECEIVE);
	
	/*Test*/
	uint8_t *p = "Hello\r\n";
	
	//printString1(p);

	/*set (global) interrupt enable bit*/
	//sei();

	/*Set PORTB pins as output*/
	//DDRB = 0XFF;
	//uint8_t data = serial_read();
	//UDR0 = data;
	//loop_until_bit_is_set(UCSR0A, UDRE0);
	
	uint8_t c;
	printString("Hai GRBL v0.9j Build 1\r\n");
	
    while (1)
    {
		/*Toggle PORTB pins*/
		/*PORTB = 0XFF;
		_delay_ms(100);
		PORTB = 0X00;
		_delay_ms(100);*/
		while((c = serial_read()) != SERIAL_NO_DATA)
		{
			UDR0 = c;
			loop_until_bit_is_set(UCSR0A, UDRE0);
			printString("\r\nOK>\r\n");
		}
   }
}

