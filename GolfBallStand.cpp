#include "Arduino.h"
#include "GolfBallStand.h"

GolfBallStand::GolfBallStand() {
	_init();
}

void GolfBallStand::_init() {
	pinMode(PIN_LED_1_UNDER, OUTPUT);
	pinMode(PIN_LED_1_FRONT, OUTPUT);
	pinMode(PIN_LED_2_UNDER, OUTPUT);
	pinMode(PIN_LED_2_FRONT, OUTPUT);
	pinMode(PIN_LED_3_UNDER, OUTPUT);
	pinMode(PIN_LED_3_FRONT, OUTPUT);
	pinMode(PIN_RED, OUTPUT);
	pinMode(PIN_GREEN, OUTPUT);
	pinMode(PIN_BLUE, OUTPUT);
	pinMode(PIN_GOLF_BALL_STAND_SWITCH, INPUT_PULLUP);
	digitalWrite(PIN_LED_1_UNDER, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_1_FRONT, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_2_UNDER, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_2_FRONT, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_3_UNDER, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_3_FRONT, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_RED, COLOR_TRANSISTOR_OFF);
	digitalWrite(PIN_GREEN, COLOR_TRANSISTOR_OFF);
	digitalWrite(PIN_BLUE, COLOR_TRANSISTOR_OFF);
}

void GolfBallStand::setLedState(int ledColor, int location, int underOrFront) {
	// Start by clearing off all LEDs and colors.
	digitalWrite(PIN_RED, COLOR_TRANSISTOR_OFF);
	digitalWrite(PIN_GREEN, COLOR_TRANSISTOR_OFF);
	digitalWrite(PIN_BLUE, COLOR_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_1_UNDER, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_2_UNDER, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_3_UNDER, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_1_FRONT, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_2_FRONT, LED_TRANSISTOR_OFF);
	digitalWrite(PIN_LED_3_FRONT, LED_TRANSISTOR_OFF);

	// Decide which of the six LEDs to turn on.
	if ((location & LOCATION_1) && (underOrFront & LED_UNDER)) {
		digitalWrite(PIN_LED_1_UNDER, LED_TRANSISTOR_ON);
	}
	if ((location & LOCATION_1) && (underOrFront & LED_FRONT)) {
		digitalWrite(PIN_LED_1_FRONT, LED_TRANSISTOR_ON);
	}
	if ((location & LOCATION_2) && (underOrFront & LED_UNDER)) {
		digitalWrite(PIN_LED_2_UNDER, LED_TRANSISTOR_ON);
	}
	if ((location & LOCATION_2) && (underOrFront & LED_FRONT)) {
		digitalWrite(PIN_LED_2_FRONT, LED_TRANSISTOR_ON);
	}
	if ((location & LOCATION_3) && (underOrFront & LED_UNDER)) {
		digitalWrite(PIN_LED_3_UNDER, LED_TRANSISTOR_ON);
	}
	if ((location & LOCATION_3) && (underOrFront & LED_FRONT)) {
		digitalWrite(PIN_LED_3_FRONT, LED_TRANSISTOR_ON);
	}

	// Set the color.
	if (ledColor & LED_BLUE) {
		digitalWrite(PIN_BLUE, COLOR_TRANSISTOR_ON);
	}
	if (ledColor & LED_GREEN) {
		digitalWrite(PIN_GREEN, COLOR_TRANSISTOR_ON);
	}
	if (ledColor & LED_RED) {
		digitalWrite(PIN_RED, COLOR_TRANSISTOR_ON);
	}
}

int GolfBallStand::getAnalogReading(int location) {
	int photoReading = -1;
	switch (location) {
	case LOCATION_1:
		photoReading = analogRead(PIN_PHOTO_1);
		break;
	case LOCATION_2:
		photoReading = analogRead(PIN_PHOTO_2);
		break;
	case LOCATION_3:
		photoReading = analogRead(PIN_PHOTO_3);
		break;
	case LOCATION_EXTERNAL:
		photoReading = analogRead(PIN_PHOTO_EXTERNAL);
		break;
	}
	return photoReading;
}

int GolfBallStand::determineBallColor(int location) {
	int returnBallType = BALL_NONE;
	setLedState(LED_OFF, location, LED_UNDER_AND_FRONT);
	delay(GBS_TIME_DELAY);
	int offReading = getAnalogReading(location);

	setLedState(LED_RED, location, LED_UNDER_AND_FRONT);
	delay(GBS_TIME_DELAY);
	int redReading = getAnalogReading(location);

	setLedState(LED_GREEN, location, LED_UNDER_AND_FRONT);
	delay(GBS_TIME_DELAY);
	int greenReading = getAnalogReading(location);

	setLedState(LED_BLUE, location, LED_UNDER_AND_FRONT);
	delay(GBS_TIME_DELAY);
	int blueReading = getAnalogReading(location);

	setLedState(LED_WHITE, location, LED_UNDER_AND_FRONT);
	delay(GBS_TIME_DELAY);
	int whiteReading = getAnalogReading(location);

	setLedState(LED_OFF, location, LED_UNDER_AND_FRONT);

	// TODO: Figure out the ball color.
	// Example of an overly simple solution.

// ************************************************
	// if (offReading < 950) {
	// // Could use the external sensor instead of a hardcode 950.
	// 	returnBallType = BALL_NONE;
	// } else {
// ************************************************

	// Passed the offReading test, now use other color tests.
// Call a ball Black or non-black only based on whiteReading.
		// if(whiteReading < 300){
		// 	returnBallType = BALL_WHITE;
		// }else if(redReading < 700) {
		// 	returnBallType = BALL_RED;
		// }else if(greenReading < 900) {
		// 	returnBallType = BALL_GREEN;
		// }else if(blueReading < 950) {
		// 	returnBallType = BALL_BLUE;
		// }else if(whiteReading > 700) {
		// 	returnBallType = BALL_BLACK;
		// }else{
		// 	returnBallType = BALL_YELLOW;
		// }
		if(location == 1){
			if (offReading < 750) {
				returnBallType = BALL_NONE;
			}else if(whiteReading < 225 && blueReading < 610){
				returnBallType = BALL_WHITE;
			} else if(whiteReading > 750 && greenReading > 825 && blueReading > 875){
				returnBallType = BALL_BLACK;
			} else if(redReading < 325){
				returnBallType = BALL_YELLOW;
			} else if(redReading < 590) {
				returnBallType = BALL_RED;
			} else if(greenReading < 650){
				returnBallType = BALL_GREEN;
			} else {
				returnBallType = BALL_BLUE;
			}
		} else if (location == 2) {
			if (offReading < 675) {
				returnBallType = BALL_NONE;
			}else if(greenReading < 325 && blueReading < 610){
				returnBallType = BALL_WHITE;
			} else if(whiteReading > 700 && redReading > 900){
				returnBallType = BALL_BLACK;
			} else if(whiteReading < 450){
				returnBallType = BALL_YELLOW;
			} else if(redReading < 650) {
				returnBallType = BALL_RED;
			} else if(whiteReading < 625){
				returnBallType = BALL_GREEN;
			} else {
				returnBallType = BALL_BLUE;
			}
		} else {
			if (offReading < 775) {
				returnBallType = BALL_NONE;
			}else if(redReading < 475 && blueReading < 410){
				returnBallType = BALL_WHITE;
			} else if(whiteReading > 725 && blueReading > 800){
				returnBallType = BALL_BLACK;
			} else if(redReading < 475){
				returnBallType = BALL_YELLOW;
			} else if(redReading < 750) {
				returnBallType = BALL_RED;
			} else if(whiteReading > 610){
				returnBallType = BALL_GREEN;
			} else {
				returnBallType = BALL_BLUE;
			}
		}




			// if(location == 1){
			// 	if (whiteReading < 700) {
			// 		returnBallType = BALL_WHITE; // Non-black
			// 	} else {
			// 		returnBallType = BALL_BLACK;
			// 	}
			// } else if(location == 2) {
			// 	if (blueReading > 800) {
			// 		returnBallType = BALL_BLUE;
			// 	} else {
			// 		returnBallType = BALL_YELLOW;
			// 	}
			// } else {
			// 	if(redReading < 800) {
			// 		returnBallType = BALL_RED;
			// 	} else {
			// 		returnBallType = BALL_GREEN;
			// 	}
			// }
	// }



	Serial.println();
	Serial.print("Readings for location ");
	Serial.println(location == LOCATION_3 ? 3 : location);
	Serial.print("  LED off reading   = ");
	Serial.println(offReading);
	Serial.print("  LED red reading   = ");
	Serial.println(redReading);
	Serial.print("  LED green reading = ");
	Serial.println(greenReading);
	Serial.print("  LED blue reading  = ");
	Serial.println(blueReading);
	Serial.print("  LED white reading = ");
	Serial.println(whiteReading);

	return returnBallType;
}
