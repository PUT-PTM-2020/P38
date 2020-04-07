#include "lis3dsh.h"
#include "main.h"
#include <cmath>
#include <stdlib.h>
#include "GLCD.h" 
#include "AsciiLib.h"

//NOTE
	//Dodac napisy do DrawMenu, ChangeTarget i ShowRanking

//***DrawBox
void DrawBox(uint16_t X, uint16_t Y, uint16_t width, uint16_t height, uint16_t border, uint16_t color)
{
	for(int i=0; i<border; i++)
	{
		LCD_DrawLine(X, Y-i, X+(width-1), Y-i, color);
		LCD_DrawLine(X+i, Y-border, X+i, Y-height+border+1, color);
		LCD_DrawLine(X, Y-height+1+i, X+(width-1), Y-height+1+i, color);
		LCD_DrawLine(X+(width-1)-i, Y-border, X+(width-1)-i, Y-height+border+1, color);
	}
}

//***FillInside

void FillInside(uint16_t X, uint16_t Y, uint16_t width, uint16_t height, uint16_t border, uint16_t color)
{
	uint16_t X=X+border;
	uint16_t Y=Y-border;

	uint16_t Xp=X+(width-1)-border;
	uint16_t Yp=Y-(height-1)+border;

	for(int i=X; i<=Xp; i++)
		for(int j=Y; j<=Yp; j++)
			LCD_SetPoint(i, j,0x0000);
}

//***MENU
void DrawMenu(uint8_t Mode)
{
	if(Mode==-1)	//-1 rysuje całe menu
	{
		LCD_Clear(1567);
		GUI_Text(120, 220, uint8_t *str,49149, 1567); //WINTER RACER
	}
	if(Mode==-1 || Mode==0)
	{
		DrawBox(86,190,150,40,3,65535);	//START
		GUI_Text(147, 176, uint8_t *str,65535, 1567);
	}
	if(Mode==-1 || Mode==1)
	{
		DrawBox(86,140,150,40,3,65535);	//RANKING
		GUI_Text(147, 126, uint8_t *str,65535, 1567);
	}
	if(Mode==-1 || Mode==2)
	{
		DrawBox(86,90,150,40,3,65535);		//WYJŚCIE
		GUI_Text(147, 76, uint8_t *str,65535, 1567);
	}
}

void ChangeTargetMenu(uint8_t option, uint8_t LastOption)
{	
	DrawMenu(LastOption);
	
	switch(option)
	{
		case 0:
		DrawBox(86,190,150,40,3,49149);	//START
		GUI_Text(147, 176, uint8_t *str,49149, 1567);
		break;
		case 1:
		DrawBox(86,140,150,40,3,65535);	//RANKING
		GUI_Text(147, 126, uint8_t *str,49149, 1567);
		break;
		case 2:
		DrawBox(86,90,150,40,3,65535);		//WYJŚCIE
		GUI_Text(147, 76, uint8_t *str,49149, 1567);
		break;
	}
}

void StartGame()
{
	while(1)
	{
		//sprawdza wychylenie w osi X
		LIS3DSH_ReadACC(out);
		accX = out[0];
			
		speedUpdate(s1.speed);
		positionUpdate(accX, s1.speed, s1.X, s1.Y);
	}
}

//***RANKING
void DrawRanking(uint8_t Mode)
{
	if(Mode==-1)
	{
		LCD_Clear(0x070F);
		GUI_Text(130, 220, uint8_t *str,49149, 0xFFFF); //RANKING
	}
	if(Mode==-1 || Mode==0)
	{
		FillInside(41, 190, 240, 140, 5, 0x05AC);
		DrawBox(133, 43, 60, 35, 3, 0x0347);
		GUI_Text(140, 60, uint8_t *str,49149, 0xFFFF); //WSTECZ
	}
	if(Mode==-1 || Mode==1)
	{
		FillInside(41, 190, 240, 140, 5, 0xC638);
		DrawBox(41, 190, 240, 140, 5, 0x05AC);
	}
}

void ChangeTargetRanking(uint8_t option, uint8_t LastOption)
{
	DrawRanking(LastOption);
	
	switch(option)
	{
		case 0:
		DrawBox(133, 43, 60, 35, 3, 0x6FF7); //WSTECZ
		break;
		case 1:
		DrawBox(41, 190, 240, 140, 5, 0x6FF7);	//RANKING
		break;
	}
}

