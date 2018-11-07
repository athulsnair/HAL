/*
 * dio_cfg.h
 *
 * Created: 01-10-2018 06:10:54 PM
 *  Author: New User
 */ 


#ifndef DIO_CFG_H_
#define DIO_CFG_H_

//#include "constants.h"

#define NUM_DIGITAL_PINS 24
#define NUM_PINS_PER_PORT 8
#define NUM_PORTS 3

/*
typedef enum 
{
    OFF = 0U,		
    ON = 1U		 
}OnOff_t;


typedef enum
{
    DISABLED = 0U,	
    ENABLED = 1U,	
    FALSE = 0U,		
    TRUE = 1U		
}LogicEnum_t;

typedef enum
{
	OUTPUT = 0x0U,	
	INPUT = 0x1U	
}PinModeEnum_t;
*/

typedef enum
{
	/* TODO: Populate this list based on available MCU pins */
	PORT1_0,              /**< PORT1_0 */
	PORT1_1,              /**< PORT1_1 */
	PORT1_2,	             /**< PORT1_2 */
	PORT1_3,	             /**< PORT1_3 */
	PORT1_4,	             /**< PORT1_4 */
	PORT1_5,	             /**< PORT1_5 */
	PORT1_6,	             /**< PORT1_6 */
	PORT1_7,	             /**< PORT1_7 */
	PORT2_0,
	PORT2_1,
	PORT2_2,
	PORT2_3,
	PORT2_4,
	PORT2_5,
	PORT2_6,
	PORT2_7,
	PORT3_0,
	PORT3_1,
	PORT3_2,
	PORT3_3,
	PORT3_4,
	PORT3_5,
	PORT3_6,
	PORT3_7,
}DioChannel_t;

typedef enum
{
	DIO_LOW,             /** Defines digital state ground */
	DIO_HIGH,            /** Defines digital state power */
	DIO_PIN_STATE_MAX	   /** Defines the maximum digital state */
}DioPinState_t;

typedef enum
{
	DIO_PULLUP_DISABLED,     /*< Used to disable the internal pull-ups */
	DIO_PULLUP_ENABLED,      /*< Used to enable the internal pull-ups */
	DIO_MAX_RESISTOR	        /*< Resistor states should be below this value */
}DioResistor_t;

typedef enum
{
	DIO_OUTPUT,
	DIO_INPUT
}DioDirection_t;

typedef struct
{
	DioChannel_t Channel;
	DioResistor_t Resistor;   //int a;
	DioDirection_t Direction; //int b;
	//                                   a  b
	}DioConfig_t;                 //DIoConfig_t conf[]  = { {2, 3}, {5, 6} }; ==> DIoConfig_t conf[0] = {2, 3}

	//                                   a  b
	//            DIoConfig_t conf[1] = {5, 6}

DioConfig_t const * const Dio_ConfigGet(void);

#endif /* DIO_CFG_H_ */