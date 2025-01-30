
;CodeVisionAVR C Compiler V2.05.3 Standard
;(C) Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type                : ATmega328P
;Program type             : Application
;Clock frequency          : 11.059200 MHz
;Memory model             : Small
;Optimize for             : Speed
;(s)printf features       : long, width, precision
;(s)scanf features        : long, width
;External RAM size        : 0
;Data Stack size          : 512 byte(s)
;Heap size                : 0 byte(s)
;Promote 'char' to 'int'  : Yes
;'char' is unsigned       : Yes
;8 bit enums              : Yes
;Global 'const' stored in FLASH     : No
;Enhanced function parameter passing: Yes
;Enhanced core instructions         : On
;Smart register allocation          : On
;Automatic register allocation      : On

	#pragma AVRPART ADMIN PART_NAME ATmega328P
	#pragma AVRPART MEMORY PROG_FLASH 32768
	#pragma AVRPART MEMORY EEPROM 1024
	#pragma AVRPART MEMORY INT_SRAM SIZE 2303
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x100

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU EECR=0x1F
	.EQU EEDR=0x20
	.EQU EEARL=0x21
	.EQU EEARH=0x22
	.EQU SPSR=0x2D
	.EQU SPDR=0x2E
	.EQU SMCR=0x33
	.EQU MCUSR=0x34
	.EQU MCUCR=0x35
	.EQU WDTCSR=0x60
	.EQU UCSR0A=0xC0
	.EQU UDR0=0xC6
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU GPIOR0=0x1E

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0100
	.EQU __SRAM_END=0x08FF
	.EQU __DSTACK_SIZE=0x0200
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTW2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	LDI  R24,BYTE3(2*@0+(@1))
	LDI  R25,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __GETD1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X+
	LD   R22,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;NAME DEFINITIONS FOR GLOBAL VARIABLES ALLOCATED TO REGISTERS
	.DEF _interval=R4

;GPIOR0 INITIALIZATION VALUE
	.EQU __GPIOR0_INIT=0x00

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  _timer0_ovf_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_0x36:
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0
_0x46:
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0
_0x51:
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x0
_0x54:
	.DB  0xD0,0x7
_0x0:
	.DB  0x2B,0x49,0x50,0x44,0x0,0x25,0x63,0x0
	.DB  0x46,0x42,0x20,0x3A,0x75,0x20,0x4F,0x4B
	.DB  0x0,0x46,0x42,0x20,0x3A,0x64,0x20,0x4F
	.DB  0x4B,0x0,0x46,0x42,0x20,0x3A,0x73,0x20
	.DB  0x4F,0x4B,0x0,0x41,0x54,0x2B,0x43,0x49
	.DB  0x50,0x53,0x54,0x41,0x54,0x55,0x53,0xD
	.DB  0xA,0x0,0x3A,0x35,0x0,0x41,0x54,0x2B
	.DB  0x52,0x53,0x54,0xD,0xA,0x0,0x3A,0x32
	.DB  0x0,0x41,0x54,0x2B,0x43,0x49,0x46,0x53
	.DB  0x52,0xD,0xA,0x0,0x41,0x54,0x2B,0x43
	.DB  0x57,0x4A,0x41,0x50,0x3F,0xD,0xA,0x0
	.DB  0x41,0x54,0x2B,0x43,0x49,0x50,0x4D,0x55
	.DB  0x58,0x3D,0x31,0xD,0xA,0x0,0x41,0x54
	.DB  0x2B,0x43,0x49,0x50,0x53,0x45,0x52,0x56
	.DB  0x45,0x52,0x3D,0x31,0x2C,0x31,0x30,0x30
	.DB  0x31,0xD,0xA,0x0,0x43,0x49,0x50,0x53
	.DB  0x45,0x4E,0x44,0x0,0x3E,0x0,0x6E,0x6F
	.DB  0x0,0x41,0x54,0x2B,0x43,0x49,0x50,0x53
	.DB  0x45,0x4E,0x44,0x3D,0x25,0x73,0x2C,0x25
	.DB  0x64,0xD,0xA,0x0,0x41,0x54,0x2B,0x43
	.DB  0x49,0x50,0x43,0x4C,0x4F,0x53,0x45,0x3D
	.DB  0x25,0x73,0xD,0xA,0x0,0x41,0x54,0x45
	.DB  0x30,0xD,0xA,0x0,0x41,0x54,0x2B,0x43
	.DB  0x57,0x4D,0x4F,0x44,0x45,0x3D,0x31,0xD
	.DB  0xA,0x0,0x41,0x54,0x2B,0x43,0x57,0x41
	.DB  0x55,0x54,0x4F,0x43,0x4F,0x4E,0x4E,0x3D
	.DB  0x31,0xD,0xA,0x0,0x41,0x54,0x2B,0x43
	.DB  0x57,0x4A,0x41,0x50,0x5F,0x44,0x45,0x46
	.DB  0x3D,0x22,0x73,0x6D,0x61,0x72,0x74,0x6C
	.DB  0x69,0x66,0x65,0x22,0x2C,0x22,0x6D,0x72
	.DB  0x62,0x31,0x33,0x31,0x31,0x31,0x33,0x22
	.DB  0xD,0xA,0x0,0x41,0x54,0x2B,0x43,0x49
	.DB  0x50,0x53,0x54,0x41,0x5F,0x44,0x45,0x46
	.DB  0x3D,0x22,0x31,0x39,0x32,0x2E,0x31,0x36
	.DB  0x38,0x2E,0x31,0x2E,0x35,0x35,0x22,0x2C
	.DB  0x22,0x31,0x39,0x32,0x2E,0x31,0x36,0x38
	.DB  0x2E,0x31,0x2E,0x31,0x22,0x2C,0x22,0x32
	.DB  0x35,0x35,0x2E,0x32,0x35,0x35,0x2E,0x32
	.DB  0x35,0x35,0x2E,0x30,0x22,0xD,0xA,0x0
	.DB  0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54
	.DB  0x4F,0x3D,0x31,0x30,0xD,0xA,0x0

__GLOBAL_INI_TBL:
	.DW  0x05
	.DW  _0x13
	.DW  _0x0*2

	.DW  0x05
	.DW  _0x13+5
	.DW  _0x0*2

	.DW  0x05
	.DW  _0x13+10
	.DW  _0x0*2

	.DW  0x09
	.DW  _0x13+15
	.DW  _0x0*2+8

	.DW  0x05
	.DW  _0x13+24
	.DW  _0x0*2

	.DW  0x09
	.DW  _0x13+29
	.DW  _0x0*2+17

	.DW  0x05
	.DW  _0x13+38
	.DW  _0x0*2

	.DW  0x09
	.DW  _0x13+43
	.DW  _0x0*2+26

	.DW  0x0F
	.DW  _0x13+52
	.DW  _0x0*2+35

	.DW  0x03
	.DW  _0x13+67
	.DW  _0x0*2+50

	.DW  0x09
	.DW  _0x13+70
	.DW  _0x0*2+53

	.DW  0x0F
	.DW  _0x13+79
	.DW  _0x0*2+35

	.DW  0x03
	.DW  _0x13+94
	.DW  _0x0*2+50

	.DW  0x03
	.DW  _0x13+97
	.DW  _0x0*2+62

	.DW  0x0B
	.DW  _0x13+100
	.DW  _0x0*2+65

	.DW  0x0C
	.DW  _0x13+111
	.DW  _0x0*2+76

	.DW  0x0E
	.DW  _0x13+123
	.DW  _0x0*2+88

	.DW  0x16
	.DW  _0x13+137
	.DW  _0x0*2+102

	.DW  0x08
	.DW  _0x3F
	.DW  _0x0*2+124

	.DW  0x02
	.DW  _0x3F+8
	.DW  _0x0*2+132

	.DW  0x03
	.DW  _0x3F+10
	.DW  _0x0*2+14

	.DW  0x03
	.DW  _0x3F+13
	.DW  _0x0*2+134

	.DW  0x03
	.DW  _0x4F
	.DW  _0x0*2+14

	.DW  0x07
	.DW  _0x52
	.DW  _0x0*2+173

	.DW  0x0E
	.DW  _0x52+7
	.DW  _0x0*2+180

	.DW  0x12
	.DW  _0x52+21
	.DW  _0x0*2+194

	.DW  0x27
	.DW  _0x52+39
	.DW  _0x0*2+212

	.DW  0x3D
	.DW  _0x52+78
	.DW  _0x0*2+251

	.DW  0x0E
	.DW  _0x52+139
	.DW  _0x0*2+88

	.DW  0x16
	.DW  _0x52+153
	.DW  _0x0*2+102

	.DW  0x0F
	.DW  _0x52+175
	.DW  _0x0*2+312

	.DW  0x0F
	.DW  _0x52+190
	.DW  _0x0*2+35

	.DW  0x0B
	.DW  _0x52+205
	.DW  _0x0*2+65

	.DW  0x0C
	.DW  _0x52+216
	.DW  _0x0*2+76

	.DW  0x02
	.DW  0x04
	.DW  _0x54*2

