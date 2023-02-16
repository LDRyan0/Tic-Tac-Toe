/* File: UserInterface.h
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 01/10/19
 * Last Modified: 21/10/19
 * Purpose: header file for UserInterface.c
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Settings.h"
#include "Input.h"
#include "GameManager.h"
#include "Logging.h"
#include <stdio.h>
#include <string.h>

void menu(int, int, int);
void makeMenuString(char* menuString);
#endif
