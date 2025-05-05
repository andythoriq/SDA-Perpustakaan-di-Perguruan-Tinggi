#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <string.h>

void displayMenu();
int getPilihan();
void inputString(char *buffer, size_t size, const char *prompt);
int inputInt(const char *prompt);

#endif // MENU_H