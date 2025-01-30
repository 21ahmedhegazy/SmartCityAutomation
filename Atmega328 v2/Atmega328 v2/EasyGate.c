#include <mega328p.h>
#include <delay.h>
#include <stdio.h>
#include <string.h>

#define  uchar unsigned char   // 0~255
#define  uint  unsigned int    // 0~65535
#define  ulong unsigned long   // 0~4,294,967,295

#define  esp8266_print   puts
#define  esp8266_read    gets
#define  wdt_reset()    #asm("wdr")

#define  Out_Up     PORTD.6 //  n6-o4
#define  Out_Dn     PORTD.7 //  n7-o5
#define  Out_R      PORTD.2 //

#define  DEBUG 1

ulong millis=0;
ulong previousMillis=0;
uint  interval=2000;

uchar *AtCommand(uchar *command, const int timeout, int debug);
uchar *AtData(uchar *data, const int timeout, int debug);
void CIPData(uchar *connectionId, uchar *data);
void init_esp(void);

void test()
{
    Out_Up=1;
    Out_Dn=1;
    delay_ms(300);
    Out_Up=0;
    Out_Dn=0;
}
//------------------------------------
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    // Reinitialize Timer 0 value
    TCNT0=0x83;  //TCNT0=0x53;
    // Place your code here
    millis++;
}
//--USART-----------------------------------
int esp8266_available(void) {
	if (UCSR0A & (1 << RXC0))
    {
		return 1;

	}
	else
    {
		return 0;
	}
}
//------------------------------------------
void init_all()
{
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTB=0x00;
DDRB=0x04;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTC=0x39;
DDRC=0x00;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=Out Func1=In Func0=In
// State7=0 State6=0 State5=0 State4=0 State3=P State2=0 State1=T State0=T
PORTD=0x08;
DDRD=0xF4;

// Timer/Counter 0 initialization
// Clock source: System Clock 8M-11.059M / 64
// Clock value: 125.000 kHz - 172.800 kHz
TCCR0A=0x00;
TCCR0B=0x03;
TCNT0=0x83;  //0x53
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x01;

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x00;

// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 115200
UCSR0A=0x00;
UCSR0B=0x18;
UCSR0C=0x06;
UBRR0H=0x00;
UBRR0L=0x05;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// Watchdog Timer initialization
// Watchdog Timer Prescaler: OSC/256k
// Watchdog Timer interrupt: Off
#pragma optsize-
#asm("wdr")
WDTCSR=0x1F;
WDTCSR=0x0F; // 2 sec
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Global enable interrupts
#asm("sei")
}
//------------------------------------------
void main(void)
{
    uchar idx[1];
    uchar buff[50];
    uchar stat[50];
    ulong currentMillis=0;
    //Out_R=1;

    init_all();
    init_esp();
    ////esp8266.setTimeout(300);

    if(DEBUG)
    {
        //Serial.println("start");
    }

    while(1)
    {
        currentMillis = millis;
        wdt_reset();

        if(esp8266_available())
        {
            //delay_ms(200);
            //+IPD,0,4:o=u

            esp8266_read(buff,50);
            if(strstr(buff, "+IPD"))
            {
                if(DEBUG)
                {
                    //Serial.println("available");
                }
                sprintf(idx,"%c",*(strstr(buff, "+IPD")+11));
                if(idx[0]=='u')
                {
                    sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));
                    CIPData(idx,"FB :u OK");
                    Out_Up=1;
                    Out_Dn=0;
                }
                else if(idx[0]=='d')
                {
                    sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));
                    CIPData(idx,"FB :d OK");
                    Out_Up=0;
                    Out_Dn=1;
                }
                else if(idx[0]=='s')
                {
                    sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));
                    CIPData(idx,"FB :s OK");
                    Out_Up=0;
                    Out_Dn=0;
                }
            }
        }
        else if(((unsigned long)(currentMillis - previousMillis) >= interval))
        {
                previousMillis = currentMillis;
                strcpy(stat,AtCommand("AT+CIPSTATUS\r\n",100,DEBUG));

                if(strstr(stat,":5") || strlen(stat) ==0)
                {
                    AtCommand("AT+RST\r\n",10000,DEBUG);
                    init_esp();

                    strcpy(stat,AtCommand("AT+CIPSTATUS\r\n",100,DEBUG));
                    if(strstr(stat,":5") || strlen(stat) ==0)
                    {
                        Out_R=0; delay_ms(1000); wdt_reset();
                        Out_R=1; delay_ms(1000); wdt_reset();

                        init_esp();
                    }
                }
                else if(strstr(stat,":2"))
                {
                    AtCommand("AT+CIFSR\r\n",100,DEBUG); // get ip address
                    AtCommand("AT+CWJAP?\r\n",100,DEBUG);

                    AtCommand("AT+CIPMUX=1\r\n",150,DEBUG); // configure for multiple connections
                    AtCommand("AT+CIPSERVER=1,1001\r\n",150,DEBUG);// turn on server on port 80
                }
                else// if( stat.indexOf(":3") > -1 || stat.indexOf(":4") > -1)
                {
                }
          }
    }
}
//------------------------------------------
uchar *AtCommand(uchar *command, const int timeout, int debug)
{
    uchar response[100]="";
    ulong time = millis;
    bit ok = 0;
    esp8266_print(command);

    if(debug)
    {
      //Serial.print(command);
    }

    while(  !ok && (time+timeout) > millis )
    {
        wdt_reset();
        if(esp8266_available())
        {
           esp8266_read(response,50);
        }

       if(strstr(command,"CIPSEND"))
        {
            if(strstr(response,">"))
            ok = 1;
        }
//        else if(strstr(command,"CIPSTATUS") )
//        {
//            if(strstr(response,"STATUS") )
//            ok = 1;
//        }
        else
        {
            if(strstr(response,"OK")  || strstr(response,"no"))
            {
                ok = 1;
            }
        }
    }

    if(debug)
    {
      //Serial.print(response);
    }
    return response;
}

