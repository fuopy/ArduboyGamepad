#ifndef _PROMPT_H
#define _PROMPT_H

#include "globals.h"

void prompt_draw(const char* const* prompts, unsigned char promptCount, char choice);
char prompt_start(const char* const* prompts, unsigned char promptCount);
void error(const char* message);
char prompt_keyboard();
char prompt_modifier();
char prompt_fkey();
void prompt_flash(const char* msg);

#endif
