#include <mega8.h>
#include <delay.h>
#include <stdio.h>
#include <string.h>
  
#define uchar unsigned char // 0~255
#define uint unsigned int   // 0~65535

#define  LEd   PORTC.0 // 
#define  Lamp  PORTC.1 //
#define  Led2  PORTC.2 //

#define  T0enb         TIMSK |= 0x01;
#define  T0dis         TIMSK &= 0xfe;
#define  T1OCA_enb     TIMSK |= 0x10;
#define  T1OCA_dis     TIMSK &= 0xef;
#define  T1OCB_enb     TIMSK |= 0x08;
#define  T1OCB_dis     TIMSK &= 0xf7;

unsigned long millis=0; 
unsigned long int previousMillis=0;   
unsigned int interval=2000; 

uchar *sendCIPData(int connectionId,uchar *data);
uchar *sendCommand(uchar *command, const int timeout, int debug);
uchar *sendData(uchar *command, const int timeout, int debug); 
//------------------------------------
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    // Reinitialize Timer 0 value
    TCNT0=0x53;
    // Place your code here
    millis++;
}
//--USART-----------------------------------
int is_RX_available(void) {
	if (UCSRA & (1 << RXC)) {
		return 1;
	}
	else {
		return 0;
	}
}

void AtCommand(unsigned char *cmd_buffer, unsigned char *feedback)
{
    bit ok;
    char buff[100] ;
    puts(cmd_buffer);      
    ok = 0;    
    while(!ok)
        {        
            gets(buff,5);
            if(strstr(buff, feedback) || strstr(buff, "no"))
            {         
                //Flash();
                ok=1;       
            }        
        }                
}

void AtData(unsigned char *data_buffer, unsigned char *id)
{
    bit ok;
    char buff[50];
    sprintf(buff,"AT+CIPSEND=%c,%d\r\n",*id,strlen(data_buffer));    
    puts(buff);   
           
    ok = 0;    
    while(!ok)
        {        
            if(getchar()==">")
            {         
                //Flash();
                ok=1;       
            }        
        } 
                
    puts(data_buffer); //FB :u OK
     
    ok = 0;    
    while(!ok)
        {    
            gets(buff,10);  
            if(strstr(buff, "OK"))
            {         
                //Flash();
                ok=1;       
            }
        }                
}
//------------------------------------------
void init_all()
{
// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=P 
PORTB=0x01;
DDRB=0x00;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0xFF;
    
// Port D initialization
// Func7=Out Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State7=1 State6=T State5=0 State4=0 State3=T State2=T State1=T State0=T 
PORTD=0x80;
DDRD=0xB0;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 10.800 kHz
// Mode: CTC top=OCR1A
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: On
TCCR1A=0x00;
TCCR1B=0x0D;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x82;
OCR1AL=0xC7;
OCR1BH=0x7E;
OCR1BL=0x8F;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x18;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 38400
UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x11;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

//// Watchdog Timer initialization
//// Watchdog Timer Prescaler: OSC/1024k
//#pragma optsize-
//WDTCR=0x1E;
//WDTCR=0x0E;
//#ifdef _OPTIMIZE_SIZE_
//#pragma optsize+
//#endif

// Global enable interrupts
#asm("sei")
}
//------------------------------------------
void reset(void)
{
        PORTB.0=0;
        delay_ms(500);                                               
        PORTB.0=1;
        delay_ms(100); 
        
}

void main(void)
{   
    unsigned char buff[50]; 
    char idx[5] ;
    init_all();     
    PORTB.0=1; 
    //Flash();   
                    
    AtCommand("AT\r\n","OK");
    AtCommand("AT+CWJAP=\"Broo\",\"mrb131113\"\r\n","OK");  
    AtCommand("AT+CIPMUX=1\r\n","OK"); 
    AtCommand("AT+CIPSTO=2\r\n","OK");  
    AtCommand("AT+CIPSERVER=1,1001\r\n","OK");    
                          
    //+IPD,0,4:o=u  
    while(1)
    {    
        if(is_RX_available()==1)   
        {
        gets(buff,50);   
        if(strstr(buff, "+IPD")) 
        {                   
            sprintf(idx,"%c",*(strstr(buff, "+IPD")+11)); 

            if(idx[0]=='u')
            {   
                sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));   
                AtData("FB :u OK",idx);   
                sprintf(buff,"AT+CIPCLOSE=%c\r\n",*idx);              
                AtCommand(buff,"OK");
                Lamp=1;   
                reset();
            }
            else if(idx[0]=='d')
            {
                sprintf(idx,"%c",*(strstr(buff, "+IPD")+5));        
                AtData("FB :d OK",idx);       
                sprintf(buff,"AT+CIPCLOSE=%c\r\n",*idx); 
                AtCommand(buff,"OK");
                Lamp=0; 
                reset();
            }    
        }   
        } 
    }         
}
//------------------------------------------
uchar *sendCIPData(int connectionId, uchar *data)
{

   uchar *cipSend = "AT+CIPSEND=";
   strcat(cipSend, connectionId);   
   strcatf(cipSend, ",");
   strcat(cipSend, strlen(data));
   strcatf(cipSend, "\r\n");
   sendCommand(cipSend,400,DEBUG);//****1000
   sendData(data,600,DEBUG);//****1000      
   
   String closeCommand = "AT+CIPCLOSE="; 
   closeCommand+=connectionId; // append connection id
   closeCommand+="\r\n";
   sendCommand(closeCommand,200,DEBUG); // close connection***1000  
}

uchar *sendCommand(uchar *command, const int timeout, int debug)
{
    String response = "";  
    bool ok = false;     
    esp8266.print(command); // send the read character to the esp8266
    if(debug)
    {
      Serial.print(command);
    }
    
    long int time = millis();
    while( (time+timeout) > millis() && !ok)
    {
      wdt_reset();
      while(esp8266.available())
      { 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }
      
      if(command.indexOf("CIPSEND") > -1)
      {
        if(response.indexOf(">") > -1)
          ok = true; 
      }
      else if(command.indexOf("CIPSTATUS") > -1)
      {
        if(response.indexOf("STATUS") > -1)
          ok = true; 
      }
      else
      {
        if(response.indexOf("OK") > -1 || response.indexOf("no") > -1)
          ok = true; 
      }  
          
    }

    if(debug)
    {
      Serial.print(response);
    }
    return response;
}

uchar *sendData(uchar *command, const int timeout, int debug)
{
    uchar *response = "";
    bool ok = false;
    int dataSize = command.length();
    char data[dataSize];
    command.toCharArray(data,dataSize);        
    esp8266.write(data,dataSize); // send the read character to the esp8266
    
    if(debug)
    {
      Serial.println("\r\nFeedBack:");
      Serial.write(data,dataSize);
    }
    
    long int time = millis();  
    while( (time+timeout) > millis() && !ok)
    {
      wdt_reset();
      while(esp8266.available())
      {     
        char c = esp8266.read(); // read the next character.
        response+=c;
      } 
      if(response.indexOf("OK") > -1)
          ok = true;
    }
    
    if(debug)
      Serial.print(response);
    return response;
}