uchar *AtData(uchar *data,  const int timeout, int debug)
{
    uchar response[50] = "";
    bit ok = 0;
    ulong time = millis;

    esp8266_print(data);

    if(debug)
    {
      //Serial.println("\r\nFeedBack:");
      //Serial.write(data,dataSize);
    }

    while( (time+timeout) > millis && !ok)
    {
      wdt_reset();
      if(esp8266_available())
      {
          esp8266_read(response,10);
      }

      if(strstr(response,"OK"))
      {
          //Flash();
          ok = 1;
      }
    }

    if(debug)
    {
       //Serial.print(response);
    }

    return response;
}

void CIPData(uchar *connectionId, uchar *data)
{
   uchar buff[50]=""; //+IPD,0,4:o=u
   sprintf(buff,"AT+CIPSEND=%s,%d\r\n",connectionId,strlen(data));
   AtCommand(buff,200,DEBUG);//****1000

   AtData(data,200,DEBUG);//****1000

   sprintf(buff,"AT+CIPCLOSE=%s\r\n",connectionId);
   AtCommand(buff,200,DEBUG); // close connection***1000
}

void init_esp(void)
{
  //AT+CWJAP?
  //AtCommand("AT+CWAUTOCONN?\r\n",100,DEBUG);
  //AtCommand("AT+CWMODE?\r\n",100,DEBUG);
  //AtCommand("AT+CIPSTA_DEF?\r\n",100,DEBUG);
  //AtCommand("AT+RFPOWER=82",100,DEBUG);

  AtCommand("ATE0\r\n",100,DEBUG);

  AtCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  AtCommand("AT+CWAUTOCONN=1\r\n",100,DEBUG);
  AtCommand("AT+CWJAP_DEF=\"SmartLife\",\"Life@2020\"\r\n",10000,DEBUG);//,\"AC:5F:3E:48:17:E7\"   // \"Broo\",\"mrb131113\",\"60:83:34:29:2d:2c\" -- \"TP-LINK_7DEADE\",\"maf123456\",\"c4:e9:84:7d:ea:de\"
  AtCommand("AT+CIPSTA_DEF=\"192.168.1.150\",\"192.168.1.1\",\"255.255.255.0\"\r\n",500,DEBUG);

  AtCommand("AT+CIPMUX=1\r\n",150,DEBUG); // configure for multiple connections
  AtCommand("AT+CIPSERVER=1,1001\r\n",150,DEBUG); // turn on server on port 1001
  AtCommand("AT+CIPSTO=10\r\n",150,DEBUG);

  AtCommand("AT+CIPSTATUS\r\n",100,DEBUG); // check if =2 got ip or =5 not
  AtCommand("AT+CIFSR\r\n",100,DEBUG); // get ip address
  AtCommand("AT+CWJAP?\r\n",100,DEBUG);

}