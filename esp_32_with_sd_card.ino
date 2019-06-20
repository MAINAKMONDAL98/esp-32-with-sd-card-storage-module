/*
 * Connect the SD card to the following pins:
 *https://github.com/MAINAKMONDAL98
 * ESP WROOM 32 | SD CARD
 *     D5         CS
 *     D18        SCK
 *     D23        MOSI
 *     D19        MISO
 *     VIN        VCC
 *     GND        GND
 */
#include "FS.h"
#include "SD.h"
#include "SPI.h"
int a = 10;


void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void setup(){
    Serial.begin(115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

 int a = 10;
  char d[8];
  dtostrf(a,0,0,d);
  delay(10000);
  writeFile(SD, "/hello.txt", d);  
createDir(SD, "/hello.txt");
}

void loop(){
  appendFile(SD, "/hello.txt", ",\n");
  char b[8];
   //int a =10;
  a= a+1;
  Serial.println(a);
  char d[8];
  dtostrf(a,0,0,d);

 appendFile(SD, "/hello.txt", d);
 
 delay(10000);
 Serial.println("fngnfgn)");
 uint64_t cardSize = SD.cardSize();
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    
   Serial.println(b);
}
