/*
 * dio.c
 *
 * Created: 02-10-2018 10:20:36 PM
 *  Author: New User
 */ 
#include "dio.h"

static uint8_t volatile * const portddr[NUM_PORTS] =
{
	(uint8_t*)&DDRB, (uint8_t*)&DDRC, (uint8_t*)&DDRD
};

uint8_t volatile * const portsin[NUM_PORTS] =
{
	(uint8_t*)&PINB, (uint8_t*)&PINC, (uint8_t*)&PIND,
};

uint8_t volatile * const portsout[NUM_PORTS] =
{
	(uint8_t*)&PORTB, (uint8_t*)&PORTC, (uint8_t*)&PORTD,
};

uint8_t volatile * const ptoggle[NUM_PORTS] =
{
	(uint8_t*)&PORTB, (uint8_t*)&PORTC, (uint8_t*)&PORTD
};

static uint8_t volatile * const resistor[NUM_PORTS] =
{
	(uint8_t*)&PORTB, (uint8_t*)&PORTC, (uint8_t*)&PORTD
};

void Dio_Init(DioConfig_t const * const Config)
{
	/* TODO: Define implementation */
	uint8_t i = 0; // Loop counter variable
	uint8_t number = 0; // Port Number
	uint8_t position = 0; // Pin Number
	// Loop through all pins, set the data register bit and the data direction
	// register bit according to the dio configuration table values
	for (i = 0; i < NUM_DIGITAL_PINS; i++)
	{
		number = Config[i].Channel / NUM_PINS_PER_PORT;
		position = Config[i].Channel % NUM_PINS_PER_PORT;


		//printf("Number: %d\n", number);
		//printf("Position: %d\n", position);
		//printf("Channel: %d\n", Config[i].Channel);
		////printf("Resistor: %d\n", Config[i].Resistor);
		//printf("Direction: %d\n\n", Config[i].Direction);

		
		if (Config[i].Direction == OUTPUT)
		{
			*portddr[number] |= (1UL << (position));
		}
		else
		{
			*portddr[number] &= ~(1UL << (position));
		}
		
	}
}

DioPinState_t Dio_ChannelRead(DioChannel_t const Channel)
{
	/* Read the port associated with the desired pin */
	DioPinState_t PortState = (DioPinState_t)*portsin[Channel/NUM_PINS_PER_PORT];

	/* Determine which bit in the port is assocaited with this channel */
	DioPinState_t PinMask = (DioPinState_t)(1UL<<(Channel%NUM_PINS_PER_PORT));

	/* Mask the port state with the pin and return the DioPinState */
	return (( PortState & PinMask) ? DIO_HIGH : DIO_LOW);
}

void Dio_ChannelWrite(DioChannel_t const Channel, DioPinState_t const State)
{
	if (State == DIO_HIGH)
	{
		*portsout[Channel/NUM_PINS_PER_PORT] |= (1UL<<(Channel%NUM_PINS_PER_PORT));
	}
	else
	{
		*portsout[Channel/NUM_PINS_PER_PORT] &= ~ (1UL<<(Channel%NUM_PINS_PER_PORT));
	}
}

void Dio_ChannelToggle(DioChannel_t const Channel)
{
	*ptoggle[Channel/NUM_PINS_PER_PORT] ^= (1UL<<(Channel%NUM_PINS_PER_PORT));
}

void Dio_ChannelDirectionSet(DioChannel_t const Channel, PinModeEnum_t const Mode)
{
	uint8_t Number = 0;                     // Port Number
	uint8_t Position = 0;                   // Pin Number

	// Calculate the register and channel that needs to be changed.
	Number   = Channel / NUM_PINS_PER_PORT;
	Position = Channel % NUM_PINS_PER_PORT;

	// Set the Data Direction register bit for this channel
	if(Mode == OUTPUT)
	{
		*portddr[Number] |= (1UL<<(Position));
	}
	else
	{
		*portddr[Number] &= ~(1UL<<(Position));
	}
}

void Dio_ChannelResistor(DioChannel_t const Channel, DioResistor_t const Resistor)
{
	uint8_t number = 0;
	uint8_t position = 0;
	
	number = Channel / NUM_PINS_PER_PORT;
	position = Channel % NUM_PINS_PER_PORT;
	
	if(Resistor == DIO_PULLUP_ENABLED)
	{
		*resistor[number] |= (1UL << position);
	}
	else
	{
		*resistor[number] &= ~(1UL << position);
	}
}

void Dio_RegisterWrite(uint8_t const Address, uint8_t const Value)
{
	uint8_t volatile * const RegisterPointer = (uint8_t *) Address;
	
	*RegisterPointer = Value;
}

uint8_t Dio_RegisterRead(uint8_t const Address)
{
	uint8_t volatile * const RegisterPointer = (uint8_t *) Address;
	
	return *RegisterPointer;
}