_0xFFFFFFFF:
	.DW  0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  MCUCR,R31
	OUT  MCUCR,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	WDR
	IN   R26,MCUSR
	CBR  R26,8
	OUT  MCUSR,R26
	STS  WDTCSR,R31
	STS  WDTCSR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;GPIOR0 INITIALIZATION
	LDI  R30,__GPIOR0_INIT
	OUT  GPIOR0,R30

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x300

	.CSEG
;#include <mega328p.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_adc_noise_red=0x02
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.SET power_ctrl_reg=smcr
	#endif
;#include <delay.h>
;#include <stdio.h>
;#include <string.h>
;
;#define  uchar unsigned char   // 0~255
;#define  uint  unsigned int    // 0~65535
;#define  ulong unsigned long   // 0~4,294,967,295
;
;#define  esp8266_print   puts
;#define  esp8266_read    gets
;#define  wdt_reset()    #asm("wdr")
;
;#define  Out_Up     PORTD.4 //  n6-o4
;#define  Out_Dn     PORTD.5 //  n7-o5
;#define  Out_R       PORTD.2 //
;
;#define  DEBUG 1
;
;ulong millis=0;
;ulong previousMillis=0;
;uint  interval=2000;
;
;uchar *AtCommand(uchar *command, const int timeout, int debug);
;uchar *AtData(uchar *data, const int timeout, int debug);
;void CIPData(uchar *connectionId, uchar *data);
;void init_esp(void);
;
;void test()
; 0000 001E {

	.CSEG
; 0000 001F     Out_Up=1;
; 0000 0020     Out_Dn=1;
; 0000 0021     delay_ms(300);
; 0000 0022     Out_Up=0;
; 0000 0023     Out_Dn=0;
; 0000 0024 }
;//------------------------------------
;interrupt [TIM0_OVF] void timer0_ovf_isr(void)
; 0000 0027 {
_timer0_ovf_isr:
	ST   -Y,R22
	ST   -Y,R23
	ST   -Y,R26
	ST   -Y,R27
	ST   -Y,R30
	ST   -Y,R31
	IN   R30,SREG
	ST   -Y,R30
; 0000 0028     // Reinitialize Timer 0 value
; 0000 0029     TCNT0=0x83;  //TCNT0=0x53;
	LDI  R30,LOW(131)
	OUT  0x26,R30
; 0000 002A     // Place your code here
; 0000 002B     millis++;
	LDI  R26,LOW(_millis)
	LDI  R27,HIGH(_millis)
	CALL __GETD1P_INC
	__SUBD1N -1
	CALL __PUTDP1_DEC
; 0000 002C }
	LD   R30,Y+
	OUT  SREG,R30
	LD   R31,Y+
	LD   R30,Y+
	LD   R27,Y+
	LD   R26,Y+
	LD   R23,Y+
	LD   R22,Y+
	RETI
