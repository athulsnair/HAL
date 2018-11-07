/*
 * dio.h
 *
 * Created: 02-10-2018 10:20:21 PM
 *  Author: New User
 */ 

#ifndef DIO_H_
#define DIO_H_

#include "dio_cfg.h"
#include "constants.h"
#include <avr/io.h>
#include <util/delay.h>

void Dio_Init(DioConfig_t const * const Config);
DioPinState_t Dio_ChannelRead(DioChannel_t const Channel);
void Dio_ChannelWrite(DioChannel_t const Channel, DioPinState_t const State);
void Dio_ChannelToggle(DioChannel_t const Channel);
void Dio_ChannelDirectionSet(DioChannel_t const Channel, PinModeEnum_t const Mode);
void Dio_ChannelResistor(DioChannel_t const Channel, DioResistor_t const Resistor);
void Dio_RegisterWrite(uint8_t const Address, uint8_t const Value);
uint8_t Dio_RegisterRead(uint8_t const Address);



#endif /* DIO_H_ */