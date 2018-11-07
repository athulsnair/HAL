//#define F_CPU 16000000UL

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dio.h"

/*
Dio_Init(<pointer from configuration table>) ==> To set GPIO pins based on the configuration table "config" found in dio_cfg.c
												 Takes parameter as the address of the first element of 
												 configuration table.
												 
Dio_ConfigGet() ==> returns the the address of the first element of configuration table "config" found in dio_cfg.c. Return value is passed as parameter for Dio_Init() function

						eg: const DioConfig_t *DioConfig = Dio_ConfigGet();
							Dio_Init(DioConfig);

Dio_ChannelDirectionSet(channel, direction) ==> to set direction of GPIO pin
						channel   : PORT1_x, PORT2_x, PORT3_x,  refer DioChannel_t in dio_cfg.h
						direction : OUTPUT / INPUT,   refer PinModeEnum_t in constants.h
						
						eg: Dio_ChannelDirectionSet(PORT3_5, OUTPUT);

Dio_ChannelWrite(channel, state) ==> Set a pin HIGH or LOW
						channel : PORT1_x, PORT2_x, PORT3_x,  refer DioChannel_t in dio_cfg.h
						state   : HIGH / LOW,   refer PinLevelEnum_t in dio_cfg.h
						
						NOTE: Channel should be set as OUTPUT
						
						eg: Dio_ChannelWrite(PORT3_5, HIGH);

Dio_ChannelToggle(channel) ==> Toggle state of a pin i.e., inverse previous state
						channel : PORT1_x, PORT2_x, PORT3_x,  refer DioChannel_t in dio_cfg.h
						
						NOTE: Channel should be set as OUTPUT
						
						eg: Dio_ChannelToggle(PORT1_2);
						
Dio_ChannelRead(channel) ==> Read current state of channel. Return 1(DIO_HIGH) or 0(DIO_LOW) for HIGH and LOW
						channel : PORT1_x, PORT2_x, PORT3_x,  refer DioChannel_t in dio_cfg.h
						
						NOTE: If a channel is not set as OUTBUT, then by default that channel is INPUT
						Dio_ChannelDirectionSet() can be used to explicitely to set a pin as INPUT, Do this to ensure channel is set as INPUT
						
						eg: Dio_ChannelRead(PORT1_0)
						
Dio_ChannelResistor(channel, sate) ==> Enable internal pull-up resistor
						channel : PORT1_x, PORT2_x, PORT3_x,  refer DioChannel_t in dio_cfg.h
						state   : ENABLED / DISABLED,   refer PinLevelEnum_t in constants.h

						NOTE: When a pin is set as INPUT, to avoid floating of when pin when button is pressed either use external pull-up/pull-down
						resistor or use internal pull-up resistor

						eg: Dio_ChannelResistor(PORT1_0, ENABLED)
						

*/

//static uint8_t volatile * const bbbb = (uint8_t*)&PORTB;

int main()
{
    
	//const DioConfig_t *DioConfig = Dio_ConfigGet();
	//Dio_Init(DioConfig);
	
	//DDRB = 0XFF;
	
	
	Dio_ChannelDirectionSet(PORT1_4, OUTPUT);
	//PORTB = 0XFF;
	while(1)
	{
		
		//Dio_ChannelToggle(PORT1_2);
		//Dio_ChannelToggle(PORT1_3);
		//Dio_ChannelToggle(PORT1_4);
		Dio_ChannelWrite(PORT1_4, HIGH);
		//PORTB |= 0b00100000;
		//*bbbb |= (1UL << (4));
		_delay_ms(1000);
		//Dio_ChannelToggle(PORT1_2);
		//Dio_ChannelToggle(PORT1_3);
		//Dio_ChannelToggle(PORT1_4);
		Dio_ChannelWrite(PORT1_4, LOW);
		//PORTB = 0b00000000;
		//*bbbb &= ~(1UL << (4));
		_delay_ms(1000);
		
		/*
		if(Dio_ChannelRead(PORT1_0))
		{
			Dio_ChannelWrite(PORT3_5, DIO_HIGH);
		}
		else
		{
			Dio_ChannelWrite(PORT3_5, DIO_LOW);
		}
		*/
	}

    return 0;
}
