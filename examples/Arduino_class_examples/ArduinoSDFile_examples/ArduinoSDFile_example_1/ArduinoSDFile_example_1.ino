
#include "arduino_logger.hpp"

#define pankey_TTGO_T8_V1_8

//#define ArduinoSDFile_Log
//#define pankey_Global_Log
//#define pankey_Arduino_Log

#include "FS.h"
#include "SD.h"
#include "ArduinoSDFile.hpp"

using namespace pankey::ArduinoFileSystem;

void setup() {
  Serial.begin(9600);
  
  delay(3000);
  Serial.println("start sd example");
  
  ArduinoSDFile<fs::SDFS> file = SD;
  file.initialize();
  bool isopen = file.open("/pankey.txt", FILE_WRITE);
  if(isopen){
    Serial.println("is open");
  }
  file.close();
}

void loop() {}
