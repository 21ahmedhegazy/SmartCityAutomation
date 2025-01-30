#define SET_BIT(VAR,BIT_NO)    (VAR|=(1<<BIT_NO))


#define CLR_BIT(VAR,BIT_NO)    (VAR&=(~(1<<BIT_NO)))

#define GET_BIT(VAR,BIT_NO)    ((VAR>>BIT_NO)&1)

#define TGL_BIT(VAR,BIT_NO)    (VAR^=(1<<BIT_NO)) 

#define WRITE_BIT(VAR,BIT_NO,VALUE)  (VAR=(VALUE<<BIT_NO)|(VAR&~(1<<BIT_NO)))
