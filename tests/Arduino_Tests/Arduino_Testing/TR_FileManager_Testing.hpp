
#ifndef TR_FileManager_Testing_hpp
	#define TR_FileManager_Testing_hpp

	#define pankey_TTGO_T8_V1_8
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "FS.h"
	#include "SD.h"
	#include "FileManager.hpp"
	#include "ArduinoSDFile.hpp"

	namespace pankey{

		namespace Arduino{
		
			Base::TestResult TR_FileManager_Testing_1(){
				Base::TestResult result;
				
				return result;
			}

			void TR_FileManager_Testing(Base::TestRunner& a_test_runner){
				a_test_runner.add("ArduinoSDFile ", TR_FileManager_Testing_1);
			}		

		}		

	}

#endif
