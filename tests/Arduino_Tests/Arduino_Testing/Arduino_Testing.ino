
#include "TestRunner.hpp"

#include "TR_FileManager_Testing.hpp"

using namespace pankey::Base;
using namespace pankey::Arduino;

void Start(){
  Serial.println("Start Test");
}

void End(){
  Serial.println("End Test");
}

void Info(const CharArray& a_test, const CharArray& a_info){
  Serial.print("Test: ");Serial.println(a_test.pointer());
  Serial.println(a_info.pointer());
}

void Error(const CharArray& a_test, const CharArray& a_error){
  Serial.print("Test: ");Serial.println(a_test.pointer());
  Serial.println(a_error.pointer());
}

void Succes(){
  Serial.println("Test Complete with no errors");
}

TestRunner tester;

void setup() {
  Serial.begin(9600);

  TR_FileManager_Testing(tester);
  
  tester.output(Start, End, Info, Error, Succes);
}

void loop() {
  tester.runTest();
  tester.run();
  delay(3000);
}