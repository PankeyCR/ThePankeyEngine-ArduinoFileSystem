
#include "arduino_logger.hpp"

#define pankey_ESP32_S3_EYE

//#define ArduinoSDFile_Log
//#define pankey_Global_Log
//#define pankey_Arduino_Log

#include <SD_MMC.h>
#include "ArduinoSDFile.hpp"
#include "CharArray.hpp"

using namespace pankey::Base;
using namespace pankey::ArduinoFileSystem;

void setup() {
  Serial.begin(9600);
  
  delay(3000);
  Serial.println("start sd example");
  
  ArduinoSDFile<fs::SDMMCFS> file = SD_MMC;
  file.initialize();
  
  bool isopen_1 = file.open("/pankey.txt", FILE_WRITE);
  if(isopen_1){
    Serial.println("is open");
    file.write("the pankey engine, sd test");
  }
  file.close();
  
  bool isopen_2 = file.open("/pankey.txt", FILE_READ);
  if(isopen_2){
    CharArray buffer = file.read(30);
    Serial.print("SD Data: ");
    Serial.println(buffer.pointer());
  }
  file.close();
}

void loop() {}