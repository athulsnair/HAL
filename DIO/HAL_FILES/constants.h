/****************************************************************************
* Title                 :   Constants
* Filename              :   constants.h
* Author                :   Jacob W Beningo
* Origin Date           :   04/16/2015
* Version               :   1.0.0
* Compiler              :   TBD
* Target                :   TBD
* Copyright             :   BENINGO EMBEDDED GROUP
* All Rights Reserved
*
* THIS SOFTWARE IS PROVIDED BY BENINGO EMBEDDED GROUP "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL BENINGO EMBEDDED GROUP OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/
/****************************************************************************
* Doxygen C Template
* Copyright (c) 2013 - Jacob Beningo - All Rights Reserved
*
* Feel free to use this Doxygen Code Template at your own risk for your own
* purposes.  The latest license and updates for this Doxygen C template can be
* found at www.beningo.com or by contacting Jacob at jacob@beningo.com.
*
* For updates, free software, training and to stay up to date on the latest
* embedded software techniques sign-up for Jacobs newsletter at
* http://www.beningo.com/814-2/
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Template.
*
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Version   Author         Description
*  01/21/13   0.5.0   Jacob Beningo   Interface Created.
*  01/11/15   0.6.0   Jacob Beningo   Converted constants to enums, clean doxygen comments.
*  11/10/15   1.0.0   Jacob Beningo   Interface released.
*****************************************************************************/
/** @file constants.h
 *  @brief This file contains standard constants used in the application.
 */
#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/**
 * Constants: I/O Pin Levels
 */
typedef enum
{
    LOW = 0x0U,			    /**< Reserved word representing the logical value 0 (OFF, 0 volts) */
    HIGH = 0x1U,		    /**< Reserved word representing the logical value 1 (ON, 5 volts) */
    ACTIVE_LOW = 0x0U,		/**< Reserved word representing the logical value 0 (OFF, 0 volts) */
    INACTIVE_HIGH = 0x1U,	/**< Reserved word representing the logical value 1 (ON, 5 volts) */
    INACTIVE_LOW = 0x0U,	/**< Reserved word representing the logical value 0 (OFF, 0 volts) */
    ACTIVE_HIGH = 0x1U		/**< Reserved word representing the logical value 1 (ON, 5 volts) */
}PinLevelEnum_t;

/**
 * Constants: Logic Values
 */
typedef enum
{
    DISABLED = 0U,	/**< Reserved word for representing the logical value 0 (OFF, 0 volts) */
    ENABLED = 1U,	/**< Reserved word for representing the logical value 1 (ON, 5 volts) */
    FALSE = 0U,		/**< Reserved word for representing the logical value 0 (OFF, 0 volts) */
    TRUE = 1U		/**<  Reserved word for representing the logical value 1 (ON, 5 volts) */
}LogicEnum_t;

/**
 * Constants: ON/OFF States
 */
typedef enum 
{
    OFF = 0U,		/**< Reserved word for representing the logical value 0 (OFF, 0 volts) */
    ON = 1U		/**< Reserved word for representing the logical value 1 (ON, 5 volts) */
}OnOff_t;

/**
 * Constants: I/O Pin Modes
 */
typedef enum
{
    OUTPUT = 0x0U,	/**< Reserved word representing the mode of an I/O pin or an I/O port as an input */
    INPUT = 0x1U	/**< Reserved word representing the mode of an I/O pin or an I/O port as an output */
}PinModeEnum_t;

/**
 * Constants: Zero
 * Used to define a constant value of zero.
 */
#define ZERO		(0U)

/**
 * Constants: null
 * Is used to define both null and NULL keywords.
 */
#define null  		(NULL)

/**
 * Constants: Number Base
 */
typedef enum 
{
    DEC = 10U,		/**< Defines the base 10 decimal numbering system */
    HEX = 16U,		/**< Defines the base 16 hexadecimal numbering system */
    OCT = 8U,		/**< Defines the base 8 octal numbering system */
    BIN = 2U		/**< Defines the base 2 binary numbering system */
}NumberBase_t;

/** Engineering Constant, Pi */
#define PI				(3.1415927)

/** Engineering Constant, Pi*2 */
#define TWO_PI			(6.2831854)

/** Engineering Constant, Pi/2 */
#define HALF_PI			(1.57079)

/** Engineering Constant, epsilon */
#define EPSILON			(0.0001)

