#include "lis3dsh.h"
#include "main.h"
#include <cmath>
#include <stdlib.h>

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
	
	while(1)
	{
		//sprawdza wychylenie w osi X
		LIS3DSH_ReadACC(out);
		accX = out[0];
			
		speedUpdate(s1.speed);
		positionUpdate(accX, s1.speed, s1.X, s1.Y);
	}
}