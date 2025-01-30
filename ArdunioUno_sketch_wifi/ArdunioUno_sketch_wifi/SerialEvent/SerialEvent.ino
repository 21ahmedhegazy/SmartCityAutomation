#include <avr/wdt.h>
#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(2,3);

const int U_Pin = 7; 
const int D_Pin = 6; 

const int U_Out = 11; 
const int D_Out = 12; 
bool DEBUG = true;

void setup() 
{
  Serial.begin(115200);
  esp8266.begin(38400);
  esp8266.setTimeout(300);
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

  Serial.println("start");
}

void loop() 
{
  Serial.println("start");
  while (true) 
  {
    Serial.println("Live");
    esp8266.end();
    delay(100);
    wdt_reset();
    if(esp8266.available()) // check if the esp is sending a message 
    {
      Serial.println("available");
    
      if(esp8266.find("+IPD,"))
      {
        delay(100);
        int connectionId = esp8266.read()-48;
        esp8266.find("o=");
        char order = (esp8266.read()); 
      
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
       //if(response.indexOf("OK") > -1)
       // break;
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    wdt_reset();
    return response;
}


String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";
           
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    bool ok = false;
    while( (time+timeout) > millis() || ok)
    {
      while(esp8266.available())
      { 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }  
    Serial.print(response);
    wdt_reset();
    return response;
}