;//--USART-----------------------------------
;int esp8266_available(void) {
; 0000 002E int esp8266_available(void) {
_esp8266_available:
; 0000 002F 	if (UCSR0A & (1 << RXC0))
	LDS  R30,192
	ANDI R30,LOW(0x80)
	BREQ _0xB
; 0000 0030     {
; 0000 0031 		return 1;
	LDI  R30,LOW(1)
	LDI  R31,HIGH(1)
	RET
; 0000 0032 
; 0000 0033 	}
; 0000 0034 	else
_0xB:
; 0000 0035     {
; 0000 0036 		return 0;
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	RET
; 0000 0037 	}
; 0000 0038 }
	RET
;//------------------------------------------
;void init_all()
; 0000 003B {
_init_all:
; 0000 003C // Crystal Oscillator division factor: 1
; 0000 003D #pragma optsize-
; 0000 003E CLKPR=0x80;
	LDI  R30,LOW(128)
	STS  97,R30
; 0000 003F CLKPR=0x00;
	LDI  R30,LOW(0)
	STS  97,R30
; 0000 0040 #ifdef _OPTIMIZE_SIZE_
; 0000 0041 #pragma optsize+
; 0000 0042 #endif
; 0000 0043 
; 0000 0044 // Input/Output Ports initialization
; 0000 0045 // Port B initialization
; 0000 0046 // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 0047 // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 0048 PORTB=0x00;
	OUT  0x5,R30
; 0000 0049 DDRB=0x04;
	LDI  R30,LOW(4)
	OUT  0x4,R30
; 0000 004A 
; 0000 004B // Port C initialization
; 0000 004C // Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
; 0000 004D // State6=T State5=T State4=T State3=T State2=T State1=T State0=T
; 0000 004E PORTC=0x39;
	LDI  R30,LOW(57)
	OUT  0x8,R30
; 0000 004F DDRC=0x00;
	LDI  R30,LOW(0)
	OUT  0x7,R30
; 0000 0050 
; 0000 0051 // Port D initialization
; 0000 0052 // Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=Out Func1=In Func0=In
; 0000 0053 // State7=0 State6=0 State5=0 State4=0 State3=P State2=0 State1=T State0=T
; 0000 0054 PORTD=0x08;
	LDI  R30,LOW(8)
	OUT  0xB,R30
; 0000 0055 DDRD=0xF4;
	LDI  R30,LOW(244)
	OUT  0xA,R30
; 0000 0056 
; 0000 0057 // Timer/Counter 0 initialization
; 0000 0058 // Clock source: System Clock 8M-11.059M / 64
; 0000 0059 // Clock value: 125.000 kHz - 172.800 kHz
; 0000 005A TCCR0A=0x00;
	LDI  R30,LOW(0)
	OUT  0x24,R30
; 0000 005B TCCR0B=0x03;
	LDI  R30,LOW(3)
	OUT  0x25,R30
; 0000 005C TCNT0=0x83;  //0x53
	LDI  R30,LOW(131)
	OUT  0x26,R30
; 0000 005D OCR0A=0x00;
	LDI  R30,LOW(0)
	OUT  0x27,R30
; 0000 005E OCR0B=0x00;
	OUT  0x28,R30
; 0000 005F 
; 0000 0060 // Timer/Counter 0 Interrupt(s) initialization
; 0000 0061 TIMSK0=0x01;
	LDI  R30,LOW(1)
	STS  110,R30
; 0000 0062 
; 0000 0063 // Timer/Counter 1 Interrupt(s) initialization
; 0000 0064 TIMSK1=0x00;
	LDI  R30,LOW(0)
	STS  111,R30
; 0000 0065 
; 0000 0066 // Timer/Counter 2 Interrupt(s) initialization
; 0000 0067 TIMSK2=0x00;
	STS  112,R30
; 0000 0068 
; 0000 0069 // USART initialization
; 0000 006A // Communication Parameters: 8 Data, 1 Stop, No Parity
; 0000 006B // USART Receiver: On
; 0000 006C // USART Transmitter: On
; 0000 006D // USART Mode: Asynchronous
; 0000 006E // USART Baud Rate: 115200
; 0000 006F UCSR0A=0x00;
	STS  192,R30
; 0000 0070 UCSR0B=0x18;
	LDI  R30,LOW(24)
	STS  193,R30
; 0000 0071 UCSR0C=0x06;
	LDI  R30,LOW(6)
	STS  194,R30
; 0000 0072 UBRR0H=0x00;
	LDI  R30,LOW(0)
	STS  197,R30
; 0000 0073 UBRR0L=0x05;
	LDI  R30,LOW(5)
	STS  196,R30
; 0000 0074 
; 0000 0075 // ADC initialization
; 0000 0076 // ADC disabled
; 0000 0077 ADCSRA=0x00;
	LDI  R30,LOW(0)
	STS  122,R30
; 0000 0078 
; 0000 0079 // Watchdog Timer initialization
; 0000 007A // Watchdog Timer Prescaler: OSC/256k
; 0000 007B // Watchdog Timer interrupt: Off
; 0000 007C #pragma optsize-
; 0000 007D #asm("wdr")
	wdr
; 0000 007E WDTCSR=0x1F;
	LDI  R30,LOW(31)
	STS  96,R30
; 0000 007F WDTCSR=0x0F; // 2 sec
	LDI  R30,LOW(15)
	STS  96,R30
; 0000 0080 #ifdef _OPTIMIZE_SIZE_
; 0000 0081 #pragma optsize+
; 0000 0082 #endif
; 0000 0083 
; 0000 0084 // Global enable interrupts
; 0000 0085 #asm("sei")
	sei
; 0000 0086 }
	RET
;//------------------------------------------
;void main(void)
; 0000 0089 {
_main:
; 0000 008A     uchar idx[1];
; 0000 008B     uchar buff[50];
; 0000 008C     uchar stat[50];
; 0000 008D     ulong currentMillis=0;
; 0000 008E     //Out_R=1;
; 0000 008F 
; 0000 0090     init_all();
	SBIW R28,63
	SBIW R28,42
	LDI  R30,LOW(0)
	ST   Y,R30
	STD  Y+1,R30
	STD  Y+2,R30
	STD  Y+3,R30
;	idx -> Y+104
;	buff -> Y+54
;	stat -> Y+4
;	currentMillis -> Y+0
	RCALL _init_all
; 0000 0091     init_esp();
	RCALL _init_esp
; 0000 0092     ////esp8266.setTimeout(300);
; 0000 0093 
; 0000 0094     if(DEBUG)
; 0000 0095     {
; 0000 0096         //Serial.println("start");
; 0000 0097     }
; 0000 0098 
; 0000 0099     while(1)
_0xE:
; 0000 009A     {
; 0000 009B         currentMillis = millis;
	LDS  R30,_millis
	LDS  R31,_millis+1
	LDS  R22,_millis+2
	LDS  R23,_millis+3
	CALL __PUTD1S0
; 0000 009C         wdt_reset();
	wdr
; 0000 009D 
; 0000 009E         if(esp8266_available())
	RCALL _esp8266_available
	SBIW R30,0
	BRNE PC+3
	JMP _0x11
; 0000 009F         {
; 0000 00A0             //delay_ms(200);
; 0000 00A1             //+IPD,0,4:o=u
; 0000 00A2 
; 0000 00A3             esp8266_read(buff,50);
	MOVW R30,R28
	ADIW R30,54
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(50)
	LDI  R27,0
	CALL _gets
; 0000 00A4             if(strstr(buff, "+IPD"))
	MOVW R30,R28
	ADIW R30,54
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,0
	CALL _strstr
	SBIW R30,0
	BRNE PC+3
	JMP _0x12
; 0000 00A5             {
; 0000 00A6                 if(DEBUG)
; 0000 00A7                 {
; 0000 00A8                     //Serial.println("available");
; 0000 00A9                 }
; 0000 00AA                 sprintf(idx,"%c",*(strstr(buff, "+IPD")+11));
	MOVW R30,R28
	SUBI R30,LOW(-(104))
	SBCI R31,HIGH(-(104))
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x0,5
	ST   -Y,R31
	ST   -Y,R30
	MOVW R30,R28
	ADIW R30,58
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,5
	CALL _strstr
	LDD  R30,Z+11
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	LDI  R24,4
	CALL _sprintf
	ADIW R28,8
; 0000 00AB                 if(idx[0]=='u')
	__GETB2SX 104
	CPI  R26,LOW(0x75)
	BRNE _0x15
; 0000 00AC                 {
; 0000 00AD                     sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));
	MOVW R30,R28
	SUBI R30,LOW(-(104))
	SBCI R31,HIGH(-(104))
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x0,5
	ST   -Y,R31
	ST   -Y,R30
	MOVW R30,R28
	ADIW R30,58
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,10
	CALL _strstr
	LDD  R30,Z+5
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	LDI  R24,4
	CALL _sprintf
	ADIW R28,8
; 0000 00AE                     CIPData(idx,"FB :u OK");
	MOVW R30,R28
	SUBI R30,LOW(-(104))
	SBCI R31,HIGH(-(104))
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,15
	RCALL _CIPData
; 0000 00AF                     Out_Up=1;
	SBI  0xB,4
; 0000 00B0                     Out_Dn=0;
	RJMP _0x53
; 0000 00B1                 }
; 0000 00B2                 else if(idx[0]=='d')
_0x15:
	__GETB2SX 104
	CPI  R26,LOW(0x64)
	BRNE _0x1B
; 0000 00B3                 {
; 0000 00B4                     sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));
	MOVW R30,R28
	SUBI R30,LOW(-(104))
	SBCI R31,HIGH(-(104))
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x0,5
	ST   -Y,R31
	ST   -Y,R30
	MOVW R30,R28
	ADIW R30,58
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,24
	CALL _strstr
	LDD  R30,Z+5
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	LDI  R24,4
	CALL _sprintf
	ADIW R28,8
; 0000 00B5                     CIPData(idx,"FB :d OK");
	MOVW R30,R28
	SUBI R30,LOW(-(104))
	SBCI R31,HIGH(-(104))
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,29
	RCALL _CIPData
; 0000 00B6                     Out_Up=0;
	CBI  0xB,4
; 0000 00B7                     Out_Dn=1;
	SBI  0xB,5
; 0000 00B8                 }
; 0000 00B9                 else if(idx[0]=='s')
	RJMP _0x20
_0x1B:
	__GETB2SX 104
	CPI  R26,LOW(0x73)
	BRNE _0x21
; 0000 00BA                 {
; 0000 00BB                     sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));
	MOVW R30,R28
	SUBI R30,LOW(-(104))
	SBCI R31,HIGH(-(104))
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x0,5
	ST   -Y,R31
	ST   -Y,R30
	MOVW R30,R28
	ADIW R30,58
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,38
	CALL _strstr
	LDD  R30,Z+5
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	LDI  R24,4
	CALL _sprintf
	ADIW R28,8
; 0000 00BC                     CIPData(idx,"FB :s OK");
	MOVW R30,R28
	SUBI R30,LOW(-(104))
	SBCI R31,HIGH(-(104))
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,43
	RCALL _CIPData
; 0000 00BD                     Out_Up=0;
	CBI  0xB,4
; 0000 00BE                     Out_Dn=0;
_0x53:
	CBI  0xB,5
; 0000 00BF                 }
; 0000 00C0             }
_0x21:
_0x20:
; 0000 00C1         }
_0x12:
; 0000 00C2         else if(((unsigned long)(currentMillis - previousMillis) >= interval))
	RJMP _0x26
_0x11:
	LDS  R26,_previousMillis
	LDS  R27,_previousMillis+1
	LDS  R24,_previousMillis+2
	LDS  R25,_previousMillis+3
	CALL __GETD1S0
	CALL __SUBD12
	MOVW R26,R30
	MOVW R24,R22
	MOVW R30,R4
	CLR  R22
	CLR  R23
	CALL __CPD21
	BRSH PC+3
	JMP _0x27
