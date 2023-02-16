/* File: Settings.h
 * Author: Liam Ryan
 * ID: 19769811
 * Date Created: 01/10/19
 * Last Modified: 16/10/19
 * Purpose: Header file for Settings.c
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#define FALSE 0
#define TRUE !FALSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Input.h"

int loadSettings(char*, int*, int*, int*);
int validateDimension(int);

#endif
