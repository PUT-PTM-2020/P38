#ifndef gra.h
#define gra.h

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MA_ILI9341.h"
#include "ff.h"

#define FA_READ 0x01
#define FA_WRITE 0x02
#define FA_OPEN_EXISTING 0x00
#define FA_CREATE_NEW 0x04
#define FA_CREATE_ALWAYS 0x08
#define FA_OPEN_ALWAYS 0x10
#define FA_OPEN_APPEND 0x30

char buffer[180];
static FATFS FatFs;
FRESULT fresult;
FIL file;
WORD bytes_written;
WORD bytes_read;

int map;

struct Skier
{
	int X;
	int Y;
	int HP;
	int speed;
	int centerWidth;
	int centerHeight;
	int *Hitbox_X;
	int *Hitbox_Y;
}s1;

struct Difficulty_Level
{
	int borderDMG;
	int snowmanDMG;
	int bowmanDMG;
	int rockDMG;
	int treeDMG;
} DMG;

struct Object
{
	int staticX;
	int staticY;
	int *hitbox_X;
	int *hitbox_Y;
};

struct Map
{
	char obstacles[125][11];
	char leftBorder[125][40];
	char rightBorder[125][40];
} m1;

char MainRanking[180];

void Boot();
char* ReadFromRanking();

#endif
