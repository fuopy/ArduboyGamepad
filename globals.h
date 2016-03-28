#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Arduboy.h>

// PROGRAM SPECIFIC
#define STATE_MAIN_MENU 0
#define STATE_GAME 1
#define STATE_HIGH_SCORES 2
#define STATE_ABOUT 3
extern unsigned char current_state;
extern unsigned char old_state;

extern Arduboy arduboy;
const unsigned char scrw = 128;
const unsigned char scrh = 64;

const int FRAME_RATE = 50;

extern unsigned char oldButtons;
extern unsigned char newButtons;



void updateNewInput();
void updateOldInput();

#define UP_DOWN (newButtons & UP_BUTTON)
#define DOWN_DOWN (newButtons & DOWN_BUTTON)
#define LEFT_DOWN (newButtons & LEFT_BUTTON)
#define RIGHT_DOWN (newButtons & RIGHT_BUTTON)
#define A_DOWN (newButtons & B_BUTTON)
#define B_DOWN (newButtons & A_BUTTON)
#define ANY_DOWN (newButtons)

#define UP_PRESSED (UP_DOWN && !(oldButtons & UP_BUTTON))
#define DOWN_PRESSED (DOWN_DOWN && !(oldButtons & DOWN_BUTTON))
#define LEFT_PRESSED (LEFT_DOWN && !(oldButtons & LEFT_BUTTON))
#define RIGHT_PRESSED (RIGHT_DOWN && !(oldButtons & RIGHT_BUTTON))
#define A_PRESSED (A_DOWN && !(oldButtons & B_BUTTON))
#define B_PRESSED (B_DOWN && !(oldButtons & A_BUTTON))
#define ANY_PRESSED ((newButtons^oldButtons) & newButtons)

#define UP_RELEASED (!UP_DOWN && (oldButtons & UP_BUTTON))
#define DOWN_RELEASED (!DOWN_DOWN && (oldButtons & DOWN_BUTTON))
#define LEFT_RELEASED (!LEFT_DOWN && (oldButtons & LEFT_BUTTON))
#define RIGHT_RELEASED (!RIGHT_DOWN && (oldButtons & RIGHT_BUTTON))
#define A_RELEASED (!A_DOWN && (oldButtons & B_BUTTON))
#define B_RELEASED (!B_DOWN && (oldButtons & A_BUTTON))
#define ANY_RELEASED ((newButtons^oldButtons) & ~newButtons)

extern char progmemString[80];
// Read PROGMEM string
char* rps(const char* const* str);
char* dps(const char* str);


extern char up_map_key;
extern char down_map_key;
extern char left_map_key;
extern char right_map_key;
extern char b_map_key;
extern char a_map_key;

#endif
