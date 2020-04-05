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

void ChangeTarget(uint8_t option, uint8_t LastOption)
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

void ShowRanking()
{
	LCD_Clear(32761);
	GUI_Text(130, 220, uint8_t *str,49149, 1567); //RANKING
	DrawBox(41, 220, 240, 160, 5, uint16_t color);
}

void Sound()
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
			ChangeTarget(option, option+1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && option!=2)
		{
			Sound();
			option++;
			ChangeTarget(option, option-1);
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
				ShowRanking();
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

int main(void) 
{
	HAL_Init();
	SystemClock_Config();
	
	Skier s1;
	DrawMenu(-1);
	UseMenu();
}