void UseRanking()
{
	int option=0;
	
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && option!=0)
		{
			Sound();
			option--;
			ChangeTargetRanking(option, option+1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && option!=1)
		{
			Sound();
			option++;
			ChangeTargetRanking(option, option-1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
		{
			Sound();
			switch(option)
			{
				case 0:
				DrawMenu();
				option=3;
				break;
				case 1:

				break;
			}
		}
		if(option==3) break;
	}
}

//***Sound
void Sound(uint8_t option)
{
	
}

void UseMenu()
{
	int option=0;
	
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && option!=0)
		{
			Sound();
			option--;
			ChangeTargetMenu(option, option+1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && option!=2)
		{
			Sound();
			option++;
			ChangeTargetMenu(option, option-1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
		{
			Sound();
			switch(option)
			{
				case 0:
				StartGame();
				break;
				case 1:
				DrawRanking();
				UseRanking();
				break;
				case 2:
				LCD_Clear(0);
				break;
			}
		}
	}
}

//***skier
struct Skier
{
	int X;	
	int Y;	//pozycja startowa
	int speed;
	int *skierHitbox_X = createHitbox_X(skierX, 10);
	int *skierHitbox_Y = createHitbox_Y(skierY, 10);
}

//***object
struct Object	//np. przeszkody
{
	int staticX;	
	int staticY;
	int *hitbox_X = createHitbox_X(staticX, 10);
	int *hitbox_Y = createHitbox_Y(staticY, 10);
}

//***map
struct Map
{
	
}

Map A,B,C,D,E;	//pięć przygotowanych map

//***hitbox
int *createHitbox_Y(int Y, int r)
{
	int size = r*8;
	int *tab = (int*)malloc(size*sizeof(int));
	
	int i=0;
	int j=r;
	
	for(; i<r*2+1; i++)
		tab[i]=Y+r;
	while(j!=0)
	{
		i++;
		j--;
		tab[i]=Y+j;
	}
	while(j!=r)
	{
		i++;
		j++;
		tab[i]=Y-j;
	}
	i++;
	for(; i<r*6+1; i++)
		tab[i]=Y-r;
	while(j!=0)
	{
		i++;
		j--;
		tab[i]=Y-j;
	}
	while(j!=r)
	{
		j++;
		i++;
		tab[i]=Y+j;
	}
	return *tab;
}

int *createHitbox_X(int X, int r)
{
	int size = r*8;
	int *tab = (int*)malloc(size*sizeof(int));
	
	int i=0;
	int j=r;
	
	tab[i]=X-j;
	
	while(j!=0)
	{
		i++;
		j--;
		tab[i]=X-j;
	}
	while(j!=r)
	{
		i++;
		j++;
		tab[i]=X+j;
	}
	i++;
	for(; i<r*4+1; i++)
		tab[i]=X+r;
	while(j!=0)
	{
		i++;
		j--;
		tab[i]=X+j;
	}
	while(j!=r)
	{
		j++;
		i++;
		tab[i]=X-j;
	}
	for(; i<r*8; i++)
		tab[i]=X+r;
	return *tab;
}

//***collision
bool collision(X1, Y1, X2, Y2)
{
	if(sizeof(X2) / sizeof(int)>sizeof(X1) / sizeof(int)) size_t n = sizeof(X2) / sizeof(int);
	else n = sizeof(X1) / sizeof(int);
	
	for(int i=0; i<n; i++)
		if(X1[i]==X2[i] && Y1[i]==Y2[i]) return 1;

	return 0;
}

//***drawSkier
void drawSkier(int position, int X, int Y)
{
	switch(position)
	{
		case 1:
		break;
		case 2:
		break;
		case 3:
		break;
	}
}

//***positionUpdate
float accX, out[4];	//accX wychylenie <-1000;1000>

void positionUpdate(float accX, float speed, int& X, int& Y)
{
	Y += speed;

	if(accX < 0.5)
	{
		for(int i=0; i<round(abs(accX))/100); i++)
		{
			drawSkier(1, X, Y);	//rysuje narciarza, 1 - pozycja narciarza skręcającego w lewo
			X += accX/100;
		}
	}
	else if(accX > 0.5)
	{
		for(int i=0; i<round(accX)/100); i++)
		{
			drawSkier(2, X, Y);	//rysuje narciarza, 2 - pozycja narciarza skręcającego w prawo
			X += accX/100;
		}
	}
	else drawSkier(3, X, Y);	//rysuje narciarza, , 3 - pozycja narciarza jadącego prosto
}

//***speedUpdate
void speedUpdate(float& speed)
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1))
	{
		speed+=
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2))
	{
		speed-=
	}
}

