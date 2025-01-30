#include <avr/wdt.h>

const int U_Pin = 7; 
const int D_Pin = 6; 

const int U_Out = 11; 
const int D_Out = 12; 
bool DEBUG = true;

void setup() 
{
  Serial.begin(38400);
  wdt_enable(WDTO_2S);

  pinMode(U_Pin,INPUT_PULLUP);
  pinMode(D_Pin,INPUT_PULLUP);
  
  pinMode(U_Out,OUTPUT);
  digitalWrite(U_Out,LOW);
  
  pinMode(D_Out,OUTPUT);
  digitalWrite(D_Out,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  sendCommand("AT+CIPSERVER=1,1001\r\n",250,DEBUG); // turn on server on port 80  
  sendCommand("AT+CIPMUX=1\r\n",250,DEBUG); // configure for multiple connections
  sendCommand("AT+CIPSTO=3\r\n",250,DEBUG);
}

void loop() 
{
  while (true) 
  {
    wdt_reset();
    if(Serial.available()) // check if the esp is sending a message 
    {
      if(Serial.find("+IPD,"))
      {
        delay(100);
        int connectionId = Serial.read()-48;
        Serial.find("o=");
        char order = (Serial.read()); 
      
        String content = "FB :";
        content+= order;
        content+= " OK ";
        sendCIPData(connectionId,content);   
             
        String closeCommand = "AT+CIPCLOSE=";
        closeCommand +=connectionId;
        closeCommand +="\r\n"; // append connection id     
        sendCommand(closeCommand,200,DEBUG); // close connection***1000

        
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

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";  
    int dataSize = command.length();
    char data[dataSize];
    command.toCharArray(data,dataSize);   
    Serial.write(data,dataSize); // send the read character to the esp8266
    
    long int time = millis();
    while( (time+timeout) > millis())
    {
      while(Serial.available())
      {     
        char c = Serial.read(); // read the next character.
        response+=c;   
      }  
    }
    
    wdt_reset();
    return response;
}


String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";         
    Serial.print(command); // send the read character to the esp8266
    
    long int time = millis();
    bool ok = false;
    while( (time+timeout) > millis() || ok)
    {
      while(Serial.available())
      { 
        char c = Serial.read(); // read the next character.
        response+=c;
      }  
    }  
    wdt_reset();
    return response;
}