; 0000 00C3         {
; 0000 00C4                 previousMillis = currentMillis;
	CALL __GETD1S0
	STS  _previousMillis,R30
	STS  _previousMillis+1,R31
	STS  _previousMillis+2,R22
	STS  _previousMillis+3,R23
; 0000 00C5                 strcpy(stat,AtCommand("AT+CIPSTATUS\r\n",100,DEBUG));
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1MN _0x13,52
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
	MOVW R26,R30
	CALL _strcpy
; 0000 00C6 
; 0000 00C7                 if(strstr(stat,":5") || strlen(stat) ==0)
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,67
	CALL _strstr
	SBIW R30,0
	BRNE _0x29
	MOVW R26,R28
	ADIW R26,4
	CALL _strlen
	SBIW R30,0
	BREQ _0x29
	RJMP _0x28
_0x29:
; 0000 00C8                 {
; 0000 00C9                     AtCommand("AT+RST\r\n",10000,DEBUG);
	__POINTW1MN _0x13,70
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(10000)
	LDI  R31,HIGH(10000)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 00CA                     init_esp();
	RCALL _init_esp
; 0000 00CB 
; 0000 00CC                     strcpy(stat,AtCommand("AT+CIPSTATUS\r\n",100,DEBUG));
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1MN _0x13,79
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
	MOVW R26,R30
	CALL _strcpy
; 0000 00CD                     if(strstr(stat,":5") || strlen(stat) ==0)
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,94
	CALL _strstr
	SBIW R30,0
	BRNE _0x2C
	MOVW R26,R28
	ADIW R26,4
	CALL _strlen
	SBIW R30,0
	BRNE _0x2B
_0x2C:
; 0000 00CE                     {
; 0000 00CF                         Out_R=0; delay_ms(1000); wdt_reset();
	CBI  0xB,2
	LDI  R26,LOW(1000)
	LDI  R27,HIGH(1000)
	CALL _delay_ms
	wdr
; 0000 00D0                         Out_R=1; delay_ms(1000); wdt_reset();
	SBI  0xB,2
	LDI  R26,LOW(1000)
	LDI  R27,HIGH(1000)
	CALL _delay_ms
	wdr
; 0000 00D1 
; 0000 00D2                         init_esp();
	RCALL _init_esp
; 0000 00D3                     }
; 0000 00D4                 }
_0x2B:
; 0000 00D5                 else if(strstr(stat,":2"))
	RJMP _0x32
_0x28:
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x13,97
	CALL _strstr
	SBIW R30,0
	BREQ _0x33
; 0000 00D6                 {
; 0000 00D7                     AtCommand("AT+CIFSR\r\n",100,DEBUG); // get ip address
	__POINTW1MN _0x13,100
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 00D8                     AtCommand("AT+CWJAP?\r\n",100,DEBUG);
	__POINTW1MN _0x13,111
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 00D9 
; 0000 00DA                     AtCommand("AT+CIPMUX=1\r\n",150,DEBUG); // configure for multiple connections
	__POINTW1MN _0x13,123
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(150)
	LDI  R31,HIGH(150)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 00DB                     AtCommand("AT+CIPSERVER=1,1001\r\n",150,DEBUG);// turn on server on port 80
	__POINTW1MN _0x13,137
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(150)
	LDI  R31,HIGH(150)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 00DC                 }
; 0000 00DD                 else// if( stat.indexOf(":3") > -1 || stat.indexOf(":4") > -1)
_0x33:
; 0000 00DE                 {
; 0000 00DF                 }
_0x32:
; 0000 00E0           }
; 0000 00E1     }
_0x27:
_0x26:
	RJMP _0xE
; 0000 00E2 }
_0x35:
	RJMP _0x35

	.DSEG
_0x13:
	.BYTE 0x9F
;//------------------------------------------
;uchar *AtCommand(uchar *command, const int timeout, int debug)
; 0000 00E5 {

	.CSEG
_AtCommand:
	PUSH R15
; 0000 00E6     uchar response[100]="";
; 0000 00E7     ulong time = millis;
; 0000 00E8     bit ok = 0;
; 0000 00E9     esp8266_print(command);
	ST   -Y,R27
	ST   -Y,R26
	SBIW R28,63
	SBIW R28,41
	LDI  R24,100
	LDI  R26,LOW(4)
	LDI  R27,HIGH(4)
	LDI  R30,LOW(_0x36*2)
	LDI  R31,HIGH(_0x36*2)
	CALL __INITLOCB
;	*command -> Y+108
;	timeout -> Y+106
;	debug -> Y+104
;	response -> Y+4
;	time -> Y+0
;	ok -> R15.0
	CLR  R15
	LDS  R30,_millis
	LDS  R31,_millis+1
	LDS  R22,_millis+2
	LDS  R23,_millis+3
	CALL __PUTD1S0
	__GETW2SX 108
	RCALL _puts
; 0000 00EA 
; 0000 00EB     if(debug)
; 0000 00EC     {
; 0000 00ED       //Serial.print(command);
; 0000 00EE     }
; 0000 00EF 
; 0000 00F0     while(  !ok && (time+timeout) > millis )
_0x38:
	SBRC R15,0
	RJMP _0x3B
	__GETW1SX 106
	CALL __GETD2S0
	CALL __CWD1
	CALL __ADDD21
	LDS  R30,_millis
	LDS  R31,_millis+1
	LDS  R22,_millis+2
	LDS  R23,_millis+3
	CALL __CPD12
	BRLO _0x3C
_0x3B:
	RJMP _0x3A
_0x3C:
; 0000 00F1     {
; 0000 00F2         wdt_reset();
	wdr
; 0000 00F3         if(esp8266_available())
	RCALL _esp8266_available
	SBIW R30,0
	BREQ _0x3D
; 0000 00F4         {
; 0000 00F5            esp8266_read(response,50);
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(50)
	LDI  R27,0
	RCALL _gets
; 0000 00F6         }
; 0000 00F7 
; 0000 00F8        if(strstr(command,"CIPSEND"))
_0x3D:
	__GETW1SX 108
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x3F,0
	CALL _strstr
	SBIW R30,0
	BREQ _0x3E
; 0000 00F9         {
; 0000 00FA             if(strstr(response,">"))
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x3F,8
	CALL _strstr
	SBIW R30,0
	BREQ _0x40
; 0000 00FB             ok = 1;
	SET
	BLD  R15,0
; 0000 00FC         }
_0x40:
; 0000 00FD //        else if(strstr(command,"CIPSTATUS") )
; 0000 00FE //        {
; 0000 00FF //            if(strstr(response,"STATUS") )
; 0000 0100 //            ok = 1;
; 0000 0101 //        }
; 0000 0102         else
	RJMP _0x41
_0x3E:
; 0000 0103         {
; 0000 0104             if(strstr(response,"OK")  || strstr(response,"no"))
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x3F,10
	CALL _strstr
	SBIW R30,0
	BRNE _0x43
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x3F,13
	CALL _strstr
	SBIW R30,0
	BREQ _0x42
_0x43:
; 0000 0105             {
; 0000 0106                 ok = 1;
	SET
	BLD  R15,0
; 0000 0107             }
; 0000 0108         }
_0x42:
_0x41:
; 0000 0109     }
	RJMP _0x38
_0x3A:
; 0000 010A 
; 0000 010B     if(debug)
; 0000 010C     {
; 0000 010D       //Serial.print(response);
; 0000 010E     }
; 0000 010F     return response;
	MOVW R30,R28
	ADIW R30,4
	ADIW R28,63
	ADIW R28,47
	POP  R15
	RET
; 0000 0110 }

	.DSEG
_0x3F:
	.BYTE 0x10
