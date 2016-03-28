#include "globals.h"
#include "prompt.h"
#include "title.h"
#include "gamepad.h"

void setup()
{
	arduboy.begin();
	arduboy.setFrameRate(FRAME_RATE);
	arduboy.setTextSize(1);
}

void loop() 
{
	// Display ARDUBOY GAMEPAD title screen
	displayTitle();
	
	// Display ROOT MENU
	displayGamePad();
}
