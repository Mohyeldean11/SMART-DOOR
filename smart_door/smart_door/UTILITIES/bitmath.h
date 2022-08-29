/*
 * bitmath.h
 *
 * Created: 8/26/2022 1:56:26 PM
 *  Author: mohye
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_

#define SetBit(reg,bit)					reg|=(1<<bit)

#define ClearBit(reg,bit)				reg&=~(1<<bit)

#define ReadBit(reg,bit)				(1&(reg>>bit))

#define ToggleBit(reg,bit)				reg^=(1,bit)



#endif /* BITMATH_H_ */