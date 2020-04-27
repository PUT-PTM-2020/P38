#ifndef gra.h
#define gra.h

#include "main.h"
#include <math.h>
#include <stdlib.h>
#include "gra.h"
#include "lis3dsh.h"
#include "ff.h"
#include "../Src/Lcd/ili9325.h"

#define FA_READ 0x01
#define FA_WRITE 0x02
#define FA_OPEN_EXISTING 0x00
#define FA_CREATE_NEW 0x04
#define FA_CREATE_ALWAYS 0x08
#define FA_OPEN_ALWAYS 0x10
#define FA_OPEN_APPEND 0x30

void DrawBox(uint16_t X, uint16_t Y, uint16_t width, uint16_t height, uint16_t border, uint16_t color);
void FillInside(uint16_t X, uint16_t Y, uint16_t width, uint16_t height, uint16_t border, uint16_t color);
void ChangeTargetMenu(uint8_t option, uint8_t LastOption);
void StartGame();
void ChangeTargetRanking(uint8_t option, uint8_t LastOption);
void UseRanking();
void Sound(uint8_t option);
void UseMenu();
int *createHitbox_Y(int Y, int r);
int *createHitbox_X(int X, int r);
_Bool collision(int *X1, int *Y1, int *X2, int *Y2);
//***STEROWANIE
void positionUpdate(float accX, float speed, int *X, int *Y);
void speedUpdate(int *speed);
//GRAFIKA
void SetSnowman(uint16_t X, uint16_t Y);
void SetRock(uint16_t X, uint16_t Y);
void SetBowman(uint16_t X, uint16_t Y);
void SetTree(uint16_t X, uint16_t Y);
void SetSkierFront(uint16_t X, uint16_t Y);
void SetSkierLeft(uint16_t X, uint16_t Y);
void SetSkierRight(uint16_t X, uint16_t Y);
void drawSkier(int position, int X, int Y);
void DrawRanking(uint8_t Mode);
void DrawMenu(uint8_t Mode);

//***skier
struct Skier
{
	int X;
	int Y;	//pozycja startowa
	int speed;
	int *skierHitbox_X; //= createHitbox_X(skierX, 10);
	int *skierHitbox_Y; //= createHitbox_Y(skierY, 10);
};
//***object
struct Object	//np. przeszkody
{
	int staticX;
	int staticY;
	int *hitbox_X; //= createHitbox_X(staticX, 10);
	int *hitbox_Y; //= createHitbox_Y(staticY, 10);
};
//***map
struct Map
{

}A,B,C,D,E; //pięć przygotowanych map

//***positionUpdate
float accX, out[4];	//accX wychylenie <-1000;1000>

#endif
