
#ifndef BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(Reg,bit_pos)    (Reg|= (1<<bit_pos))
#define CLR_BIT(Reg,bit_pos)    (Reg&=~(1<<bit_pos))
#define TOGGLE_Bit(Reg,bit_pos) (Reg^= (1<<bit_pos))
#define GET_BIT(Reg,bit_pos)	((Reg>>bit_pos)&(1))
#define TOGGLE_PORT(Reg)        (Reg^=(0xFF))
#endif

