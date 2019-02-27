//Morse Code Microbits
//yt build && cp /home/seed/IoT/Challenges/Challenge2/build/bbc-microbit-classic-gcc/source/challenge2-combined.hex /media/seed/MICROBIT

#include <string.h>
#include "MicroBit.h"

MicroBit uBit;

// current time since power on in milliseconds	
uint64_t system_timer_current_time();

// Setting button
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);

// Setting Pin
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);


typedef struct
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

    // For reading button
	bool pressed = false;
	bool pinRead = false;

	while(1){

		/* =================================================== */

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
  			// is it finished
  			else if (delta > 1000 && delta < 3000){
  				uBit.display.print("S");
  				uBit.io.P0.setDigitalValue(1);
  				uBit.sleep(130);
  				uBit.io.P0.setDigitalValue(0);
  			}
  			// Is it an error
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

  		/* ======================================================= */

  		// Read the pin
  		uint64_t pinIn = uBit.io.P0.getDigitalValue();

  		// If pin is turned on
  		if (pinIn == 1){

  			// Start counting Pin
  			uint64_t inReading = system_timer_current_time();

  			// While pin is on
  			while (pinIn == 1){
  				pinIn = uBit.io.P0.getDigitalValue();
  				pinRead = true;
  			}

  			// Count how long the pin was on for
  			uint64_t pinBlah = system_timer_current_time() - inReading;

  			// If the pin was turned on
  			if (pinRead){
  				// Was it a dot
  				if (pinBlah < 51){
  					//uBit.display.print(".");
  					strcat(input,".");
  					uBit.sleep(50);
  				}
  				// Was it a dash
  				else if (pinBlah > 51 && pinBlah < 101){
  					//uBit.display.print("-");
                    strcat(input,"-");
  					uBit.sleep(50);
  				}
  				// Was it Space
  				else if (pinBlah > 101 && pinBlah < 151){
                    //uBit.display.print("S");
                    strcat(input," ");
                    uBit.sleep(50);
  				}
  				// Was it an end
  				else {
                    uBit.display.print("E");
                    uBit.sleep(500);

                    pinRead = false;
                    uBit.display.clear();
                    char* segment;
                    int i;
                    segment = strtok(input, " ");

                    while(segment)
                    {
                        for(i=0; i < 36; ++i)
                        {
                            if (!strcmp(segment, table[i].morse))
                            {
                                uBit.display.scroll(table[i].ascii);
                            }
                        }
                        segment = strtok(nullptr, " ");
                    }
                    memset(input, 0, sizeof input);
                    uBit.sleep(1000);
  				}
                uBit.display.clear();
  			}
  		}
	}
	release_fiber();
}