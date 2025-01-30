
#include <SoftwareSerial.h>
 
#define DEBUG true
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.

const int U_Pin = 7; 
const int D_Pin = 6; 

const int U_Out = 11; 
const int D_Out = 12; 
     
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  esp8266.begin(38400); // your esp's baud rate might be different // 38400
   
  pinMode(U_Pin,INPUT_PULLUP);
  pinMode(D_Pin,INPUT_PULLUP);
  
  pinMode(U_Out,OUTPUT);
  digitalWrite(U_Out,LOW);
  
  pinMode(D_Out,OUTPUT);
  digitalWrite(D_Out,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  //esp8266.print("AT+UART_DEF=115200,8,1,0,3");
  //esp8266.print("AT+UART=115200,8,1,0,3");
  
//  sendCommand("AT+RST\r\n",2000,DEBUG); // reset module
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point  
  sendCommand("AT+CIPSTA_DEF=\"192.168.1.55\",\"192.168.1.1\",\"255.255.0.0\"\r\n",1000,DEBUG); 
  sendCommand("AT+CWAUTOCONN=1\r\n",1000,DEBUG); 
  sendCommand("AT+CWJAP=\"Braa\",\"alaa131113\"\r\n",1000,DEBUG); // , "ca:d7:19:d8:a6:44" 

  delay(5000);
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendCommand("AT+CIPSERVER=1,1001\r\n",1000,DEBUG); // turn on server on port 80  
  sendCommand("AT+CIPSTATUS\r\n",1000,DEBUG); // check if =2 got ip or =5 not
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  
  Serial.println("Setup End");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(esp8266.available()) // check if the esp is sending a message 
  {
    delay(250); 
    if(esp8266.find("+IPD,"))
    {
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns                                       // the ASCII decimal value and 0 (the first decimal number) starts at 48
          
     esp8266.find("o="); // advance cursor to "pin="
     
     char order = (esp8266.read()); 
     //int pinNumber = (esp8266.read()-48); // get first number i.e. if the pin 13 then the 1st number is 1
     //int secondNumber = (esp8266.read()-48);
     //if(secondNumber>=0 && secondNumber<=9)
     //{
     //   pinNumber*=10;
     //   pinNumber +=secondNumber; // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
     //}

     // build string that is send back to device that is requesting pin toggle
     String content;
     content = "FB :";
     content += order;
     content += " OK ";
     
     sendCIPData(connectionId,content);
          
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendCommand(closeCommand,250,DEBUG); // close connection***1000
  
     digitalWrite(13,HIGH); // toggle led 

     int up = digitalRead(U_Pin); 
     int dn = digitalRead(D_Pin); 

     if(order=='u')
     {
        digitalWrite(U_Out,HIGH);
     }
     else if(order == 's')
     {
        digitalWrite(U_Out, LOW); // stop pin 
     }
     
     digitalWrite(13, LOW); // toggle led
   
    }
  }
}

void sendCIPData(int connectionId, String data)
{
   String cipSend = "AT+CIPSEND=";
   cipSend += connectionId;
   cipSend += ",";
   cipSend +=data.length();
   cipSend +="\r\n";
   sendCommand(cipSend,100,DEBUG);//****1000
   sendData(data,100,DEBUG);//****1000
}

String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";
           
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    int dataSize = command.length();
    char data[dataSize];
    command.toCharArray(data,dataSize);
           
    esp8266.write(data,dataSize); // send the read character to the esp8266
    if(debug)
    {
      Serial.println("\r\n=Smart=");
      Serial.write(data,dataSize);
    }
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}


