/*

Platforms for this class:
	pankey_TTGO_T8_V1_8
	pankey_ESP32_S3_EYE
	pankey_ESP32_POE_ETHERNET
	pankey_ESP32_DEV
	pankey_TTGO_T7
	pankey_GENERIC_ARDUINO
	pankey_ADAFRUIT_FEATHER_M0

*/
#ifndef ArduinoSDFile_hpp
#define ArduinoSDFile_hpp

	#include "iFile.hpp"
	
	#if defined(pankey_TTGO_T8_V1_8)
		#include "SPI.h"
	#elif defined(pankey_ESP32_S3_EYE)
	
	#elif defined(pankey_ESP32_POE_ETHERNET)
		#include "SPI.h"
	#elif defined(pankey_ESP32_DEV)
		#include "SPI.h"
	#elif defined(pankey_TTGO_T7)
		#include "SPI.h"
	#elif defined(pankey_GENERIC_ARDUINO)
		#include "SPI.h"
	#elif defined(pankey_ADAFRUIT_FEATHER_M0)
		#include "SPI.h"
	#endif

	#if defined(pankey_Log) && (defined(ArduinoSDFile_Log) || defined(pankey_Global_Log) || defined(pankey_ArduinoFileSystem_Log))
		#include "Logger_status.hpp"
		#define ArduinoSDFileLog(status,method,mns) pankey_Log(status,"ArduinoSDFile",method,mns)
	#else
		#define ArduinoSDFileLog(status,method,mns)
	#endif


	namespace pankey{

		namespace ArduinoFileSystem{

			template<class T>
			class ArduinoSDFile : public FileSystem::iFile{
				public:
					static bool init;
					using FileSystem::iFile::readArray;
					using FileSystem::iFile::writeArray;

					ArduinoSDFile(){}
		
					ArduinoSDFile(const ArduinoSDFile& a_file) : m_sd(a_file.m_sd){
						ArduinoSDFileLog(pankey_Log_StartMethod, "Constructor",  "");
						ArduinoSDFileLog(pankey_Log_EndMethod, "Constructor",  "");
					}

					ArduinoSDFile(T& a_sd) : m_sd(a_sd){
						ArduinoSDFileLog(pankey_Log_StartMethod, "Constructor",  "");
						ArduinoSDFileLog(pankey_Log_EndMethod, "Constructor",  "");
					}
					virtual ~ArduinoSDFile(){}
		
					virtual void initialize(){
						ArduinoSDFileLog(pankey_Log_StartMethod, "initialize",  "");
						if(!init){
							init = true;
							#if defined(pankey_TTGO_T8_V1_8)
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  "ARDUINO_TTGO_T8_V1_8");
								SPI.begin(14, 2, 15, 13);//sclk , miso , mosi , cs
								m_sd.begin(13);
								uint8_t cardType = m_sd.cardType();
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  (cardType == CARD_NONE)?"No SD card attached":"SD card detected");
							#elif defined(pankey_ESP32_S3_EYE)
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  "ARDUINO_ESP32_S3_EYE");
								m_sd.setPins(39, 38, 40, 41, 42, 2);  // CLK, CMD, D0, D1, D2, D3
								SD_MMC.begin("/sdcard", true);
								uint8_t cardType = m_sd.cardType();
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  (cardType == CARD_NONE)?"No SD card attached":"SD card detected");
							#elif defined(pankey_ESP32_POE_ETHERNET)
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  "ARDUINO_ESP32_POE_ETHERNET");
								SPI.begin(14, 2, 15, 13);//sclk , miso , mosi , cs
								m_sd.begin(13);
								uint8_t cardType = m_sd.cardType();
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  (cardType == CARD_NONE)?"No SD card attached":"SD card detected");
							#elif defined(pankey_ESP32_DEV)
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  "ARDUINO_ESP32_DEV");
								SPI.begin(14, 2, 15, 13);
								m_sd.begin(13);
								uint8_t cardType = m_sd.cardType();
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  (cardType == CARD_NONE)?"No SD card attached":"SD card detected");
							#elif defined(pankey_TTGO_T7)
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  "ARDUINO_TTGO_T7_V14_Mini32");
								SPI.begin(21, 22, 19, 0);//sclk , miso , mosi , cs
								m_sd.begin(0);
								uint8_t cardType = m_sd.cardType();
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  (cardType == CARD_NONE)?"No SD card attached":"SD card detected");
							#elif defined(pankey_GENERIC_ARDUINO)
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  "ARDUINO_ARCH_AVR");
								m_sd.begin(4);
							#elif defined(pankey_ADAFRUIT_FEATHER_M0)
								ArduinoSDFileLog(pankey_Log_Statement, "initialize",  "ARDUINO_SAMD_ZERO");
								m_sd.begin(4);
							#endif
						}
						ArduinoSDFileLog(pankey_Log_EndMethod, "initialize",  "");
					}

					virtual bool open(const Base::CharArray& a_filename, const Base::CharArray& a_mode){
						ArduinoSDFileLog(pankey_Log_StartMethod, "open",  "");
						ArduinoSDFileLog(pankey_Log_Statement, "open",  "FileName: ");
						ArduinoSDFileLog(pankey_Log_Statement, "open",  a_filename.pointer());
						ArduinoSDFileLog(pankey_Log_Statement, "open",  "Mode: ");
						ArduinoSDFileLog(pankey_Log_Statement, "open",  a_mode.pointer());
						String i_path = a_filename.pointer();
						ArduinoSDFileLog(pankey_Log_Statement, "open",  "Path: ");
						ArduinoSDFileLog(pankey_Log_Statement, "open",  i_path);
						m_file = m_sd.open(i_path, a_mode.pointer());
						m_open = m_file;
						ArduinoSDFileLog(pankey_Log_Statement, "open",  m_file? "File has been open": "Failed to open file");
						ArduinoSDFileLog(pankey_Log_EndMethod, "open",  "");
						return m_open;
					}

					virtual void close(){
						ArduinoSDFileLog(pankey_Log_StartMethod, "close",  "");
						if(m_file){
							m_file.close();
							m_file = File();
							m_open = false;
						}
						ArduinoSDFileLog(pankey_Log_EndMethod, "close",  "");
					}

					virtual int read(Base::CharArray& a_buffer, int a_size){
						ArduinoSDFileLog(pankey_Log_StartMethod, "read",  "");
						if(!m_file){
							ArduinoSDFileLog(pankey_Log_EndMethod, "read",  "exiting with no file open");
							return -1;
						}
			
						a_buffer.clear();
						char i_char;
			
						for(int x = 0; x < a_size && m_file.available(); x++) {
							i_char = (char)m_file.read();
							if(i_char == '\0' || i_char == '\r'){
								ArduinoSDFileLog(pankey_Log_Statement, "read",  "i_char == 0 or r");
								break;
							}
							ArduinoSDFileLog(pankey_Log_Statement, "read",  "char read: ");
							ArduinoSDFileLog(pankey_Log_Statement, "read",  i_char);
							a_buffer.addLocalValue(i_char);
						}
			
						ArduinoSDFileLog(pankey_Log_EndMethod, "read",  "");
						return a_buffer.length();
					}

					virtual Base::CharArray read(int a_size){
						ArduinoSDFileLog(pankey_Log_StartMethod, "read",  "");
			
						Base::CharArray i_text;
						char i_char;
			
						while(m_file.available()){
							i_char = (char)m_file.read();
							if(i_char == '\0' || i_char == '\r'){
								ArduinoSDFileLog(pankey_Log_Statement, "read",  "i_char == 0 or r");
								break;
							}
							ArduinoSDFileLog(pankey_Log_Statement, "read",  i_char);
							i_text.addLocalValue(i_char);
						}
			
						ArduinoSDFileLog(pankey_Log_EndMethod, "read",  "");
						return i_text;
					}

					virtual int read(void* a_data, int a_count, Base::memory_size a_size){
						ArduinoSDFileLog(pankey_Log_StartMethod, "read",  "");

						Base::memory_size totalSize = a_count * a_size;
						int i_read = m_file.read((uint8_t*) a_data, totalSize);
			
						ArduinoSDFileLog(pankey_Log_Statement, "read",  "Total bytes read");
						ArduinoSDFileLog(pankey_Log_Statement, "read",  i_read);
			
						ArduinoSDFileLog(pankey_Log_EndMethod, "read",  "");
						return i_read;
					}

					virtual void write(const Base::CharArray& a_data){
						ArduinoSDFileLog(pankey_Log_StartMethod, "write",  "");

						String i_string = a_data.pointer();
						ArduinoSDFileLog(pankey_Log_Statement, "write",  i_string);
						m_file.print(i_string);

						ArduinoSDFileLog(pankey_Log_EndMethod, "write",  "");
					}

					virtual void write(const void* a_data, int a_count, Base::memory_size a_size){
						ArduinoSDFileLog(pankey_Log_StartMethod, "write",  "");

						Base::memory_size totalSize = a_count * a_size;
						m_file.write((const uint8_t*) a_data, totalSize);

						ArduinoSDFileLog(pankey_Log_EndMethod, "write",  "");
					}

					virtual bool seek(int a_position){
						return false;
					}
					virtual bool isOpen()const{
						return m_open;
					}

					virtual Base::CharArray pathSeparator() const{
						return "/";
					}

				protected:
					T& m_sd;
					File m_file;
					bool m_open = false;
			};

			template<class T>
			bool ArduinoSDFile<T>::init = false;
		}

	}

#endif