/** Engineering Constant, converting degrees to radians */
#define DEG_TO_RAD		(0.01745329)

/** Engineering Constant, converting radians to degrees */
#define RAD_TO_DEG		(57.2957786)

/** Register Bit 0 shift */
#define REGBIT0 (1UL)

/** Register Bit 1 shift */
#define REGBIT1 (1UL<<1U)

/** Register Bit 2 shift */
#define REGBIT2 (1UL<<2U)

/** Register Bit 3 shift */
#define REGBIT3 (1UL<<3U)

/** Register Bit 4 shift */
#define REGBIT4 (1UL<<4U)

/** Register Bit 5 shift */
#define REGBIT5 (1UL<<5U)

/** Register Bit 6 shift */
#define REGBIT6 (1UL<<6U)

/** Register Bit 7 shift */
#define REGBIT7 (1UL<<7U)

/** Register Bit 8 shift */
#define REGBIT8 (1UL<<8U)

/** Register Bit 9 shift */
#define REGBIT9 (1UL<<9U)

/** Register Bit 10 shift */
#define REGBIT10 (1UL<<10U)

/** Register Bit 11 shift */
#define REGBIT11 (1UL<<11U)

/** Register Bit 12 shift */
#define REGBIT12 (1UL<<12U)

/** Register Bit 13 shift */
#define REGBIT13 (1UL<<13U)

/** Register Bit 14 shift */
#define REGBIT14 (1UL<<14U)

/** Register Bit 15 shift */
#define REGBIT15 (1UL<<15U)

/** Register Bit 16 shift */
#define REGBIT16 (1UL<<16U)

/** Register Bit 17 shift */
#define REGBIT17 (1UL<<17U)

/** Register Bit 18 shift */
#define REGBIT18 (1UL<<18U)

/** Register Bit 19 shift */
#define REGBIT19 (1UL<<19U)

/** Register Bit 20 shift */
#define REGBIT20 (1UL<<20U)

/** Register Bit 21 shift */
#define REGBIT21 (1UL<<21U)

/** Register Bit 22 shift */
#define REGBIT22 (1UL<<22U)

/** Register Bit 23 shift */
#define REGBIT23 (1UL<<23U)

/** Register Bit 24 shift */
#define REGBIT24 (1UL<<24U)

/** Register Bit 25 shift */
#define REGBIT25 (1UL<<25U)

/** Register Bit 26 shift */
#define REGBIT26 (1UL<<26U)

/** Register Bit 27 shift */
#define REGBIT27 (1UL<<27U)

/** Register Bit 28 shift */
#define REGBIT28 (1UL<<28U)

/** Register Bit 29 shift */
#define REGBIT29 (1UL<<29U)

/** Register Bit 30 shift */
#define REGBIT30 (1UL<<30U)

/** Register Bit 31 shift */
#define REGBIT31 (1UL<<31U)

/**
 * Constants: Byte Numbering
 * Used to represent number of bytes.  ONE_BYTE, TWO_BYTES, ... NINE_BYTES
 */
typedef enum 
{
    ONE_BYTES = 1U,		/**< One byte */
    TWO_BYTES = 2U,		/**< Two byte */
    THREE_BYTES = 3U,		/**< Three byte */
    FOUR_BYTES = 4U,		/**< Four byte */
    FIVE_BYTES = 5U,		/**< Five byte */
    SIX_BYTES = 6U,		/**< Six byte */
    SEVEN_BYTES = 7U,		/**< Seven byte */
    EIGHT_BYTES = 8U,		/**< Eight byte */
    NINE_BYTES = 9U		/**< Nine byte */
}Byte_t;

/**
 * Constants: Percentages
 * General percent constants.
 */
typedef enum 
{
    PERCENT_0 = 0,		/**< PERCENT_0 is 0% */
    PERCENT_100 = 100		/**< PERCENT_100 is 100% */
}Percent_t;

/**
 * Constants: CLOCK_DIVIDEBY_X
 * Clock Prescaler Values.
 */
