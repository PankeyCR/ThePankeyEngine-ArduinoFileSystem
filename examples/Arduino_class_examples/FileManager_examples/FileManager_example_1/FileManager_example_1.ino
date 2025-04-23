
#include "arduino_logger.hpp"

#define pankey_ESP32_S3_EYE

//#define ArduinoSDFile_Log
//#define pankey_Global_Log
//#define pankey_Arduino_Log

#include <SD_MMC.h>
#include "ArduinoSDFile.hpp"
#include "FileManager.hpp"

using namespace pankey::Arduino;
using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
  
  delay(3000);
  Serial.println("start sd example");
  
  ArduinoSDFile<fs::SDMMCFS> file = SD_MMC;
  FileManager manager = file;
  manager.createDir("pankey");
}

void loop() {}