#ifndef _CONFIG_h
	#define _CONFIG_h

	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif

	// Use if debug information over serial required
	#define DEBUG

	// Definition of Pipe
	const uint64_t pipe = 0xE8E8F0F0E1LL;

	// For Mega2560
	#ifdef __AVR_ATmega2560__
		//Pin definition
		#define CEPIN 9
		#define CSPIN 10

		//Definition of Serial ports
		#define SERIALIO Serial1
		#define DEBUGSERIAL Serial
	#endif

	// For Arduino Nano
	#ifdef ARDUINO_AVR_NANO
		//Pin definition

		//nRF24: 
		/*nRF24 > Ardunio nano
		------------------------
		VCC   > 3.3 V
		GND   > GND
		MOSI  > 11
		MISO  > 12
		SCK   > 13
		IRQ   > not connected*/
		#define CEPIN 9
		#define CSPIN 10
		/*VESC UART
		VESC    Arduino Nano
		VCC   > 5V      (black wire)  
		GND   > GND     (white wire)
		TX    > RX      (orange wire)
		RX    > TX      (green wire)
		*/
		// Definition of Serial ports
		#define SERIALIO Serial
		#define DEBUGSERIAL Serial
	#endif

	// Settings for Nunchuk control
	#define SET_NUNCHUK_CONTROL


	// Setting for current control
	// #define SET_CURRENT_CONTROL
	#define DEADBAND_POS 1
	#define DEADBAND_NEG -1

	// Settings for remote
	#define TIMEOUTMAX  500

	////Define remote Package
	//
	//struct remotePackage {
	//  
	//  int   valXJoy;
	//  int   valYJoy;
	//  boolean valUpperButton;
	//  boolean valLowerButton;
	//  
	//} ; >> moved to datatypes.h in lib VescUartControl
#endif