typedef enum 
{
    CLOCK_DIVIDEBY_1 = 1,		/**< Divide clock by 1 */
    CLOCK_DIVIDEBY_2 = 2,		/**< Divide clock by 2 */
    CLOCK_DIVIDEBY_4 = 4,		/**< Divide clock by 4 */
    CLOCK_DIVIDEBY_8  = 8,		/**< Divide clock by 8 */
    CLOCK_DIVIDEBY_16 = 16,		/**< Divide clock by 16 */
    CLOCK_DIVIDEBY_32 = 32,		/**< Divide clock by 32 */
    CLOCK_DIVIDEBY_64 = 64,		/**< Divide clock by 64 */
    CLOCK_DIVIDEBY_128 = 128,		/**< Divide clock by 128 */
    CLOCK_DIVIDEBY_256 = 256		/**< Divide clock by 256 */
}ClockDivide_t;

/** Defines the unsigned long value for 1 MHz clock frequency. */
#define CLOCK_1_MHZ                     (1000000UL)

/** Defines the unsigned long value for 2 MHz clock frequency. */
#define CLOCK_2_MHZ                     (2000000UL)

/** Defines the unsigned long value for 4 MHz clock frequency. */
#define CLOCK_4_MHZ                     (4000000UL)

/** Defines the unsigned long value for 7.37 MHz clock frequency. */
#define CLOCK_7_37_MHZ                  (7370000UL)

/** Defines the unsigned long value for 8 MHz clock frequency. */
#define CLOCK_8_MHZ                     (8000000UL)

/** Defines the unsigned long value for 12 MHz clock frequency. */
#define CLOCK_12_MHZ                    (12000000UL)

/** Defines the unsigned long value for 16 MHz clock frequency. */
#define CLOCK_16_MHZ                    (16000000UL)

/** Defines the unsigned long value for 24 MHz clock frequency. */
#define CLOCK_24_MHZ                    (24000000UL)

/** Defines the unsigned long value for 32 MHz clock frequency. */
#define CLOCK_32_MHZ                    (32000000UL)

/** Defines the unsigned long value for 40 MHz clock frequency. */
#define CLOCK_40_MHZ                    (40000000UL)

/** Defines the unsigned long value for 48 MHz clock frequency. */
#define CLOCK_48_MHZ                    (48000000UL)

/**
 Constants: CLOCK_PERIOD_NS_X_MHZ
 Defines the unsigned long value of the clock period in nanoseconds.
*/
typedef enum 
{
    CLOCK_PERIOD_NS_1_MHZ = 1000UL,		/**< 1 MHz clock period */
    CLOCK_PERIOD_NS_2_MHZ = 500UL,		/**< 2 MHz clock period */
    CLOCK_PERIOD_NS_4_MHZ = 250UL,		/**< 4 MHz clock period */
    CLOCK_PERIOD_NS_8_MHZ = 125UL,		/**< 8 MHz clock period */
    CLOCK_PERIOD_NS_16_MHZ = 62UL,		/**< 16 MHz clock period */
    CLOCK_PERIOD_NS_24_MHZ = 42UL,		/**< 24 MHz clock period */
    CLOCK_PERIOD_NS_32_MHZ = 31UL,		/**< 32 MHz clock period */
    CLOCK_PERIOD_NS_40_MHZ = 25UL,		/**< 40 MHz clock period */
    CLOCK_PERIOD_NS_48_MHZ = 21UL		/**< 48 MHz clock period */
}ClockPeriod_t;

/** Clear a flag to 1 */
#define CLEAR_FLAG_POS                  (TRUE)

/** Clear a flag to 0 */
#define CLEAR_FLAG_NUL                  (FALSE)

/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/
// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif
/**
 * Macro: Abs
 *   Returns the absolute value of a number.
 *
 * Parameters:
 *   n  - the number
 *
 * Returns:
 *   n  - if is greater than or equal to 0
 *   -n - if x is less than zero
 *
 * Example:
 *
 * : // Take the absolute value of the number
 * : abs = Abs(num);
 */
#define Abs(x)       ((x)>0?(x):-(x))

/**
  Macro: Constrain
    Constrains a number to be within a range.

  Parameters:
    amt  - the number to constrain, all data types
    low  - the lower end of the range, all data types
    high - the upper end of the range, all data types

  Returns:
    amt  - if amt is between a and b
    low  - if amt is less than low
    high - if amt is greater than high

  Example:

  : // limits range of sensor values to between 10 and 150
  : sensVal = Constrain(sensVal, 10, 150);

  Related:
    Min, Max
*/
#define Constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

/**
  Macro: Degrees
  This macro converts radians to degrees.
*/
#define Degrees(rad) ((rad)*RAD_TO_DEG)

