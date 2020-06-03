#ifndef gra.h
#define gra.h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "gra.h"
#include "lis3dsh.h"
#include "ff.h"
#include "maps.h"


#define FA_READ 0x01
#define FA_WRITE 0x02
#define FA_OPEN_EXISTING 0x00
#define FA_CREATE_NEW 0x04
#define FA_CREATE_ALWAYS 0x08
#define FA_OPEN_ALWAYS 0x10
#define FA_OPEN_APPEND 0x30

//--- SKIER ---
struct Skier
{
	int HP = 3;
	int X;
	int Y;
	int speed;
	int centerWidth = 13;
	int centerHeight = 23;
	int *Hitbox_X;
	int *Hitbox_Y;
};
//--- Difficulty_Level ---
struct Difficulty_Level
{
	int borderDMG = 3;
	int snowmanDMG = 1;
	int bowmanDMG = 2;
	int rockDMG = 3;
	int treeDMG = 2;
} DMG;
//--- OBJECT ---
struct Object
{
	int staticX;
	int staticY;
	int *hitbox_X;
	int *hitbox_Y;
};
//--- MAP ---
struct Map
{
	int obstacles[5000][11];
	int leftBorder[5000][77];
	int rightBorder[5000][77];
}A;
//--- PositionUpdate ---
float accX, out[4];	// <-1000;1000>

//--- RANKING ---
char ranking[180];

void DrawRankingText2(int X, int Y);
void DrawBack(int X, int Y);
void NewRecordInRanking(char nick[10], char ranking[180], int mytime, int hp);
void ReadFromRanking(char* ranking);
void RankingFailInfo(int X, int Y);
char* SortRanking(char ranking[180]);
void SetRanking();
void ShowRankingOnBoard();
void SetChar10(char ch, int type, int X, int Y);
void UseRanking();
void WriteToRanking(char* ranking);

//--- MENU ---
void DrawStartText(int X, int Y);
void DrawRankingText(int X, int Y);
void DrawExitText(int X, int Y);
void DrawWinterRacerText(int X, int Y);
void DrawWinterRacerLogo(int X, int Y);
void ChangeTargetMenu(uint8_t option, uint8_t LastOption);
void UseMenu();

//--- GAME ---
int BorderCollision(int *X1, int *Y1, int r1a, int r1b, int *X2, int *Y2);
int *CreateSquareHitboxY(int Y, int r);
int *CreateSquareHitboxX(int X, int r);
int *CreateRectangleHitboxY(int Y, int r1, int r2);
int *CreateRectangleHitboxX(int X, int r1, int r2);
int Collision(int *X1, int *Y1, int r1a, int r1b, int *X2, int *Y2, int r2a, int r2b);
void DrawSkier(int position, int X, int Y);
void PrintInfo(int option);
void DrawTextPressToStart(int X, int Y);
void DrawTextPressToPause(int X, int Y);
void DrawGameOver(int X, int Y);
void DrawTextPressToContinue(int X, int Y);
void DrawAddingPage(int X, int Y);
void DrawCharSquare(int X, int Y, int color);
void DrawCurrentCharSquare(int X, int Y);
void DrawLeftArrow(int X, int Y, int color);
void DrawRightArrow(int X, int Y);
void DrawKmph(int X, int Y);
void DrawMeta(int Y);
void FailInfo(int X, int Y, int color);
void MetaCollision(int *X1, int *Y1, int r1a, int r1b, int *X2, int *Y2);
void PressStartButton();
void PressPauseButton();
void PositionUpdate(float accX, int speed, int *X, int *Y);
void PressContinueButton();
void SetUI(int HP, int speedValue, int miniMap, int info);
void SetSnowman(uint16_t X, uint16_t Y);
void SetRock(uint16_t X, uint16_t Y);
void SetBowman(uint16_t X, uint16_t Y);
void SetTree(uint16_t X, uint16_t Y);
void SetSkierFront(uint16_t X, uint16_t Y);
void SetSkierLeft(uint16_t X, uint16_t Y);
void SetSkierRight(uint16_t X, uint16_t Y);
void SetHeartRed(uint16_t X, uint16_t Y);
void SetHeartGray(uint16_t X, uint16_t Y);
void SetChar20(char ch, int position, int X, int Y);
void SetChar12(char ch, int X, int Y);
int SpeedUpdate(int speed);
void SetObstacle(int obs, int X, int Y);
void SavedInfo(int X, int Y, int color);
void UpdateArrow(int distance);
void UpdateMiniMap(int distance);
void UpdateHP(int HP);
void UpdateSpeedValue(int speed);

#endif