//***SetSnowman
void SetSnowman(uint16_t X, uint16_t Y)
{
	for(int i=13; i<=18; i++)
		LCD_SetPoint(X+i, Y,0x0000);

	LCD_SetPoint(X+11, Y+1,0x0000);
	LCD_SetPoint(X+12, Y+1,0x0000);
	for(int i=13; i<=18; i++)
		LCD_SetPoint(X+i, Y+1,0xFFFF);
	LCD_SetPoint(X+19, Y+1,0x0000);
	LCD_SetPoint(X+20, Y+1,0x0000);

	LCD_SetPoint(X+10, Y+2,0x0000);
	for(int i=11; i<=20; i++)
		LCD_SetPoint(X+i, Y+2,0xFFFF);
	LCD_SetPoint(X+21, Y+2,0x0000);
	
	LCD_SetPoint(X+9, Y+3,0x0000);
	for(int i=10; i<=14; i++)
		LCD_SetPoint(X+i, Y+3,0xFFFF);
	LCD_SetPoint(X+15, Y+3,0x0000);
	LCD_SetPoint(X+16, Y+3,0x0000);
	for(int i=17; i<=21; i++)
		LCD_SetPoint(X+i, Y+3,0xFFFF);
	LCD_SetPoint(X+22, Y+3,0x0000);

	LCD_SetPoint(X+9, Y+4,0x0000);
	for(int i=10; i<=14; i++)
		LCD_SetPoint(X+i, Y+4,0xFFFF);
	LCD_SetPoint(X+15, Y+4,0x0000);
	LCD_SetPoint(X+16, Y+4,0x0000);
	for(int i=17; i<=21; i++)
		LCD_SetPoint(X+i, Y+4,0xFFFF);
	LCD_SetPoint(X+22, Y+4,0x0000);

	LCD_SetPoint(X+9, Y+5,0x0000);
	for(int i=10; i<=21; i++)
		LCD_SetPoint(X+i, Y+5,0xFFFF);
	LCD_SetPoint(X+22, Y+5,0x0000);

	LCD_SetPoint(X+3, Y+6,0xF945);
	LCD_SetPoint(X+4, Y+6,0xF945);
	LCD_SetPoint(X+9, Y+6,0xFFFF);
	for(int i=10; i<=14; i++)
		LCD_SetPoint(X+i, Y+6,0xFFFF);
	LCD_SetPoint(X+15, Y+6,0xFFFF);
	LCD_SetPoint(X+16, Y+6,0xFFFF);
	for(int i=17; i<=21; i++)
		LCD_SetPoint(X+i, Y+6,0xFFFF);
	LCD_SetPoint(X+22, Y+6,0xFFFF);

	LCD_SetPoint(X+3, Y+7,0xF945);
	LCD_SetPoint(X+4, Y+7,0xF945);
	LCD_SetPoint(X+9, Y+7,0xFFFF);
	for(int i=10; i<=14; i++)
		LCD_SetPoint(X+i, Y+7,0xFFFF);
	LCD_SetPoint(X+15, Y+7,0xFFFF);
	LCD_SetPoint(X+16, Y+7,0xFFFF);
	for(int i=17; i<=21; i++)
		LCD_SetPoint(X+i, Y+7,0xFFFF);
	LCD_SetPoint(X+22, Y+7,0xFFFF);

	LCD_SetPoint(X+3, Y+8,0xF945);
	LCD_SetPoint(X+4, Y+8,0xF945);
	LCD_SetPoint(X+6, Y+8,0x71A3);
	LCD_SetPoint(X+7, Y+8,0x71A3);
	LCD_SetPoint(X+8, Y+8,0x71A3);
	LCD_SetPoint(X+9, Y+8,0x0000);
	for(int i=10; i<=21; i++)
		LCD_SetPoint(X+i, Y+8,0xFFFF);
	LCD_SetPoint(X+22, Y+8,0x0000);
	LCD_SetPoint(X+23, Y+8,0x71A3);
	LCD_SetPoint(X+24, Y+8,0x71A3);
	
	LCD_SetPoint(X+3, Y+9,0xF945);
	LCD_SetPoint(X+4, Y+9,0xF945);
	LCD_SetPoint(X+5, Y+9,0x71A3);
	LCD_SetPoint(X+6, Y+9,0x71A3);
	LCD_SetPoint(X+7, Y+9,0x71A3);
	LCD_SetPoint(X+8, Y+9,0x71A3);
	LCD_SetPoint(X+9, Y+9,0x0000);
	for(int i=10; i<=14; i++)
		LCD_SetPoint(X+i, Y+9,0xFFFF);
	LCD_SetPoint(X+15, Y+9,0x0000);
	LCD_SetPoint(X+16, Y+9,0x0000);
	for(int i=17; i<=21; i++)
		LCD_SetPoint(X+i, Y+9,0xFFFF);
	LCD_SetPoint(X+22, Y+9,0x0000);
	LCD_SetPoint(X+23, Y+9,0xF945);
	LCD_SetPoint(X+24, Y+9,0xF945);
	LCD_SetPoint(X+25, Y+9,0x71A3);

	LCD_SetPoint(X+3, Y+10,0xF945);
	LCD_SetPoint(X+4, Y+10,0xF945);
	LCD_SetPoint(X+5, Y+10,0x71A3);
	LCD_SetPoint(X+9, Y+10,0x0000);
	for(int i=10; i<=14; i++)
		LCD_SetPoint(X+i, Y+10,0xFFFF);
	LCD_SetPoint(X+15, Y+10,0x0000);
	LCD_SetPoint(X+16, Y+10,0x0000);
	for(int i=17; i<=21; i++)
		LCD_SetPoint(X+i, Y+10,0xFFFF);
	LCD_SetPoint(X+22, Y+10,0x0000);
	LCD_SetPoint(X+23, Y+10,0xF945);
	LCD_SetPoint(X+24, Y+10,0xF945);
	LCD_SetPoint(X+25, Y+10,0x71A3);
	LCD_SetPoint(X+26, Y+10,0x71A3);

	LCD_SetPoint(X+2, Y+11,0x71A3);
	LCD_SetPoint(X+3, Y+11,0xF945);
	LCD_SetPoint(X+4, Y+11,0xF945);
	LCD_SetPoint(X+10, Y+10,0x0000);
	for(int i=11; i<=21; i++)
		LCD_SetPoint(X+i, Y+10,0xFFFF);
	LCD_SetPoint(X+22, Y+11,0xF945);
	LCD_SetPoint(X+23, Y+11,0xF945);
	LCD_SetPoint(X+24, Y+11,0xF945);
	LCD_SetPoint(X+25, Y+11,0x71A3);
	LCD_SetPoint(X+26, Y+11,0x71A3);
	LCD_SetPoint(X+27, Y+11,0x71A3);

	LCD_SetPoint(X+3, Y+12,0xF945);
	LCD_SetPoint(X+4, Y+12,0xF945);
	LCD_SetPoint(X+11, Y+12,0x0000);
	for(int i=12; i<=20; i++)
		LCD_SetPoint(X+i, Y+10,0xFFFF);
	LCD_SetPoint(X+21, Y+12,0xF945);
	LCD_SetPoint(X+22, Y+12,0xF945);
	LCD_SetPoint(X+23, Y+12,0xF945);
	LCD_SetPoint(X+27, Y+12,0x71A3);

	LCD_SetPoint(X+3, Y+13,0xF945);
	LCD_SetPoint(X+4, Y+13,0xF945);
	for(int i=11; i<=22; i++)
		LCD_SetPoint(X+i, Y+13,0xF945);

	LCD_SetPoint(X+3, Y+14,0xF945);
	LCD_SetPoint(X+4, Y+14,0xF945);
	for(int i=11; i<=21; i++)
		LCD_SetPoint(X+i, Y+13,0xF945);

	LCD_SetPoint(X+3, Y+15,0xF945);
	LCD_SetPoint(X+4, Y+15,0xF945);
	LCD_SetPoint(X+11, Y+15,0x0000);
	for(int i=12; i<=19; i++)
		LCD_SetPoint(X+i, Y+15,0xFFFF);
	LCD_SetPoint(X+20, Y+15,0x0000);

	LCD_SetPoint(X+3, Y+16,0xF945);
	LCD_SetPoint(X+4, Y+16,0xF945);
	LCD_SetPoint(X+11, Y+16,0x0000);
	LCD_SetPoint(X+12, Y+16,0xFFFF);
	LCD_SetPoint(X+13, Y+16,0xFFFF);
	LCD_SetPoint(X+14, Y+16,0xFFFF);
	LCD_SetPoint(X+15, Y+16,0x0000);
	LCD_SetPoint(X+16, Y+16,0x0000);
	LCD_SetPoint(X+17, Y+16,0xFFFF);
	LCD_SetPoint(X+18, Y+16,0xFFFF);
	LCD_SetPoint(X+19, Y+16,0xFFFF);
	LCD_SetPoint(X+20, Y+16,0x0000);

	LCD_SetPoint(X+1, Y+17,0xF945);
	LCD_SetPoint(X+2, Y+17,0xF945);
	LCD_SetPoint(X+3, Y+17,0xF945);
	LCD_SetPoint(X+4, Y+17,0xF945);
	LCD_SetPoint(X+10, Y+17,0x0000);
	LCD_SetPoint(X+11, Y+17,0xFFFF);
	LCD_SetPoint(X+12, Y+17,0xFFFF);
	LCD_SetPoint(X+13, Y+17,0xFFFF);
	LCD_SetPoint(X+14, Y+17,0x0000);
	LCD_SetPoint(X+15, Y+17,0xFFFF);
	LCD_SetPoint(X+16, Y+17,0xFFFF);
	LCD_SetPoint(X+17, Y+17,0x0000);
	LCD_SetPoint(X+18, Y+17,0xFFFF);
	LCD_SetPoint(X+19, Y+17,0xFFFF);
	LCD_SetPoint(X+20, Y+17,0xFFFF);
	LCD_SetPoint(X+21, Y+17,0x0000);

	LCD_SetPoint(X+2, Y+18,0xF945);
	LCD_SetPoint(X+3, Y+18,0xF945);
	LCD_SetPoint(X+10, Y+18,0x0000);
	LCD_SetPoint(X+11, Y+18,0xFFFF);
	LCD_SetPoint(X+12, Y+18,0xFFFF);
	LCD_SetPoint(X+13, Y+18,0xFCA0);
	LCD_SetPoint(X+14, Y+18,0xFCA0);
	LCD_SetPoint(X+15, Y+18,0xFCA0);
	for(int i=16; i<=20; i++)
		LCD_SetPoint(X+i, Y+18,0xFFFF);
	LCD_SetPoint(X+21, Y+18,0x0000);

	LCD_SetPoint(X+10, Y+19,0x0000);
	LCD_SetPoint(X+11, Y+19,0xFFFF);
	LCD_SetPoint(X+12, Y+19,0xFFFF);
	LCD_SetPoint(X+13, Y+19,0xFFFF);
	LCD_SetPoint(X+14, Y+19,0xFFFF);
	LCD_SetPoint(X+15, Y+19,0xFCA0);
	for(int i=16; i<=20; i++)
		LCD_SetPoint(X+i, Y+19,0xFFFF);
	LCD_SetPoint(X+21, Y+19,0x0000);

	LCD_SetPoint(X+10, Y+20,0x0000);
	LCD_SetPoint(X+11, Y+20,0xFFFF);
	LCD_SetPoint(X+12, Y+20,0xFFFF);
	LCD_SetPoint(X+13, Y+20,0x0000);
	LCD_SetPoint(X+14, Y+20,0x0000);
	LCD_SetPoint(X+15, Y+20,0xFFFF);
	LCD_SetPoint(X+16, Y+20,0xFFFF);
	LCD_SetPoint(X+17, Y+20,0x0000);
	LCD_SetPoint(X+18, Y+20,0x0000);
	LCD_SetPoint(X+19, Y+20,0xFFFF);
	LCD_SetPoint(X+20, Y+20,0xFFFF);
	LCD_SetPoint(X+21, Y+20,0x0000);

	LCD_SetPoint(X+11, Y+21,0x0000);
	LCD_SetPoint(X+12, Y+21,0xFFFF);
	LCD_SetPoint(X+13, Y+21,0xFFFF);
	LCD_SetPoint(X+14, Y+21,0x0000);
	LCD_SetPoint(X+15, Y+21,0xFFFF);
	LCD_SetPoint(X+16, Y+21,0xFFFF);
	LCD_SetPoint(X+17, Y+21,0x0000);
	LCD_SetPoint(X+18, Y+21,0xFFFF);
	LCD_SetPoint(X+19, Y+21,0xFFFF);
	LCD_SetPoint(X+20, Y+21,0x0000);

	LCD_SetPoint(X+11, Y+22,0x0000);
	for(int i=12; i<=19; i++)
		LCD_SetPoint(X+i, Y+22,0xFFFF);
	LCD_SetPoint(X+20, Y+22,0x0000);

	LCD_SetPoint(X+12, Y+23,0x0000);
	LCD_SetPoint(X+13, Y+23,0x0000);
	for(int i=14; i<=17; i++)
		LCD_SetPoint(X+i, Y+23,0xFFFF);
	LCD_SetPoint(X+18, Y+23,0x0000);
	LCD_SetPoint(X+19, Y+23,0x0000);

	LCD_SetPoint(X+10, Y+24,0x0000);
	LCD_SetPoint(X+11, Y+24,0x0000);
	for(int i=12; i<=19; i++)
		LCD_SetPoint(X+i, Y+24,0xF945);
	LCD_SetPoint(X+20, Y+24,0x0000);
	LCD_SetPoint(X+21, Y+24,0x0000);

	for(int i=12; i<=19; i++)
		LCD_SetPoint(X+i, Y+25,0xF945);

	for(int i=12; i<=19; i++)
		LCD_SetPoint(X+i, Y+26,0x0000);

		for(int i=12; i<=19; i++)
		LCD_SetPoint(X+i, Y+27,0x0000);
}