/**
  Macro: Max
    Returns the larger of two numbers.

  Parameters:
    a - the first number, any data types
    b - the second number, any data types

  Returns:
    The larger of the two numbers.

  Example:

  Related:
    Min, Constrain
*/
#define Max(a,b)     ((a)>(b)?(a):(b))

/**
  Macro: Min
    Returns the smaller of two numbers.

  Parameters:
    a - the first number, any data types
    b - the second number, any data types

  Returns:
    The smaller of the two numbers.

  Example:

  Related:
    Max, Constrain
*/
#define Min(a,b)     ((a)<(b)?(a):(b))

/**
  Macro: Round
  This macro rounds a float to a integer.
*/
#define Round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

/**
  Macro: Radians
  This macro converts degrees to radians.
*/
#define Radians(deg) ((deg)*DEG_TO_RAD)

/**
  Macro: Sq
    Returns the square a number.
*/
#define Sq(x)        ((x)*(x))


/** Macro: Bit Manipulation - Access specified bit */
#define bit(x) (1UL<<(x))

/** Macro: Bit Manipulation - Set the specified bit */
#define setBits(x, y) ((x)|=(y))

/** Macro: Bit Manipulation - Clears the bit */
#define clearBits(x, y) ((x)&=(~(y)))

/** Macro: Bit Manipulation - Read a bit */
#define bitRead(x,y) (((x)>>(y)) & 1)

/** Macro: Bit Manipulation - Write a bit */
#define bitWrite(x, y, v) ((v) ? bitSet((x), (y)) : bitClear((x), (y)))

/** Macro: Bit Manipulation - Access lower byte */
#define lowByte(x) ((x) & 0x00ff)

/** Macro: Bit Manipulation - Access the top byte of a 16 bit number */
#define highByte(x) ((x)>>8)

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * Enum: Number of bits to shift
 */
typedef enum
{
    ZERO_BITS,          /**< Shift 0 bytes */
    ONE_BIT,            /**< Shift 1 bytes */
    TWO_BITS,           /**< Shift 2 bytes */
    THREE_BITS,         /**< Shift 3 bytes */
    FOUR_BITS,          /**< Shift 4 bytes */
    FIVE_BITS,          /**< Shift 5 bytes */
    SIX_BITS,           /**< Shift 6 bytes */
    SEVEN_BITS,         /**< Shift 7 bytes */
    EIGHT_BITS,         /**< Shift 8 bytes */
    NINE_BITS,          /**< Shift 9 bytes */
    TEN_BITS,           /**< Shift 10 bytes */
    ELEVEN_BITS,        /**< Shift 11 bytes */
    TWELVE_BITS,        /**< Shift 12 bytes */
    THIRTEEN_BITS,      /**< Shift 13 bytes */
    FOURTEEN_BITS,      /**< Shift 14 bytes */
    FIFTEEN_BITS,       /**< Shift 15 bytes */
    SIXTEEN_BITS,       /**< Shift 16 bytes */
    SEVENTEEN_BITS,     /**< Shift 17 bytes */
    EIGHTEEN_BITS,      /**< Shift 18 bytes */
    NINETEEN_BITS,      /**< Shift 19 bytes */
    TWENTY_BITS,        /**< Shift 20 bytes */
    TWENTYONE_BITS,     /**< Shift 21 bytes */
    TWENTYTWO_BITS,     /**< Shift 22 bytes */
    TWENTYTHREE_BITS,   /**< Shift 23 bytes */
    TWENTYFOUR_BITS,    /**< Shift 24 bytes */
    TWENTYFIVE_BITS,    /**< Shift 25 bytes */
    TWENTYSIX_BITS,     /**< Shift 26 bytes */
    TWENTYSEVEN_BITS,   /**< Shift 27 bytes */
    TWENTYEIGHT_BITS,   /**< Shift 28 bytes */
    TWENTYNINE_BITS,    /**< Shift 29 bytes */
    THIRTY_BITS,        /**< Shift 30 bytes */
    THIRTYONE_BITS,     /**< Shift 31 bytes */
    THIRTYTWO_BITS      /**< Shift 32 bytes */
} BitShift_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif



#ifdef __cplusplus
} // extern "C"
#endif

#endif /*CONSTANTS_H_*/

/*** End of File **************************************************************/