;
;uchar *AtData(uchar *data,  const int timeout, int debug)
; 0000 0113 {

	.CSEG
_AtData:
	PUSH R15
; 0000 0114     uchar response[50] = "";
; 0000 0115     bit ok = 0;
; 0000 0116     ulong time = millis;
; 0000 0117 
; 0000 0118     esp8266_print(data);
	ST   -Y,R27
	ST   -Y,R26
	SBIW R28,54
	LDI  R24,50
	LDI  R26,LOW(4)
	LDI  R27,HIGH(4)
	LDI  R30,LOW(_0x46*2)
	LDI  R31,HIGH(_0x46*2)
	CALL __INITLOCB
;	*data -> Y+58
;	timeout -> Y+56
;	debug -> Y+54
;	response -> Y+4
;	ok -> R15.0
;	time -> Y+0
	CLR  R15
	LDS  R30,_millis
	LDS  R31,_millis+1
	LDS  R22,_millis+2
	LDS  R23,_millis+3
	CALL __PUTD1S0
	LDD  R26,Y+58
	LDD  R27,Y+58+1
	RCALL _puts
; 0000 0119 
; 0000 011A     if(debug)
; 0000 011B     {
; 0000 011C       //Serial.println("\r\nFeedBack:");
; 0000 011D       //Serial.write(data,dataSize);
; 0000 011E     }
; 0000 011F 
; 0000 0120     while( (time+timeout) > millis && !ok)
_0x48:
	LDD  R30,Y+56
	LDD  R31,Y+56+1
	CALL __GETD2S0
	CALL __CWD1
	CALL __ADDD21
	LDS  R30,_millis
	LDS  R31,_millis+1
	LDS  R22,_millis+2
	LDS  R23,_millis+3
	CALL __CPD12
	BRSH _0x4B
	SBRS R15,0
	RJMP _0x4C
_0x4B:
	RJMP _0x4A
_0x4C:
; 0000 0121     {
; 0000 0122       wdt_reset();
	wdr
; 0000 0123       if(esp8266_available())
	RCALL _esp8266_available
	SBIW R30,0
	BREQ _0x4D
; 0000 0124       {
; 0000 0125           esp8266_read(response,10);
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(10)
	LDI  R27,0
	RCALL _gets
; 0000 0126       }
; 0000 0127 
; 0000 0128       if(strstr(response,"OK"))
_0x4D:
	MOVW R30,R28
	ADIW R30,4
	ST   -Y,R31
	ST   -Y,R30
	__POINTW2MN _0x4F,0
	CALL _strstr
	SBIW R30,0
	BREQ _0x4E
; 0000 0129       {
; 0000 012A           //Flash();
; 0000 012B           ok = 1;
	SET
	BLD  R15,0
; 0000 012C       }
; 0000 012D     }
_0x4E:
	RJMP _0x48
_0x4A:
; 0000 012E 
; 0000 012F     if(debug)
; 0000 0130     {
; 0000 0131        //Serial.print(response);
; 0000 0132     }
; 0000 0133 
; 0000 0134     return response;
	MOVW R30,R28
	ADIW R30,4
	ADIW R28,60
	POP  R15
	RET
; 0000 0135 }

	.DSEG
_0x4F:
	.BYTE 0x3
;
;void CIPData(uchar *connectionId, uchar *data)
; 0000 0138 {

	.CSEG
_CIPData:
; 0000 0139    uchar buff[50]=""; //+IPD,0,4:o=u
; 0000 013A    sprintf(buff,"AT+CIPSEND=%s,%d\r\n",connectionId,strlen(data));
	ST   -Y,R27
	ST   -Y,R26
	SBIW R28,50
	LDI  R24,50
	LDI  R26,LOW(0)
	LDI  R27,HIGH(0)
	LDI  R30,LOW(_0x51*2)
	LDI  R31,HIGH(_0x51*2)
	CALL __INITLOCB
;	*connectionId -> Y+52
;	*data -> Y+50
;	buff -> Y+0
	MOVW R30,R28
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x0,137
	ST   -Y,R31
	ST   -Y,R30
	LDD  R30,Y+56
	LDD  R31,Y+56+1
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	LDD  R26,Y+58
	LDD  R27,Y+58+1
	CALL _strlen
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	LDI  R24,8
	CALL _sprintf
	ADIW R28,12
; 0000 013B    AtCommand(buff,200,DEBUG);//****1000
	MOVW R30,R28
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(200)
	LDI  R31,HIGH(200)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 013C 
; 0000 013D    AtData(data,200,DEBUG);//****1000
	LDD  R30,Y+50
	LDD  R31,Y+50+1
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(200)
	LDI  R31,HIGH(200)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtData
; 0000 013E 
; 0000 013F    sprintf(buff,"AT+CIPCLOSE=%s\r\n",connectionId);
	MOVW R30,R28
	ST   -Y,R31
	ST   -Y,R30
	__POINTW1FN _0x0,156
	ST   -Y,R31
	ST   -Y,R30
	LDD  R30,Y+56
	LDD  R31,Y+56+1
	CLR  R22
	CLR  R23
	CALL __PUTPARD1
	LDI  R24,4
	CALL _sprintf
	ADIW R28,8
; 0000 0140    AtCommand(buff,200,DEBUG); // close connection***1000
	MOVW R30,R28
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(200)
	LDI  R31,HIGH(200)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0141 }
	ADIW R28,54
	RET
;
;void init_esp(void)
; 0000 0144 {
_init_esp:
; 0000 0145   //AT+CWJAP?
; 0000 0146   //AtCommand("AT+CWAUTOCONN?\r\n",100,DEBUG);
; 0000 0147   //AtCommand("AT+CWMODE?\r\n",100,DEBUG);
; 0000 0148   //AtCommand("AT+CIPSTA_DEF?\r\n",100,DEBUG);
; 0000 0149   //AtCommand("AT+RFPOWER=82",100,DEBUG);
; 0000 014A 
; 0000 014B   AtCommand("ATE0\r\n",100,DEBUG);
	__POINTW1MN _0x52,0
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 014C 
; 0000 014D   AtCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
	__POINTW1MN _0x52,7
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(1000)
	LDI  R31,HIGH(1000)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 014E   AtCommand("AT+CWAUTOCONN=1\r\n",100,DEBUG);
	__POINTW1MN _0x52,21
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 014F   AtCommand("AT+CWJAP_DEF=\"smartlife\",\"mrb131113\"\r\n",10000,DEBUG);//,\"AC:5F:3E:48:17:E7\"   // \"Broo\",\"mrb131113\",\"60:83:34:29:2d:2c\" -- \"TP-LINK_7DEADE\",\"maf123456\",\"c4:e9:84:7d:ea:de\"
	__POINTW1MN _0x52,39
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(10000)
	LDI  R31,HIGH(10000)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0150   AtCommand("AT+CIPSTA_DEF=\"192.168.1.55\",\"192.168.1.1\",\"255.255.255.0\"\r\n",500,DEBUG);
	__POINTW1MN _0x52,78
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(500)
	LDI  R31,HIGH(500)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0151 
; 0000 0152   AtCommand("AT+CIPMUX=1\r\n",150,DEBUG); // configure for multiple connections
	__POINTW1MN _0x52,139
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(150)
	LDI  R31,HIGH(150)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0153   AtCommand("AT+CIPSERVER=1,1001\r\n",150,DEBUG); // turn on server on port 1001
	__POINTW1MN _0x52,153
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(150)
	LDI  R31,HIGH(150)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0154   AtCommand("AT+CIPSTO=10\r\n",150,DEBUG);
	__POINTW1MN _0x52,175
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(150)
	LDI  R31,HIGH(150)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0155 
; 0000 0156   AtCommand("AT+CIPSTATUS\r\n",100,DEBUG); // check if =2 got ip or =5 not
	__POINTW1MN _0x52,190
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0157   AtCommand("AT+CIFSR\r\n",100,DEBUG); // get ip address
	__POINTW1MN _0x52,205
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0158   AtCommand("AT+CWJAP?\r\n",100,DEBUG);
	__POINTW1MN _0x52,216
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(1)
	LDI  R27,0
	RCALL _AtCommand
; 0000 0159 
; 0000 015A }
	RET

	.DSEG
_0x52:
	.BYTE 0xE4
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_adc_noise_red=0x02
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.SET power_ctrl_reg=smcr
	#endif

	.CSEG
_getchar:
_0x2000003:
	LDS  R30,192
	ANDI R30,LOW(0x80)
	BREQ _0x2000003
	LDS  R30,198
	RET
_putchar:
	ST   -Y,R26
_0x2000006:
	LDS  R30,192
	ANDI R30,LOW(0x20)
	BREQ _0x2000006
	LD   R30,Y
	STS  198,R30
	ADIW R28,1
	RET
