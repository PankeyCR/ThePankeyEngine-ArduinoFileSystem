
#include "arduino_logger.hpp"

#define pankey_ESP32_S3_EYE

//#define ArduinoSDFile_Log
//#define pankey_Global_Log
//#define pankey_Arduino_Log

#include <SD_MMC.h>
#include "ArduinoSDFile.hpp"

using namespace pankey::ArduinoFileSystem;

void setup() {
  Serial.begin(9600);
  
  delay(3000);
  Serial.println("start sd example");
  
  ArduinoSDFile<fs::SDMMCFS> file = SD_MMC;
  file.initialize();
  bool isopen = file.open("/pankey.txt", FILE_WRITE);
  if(isopen){
    Serial.println("is open");
  }
  file.close();
}

void loop() {}