#include <Wire.h>
#include <Eeprom24Cxx.h>
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <IRLibRecvPCI.h> 
#include <SoftwareSerial.h>

int Tx = 7;
int Rx = 8;
SoftwareSerial bluetooth(Rx, Tx);


static Eeprom24C eeprom(32,0x50); //24C32

unsigned int device_and_address[3][4] = {{0, 220, 440, 660},{880, 1100, 1320, 1540},{1760, 1980, 2200, 2420}};
unsigned int device_command_datalength[3][4] = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}};
IRsendRaw mySender;
uint16_t raw_data[110];
uint16_t raw_data_send[110];
IRrecvPCI myReceiver(2);//pin number for the receiver
unsigned int address = 0;

byte received_length = 0;

String received_bluetooth_sequence = "";

void reset_raw_data(){
    for(int j = 0; j < 110; j++){
      raw_data[j] = 0;
    }
}

void reset_raw_data_send(){
    for(int j = 0; j < 110; j++){
      raw_data_send[j] = 0;
    }
}


void stuff_buffer(){
  raw_data[received_length-1] = 1000;
  raw_data[received_length] = 1000;
  received_length = 0;
}

void read_stack(unsigned int address){
  for(int i = 0; i < 110; i++){
    Serial.println(eeprom.read_2_byte(address+i*2));
  }
}

void write_stack(unsigned int address){
  for(int i = 0; i < 110; i++){
    eeprom.write_2_byte(address + i*2, raw_data[i]);
  }
}

void read_data_send(unsigned int address){
  for(int i = 0; i < 110; i++){
    raw_data_send[i] = eeprom.read_2_byte(address+i*2);
  }
}

void set_data_length(int device, int command, int received_length){
  device_command_datalength[device][command] = received_length;
}

void setup()
{
    Serial.begin(9600);
    while(!Serial){;}
    bluetooth.begin(9600);
    while(!bluetooth){;}
    delay(1000);
    reset_raw_data();
    reset_raw_data_send();
}

void loop()
{
  while(bluetooth.available())
  {
    char ch = bluetooth.read();
    if(ch == '#'){
      break;
    }
    received_bluetooth_sequence += ch;
  }
  if(received_bluetooth_sequence.length() == 4){
    Serial.println(received_bluetooth_sequence);
    byte device = received_bluetooth_sequence[1]-'0'-1;
    byte command = received_bluetooth_sequence[3]-'0'-1;
    Serial.println(device);
    Serial.println(command);
    address = device_and_address[device][command];
    Serial.println(address);
    myReceiver.enableIRIn();
    delay(2000);
    if(myReceiver.getResults()){
       received_length = recvGlobal.recvLength;
       Serial.println(F("First IR"));
       for(bufIndex_t i=1;i<recvGlobal.recvLength;i++) {
          Serial.print(recvGlobal.recvBuffer[i],DEC);
          Serial.print(F(", "));
          if( (i % 8)==0) Serial.print(F("\n\t"));
         raw_data[i-1] = recvGlobal.recvBuffer[i];
       }
       Serial.println(F("1000};"));
       Serial.print(F("Receive length = "));
       Serial.println(received_length);
    }
    
    myReceiver.enableIRIn();
    delay(200);
    if(myReceiver.getResults()){
      if(recvGlobal.recvLength > received_length){
        Serial.println(F("Second IR"));
        received_length = recvGlobal.recvLength;
        for(bufIndex_t i=1;i<recvGlobal.recvLength;i++) {
          Serial.print(recvGlobal.recvBuffer[i],DEC);
          Serial.print(F(", "));
          if( (i % 8)==0) Serial.print(F("\n\t"));
          raw_data[i-1] = recvGlobal.recvBuffer[i];
        }
        Serial.println(F("1000};"));
          Serial.print(F("Receive length = "));
          Serial.println(received_length);
      }
    }
    
    myReceiver.enableIRIn();
    delay(200);
    if(myReceiver.getResults()){
        if(recvGlobal.recvLength > received_length){
          Serial.println(F("Third IR"));
          received_length = recvGlobal.recvLength;
          for(bufIndex_t i=1;i<recvGlobal.recvLength;i++) {
            Serial.print(recvGlobal.recvBuffer[i],DEC);
            Serial.print(F(", "));
            if( (i % 8)==0) Serial.print(F("\n\t"));
            raw_data[i-1] = recvGlobal.recvBuffer[i];
          }
          Serial.println(F("1000};"));
          Serial.print(F("Receive length = "));
          Serial.println(received_length);
       }
    }
    Serial.print(F("raw_data[0] = "));
    Serial.println(raw_data[0]);
    set_data_length(device,command,received_length);
    if(raw_data[0] > 3000){
      //Serial.println(F("1"));
      stuff_buffer();

      //Serial.println(F("2"));
      write_stack(address);

      //Serial.println(F("3"));
      delay(100);
      reset_raw_data();
      
      //Serial.println(F("4"));
      read_stack(address);
      
      //Serial.println(F("5"));
      bluetooth.print(received_bluetooth_sequence);
      delay(100);
    }else{
        bluetooth.print("404");
    }
    received_bluetooth_sequence = "";
  }else{
    /*****************************************************************/
    if(received_bluetooth_sequence.length() == 2){
      //Serial.println(received_bluetooth_sequence);
      byte device = received_bluetooth_sequence[0]-'0'-1;
      byte command = received_bluetooth_sequence[1]-'0'-1;
      //Serial.println(device);
      //Serial.println(command);
      address = device_and_address[device][command];
      read_data_send(address);
      int RAW_DATA_LENGTH = device_command_datalength[device][command];
      mySender.send(raw_data_send,RAW_DATA_LENGTH,36);
      delay(1000);
      reset_raw_data_send();
      bluetooth.print(received_bluetooth_sequence);
      delay(100);
    }
  }
  
}