_puts:
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R17
_0x2000009:
	LDD  R26,Y+1
	LDD  R27,Y+1+1
	LD   R30,X+
	STD  Y+1,R26
	STD  Y+1+1,R27
	MOV  R17,R30
	CPI  R30,0
	BREQ _0x200000B
	MOV  R26,R17
	RCALL _putchar
	RJMP _0x2000009
_0x200000B:
	LDI  R26,LOW(10)
	RCALL _putchar
	LDD  R17,Y+0
	ADIW R28,3
	RET
_gets:
	ST   -Y,R27
	ST   -Y,R26
	CALL __SAVELOCR6
	__GETWRS 16,17,6
	__GETWRS 18,19,8
_0x200000F:
	MOV  R0,R16
	OR   R0,R17
	BREQ _0x2000011
_0x2000012:
	RCALL _getchar
	MOV  R21,R30
	CPI  R21,8
	BRNE _0x2000013
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	CP   R16,R26
	CPC  R17,R27
	BRSH _0x2000014
	__SUBWRN 18,19,1
	__ADDWRN 16,17,1
_0x2000014:
	RJMP _0x2000012
_0x2000013:
	CPI  R21,10
	BREQ _0x2000011
	PUSH R19
	PUSH R18
	__ADDWRN 18,19,1
	MOV  R30,R21
	POP  R26
	POP  R27
	ST   X,R30
	__SUBWRN 16,17,1
	RJMP _0x200000F
_0x2000011:
	MOVW R26,R18
	LDI  R30,LOW(0)
	ST   X,R30
	LDD  R30,Y+8
	LDD  R31,Y+8+1
	CALL __LOADLOCR6
	ADIW R28,10
	RET
_put_buff_G100:
	ST   -Y,R27
	ST   -Y,R26
	ST   -Y,R17
	ST   -Y,R16
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	ADIW R26,2
	CALL __GETW1P
	SBIW R30,0
	BREQ _0x2000016
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	ADIW R26,4
	CALL __GETW1P
	MOVW R16,R30
	SBIW R30,0
	BREQ _0x2000018
	__CPWRN 16,17,2
	BRLO _0x2000019
	MOVW R30,R16
	SBIW R30,1
	MOVW R16,R30
	__PUTW1SNS 2,4
_0x2000018:
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	ADIW R26,2
	LD   R30,X+
	LD   R31,X+
	ADIW R30,1
	ST   -X,R31
	ST   -X,R30
	SBIW R30,1
	LDD  R26,Y+4
	STD  Z+0,R26
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	CALL __GETW1P
	TST  R31
	BRMI _0x200001A
	LD   R30,X+
	LD   R31,X+
	ADIW R30,1
	ST   -X,R31
	ST   -X,R30
_0x200001A:
_0x2000019:
	RJMP _0x200001B
_0x2000016:
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	LDI  R30,LOW(65535)
	LDI  R31,HIGH(65535)
	ST   X+,R30
	ST   X,R31
_0x200001B:
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,5
	RET
__print_G100:
	ST   -Y,R27
	ST   -Y,R26
	SBIW R28,12
	CALL __SAVELOCR6
	LDI  R17,0
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   X+,R30
	ST   X,R31
_0x200001C:
	LDD  R30,Y+24
	LDD  R31,Y+24+1
	ADIW R30,1
	STD  Y+24,R30
	STD  Y+24+1,R31
	SBIW R30,1
	LPM  R30,Z
	MOV  R18,R30
	CPI  R30,0
	BRNE PC+3
	JMP _0x200001E
	MOV  R30,R17
	CPI  R30,0
	BRNE _0x2000022
	CPI  R18,37
	BRNE _0x2000023
	LDI  R17,LOW(1)
	RJMP _0x2000024
_0x2000023:
	ST   -Y,R18
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
_0x2000024:
	RJMP _0x2000021
_0x2000022:
	CPI  R30,LOW(0x1)
	BRNE _0x2000025
	CPI  R18,37
	BRNE _0x2000026
	ST   -Y,R18
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	RJMP _0x20000ED
_0x2000026:
	LDI  R17,LOW(2)
	LDI  R30,LOW(0)
	STD  Y+17,R30
	LDI  R16,LOW(0)
	CPI  R18,45
	BRNE _0x2000027
	LDI  R16,LOW(1)
	RJMP _0x2000021
_0x2000027:
	CPI  R18,43
	BRNE _0x2000028
	LDI  R30,LOW(43)
	STD  Y+17,R30
	RJMP _0x2000021
_0x2000028:
	CPI  R18,32
	BRNE _0x2000029
	LDI  R30,LOW(32)
	STD  Y+17,R30
	RJMP _0x2000021
_0x2000029:
	RJMP _0x200002A
_0x2000025:
	CPI  R30,LOW(0x2)
	BRNE _0x200002B
_0x200002A:
	LDI  R21,LOW(0)
	LDI  R17,LOW(3)
	CPI  R18,48
	BRNE _0x200002C
	ORI  R16,LOW(128)
	RJMP _0x2000021
_0x200002C:
	RJMP _0x200002D
_0x200002B:
	CPI  R30,LOW(0x3)
	BRNE _0x200002E
_0x200002D:
	CPI  R18,48
	BRLO _0x2000030
	CPI  R18,58
	BRLO _0x2000031
_0x2000030:
	RJMP _0x200002F
_0x2000031:
	LDI  R26,LOW(10)
	MUL  R21,R26
	MOV  R21,R0
	MOV  R30,R18
	SUBI R30,LOW(48)
	ADD  R21,R30
	RJMP _0x2000021
_0x200002F:
	LDI  R20,LOW(0)
	CPI  R18,46
	BRNE _0x2000032
	LDI  R17,LOW(4)
	RJMP _0x2000021
_0x2000032:
	RJMP _0x2000033
_0x200002E:
	CPI  R30,LOW(0x4)
	BRNE _0x2000035
	CPI  R18,48
	BRLO _0x2000037
	CPI  R18,58
	BRLO _0x2000038
_0x2000037:
	RJMP _0x2000036
_0x2000038:
	LDI  R26,LOW(10)
	MUL  R20,R26
	MOV  R20,R0
	MOV  R30,R18
	SUBI R30,LOW(48)
	ADD  R20,R30
	RJMP _0x2000021
_0x2000036:
_0x2000033:
	CPI  R18,108
	BRNE _0x2000039
	ORI  R16,LOW(2)
	LDI  R17,LOW(5)
	RJMP _0x2000021
_0x2000039:
	RJMP _0x200003A
_0x2000035:
	CPI  R30,LOW(0x5)
	BREQ PC+3
	JMP _0x2000021
_0x200003A:
	MOV  R30,R18
	CPI  R30,LOW(0x63)
	BRNE _0x200003F
	LDD  R30,Y+22
	LDD  R31,Y+22+1
	SBIW R30,4
	STD  Y+22,R30
	STD  Y+22+1,R31
	LDD  R26,Z+4
	ST   -Y,R26
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	RJMP _0x2000040
_0x200003F:
	CPI  R30,LOW(0x73)
	BRNE _0x2000042
	LDD  R30,Y+22
	LDD  R31,Y+22+1
	SBIW R30,4
	STD  Y+22,R30
	STD  Y+22+1,R31
	LDD  R26,Y+22
	LDD  R27,Y+22+1
	ADIW R26,4
	CALL __GETW1P
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	CALL _strlen
	MOV  R17,R30
	RJMP _0x2000043
_0x2000042:
	CPI  R30,LOW(0x70)
	BRNE _0x2000045
	LDD  R30,Y+22
	LDD  R31,Y+22+1
	SBIW R30,4
	STD  Y+22,R30
	STD  Y+22+1,R31
	LDD  R26,Y+22
	LDD  R27,Y+22+1
	ADIW R26,4
	CALL __GETW1P
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	CALL _strlenf
	MOV  R17,R30
	ORI  R16,LOW(8)
_0x2000043:
	ANDI R16,LOW(127)
	CPI  R20,0
	BREQ _0x2000047
	CP   R20,R17
	BRLO _0x2000048
_0x2000047:
	RJMP _0x2000046
_0x2000048:
	MOV  R17,R20
