#include "globals.h"

void displayTitle()
{
	arduboy.clear();	
	arduboy.setTextSize(2);
	arduboy.setCursor(18+4, 12);
	arduboy.print("Arduboy");
	arduboy.setCursor(22+4, 28);
	arduboy.print("Gamepad");
	arduboy.setTextSize(1);
	arduboy.setCursor(0, scrh-8);
	arduboy.print("fuopy 2016");
	//arduboy.drawBitmap(0, 0, titleScreen, 128, 64, 1);
	arduboy.display();
	
	while(true) {
		updateNewInput();
		if(A_PRESSED) break;
		updateOldInput();
	}	
	updateOldInput();
}