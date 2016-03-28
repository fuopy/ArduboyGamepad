#include "globals.h"

Arduboy arduboy;

unsigned char newButtons = 0;
unsigned char oldButtons = 0;

void updateNewInput()
{
	newButtons = arduboy.getInput();
}

void updateOldInput()
{
	oldButtons = newButtons;
}

char progmemString[] = "";

char up_map_key = 0xB3;
char down_map_key = 0xB3;
char left_map_key = 0xB3;
char right_map_key = 0xB3;
char b_map_key = 0xB3;
char a_map_key = 0xB3;

char* rps(const char* const* str)
{
	strcpy_P(progmemString, (char*)pgm_read_word(str));
	return progmemString;
}

char* dps(const char* str)
{
	strcpy_P(progmemString, (char*)pgm_read_word(str));
	return progmemString;
}