_0x2000046:
	LDI  R20,LOW(0)
	LDI  R30,LOW(0)
	STD  Y+16,R30
	LDI  R19,LOW(0)
	RJMP _0x2000049
_0x2000045:
	CPI  R30,LOW(0x64)
	BREQ _0x200004C
	CPI  R30,LOW(0x69)
	BRNE _0x200004D
_0x200004C:
	ORI  R16,LOW(4)
	RJMP _0x200004E
_0x200004D:
	CPI  R30,LOW(0x75)
	BRNE _0x200004F
_0x200004E:
	LDI  R30,LOW(10)
	STD  Y+16,R30
	SBRS R16,1
	RJMP _0x2000050
	__GETD1N 0x3B9ACA00
	__PUTD1S 8
	LDI  R17,LOW(10)
	RJMP _0x2000051
_0x2000050:
	__GETD1N 0x2710
	__PUTD1S 8
	LDI  R17,LOW(5)
	RJMP _0x2000051
_0x200004F:
	CPI  R30,LOW(0x58)
	BRNE _0x2000053
	ORI  R16,LOW(8)
	RJMP _0x2000054
_0x2000053:
	CPI  R30,LOW(0x78)
	BREQ PC+3
	JMP _0x2000092
_0x2000054:
	LDI  R30,LOW(16)
	STD  Y+16,R30
	SBRS R16,1
	RJMP _0x2000056
	__GETD1N 0x10000000
	__PUTD1S 8
	LDI  R17,LOW(8)
	RJMP _0x2000051
_0x2000056:
	__GETD1N 0x1000
	__PUTD1S 8
	LDI  R17,LOW(4)
_0x2000051:
	CPI  R20,0
	BREQ _0x2000057
	ANDI R16,LOW(127)
	RJMP _0x2000058
_0x2000057:
	LDI  R20,LOW(1)
_0x2000058:
	SBRS R16,1
	RJMP _0x2000059
	LDD  R30,Y+22
	LDD  R31,Y+22+1
	SBIW R30,4
	STD  Y+22,R30
	STD  Y+22+1,R31
	LDD  R26,Y+22
	LDD  R27,Y+22+1
	ADIW R26,4
	CALL __GETD1P
	RJMP _0x20000EE
_0x2000059:
	SBRS R16,2
	RJMP _0x200005B
	LDD  R30,Y+22
	LDD  R31,Y+22+1
	SBIW R30,4
	STD  Y+22,R30
	STD  Y+22+1,R31
	LDD  R26,Y+22
	LDD  R27,Y+22+1
	ADIW R26,4
	CALL __GETW1P
	CALL __CWD1
	RJMP _0x20000EE
_0x200005B:
	LDD  R30,Y+22
	LDD  R31,Y+22+1
	SBIW R30,4
	STD  Y+22,R30
	STD  Y+22+1,R31
	LDD  R26,Y+22
	LDD  R27,Y+22+1
	ADIW R26,4
	CALL __GETW1P
	CLR  R22
	CLR  R23
_0x20000EE:
	__PUTD1S 12
	SBRS R16,2
	RJMP _0x200005D
	LDD  R26,Y+15
	TST  R26
	BRPL _0x200005E
	__GETD1S 12
	CALL __ANEGD1
	__PUTD1S 12
	LDI  R30,LOW(45)
	STD  Y+17,R30
_0x200005E:
	LDD  R30,Y+17
	CPI  R30,0
	BREQ _0x200005F
	SUBI R17,-LOW(1)
	SUBI R20,-LOW(1)
	RJMP _0x2000060
_0x200005F:
	ANDI R16,LOW(251)
_0x2000060:
_0x200005D:
	MOV  R19,R20
_0x2000049:
	SBRC R16,0
	RJMP _0x2000061
_0x2000062:
	CP   R17,R21
	BRSH _0x2000065
	CP   R19,R21
	BRLO _0x2000066
_0x2000065:
	RJMP _0x2000064
_0x2000066:
	SBRS R16,7
	RJMP _0x2000067
	SBRS R16,2
	RJMP _0x2000068
	ANDI R16,LOW(251)
	LDD  R18,Y+17
	SUBI R17,LOW(1)
	RJMP _0x2000069
_0x2000068:
	LDI  R18,LOW(48)
_0x2000069:
	RJMP _0x200006A
_0x2000067:
	LDI  R18,LOW(32)
_0x200006A:
	ST   -Y,R18
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	SUBI R21,LOW(1)
	RJMP _0x2000062
_0x2000064:
_0x2000061:
_0x200006B:
	CP   R17,R20
	BRSH _0x200006D
	ORI  R16,LOW(16)
	SBRS R16,2
	RJMP _0x200006E
	ANDI R16,LOW(251)
	LDD  R30,Y+17
	ST   -Y,R30
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	CPI  R21,0
	BREQ _0x200006F
	SUBI R21,LOW(1)
_0x200006F:
	SUBI R17,LOW(1)
	SUBI R20,LOW(1)
_0x200006E:
	LDI  R30,LOW(48)
	ST   -Y,R30
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	CPI  R21,0
	BREQ _0x2000070
	SUBI R21,LOW(1)
_0x2000070:
	SUBI R20,LOW(1)
	RJMP _0x200006B
_0x200006D:
	MOV  R19,R17
	LDD  R30,Y+16
	CPI  R30,0
	BRNE _0x2000071
_0x2000072:
	CPI  R19,0
	BREQ _0x2000074
	SBRS R16,3
	RJMP _0x2000075
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	LPM  R18,Z+
	STD  Y+6,R30
	STD  Y+6+1,R31
	RJMP _0x2000076
_0x2000075:
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	LD   R18,X+
	STD  Y+6,R26
	STD  Y+6+1,R27
_0x2000076:
	ST   -Y,R18
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	CPI  R21,0
	BREQ _0x2000077
	SUBI R21,LOW(1)
_0x2000077:
	SUBI R19,LOW(1)
	RJMP _0x2000072
_0x2000074:
	RJMP _0x2000078
_0x2000071:
_0x200007A:
	__GETD1S 8
	__GETD2S 12
	CALL __DIVD21U
	MOV  R18,R30
	CPI  R18,10
	BRLO _0x200007C
	SBRS R16,3
	RJMP _0x200007D
	SUBI R18,-LOW(55)
	RJMP _0x200007E
_0x200007D:
	SUBI R18,-LOW(87)
_0x200007E:
	RJMP _0x200007F
_0x200007C:
	SUBI R18,-LOW(48)
_0x200007F:
	SBRC R16,4
	RJMP _0x2000081
	CPI  R18,49
	BRSH _0x2000083
	__GETD2S 8
	__CPD2N 0x1
	BRNE _0x2000082
_0x2000083:
	RJMP _0x2000085
_0x2000082:
	CP   R20,R19
	BRSH _0x20000EF
	CP   R21,R19
	BRLO _0x2000088
	SBRS R16,0
	RJMP _0x2000089
_0x2000088:
	RJMP _0x2000087
_0x2000089:
	LDI  R18,LOW(32)
	SBRS R16,7
	RJMP _0x200008A
_0x20000EF:
	LDI  R18,LOW(48)
_0x2000085:
	ORI  R16,LOW(16)
	SBRS R16,2
	RJMP _0x200008B
	ANDI R16,LOW(251)
	LDD  R30,Y+17
	ST   -Y,R30
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	CPI  R21,0
	BREQ _0x200008C
	SUBI R21,LOW(1)
_0x200008C:
_0x200008B:
_0x200008A:
_0x2000081:
	ST   -Y,R18
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	CPI  R21,0
	BREQ _0x200008D
	SUBI R21,LOW(1)
_0x200008D:
_0x2000087:
	SUBI R19,LOW(1)
	__GETD1S 8
	__GETD2S 12
	CALL __MODD21U
	__PUTD1S 12
	LDD  R30,Y+16
	__GETD2S 8
	CLR  R31
	CLR  R22
	CLR  R23
	CALL __DIVD21U
	__PUTD1S 8
	CALL __CPD10
	BREQ _0x200007B
	RJMP _0x200007A
_0x200007B:
_0x2000078:
	SBRS R16,0
	RJMP _0x200008E
