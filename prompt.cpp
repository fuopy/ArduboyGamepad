#include "prompt.h"

char prompt_start(const char* const* prompts, unsigned char promptCount)
{
	char choice = 0;
	prompt_draw(prompts, promptCount, choice);
	updateOldInput();
	
	while(true) {
		updateNewInput();
		if(A_PRESSED) {
			updateOldInput();
			return choice;
		}
		if(B_PRESSED) {		
			updateOldInput();
			return 255;
		}
		if(DOWN_PRESSED) {
			if(choice < promptCount-1) {
				choice++;
				prompt_draw(prompts, promptCount, choice);
			}
		}
		if(UP_PRESSED) {
			if(choice > 0) {
				choice--;
				prompt_draw(prompts, promptCount, choice);
			}
		}
		updateOldInput();
	}
	
	return choice;
}
void prompt_draw(const char* const* prompts, unsigned char promptCount, char choice)
{
	arduboy.clear();
	arduboy.setTextSize(1);
	arduboy.setCursor(0, 0);
	arduboy.print(rps(&(prompts[0])));
	unsigned char startPos = (choice>=6) ? choice-6 : 0;
	unsigned char endPos = startPos + 6;
	for(unsigned char i = startPos; (i<promptCount) && (i<=endPos); ++i) {
		if(i == choice) {
			arduboy.setCursor(0, 8*(i+1-startPos));
			arduboy.print(">");
		}
		arduboy.setCursor(8, 8*(i+1-startPos));
		arduboy.print(rps(&(prompts[i+1])));
	}
	arduboy.display(); 
}

const char okString[] PROGMEM = "Continue";
void error(const char* message)
{
	const char* messages[] = {message, okString};
	prompt_start(messages, 1);
}


char prompt_table(const char choiceString[], const char* const rowStrings[], char rows, char tabWidth, char tabCount) {
	char cursor = 0;
	int i;
	for(i=0; i<rows; ++i) {
		arduboy.setCursor(0, i*8+8);
		arduboy.print(rps(&(rowStrings[i])));
	}
	
	updateOldInput();
	while(true) {
		updateNewInput();
		if(UP_PRESSED || DOWN_PRESSED || LEFT_PRESSED || RIGHT_PRESSED) {
			arduboy.setCursor((cursor%tabCount) * 6 * tabWidth, (cursor/tabCount) * 8 + 8);
			arduboy.print(" ");
		}
		if(A_PRESSED) {
			return pgm_read_byte_near(choiceString + cursor);
		} else if(B_PRESSED) {
			return 0;
		} else if(UP_PRESSED) {
			if(cursor < tabCount)
				cursor += tabCount*rows;
			cursor -= tabCount;
		} else if(DOWN_PRESSED) {
			cursor += tabCount;
			if(cursor >= tabCount*rows)
				cursor -= tabCount*rows;
		} else if(LEFT_PRESSED) {
			if(cursor % tabCount == 0)
				cursor += tabCount;
			cursor --;
		} else if(RIGHT_PRESSED) {
			cursor ++;
			if(cursor % tabCount == 0)
				cursor -= tabCount;
		}
		arduboy.setCursor((cursor%tabCount) * 6 * tabWidth, (cursor/tabCount) * 8 + 8);
		arduboy.print(">");
		arduboy.display();
		updateOldInput();
	}
}


const char modifierRowStrings_0[] PROGMEM = " LCTL LSFT LALT LGUI";
const char modifierRowStrings_1[] PROGMEM = " RCTL RSFT RALT RGUI";
const char modifierRowStrings_2[] PROGMEM = " UP   DOWN LEFT RIGT";
const char modifierRowStrings_3[] PROGMEM = " BKSP TAB  CR   ESC ";
const char modifierRowStrings_4[] PROGMEM = " INS  DEL  PGUP PGDN";
const char modifierRowStrings_5[] PROGMEM = " HOME END  CAPS     ";
const char* const modifierRowStrings[] PROGMEM = {
	modifierRowStrings_0,
	modifierRowStrings_1,
	modifierRowStrings_2,
	modifierRowStrings_3,
	modifierRowStrings_4,
	modifierRowStrings_5
};
const char numModifierRows = 6;
const char modifierReturnString[] PROGMEM = {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0xDA,0xD9,0xD8,0xD7,0xB2,0xB3,0xB0,0xB1,0xD1,0xD4,0xD3,0xD6,0xD2,0xD5,0xC1,'\0'};

char prompt_modifier()
{
	return prompt_table(modifierReturnString, modifierRowStrings, numModifierRows, 5, 4);
}



const char fkeyRowStrings_0[] PROGMEM = " F1  F2  F3  F4  F5 ";
const char fkeyRowStrings_1[] PROGMEM = " F6  F7  F8  F9  F10";
const char fkeyRowStrings_2[] PROGMEM = " F11 F12";
const char* const fkeyRowStrings[] PROGMEM = {
	fkeyRowStrings_0,
	fkeyRowStrings_1,
	fkeyRowStrings_2,
};
const char numfkeyRows = 3;
const char fkeyReturnString[] PROGMEM = {0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, '\0'};

char prompt_fkey()
{
	return prompt_table(fkeyReturnString, fkeyRowStrings, numfkeyRows, 4, 5);
}





const char alphaRowStrings_0[] PROGMEM = " 1 2 3 4 5 6 7 8 9 0";
const char alphaRowStrings_1[] PROGMEM = " Q W E R T Y U I O P";
const char alphaRowStrings_2[] PROGMEM = " A S D F G H J K L  ";
const char alphaRowStrings_3[] PROGMEM = " Z X C V B N M , . /";
const char alphaRowStrings_4[] PROGMEM = " ` - = [ ] \\ ; '    ";

const char* const alphaRowStrings[] PROGMEM = {
	alphaRowStrings_0,
	alphaRowStrings_1,
	alphaRowStrings_2,
	alphaRowStrings_3,
	alphaRowStrings_4
};
const char numAlphaRows = 5;
const char keyboardReturnString[] PROGMEM = "1234567890QWERTYUIOPASDFGHJKL ZXCVBNM,./`-=[]\\;'  ";

char prompt_keyboard()
{
	return prompt_table(keyboardReturnString, alphaRowStrings, numAlphaRows, 2, 10);
}

void prompt_flash(const char* msg)
{
		arduboy.clear();
		arduboy.setCursor(0, 0);
		arduboy.print(msg);
		arduboy.display();
		delay(600);
}