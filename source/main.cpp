/**
 * File: main.cpp
 * Author: Ryan Williams
 * Date: 01-03-2019
 * Desc: Morse code sender and reciever written in c++ on a MicroBit
 */

#include <string.h>
#include "MicroBit.h"

MicroBit uBit;

// current time since power on in milliseconds	
uint64_t system_timer_current_time();
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);


typedef struct //Used to convert Morse to ASCII
{
    char* const morse;
    char* const ascii;
} morse_table_t;

int main() {
	uBit.init();

    char input[] = "";

    morse_table_t table[] = { {".-",    "A"},
                              {"-...",  "B"},
                              {"-.-.",  "C"},
                              {"-..",   "D"},
                              {".",     "E"},
                              {"..-.",  "F"},
                              {"--.",   "G"},
                              {"....",  "H"},
                              {"..",    "I"},
                              {".---",  "J"},
                              {"-.-",   "K"},
                              {".-..",  "L"},
                              {"--",    "M"},
                              {"-.",    "N"},
                              {"---",   "O"},
                              {".--.",  "P"},
                              {"--.-",  "Q"},
                              {".-.",   "R"},
                              {"...",   "S"},
                              {"-",     "T"},
                              {"..-",   "U"},
                              {"...-",  "V"},
                              {".--",   "W"},
                              {"-..-",  "X"},
                              {"-.--",  "Y"},
                              {"--..",  "Z"},
                              {"-----", "0"},
                              {".----", "1"},
                              {"..---", "2"},
                              {"...--", "3"},
                              {"....-", "4"},
                              {".....", "5"},
                              {"-....", "6"},
                              {"--...", "7"},
                              {"---..", "8"},
                              {"----.", "9"}

    };

    //For reading button presses
	bool pressed = false;
	bool pinRead = false;

	while(1){

        ///////////////////////////////WRITING//////////////////////////////////

		// Start counting Button
		uint64_t reading = system_timer_current_time();

		// Button held down
		while (buttonA.isPressed()) {
			pressed = true;
		}

		// How long was the button pressed
  		uint64_t delta = system_timer_current_time() - reading;

  		// After button press
  		if (pressed) {

  			// Is it a dot
  			if (delta < 500) {
  				uBit.display.print(".");
  				uBit.io.P0.setDigitalValue(1);
  				uBit.sleep(30);
  				uBit.io.P0.setDigitalValue(0);
  			}
  			// is it a dash
  			else if (delta > 500 && delta < 1000){
  				uBit.display.print("-");
  				uBit.io.P0.setDigitalValue(1);
  				uBit.sleep(80);
  				uBit.io.P0.setDigitalValue(0);
  			}
  			// Is it an END OF MESSAGE
  			else {
  				uBit.display.print("E");
                uBit.io.P0.setDigitalValue(1);
                uBit.sleep(151);
                uBit.io.P0.setDigitalValue(0);
  			}

  			// Reset
  			pressed = false;
  			uBit.display.clear();
  		}

  		///////////////////////////////READING//////////////////////////////////

  		// Read the pin
  		uint64_t pinIn = uBit.io.P0.getDigitalValue();

  		// If pin is turned on
  		if (pinIn == 1){

  			// Start counting Pin
  			uint64_t inReading = system_timer_current_time();
  			bool validMessage = false;


  			while (pinIn == 1){ //While pin is on
  				pinIn = uBit.io.P0.getDigitalValue();
  				pinRead = true;
  			}

  			// Count how long the pin was on for
  			uint64_t pinOnTime = system_timer_current_time() - inReading;


  			if (pinRead){ //If pin on enter "Reading Mode"

  				if (pinOnTime < 51){ // Was it a dot
  					strcat(input,".");
  				}
  				else if (pinOnTime > 51 && pinOnTime < 101){ //Was it a dash
                    strcat(input,"-");
  				}
  				else { //Was it end of message
  				    
                    pinRead = false;
                    uBit.display.clear();
                    char* segment;
                    int i;
                    segment = strtok(input, " ");

                    while(segment)
                    {
                        for(i=0; i < 36; ++i) //For every member in struct
                        {
                            if (!strcmp(segment, table[i].morse)) //If found display char
                            {
                                validMessage = true;
                                uBit.sleep(1000);
                                uBit.display.scroll(table[i].ascii);
                            }
                        }
                        segment = strtok(nullptr, " ");
                    }
                    if (!validMessage) //If message invalid alight top right pixel
                    {
                        uBit.display.image.setPixelValue(4,0,255);
                        uBit.sleep(2000);
                    }
                    memset(input, 0, sizeof input); //Clear input string for next char
  				}
                uBit.display.clear();
  			}
  		}
	}
}