_0x200008F:
	CPI  R21,0
	BREQ _0x2000091
	SUBI R21,LOW(1)
	LDI  R30,LOW(32)
	ST   -Y,R30
	LDD  R26,Y+19
	LDD  R27,Y+19+1
	LDD  R30,Y+21
	LDD  R31,Y+21+1
	ICALL
	RJMP _0x200008F
_0x2000091:
_0x200008E:
_0x2000092:
_0x2000040:
_0x20000ED:
	LDI  R17,LOW(0)
_0x2000021:
	RJMP _0x200001C
_0x200001E:
	LDD  R26,Y+18
	LDD  R27,Y+18+1
	CALL __GETW1P
	CALL __LOADLOCR6
	ADIW R28,26
	RET
_sprintf:
	PUSH R15
	MOV  R15,R24
	SBIW R28,6
	CALL __SAVELOCR4
	MOVW R26,R28
	ADIW R26,12
	CALL __ADDW2R15
	CALL __GETW1P
	SBIW R30,0
	BRNE _0x2000093
	LDI  R30,LOW(65535)
	LDI  R31,HIGH(65535)
	RJMP _0x2060001
_0x2000093:
	MOVW R26,R28
	ADIW R26,6
	CALL __ADDW2R15
	MOVW R16,R26
	MOVW R26,R28
	ADIW R26,12
	CALL __ADDW2R15
	CALL __GETW1P
	STD  Y+6,R30
	STD  Y+6+1,R31
	LDI  R30,LOW(0)
	STD  Y+8,R30
	STD  Y+8+1,R30
	MOVW R26,R28
	ADIW R26,10
	CALL __ADDW2R15
	CALL __GETW1P
	ST   -Y,R31
	ST   -Y,R30
	ST   -Y,R17
	ST   -Y,R16
	LDI  R30,LOW(_put_buff_G100)
	LDI  R31,HIGH(_put_buff_G100)
	ST   -Y,R31
	ST   -Y,R30
	MOVW R26,R28
	ADIW R26,10
	RCALL __print_G100
	MOVW R18,R30
	LDD  R26,Y+6
	LDD  R27,Y+6+1
	LDI  R30,LOW(0)
	ST   X,R30
	MOVW R30,R18
_0x2060001:
	CALL __LOADLOCR4
	ADIW R28,10
	POP  R15
	RET

	.CSEG
_strcpy:
	ST   -Y,R27
	ST   -Y,R26
    ld   r30,y+
    ld   r31,y+
    ld   r26,y+
    ld   r27,y+
    movw r24,r26
strcpy0:
    ld   r22,z+
    st   x+,r22
    tst  r22
    brne strcpy0
    movw r30,r24
    ret
_strlen:
	ST   -Y,R27
	ST   -Y,R26
    ld   r26,y+
    ld   r27,y+
    clr  r30
    clr  r31
strlen0:
    ld   r22,x+
    tst  r22
    breq strlen1
    adiw r30,1
    rjmp strlen0
strlen1:
    ret
_strlenf:
	ST   -Y,R27
	ST   -Y,R26
    clr  r26
    clr  r27
    ld   r30,y+
    ld   r31,y+
strlenf0:
	lpm  r0,z+
    tst  r0
    breq strlenf1
    adiw r26,1
    rjmp strlenf0
strlenf1:
    movw r30,r26
    ret
_strstr:
	ST   -Y,R27
	ST   -Y,R26
    ldd  r26,y+2
    ldd  r27,y+3
    movw r24,r26
strstr0:
    ld   r30,y
    ldd  r31,y+1
strstr1:
    ld   r23,z+
    tst  r23
    brne strstr2
    movw r30,r24
    rjmp strstr3
strstr2:
    ld   r22,x+
    cp   r22,r23
    breq strstr1
    adiw r24,1
    movw r26,r24
    tst  r22
    brne strstr0
    clr  r30
    clr  r31
strstr3:
	ADIW R28,4
	RET

	.CSEG

	.DSEG
_millis:
	.BYTE 0x4
_previousMillis:
	.BYTE 0x4

	.CSEG

	.CSEG
_delay_ms:
	adiw r26,0
	breq __delay_ms1
__delay_ms0:
	__DELAY_USW 0xACD
	wdr
	sbiw r26,1
	brne __delay_ms0
__delay_ms1:
	ret

__ADDW2R15:
	CLR  R0
	ADD  R26,R15
	ADC  R27,R0
	RET

__ADDD21:
	ADD  R26,R30
	ADC  R27,R31
	ADC  R24,R22
	ADC  R25,R23
	RET

__SUBD12:
	SUB  R30,R26
	SBC  R31,R27
	SBC  R22,R24
	SBC  R23,R25
	RET

__ANEGD1:
	COM  R31
	COM  R22
	COM  R23
	NEG  R30
	SBCI R31,-1
	SBCI R22,-1
	SBCI R23,-1
	RET

__CWD1:
	MOV  R22,R31
	ADD  R22,R22
	SBC  R22,R22
	MOV  R23,R22
	RET

__DIVD21U:
	PUSH R19
	PUSH R20
	PUSH R21
	CLR  R0
	CLR  R1
	CLR  R20
	CLR  R21
	LDI  R19,32
__DIVD21U1:
	LSL  R26
	ROL  R27
	ROL  R24
	ROL  R25
	ROL  R0
	ROL  R1
	ROL  R20
	ROL  R21
	SUB  R0,R30
	SBC  R1,R31
	SBC  R20,R22
	SBC  R21,R23
	BRCC __DIVD21U2
	ADD  R0,R30
	ADC  R1,R31
	ADC  R20,R22
	ADC  R21,R23
	RJMP __DIVD21U3
__DIVD21U2:
	SBR  R26,1
__DIVD21U3:
	DEC  R19
	BRNE __DIVD21U1
	MOVW R30,R26
	MOVW R22,R24
	MOVW R26,R0
	MOVW R24,R20
	POP  R21
	POP  R20
	POP  R19
	RET

__MODD21U:
	RCALL __DIVD21U
	MOVW R30,R26
	MOVW R22,R24
	RET

__GETW1P:
	LD   R30,X+
	LD   R31,X
	SBIW R26,1
	RET

__GETD1P:
	LD   R30,X+
	LD   R31,X+
	LD   R22,X+
	LD   R23,X
	SBIW R26,3
	RET

__GETD1P_INC:
	LD   R30,X+
	LD   R31,X+
	LD   R22,X+
	LD   R23,X+
	RET

__PUTDP1_DEC:
	ST   -X,R23
	ST   -X,R22
	ST   -X,R31
	ST   -X,R30
	RET

__GETD1S0:
	LD   R30,Y
	LDD  R31,Y+1
	LDD  R22,Y+2
	LDD  R23,Y+3
	RET

__GETD2S0:
	LD   R26,Y
	LDD  R27,Y+1
	LDD  R24,Y+2
	LDD  R25,Y+3
	RET

__PUTD1S0:
	ST   Y,R30
	STD  Y+1,R31
	STD  Y+2,R22
	STD  Y+3,R23
	RET

__PUTPARD1:
	ST   -Y,R23
	ST   -Y,R22
	ST   -Y,R31
	ST   -Y,R30
	RET

__CPD10:
	SBIW R30,0
	SBCI R22,0
	SBCI R23,0
	RET

__CPD12:
	CP   R30,R26
	CPC  R31,R27
	CPC  R22,R24
	CPC  R23,R25
	RET

__CPD21:
	CP   R26,R30
	CPC  R27,R31
	CPC  R24,R22
	CPC  R25,R23
	RET

__SAVELOCR6:
	ST   -Y,R21
__SAVELOCR5:
	ST   -Y,R20
__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR6:
	LDD  R21,Y+5
__LOADLOCR5:
	LDD  R20,Y+4
__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

__INITLOCB:
__INITLOCW:
	ADD  R26,R28
	ADC  R27,R29
__INITLOC0:
	LPM  R0,Z+
	ST   X+,R0
	DEC  R24
	BRNE __INITLOC0
	RET

;END OF CODE MARKER
__END_OF_CODE:
