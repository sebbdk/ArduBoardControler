#include <SPI.h>

#include "Config.h"

//Using the nRF34 library from https://github.com/TMRh20/RF24
#include <nRF24L01.h>
#include "RF24.h"
#include "printf.h"

//Library for VESC UART
#include "VescUart.h"
#include "datatypes.h"
#include "local_datatypes.h"

//Define variables for remote
struct remotePackage remPack;
bool recOK = true;
uint32_t lastTimeReceived = 0;
struct bldcMeasure VescMeasuredValues;
int8_t persXJoy = 0;

RF24 radio(CEPIN, CSPIN);

void inline startRadio();
void inline doCurrentControl();

void setup() {
	#ifdef DEBUG
	  DEBUGSERIAL.begin(115200);
	  DEBUGSERIAL.println("Nrf24L01 Receiver Starting");
	#endif

	// Initialize REM package
	remPack.valXJoy			= 512; //middle Position
	remPack.valYJoy			= 512;
	remPack.valLowerButton	= 0;
	remPack.valLowerButton	= 0;

	//Initial for Radio
	SERIALIO.begin(115200);
	delay(1000);

	startRadio();
}

void loop() {
	//Getting Values from Vesc over UART
	if (VescUartGetValue(VescMeasuredValues)) {
		//	SerialPrint(VescMeasuredValues);
	} else {
		#ifdef DEBUG
			DEBUGSERIAL.println("Failed to get data from UART!");
		#endif // DEBUG
	}

	//writing package to TX in AckPayload
	//data will be send with next acknowledgement to TX
	radio.writeAckPayload(pipe, &VescMeasuredValues, sizeof(VescMeasuredValues));
		
	//Get data from TX	
	while (radio.available()) {
		radio.read(&remPack, sizeof(remPack));
		recOK = true;
	}
	
	uint32_t now = millis();
	if (recOK == true) {
		lastTimeReceived = millis();
		recOK = false;

		#ifdef DEBUG
			DEBUGSERIAL.println("Received TX successfully!");
		#endif
	} else if ((now - lastTimeReceived) > TIMEOUTMAX) { //Check if package were received within timeout
		remPack.valXJoy = 128; //middle Position
		remPack.valYJoy = 128;
		remPack.valUpperButton = false;
		remPack.valLowerButton = false;

		#ifdef DEBUG
			DEBUGSERIAL.println("TX-signal lost!!");
		#endif
	}

	#ifdef DEBUG
		DEBUGSERIAL.println("Received package / Package in main loop: ");
		DEBUGSERIAL.print("valXJoy = "); DEBUGSERIAL.print(remPack.valXJoy); DEBUGSERIAL.print(" valYJoy = "); DEBUGSERIAL.println(remPack.valYJoy);
		DEBUGSERIAL.print("LowerButton = "); DEBUGSERIAL.print(remPack.valLowerButton); DEBUGSERIAL.print(" UpperButton = "); DEBUGSERIAL.println(remPack.valUpperButton);
		DEBUGSERIAL.print("Calcx: "); DEBUGSERIAL.println(((float)persXJoy / 100) * 40.0);
	#endif

	#ifdef SET_NUNCHUK_CONTROL
		VescUartSetNunchukValues(remPack);
	#endif

	#ifdef SET_CURRENT_CONTROL
		doCurrentControl()
	#endif
}

void inline startRadio() {
	radio.begin();
	radio.enableAckPayload();
	radio.enableDynamicPayloads();
	radio.openReadingPipe(1, pipe);
	radio.startListening();
}

void inline doCurrentControl() {
	//ToDo: was only used for initial tests. Never realy tested while driving!! Needs to be checked if it should be used
	//Read the remote controls and control Vesc

	//Read the x-joystick and controls motor current and break
	persXJoy = map(remPack.valYJoy, 0, 255, -100, 100);

	//transform values read to int
	if (persXJoy > DEADBAND_POS) {
		VescUartSetCurrent(((float)persXJoy / 100) * 40.0);

		#ifdef DEBUG
			DEBUGSERIAL.println("Throttle");
		#endif
	} else if (persXJoy < DEADBAND_NEG) {
		VescUartSetCurrentBrake(((float)persXJoy / 100) * -3.0);

		#ifdef DEBUG
			DEBUGSERIAL.println("Break");
		#endif
	} else {
		VescUartSetCurrent(0.0);
		VescUartSetCurrentBrake(0.0);
	}
}
