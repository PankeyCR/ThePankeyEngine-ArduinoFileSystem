
#include "arduino_logger.hpp"

#define pankey_TTGO_T8_V1_8

// #define ArduinoSDFile_Log
//#define pankey_Global_Log
//#define pankey_Arduino_Log

#include "FS.h"
#include "SD.h"
#include "ArduinoSDFile.hpp"
#include "ArrayPointer.hpp"

using namespace pankey::Base;
using namespace pankey::ArduinoFileSystem;

int array_size = 10000;
ArrayPointer<float> g_values;

void setup() {
  Serial.begin(9600);
  
  delay(3000);
  Serial.println("start sd example");
  g_values.createArrayFast(array_size);
  
  ArduinoSDFile<fs::SDFS> file = SD;
  file.initialize();
  bool isopen = file.open("/pankey.txt", FILE_READ);
  if(isopen){
    Serial.println("is open");
    file.readArray<float>(g_values, array_size);
  }
  file.close();
}

void loop() {
  Serial.print("printing values from sd with length: ");
  Serial.println(g_values.length());
  for(int x = 0; x < g_values.length(); x++){
    float f_value = g_values.getFast(x);
    Serial.println(f_value);
  }
}
