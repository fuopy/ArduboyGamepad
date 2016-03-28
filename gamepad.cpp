#include <Keyboard.h>
#include "globals.h"
#include "prompt.h"

void editGamePad();
char getSomeCharacter();
void enterPadMode();
void pressKey(char key);
void releaseKey(char key);
void manageFiles();
void loadKeys(byte file, byte set);
void saveKeys(byte file, byte set);

const char rootItems_0[] PROGMEM = "[     Game Pad      ]";
const char rootItems_1[] PROGMEM = "File Management";
const char rootItems_2[] PROGMEM = "Configure Keys";
const char rootItems_3[] PROGMEM = "Begin!";
const char* const rootItems[] PROGMEM = {
	rootItems_0,
	rootItems_1,
	rootItems_2,
	rootItems_3
};
const char rootItemsCount = 3;

const char managementItems_0[] PROGMEM = "[  File Management  ]";
const char managementItems_1[] PROGMEM = "Load Keys";
const char managementItems_2[] PROGMEM = "Save Keys";
const char* const managementItems[] PROGMEM = {
	managementItems_0,
	managementItems_1,
	managementItems_2
};
const char managementItemsCount = 2;

const char configureItems_0[] PROGMEM = "[  Configure Keys   ]";
const char configureItems_1[] PROGMEM = "Up";
const char configureItems_2[] PROGMEM = "Down";
const char configureItems_3[] PROGMEM = "Left";
const char configureItems_4[] PROGMEM = "Right";
const char configureItems_5[] PROGMEM = "B";
const char configureItems_6[] PROGMEM = "A";

const char* const configureItems[] PROGMEM = {
	configureItems_0,
	configureItems_1,
	configureItems_2,
	configureItems_3,
	configureItems_4,
	configureItems_5,
	configureItems_6,
};
const char configureItemsCount = 6;

const char characterGroupItems_0[] PROGMEM = "[     Key Type      ]";
const char characterGroupItems_1[] PROGMEM = "Alphanumeric";
const char characterGroupItems_2[] PROGMEM = "Modifier";
const char characterGroupItems_3[] PROGMEM = "F Keys";
const char* const characterGroupItems[] PROGMEM = {
	characterGroupItems_0,
	characterGroupItems_1,
	characterGroupItems_2,
	characterGroupItems_3
};
const char characterGroupItemsCount = 3;

const char saveSlotItems_0[] PROGMEM = "[ Select File Slot  ]";
const char saveSlotItems_1[] PROGMEM = "Gamepad 1";
const char saveSlotItems_2[] PROGMEM = "Gamepad 2";
const char saveSlotItems_3[] PROGMEM = "Gamepad 3";
const char saveSlotItems_4[] PROGMEM = "Gamepad 4";
const char saveSlotItems_5[] PROGMEM = "Gamepad 5";
const char* const saveSlotItems[] PROGMEM = {
	saveSlotItems_0,
	saveSlotItems_1,
	saveSlotItems_2,
	saveSlotItems_3,
	saveSlotItems_4,
	saveSlotItems_5
};
const char saveSlotItemsCount = 5;

void displayGamePad()
{
	unsigned char choice;
	while(choice != 255) {
		choice = prompt_start(rootItems, rootItemsCount);
		if(choice == 0) {
			manageFiles();
		} else if(choice == 1) {
			editGamePad();
		} else if(choice == 2) {
			enterPadMode();
		}
	}
}

void manageFiles()
{
	unsigned char choice;
	byte file;
	choice = prompt_start(managementItems, managementItemsCount);
	if(choice == 0) {
		file = prompt_start(saveSlotItems, saveSlotItemsCount);
		if(file != 255) {
			loadKeys(5, file);
			prompt_flash("Load complete!");
		}
	}
	else if(choice == 1) {
		file = prompt_start(saveSlotItems, saveSlotItemsCount);
		if(file != 255) {
			saveKeys(5, file);
			prompt_flash("Save complete!");
		}
	}
}

void editGamePad()
{
	unsigned char choice;
	char character;
	while(choice != 255) {
		choice = prompt_start(configureItems, configureItemsCount);
		if(choice == 255) return;
		character = getSomeCharacter();
		if(character != 0) {
			switch(choice) {
				case 0:
					up_map_key = character;
					break;
				case 1:
					down_map_key = character;
					break;
				case 2:
					left_map_key = character;
					break;
				case 3:
					right_map_key = character;
					break;
				case 4:
					b_map_key = character;
					break;
				case 5:
					a_map_key = character;
					break;
			}
			prompt_flash("Key set!");
		}
	}
}

const char inputPrompt[] PROGMEM = "Select a key...";

char getSomeCharacter()
{
	unsigned char choice = prompt_start(characterGroupItems, characterGroupItemsCount);
	arduboy.clear();
	arduboy.setCursor(0, 0);
	arduboy.print("Select a key...");
	if(choice == 0)
		return prompt_keyboard();
	else if(choice == 1)
		return prompt_modifier();
	else if(choice == 2)
		return prompt_fkey();
	return 0;
}

void enterPadMode()
{
	arduboy.clear();
	arduboy.display();
	arduboy.setRGBled(0, 1, 0);
	while(true) {
		updateNewInput();
		
		if(A_PRESSED) pressKey(a_map_key);
		if(A_RELEASED) releaseKey(a_map_key);

		if(B_PRESSED) pressKey(b_map_key);
		if(B_RELEASED) releaseKey(b_map_key);

		if(UP_PRESSED) pressKey(up_map_key);
		if(UP_RELEASED) releaseKey(up_map_key);

		if(DOWN_PRESSED) pressKey(down_map_key);
		if(DOWN_RELEASED) releaseKey(down_map_key);

		if(LEFT_PRESSED) pressKey(left_map_key);
		if(LEFT_RELEASED) releaseKey(left_map_key);

		if(RIGHT_PRESSED) pressKey(right_map_key);
		if(RIGHT_RELEASED) releaseKey(right_map_key);
		
		updateOldInput();
	}
}

void pressKey(char key)
{
	Keyboard.begin();
	Keyboard.press(key);
	delay(10);
	Keyboard.end();
}

void releaseKey(char key)
{
	Keyboard.begin();
	Keyboard.release(key);
	delay(10);
	Keyboard.end();
}

void loadKeys(byte file, byte set)
{
	int address = file * 10 * 5 + set*10;
	
	up_map_key = EEPROM.read(address);
	down_map_key = EEPROM.read(address+1);
	left_map_key = EEPROM.read(address+2);
	right_map_key = EEPROM.read(address+3);
	b_map_key = EEPROM.read(address+4);
	a_map_key = EEPROM.read(address+5);
}

void saveKeys(byte file, byte set)
{
	int address = file * 10 * 5 + set*6;
	
	EEPROM.write(address, up_map_key);
	EEPROM.write(address+1, down_map_key);
	EEPROM.write(address+2, left_map_key);
	EEPROM.write(address+3, right_map_key);
	EEPROM.write(address+4, b_map_key);
	EEPROM.write(address+5, a_map_key);
}