//***SetRock
void SetRock(uint16_t X, uint16_t Y)
{
	for(int i=7; i<=19; i++)
		LCD_SetPoint(X+i, Y,0x0000);

	LCD_SetPoint(X+6, Y+1,0x0000);
	LCD_SetPoint(X+7, Y+1,0xA4B2);
	LCD_SetPoint(X+8, Y+1,0xA4B2);
	LCD_SetPoint(X+9, Y+1,0xA4B2);
	LCD_SetPoint(X+10, Y+1,0xD618);
	LCD_SetPoint(X+11, Y+1,0xD618);
	LCD_SetPoint(X+12, Y+1,0xD618);
	LCD_SetPoint(X+13, Y+1,0xD618);
	LCD_SetPoint(X+14, Y+1,0xD618);
	LCD_SetPoint(X+15, Y+1,0xD618);
	LCD_SetPoint(X+16, Y+1,0x4A08);
	LCD_SetPoint(X+17, Y+1,0x4A08);
	LCD_SetPoint(X+18, Y+1,0x4A08);
	LCD_SetPoint(X+19, Y+1,0x4A08);
	LCD_SetPoint(X+20, Y+1,0x0000);
	LCD_SetPoint(X+21, Y+1,0x0000);

	LCD_SetPoint(X+2, Y+2,0x0000);
	LCD_SetPoint(X+3, Y+2,0x0000);
	LCD_SetPoint(X+4, Y+2,0x0000);
	LCD_SetPoint(X+5, Y+2,0x0000);
	LCD_SetPoint(X+6, Y+2,0x4A08);
	LCD_SetPoint(X+7, Y+2,0xA4B2);
	LCD_SetPoint(X+8, Y+2,0xD618);
	LCD_SetPoint(X+9, Y+2,0xD618);
	LCD_SetPoint(X+10, Y+2,0xD618);
	LCD_SetPoint(X+11, Y+2,0xA4B2);
	LCD_SetPoint(X+12, Y+2,0xA4B2);
	LCD_SetPoint(X+13, Y+2,0xD618);
	LCD_SetPoint(X+14, Y+2,0xD618);
	LCD_SetPoint(X+15, Y+2,0xD618);
	LCD_SetPoint(X+16, Y+2,0xD618);
	LCD_SetPoint(X+17, Y+2,0x4A08);
	LCD_SetPoint(X+18, Y+2,0x4A08);
	LCD_SetPoint(X+19, Y+2,0x4A08);
	LCD_SetPoint(X+20, Y+2,0x4A08);
	LCD_SetPoint(X+21, Y+2,0x4A08);
	LCD_SetPoint(X+22, Y+2,0x0000);

	LCD_SetPoint(X+1, Y+3,0x0000);
	LCD_SetPoint(X+2, Y+3,0x4A08);
	LCD_SetPoint(X+3, Y+3,0x4A08);
	LCD_SetPoint(X+4, Y+3,0x4A08);
	LCD_SetPoint(X+5, Y+3,0xD618);
	LCD_SetPoint(X+6, Y+3,0x4A08);
	LCD_SetPoint(X+7, Y+3,0xD618);
	LCD_SetPoint(X+8, Y+3,0xD618);
	LCD_SetPoint(X+9, Y+3,0xA4B2);
	LCD_SetPoint(X+10, Y+3,0xA4B2);
	LCD_SetPoint(X+11, Y+3,0xD618);
	LCD_SetPoint(X+12, Y+3,0xA4B2);
	LCD_SetPoint(X+13, Y+3,0xA4B2);
	LCD_SetPoint(X+14, Y+3,0xA4B2);
	LCD_SetPoint(X+15, Y+3,0xA4B2);
	LCD_SetPoint(X+16, Y+3,0xA4B2);
	LCD_SetPoint(X+17, Y+3,0xA4B2);
	LCD_SetPoint(X+18, Y+3,0xD618);
	LCD_SetPoint(X+19, Y+3,0xD618);
	LCD_SetPoint(X+20, Y+3,0x4A08);
	LCD_SetPoint(X+21, Y+3,0x4A08);
	LCD_SetPoint(X+22, Y+3,0x4A08);
	LCD_SetPoint(X+23, Y+3,0x0000);

	LCD_SetPoint(X+1, Y+4,0x0000);
	LCD_SetPoint(X+2, Y+4,0x4A08);
	LCD_SetPoint(X+3, Y+4,0x4A08);
	LCD_SetPoint(X+4, Y+4,0xD618);
	LCD_SetPoint(X+5, Y+4,0xD618);
	LCD_SetPoint(X+6, Y+4,0x4A08);
	for(int i=7; i<=21; i++)
		LCD_SetPoint(X+i, Y+4,0xD618);
	LCD_SetPoint(X+22, Y+4,0x4A08);
	LCD_SetPoint(X+23, Y+4,0x4A08);
	LCD_SetPoint(X+24, Y+4,0x0000);

	LCD_SetPoint(X+1, Y+5,0x0000);
	LCD_SetPoint(X+2, Y+5,0x4A08);
	LCD_SetPoint(X+3, Y+5,0xD618);
	LCD_SetPoint(X+4, Y+5,0xD618);
	LCD_SetPoint(X+5, Y+5,0x4A08);
	LCD_SetPoint(X+6, Y+5,0x4A08);
	LCD_SetPoint(X+7, Y+5,0xA4B2);
	for(int i=8; i<=21; i++)
		LCD_SetPoint(X+i, Y+5,0xD618);
	LCD_SetPoint(X+9, Y+5,0x4A08);
	LCD_SetPoint(X+10, Y+5,0x4A08);
	LCD_SetPoint(X+11, Y+5,0x0000);

	LCD_SetPoint(X+1, Y+6,0x0000);
	LCD_SetPoint(X+2, Y+6,0xD618);
	LCD_SetPoint(X+3, Y+6,0xD618);
	LCD_SetPoint(X+4, Y+6,0xD618);
	LCD_SetPoint(X+5, Y+6,0xD618);
	LCD_SetPoint(X+6, Y+6,0x4A08);
	LCD_SetPoint(X+7, Y+6,0xA4B2);
	LCD_SetPoint(X+8, Y+6,0xA4B2);
	LCD_SetPoint(X+9, Y+6,0xA4B2);
	LCD_SetPoint(X+10, Y+6,0xA4B2);
	for(int i=11; i<=21; i++)
		LCD_SetPoint(X+i, Y+6,0xD618);
	LCD_SetPoint(X+22, Y+6,0xA4B2);
	LCD_SetPoint(X+23, Y+6,0x0000);

	LCD_SetPoint(X+1, Y+7,0x0000);
	LCD_SetPoint(X+2, Y+7,0xD618);
	LCD_SetPoint(X+3, Y+7,0xD618);
	LCD_SetPoint(X+4, Y+7,0xD618);
	LCD_SetPoint(X+5, Y+7,0xD618);
	LCD_SetPoint(X+6, Y+7,0x4A08);
	LCD_SetPoint(X+7, Y+7,0xA4B2);
	LCD_SetPoint(X+8, Y+7,0xD618);
	LCD_SetPoint(X+9, Y+7,0xD618);
	LCD_SetPoint(X+10, Y+7,0xD618);
	LCD_SetPoint(X+11, Y+7,0xA4B2);
	LCD_SetPoint(X+12, Y+7,0xA4B2);
	LCD_SetPoint(X+13, Y+7,0xA4B2);
	LCD_SetPoint(X+14, Y+7,0xA4B2);
	for(int i=15; i<=21; i++)
		LCD_SetPoint(X+i, Y+7,0xD618);
	LCD_SetPoint(X+22, Y+7,0xA4B2);
	LCD_SetPoint(X+23, Y+7,0x0000);

	LCD_SetPoint(X+1, Y+8,0x0000);
	LCD_SetPoint(X+2, Y+8,0xA4B2);
	LCD_SetPoint(X+3, Y+8,0xD618);
	LCD_SetPoint(X+4, Y+8,0xD618);
	LCD_SetPoint(X+5, Y+8,0xD618);
	LCD_SetPoint(X+6, Y+8,0xD618);
	LCD_SetPoint(X+7, Y+8,0x4A08);
	for(int i=8; i<=14; i++)
		LCD_SetPoint(X+i, Y+8,0xD618);
	LCD_SetPoint(X+15, Y+8,0xA4B2);
	for(int i=16; i<=21; i++)
		LCD_SetPoint(X+i, Y+8,0xD618);
	LCD_SetPoint(X+22, Y+8,0xA4B2);
	LCD_SetPoint(X+23, Y+8,0x0000);

	LCD_SetPoint(X+2, Y+9,0x0000);
	LCD_SetPoint(X+3, Y+9,0xA4B2);
	LCD_SetPoint(X+4, Y+9,0xD618);
	LCD_SetPoint(X+5, Y+9,0xD618);
	LCD_SetPoint(X+6, Y+9,0xD618);
	LCD_SetPoint(X+7, Y+9,0x4A08);
	LCD_SetPoint(X+8, Y+9,0xA4B2);
	for(int i=9; i<=14; i++)
		LCD_SetPoint(X+i, Y+9,0xD618);
	LCD_SetPoint(X+15, Y+9,0xA4B2);
	LCD_SetPoint(X+16, Y+9,0xD618);
	LCD_SetPoint(X+17, Y+9,0xD618);
	LCD_SetPoint(X+18, Y+9,0xD618);
	LCD_SetPoint(X+19, Y+9,0x4A08);
	LCD_SetPoint(X+20, Y+9,0xA4B2);
	LCD_SetPoint(X+21, Y+9,0xD618);
	LCD_SetPoint(X+22, Y+9,0x0000);

	LCD_SetPoint(X+2, Y+10,0x0000);
	LCD_SetPoint(X+3, Y+10,0xA4B2);
	LCD_SetPoint(X+4, Y+10,0xD618);
	LCD_SetPoint(X+5, Y+10,0xD618);
	LCD_SetPoint(X+6, Y+10,0xD618);
	LCD_SetPoint(X+7, Y+10,0x4A08);
	for(int i=8; i<=12; i++)
		LCD_SetPoint(X+i, Y+10,0xA4B2);
	LCD_SetPoint(X+13, Y+10,0xD618);
	LCD_SetPoint(X+14, Y+10,0xD618);
	LCD_SetPoint(X+15, Y+10,0xA4B2);
	LCD_SetPoint(X+16, Y+10,0xD618);
	LCD_SetPoint(X+17, Y+10,0xD618);
	LCD_SetPoint(X+18, Y+10,0xD618);
	LCD_SetPoint(X+19, Y+10,0xD618);
	LCD_SetPoint(X+20, Y+10,0xA4B2);
	LCD_SetPoint(X+21, Y+10,0x4A08);
	LCD_SetPoint(X+22, Y+10,0x0000);

	LCD_SetPoint(X+2, Y+11,0x0000);
	LCD_SetPoint(X+3, Y+11,0x4A08);
	LCD_SetPoint(X+4, Y+11,0xD618);
	LCD_SetPoint(X+5, Y+11,0xD618);
	LCD_SetPoint(X+6, Y+11,0xD618);
	LCD_SetPoint(X+7, Y+11,0x4A08);
	LCD_SetPoint(X+8, Y+11,0xA4B2);
	LCD_SetPoint(X+9, Y+11,0xD618);
	LCD_SetPoint(X+10, Y+11,0xD618);
	LCD_SetPoint(X+11, Y+11,0xA4B2);
	for(int i=12; i<=20; i++)
		LCD_SetPoint(X+i, Y+11,0xD618);
	LCD_SetPoint(X+21, Y+11,0x4A08);
	LCD_SetPoint(X+22, Y+11,0x0000);

	LCD_SetPoint(X+3, Y+12,0x0000);
	LCD_SetPoint(X+4, Y+12,0xD618);
	LCD_SetPoint(X+5, Y+12,0xD618);
	LCD_SetPoint(X+6, Y+12,0xA4B2);
	LCD_SetPoint(X+7, Y+12,0x4A08);
	LCD_SetPoint(X+8, Y+12,0xA4B2);
	LCD_SetPoint(X+9, Y+12,0xD618);
	LCD_SetPoint(X+10, Y+12,0xD618);
	LCD_SetPoint(X+11, Y+12,0xD618);
	LCD_SetPoint(X+12, Y+12,0xA4B2);
	LCD_SetPoint(X+13, Y+12,0xA4B2);
	for(int i=14; i<=20; i++)
		LCD_SetPoint(X+i, Y+12,0xD618);
	LCD_SetPoint(X+21, Y+12,0x4A08);
	LCD_SetPoint(X+22, Y+12,0x0000);

	LCD_SetPoint(X+3, Y+13,0x0000);
	LCD_SetPoint(X+4, Y+13,0xD618);
	LCD_SetPoint(X+5, Y+13,0xD618);
	LCD_SetPoint(X+6, Y+13,0xA4B2);
	LCD_SetPoint(X+7, Y+13,0x4A08);
	for(int i=8; i<=14; i++)
		LCD_SetPoint(X+i, Y+13,0xD618);
	LCD_SetPoint(X+15, Y+13,0xA4B2);
	for(int i=16; i<=20; i++)
		LCD_SetPoint(X+i, Y+13,0xD618);
	LCD_SetPoint(X+21, Y+13,0x0000);

	LCD_SetPoint(X+3, Y+14,0x0000);
	LCD_SetPoint(X+4, Y+14,0xD618);
	LCD_SetPoint(X+5, Y+14,0xD618);
	LCD_SetPoint(X+6, Y+14,0xA4B2);
	LCD_SetPoint(X+7, Y+14,0xA4B2);
	for(int i=8; i<=14; i++)
		LCD_SetPoint(X+i, Y+14,0xD618);
	LCD_SetPoint(X+15, Y+14,0xA4B2);
	for(int i=16; i<=19; i++)
		LCD_SetPoint(X+i, Y+14,0xD618);
	LCD_SetPoint(X+20, Y+14,0x4A08);
	LCD_SetPoint(X+21, Y+14,0x0000);

	LCD_SetPoint(X+4, Y+15,0x0000);
	LCD_SetPoint(X+5, Y+15,0xD618);
	LCD_SetPoint(X+6, Y+15,0xD618);
	LCD_SetPoint(X+7, Y+15,0xA4B2);
	LCD_SetPoint(X+8, Y+15,0xA4B2);
	for(int i=9; i<=14; i++)
		LCD_SetPoint(X+i, Y+15,0xD618);
	LCD_SetPoint(X+15, Y+15,0xA4B2);
	LCD_SetPoint(X+16, Y+15,0xD618);
	LCD_SetPoint(X+17, Y+15,0xD618);
	LCD_SetPoint(X+18, Y+15,0xD618);
	LCD_SetPoint(X+19, Y+15,0xD618);
	LCD_SetPoint(X+20, Y+15,0xA4B2);
	LCD_SetPoint(X+21, Y+15,0x0000);

	LCD_SetPoint(X+4, Y+16,0x0000);
	LCD_SetPoint(X+5, Y+16,0x4A08);
	LCD_SetPoint(X+6, Y+16,0xD618);
	LCD_SetPoint(X+7, Y+16,0xD618);
	LCD_SetPoint(X+8, Y+16,0xA4B2);
	for(int i=9; i<=14; i++)
		LCD_SetPoint(X+i, Y+16,0xD618);
	LCD_SetPoint(X+15, Y+16,0xA4B2);
	LCD_SetPoint(X+16, Y+16,0xA4B2);
	LCD_SetPoint(X+17, Y+16,0xD618);
	LCD_SetPoint(X+18, Y+16,0xD618);
	LCD_SetPoint(X+19, Y+16,0x4A08);
	LCD_SetPoint(X+20, Y+16,0x4A08);
	LCD_SetPoint(X+21, Y+16,0x0000);

	LCD_SetPoint(X+5, Y+17,0x0000);
	LCD_SetPoint(X+6, Y+17,0x4A08);
	for(int i=7; i<=11; i++)
		LCD_SetPoint(X+i, Y+17,0xD618);
	LCD_SetPoint(X+12, Y+17,0xA4B2);
	LCD_SetPoint(X+13, Y+17,0xD618);
	LCD_SetPoint(X+14, Y+17,0xD618);
	LCD_SetPoint(X+15, Y+17,0x4A08);
	LCD_SetPoint(X+16, Y+17,0xA4B2);
	LCD_SetPoint(X+17, Y+17,0xD618);
	LCD_SetPoint(X+18, Y+17,0x4A08);
	LCD_SetPoint(X+19, Y+17,0x4A08);
	LCD_SetPoint(X+20, Y+17,0x0000);

	LCD_SetPoint(X+6, Y+18,0x0000);
	LCD_SetPoint(X+7, Y+18,0x0000);
	LCD_SetPoint(X+8, Y+18,0x0000);
	LCD_SetPoint(X+9, Y+18,0x4A08);
	for(int i=10; i<=14; i++)
		LCD_SetPoint(X+i, Y+18,0xD618);
	LCD_SetPoint(X+15, Y+18,0xA4B2);
	LCD_SetPoint(X+16, Y+18,0xD618);
	LCD_SetPoint(X+17, Y+18,0xD618);
	LCD_SetPoint(X+18, Y+18,0xD618);
	LCD_SetPoint(X+19, Y+18,0x4A08);
	LCD_SetPoint(X+20, Y+18,0x0000);

	LCD_SetPoint(X+9, Y+19,0x0000);
	LCD_SetPoint(X+10, Y+19,0x4A08);
	LCD_SetPoint(X+11, Y+19,0xD618);
	LCD_SetPoint(X+12, Y+19,0xD618);
	LCD_SetPoint(X+13, Y+19,0xD618);
	LCD_SetPoint(X+14, Y+19,0xA4B2);
	LCD_SetPoint(X+15, Y+19,0xA4B2);
	LCD_SetPoint(X+16, Y+19,0xD618);
	LCD_SetPoint(X+17, Y+19,0xD618);
	LCD_SetPoint(X+18, Y+19,0xD618);
	LCD_SetPoint(X+19, Y+19,0x0000);

	LCD_SetPoint(X+10, Y+20,0x0000);
	for(int i=11; i<=15; i++)
		LCD_SetPoint(X+i, Y+20,0xD618);
	LCD_SetPoint(X+16, Y+20,0x4A08);
	LCD_SetPoint(X+17, Y+20,0x0000);
	LCD_SetPoint(X+18, Y+20,0x0000);

	LCD_SetPoint(X+11, Y+21,0x0000);
	LCD_SetPoint(X+12, Y+21,0xD618);
	LCD_SetPoint(X+13, Y+21,0xD618);
	LCD_SetPoint(X+14, Y+21,0xD618);
	LCD_SetPoint(X+15, Y+21,0x4A08);
	LCD_SetPoint(X+16, Y+21,0x0000);

	for(int i=12; i<=15; i++)
		LCD_SetPoint(X+i, Y+22,0x0000);
}

int main(void) 
{
	HAL_Init();
	SystemClock_Config();
	LCD_Initialization();
	
	Skier s1;
	DrawMenu(-1);
	UseMenu();
}