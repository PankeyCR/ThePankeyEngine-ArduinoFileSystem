
#include "arduino_logger.hpp"

#define pankey_TTGO_T8_V1_8

//#define ArduinoSDFile_Log
//#define pankey_Global_Log
//#define pankey_Arduino_Log

#include "FS.h"
#include "SD.h"
#include "ArduinoSDFile.hpp"
#include "ArrayPointer.hpp"

using namespace pankey::Base;
using namespace pankey::ArduinoFileSystem;

void setup() {
  Serial.begin(9600);
  
  delay(3000);
  Serial.println("start sd example");

  int array_size = 10000;

  ArrayPointer<float> i_values;
  i_values.createArrayFast(array_size);

  for(int x = 0; x < array_size; x++){
    i_values.addFast(15.5f);
  }
  
  ArduinoSDFile<fs::SDFS> file = SD;
  file.initialize();
  bool isopen = file.open("/pankey.txt", FILE_WRITE);
  if(isopen){
    Serial.println("is open");
    file.writeArray<float>(i_values, array_size);
  }
  file.close();
}

void loop() {}
