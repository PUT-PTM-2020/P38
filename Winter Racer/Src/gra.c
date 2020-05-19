#include "gra.h"
#define MAP_DISTANCE 500

//NOTE
	//Dodac napisy do DrawMenu, ChangeTarget i ShowRanking

//--- StartScreen --- TODO
void StartScreen()
{

}
//--- ExitScreen --- TODO
void ExitScreen()
{

}
//--- DrawBox --- TODO
void DrawBox(uint16_t X, uint16_t Y, uint16_t width, uint16_t height, uint16_t border, uint16_t color)
{
	for(int i=0; i<border; i++)
	{
		//LCD_DrawLine(X, Y-i, X+(width-1), Y-i, color);
		//LCD_DrawLine(X+i, Y-border, X+i, Y-height+border+1, color);
		//LCD_DrawLine(X, Y-height+1+i, X+(width-1), Y-height+1+i, color);
		//LCD_DrawLine(X+(width-1)-i, Y-border, X+(width-1)-i, Y-height+border+1, color);
	}
}
//--- FillInside --- TODO
void FillInside(uint16_t X, uint16_t Y, uint16_t width, uint16_t height, uint16_t border, uint16_t color)
{
	X=X+border;
	Y=Y-border;

	uint16_t Xp=X+(width-1)-border;
	uint16_t Yp=Y-(height-1)+border;

	for(int i=X; i<=Xp; i++)
		for(int j=Y; j<=Yp; j++)
		{
			//ili9325_WritePixel(i, j,0);
		}
}
//--- DrawMenu --- TODO
void DrawMenu(uint8_t Mode)
{
	if(Mode==-1)	//-1 rysuje całe menu
	{
		LCD_Clear(1567);
		//GUI_Text(120, 220, uint8_t *str,49149, 1567); //WINTER RACER
	}
	if(Mode==-1 || Mode==0)
	{
		DrawBox(86,190,150,40,3,65535);	//START
		//GUI_Text(147, 176, uint8_t *str,65535, 1567);
	}
	if(Mode==-1 || Mode==1)
	{
		DrawBox(86,140,150,40,3,65535);	//RANKING
		//GUI_Text(147, 126, uint8_t *str,65535, 1567);
	}
	if(Mode==-1 || Mode==2)
	{
		DrawBox(86,90,150,40,3,65535);		//WYJŚCIE
		//GUI_Text(147, 76, uint8_t *str,65535, 1567);
	}
}
//--- ChangeTargetMenu --- TODO
void ChangeTargetMenu(uint8_t option, uint8_t LastOption)
{	
	DrawMenu(LastOption);
	
	switch(option)
	{
		case 0:
		DrawBox(86,190,150,40,3,49149);	//START
		//GUI_Text(147, 176, uint8_t *str,49149, 1567);
		break;
		case 1:
		DrawBox(86,140,150,40,3,65535);	//RANKING
		//GUI_Text(147, 126, uint8_t *str,49149, 1567);
		break;
		case 2:
		DrawBox(86,90,150,40,3,65535);		//WYJŚCIE
		//GUI_Text(147, 76, uint8_t *str,49149, 1567);
		break;
	}
}
//--- DrawRanking --- TODO
void DrawRanking(uint8_t Mode)
{
	if(Mode==-1)
	{
		LCD_Clear(0x070F);
		//GUI_Text(130, 220, uint8_t *str,49149, 65535); //RANKING
	}
	if(Mode==-1 || Mode==0)
	{
		FillInside(41, 190, 240, 140, 5, 0x05AC);
		DrawBox(133, 43, 60, 35, 3, 0x0347);
		//GUI_Text(140, 60, uint8_t *str,49149, 65535); //WSTECZ
	}
	if(Mode==-1 || Mode==1)
	{
		FillInside(41, 190, 240, 140, 5, 0xC638);
		DrawBox(41, 190, 240, 140, 5, 0x05AC);
		ShowRankingOnBoard();
	}
}
//--- ChangeTargetRanking --- TODO
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
//--- UseRanking --- TODO
void UseRanking()
{
	int option=0;
	
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && option!=0)
		{
			Sound(1);
			option--;
			ChangeTargetRanking(option, option+1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && option!=1)
		{
			Sound(1);
			option++;
			ChangeTargetRanking(option, option-1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
		{
			Sound(1);
			switch(option)
			{
				case 0:
				DrawMenu(-1);
				option=3;
				break;
				case 1:

				break;
			}
		}
		if(option==3) break;
	}
}
//--- Sound --- TODO
void Sound(uint8_t option)
{
	switch(option)
	{
	case 1:
		//Dzwiek wyboru opcji w menu
		break;
	case 2:
		//Dzwiek przelaczenia opcji w menu
		break;
	case 3:
		//Fanfary zwyciestwa
		break;
	case 4:
		//Smutne trabki przegranej
		break;
	case 5:
		//Zderzenie z przeszkoda
		break;
	case 6:
		//Muzyczka w tle
		break;
	case 7:
		//Dźwięk nart
		break;
	}
}
//--- UpdateSpeedValue --- TODO
void UpdateSpeedValue(int speed)
{
	int SpeedInKm = round(7500/speed);
	for(int i=78; i<156; i++)
		for(int j=0; j<30; j++)
			ili9325_WritePixel(1+i,240-j,29614);
}
//--- PrintInfo --- TODO
void PrintInfo(int option)
{
	for(int i=0; i<320; i++)
		for(int j=0; j<18; j++)
			ili9325_WritePixel(1+i,1+j,29614);
	switch(option)
	{
	case 1:	//Press k3 to Start
		break;
	case 2:	//Press k3 to Pause
		break;
	}
}
//--- RunGame --- TODO
void RunGame()
{
	SetUI(3,0,0,1);
	struct Skier s1;
	s1.Y = 155;
	s1.X = 145;
	DrawSkier(1, s1.X, s1.Y);

	int leftBorderHitboxX[192];
	int leftBorderHitboxY[192];
	int rightBorderHitboxX[192];
	int rightBorderHitboxY[192];
	int leftBorderFlag = 0;
	int rightBorderFlag = 0;

	int* objectBorderHitboxX;
	int* objectBorderHitboxY;
	int objectR1 = 0;
	int objectR2 = 0;

	int position = 0;
	int arrow = 0;

	PressStartButton();

	while(1)
	{
		ili9325_FillRect(0,19,320,192,65535); //czyszczenie ekranu
		s1.Hitbox_Y = CreateRectangleHitboxY(s1.position+5+s1.centerHeight,s1.centerWidth,s1.centerHeight);
		s1.Hitbox_X = CreateRectangleHitboxX(s1.X+s1.centerWidth,s1.centerWidth,s1.centerHeight);
		UpdateSpeedValue(s1.speed);
		PressPauseButton();

		LIS3DSH_ReadACC(out);
		accX = out[0];

		for(int i=position, k=0; i<192+position; i++, k++)
		{
			leftBorderFlag = 0;
			rightBorderFlag = 0;
			for(int j=0; j<77; j++)
			{
				if(A.leftBorder[i][j]==1)
				{
					ili9325_WritePixel(29+j, 210-i, 51071);
					ili9325_WritePixel(30+j, 210-i, 51071);
					leftBorderHitboxX[k] = 30+j;
					leftBorderHitboxY[k] = 210-i;
					leftBorderFlag = 1;
				}
				if(A.rightBorder[i][j]==1)
				{
					ili9325_WritePixel(212+j, 210-i, 51071);
					ili9325_WritePixel(213+j, 210-i, 51071);
					rightBorderHitboxX[k] = 30+j;
					rightBorderHitboxY[k] = 210-i;
					rightBorderFlag = 1;
				}
				if((rightBorderFlag==1) && (leftBorderFlag==1))
					break;
			}
		}
		for(int i=position; i<192+position; i++)
		{
			for(int j=0; j<11; j++)
			{
				if(A.obstacles[i][j]!=0)
				{
					SetObstacle(A.obstacles[i][j], 30+26*j, i);	//dodać ograniczenie obszaru rysowania
					switch(A.obstacles[i][j])
					{
					case 1:
						objectR1 = 13;
						objectR2 = 14;
						objectBorderHitboxX = CreateRectangleHitboxX(14, objectR1, objectR2);
						objectBorderHitboxY = CreateRectangleHitboxY(15, objectR1, objectR2);
						break;
					case 2:
						objectR1 = 11;
						objectR2 = 11;
						objectBorderHitboxX = CreateRectangleHitboxX(12, objectR1, objectR2);
						objectBorderHitboxY = CreateRectangleHitboxY(12, objectR1, objectR2);
						break;
					case 3:
						objectR1 = 11;
						objectR2 = 16;
						objectBorderHitboxX = CreateRectangleHitboxX(12, objectR1, objectR2);
						objectBorderHitboxY = CreateRectangleHitboxY(17, objectR1, objectR2);
						break;
					case 4:
						objectR1 = 15;
						objectR2 = 14;
						objectBorderHitboxX = CreateRectangleHitboxX(16, objectR1, objectR2);
						objectBorderHitboxY = CreateRectangleHitboxY(15, objectR1, objectR2);
						break;
					}
					if(Collision(s1.Hitbox_X, s1.Hitbox_Y, s1.centerWidth, s1.centerHeight, objectBorderHitboxX,
							objectBorderHitboxY, objectR1, objectR2))
					{
						switch(A.obstacles[i][j])
						{
						case 1:
							s1.HP -= DMG.snowmanDMG;
							break;
						case 2:
							s1.HP -= DMG.rockDMG;
							break;
						case 3:
							s1.HP -= DMG.bowmanDMG;
							break;
						case 4:
							s1.HP -= DMG.treeDMG;
							break;
						}
						if(s1.hp<0)
						{
							GameOver();
							return;
						}
						else
						{
							UpdateHP(s1.HP);
							s1.X = 145;
							s1.Y = 155;
							s1.speed = 500;
						}
					}
				}
			}
		}

		if(BorderCollision(s1.Hitbox_X, s1.Hitbox_Y, s1.centerHeight, s1.centerWidth, leftBorderHitboxX, leftBorderHitboxY))
		{
			s1.HP -= DMG.borderDMG;
			if(s1.HP<0)
			{
				GameOver();
				return;
			}
		}
		else if(BorderCollision(s1.Hitbox_X, s1.Hitbox_Y, s1.centerHeight, s1.centerWidth, rightBorderHitboxX, rightBorderHitboxY))
		{
			s1.HP -= DMG.borderDMG;
			if(s1.HP<0)
			{
				GameOver();
				return;
			}
			else
			{
				UpdateHP(s1.HP);
				s1.X = 145;
				s1.Y = 155;
				s1.speed = 500;
			}
		}

		s1.speed = SpeedUpdate(s1.speed);
		PositionUpdate(accX, s1.speed, s1.X, s1.Y);

		if(position%42==0)
		{
			arrow++;
			UpdateMiniMap(arrow);
		}

		position++;
	}
}
//--- ShowRankingOnBoard --- TODO
void ShowRankingOnBoard()
{
	char ranking[180] = ReadFromRanking();
	int FirstFreePosition = 0;
	for(int i=0; i<=162; i+=18)
	{
		if((ranking[i]=='0')&&(ranking[i+1]=='0'))
	    {
			FirstFreePosition = i;
			break;
	    }
	    else if((i==162) && (ranking[i]!='0'))
	    {
	    	FirstFreePosition = i;
	    }
	}
	char records[10][18];
	for (int i=0; i<10; i++)
	{
		for(int j=0; j<18; j++)
		{
			records[i][j] = ranking[i*18+j];
		}
	}
	char points[10][3];
	char times[10][3];
	char nicks[10][10];
	for (int i=0; i<10; i++)
	{
		for(int j=0; j<3; j++)
		{
			points[i][j] = ranking[i*18+j+15];
		}
	}
	for (int i=0; i<10; i++)
	{
		for(int j=0; j<3; j++)
		{
			times[i][j] = ranking[i*18+j+11];
		}
	}
	for (int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			nicks[i][j] = ranking[i*18+j+1];
		}
	}

	if(FirstFreePosition==0)
	{
		//Brak wyników w rankingu
	}
	else
	{
		for(int i=0; i<10; i++)
		{
			//Pokaż wyniki na tablicy
			//nicks[i][j]
			//points[i][j]
			//times[i][j]
		}
	}
}
//--- GameOver --- TODO
void GameOver()
{
	PressContinueButton();
}



//--- UseMenu --- DONE
void UseMenu()
{
	int option=0;

	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && option!=0)
		{
			Sound(2);
			option--;
			ChangeTargetMenu(option, option+1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && option!=2)
		{
			Sound(2);
			option++;
			ChangeTargetMenu(option, option-1);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
		{
			Sound(1);
			switch(option)
			{
				case 0:
					RunGame();
				break;
				case 1:
					DrawRanking(-1);
					UseRanking();
				break;
				case 2:
					ili9325_DisplayOff();
				break;
			}
		}
	}
}


//--- SortRanking --- DONE
char* SortRanking(char ranking[180])
{
    char position[10][18];
    int points[10];
    int bpoints[10];

    for(int i=0, k=0; i<=162; i+=18, k++)
    {
      char chpoints[3];
        for(int j=0; j<18; j++)
        {
          position[k][j] = ranking[i+j];
        }
        chpoints[0]=position[k][15];
        chpoints[1]=position[k][16];
        chpoints[2]=position[k][17];
        sscanf(chpoints, "%d", &points[k]);
    }

    for(int i=0; i<10; i++)
      bpoints[i] = points[i];

    int i, i_max, max, j;
    int N = 10;
    for (j = N-1; j > 0; j--)
    {
      max = points[0];
      i_max = 0;
      for ( i = 1; i <= j; i++ )
        if ( points[i] < max )
        {
          max = points[i];
          i_max = i;
        }
      points[i_max] = points[j];
      points[j] = max;
    }

    int temp[10]={12,12,12,12,12,12,12,12,12,12};
    int info = 0;

    for(int i=0, k=0; i<10; k+=18, i++)
    {
      for(int j=0; j<10; j++)
      {
        if(points[i]==bpoints[j])
        {
          info = 0;
          for(int o=0; o<10; o++)
          {
            if(temp[o]==j)
            {
              info = 1;
            }
          }
          if(info==0)
          {
            temp[i]=j;
            for(int q=0; q<18; q++)
            {
              ranking[k+q]=position[j][q];
            }
            break;
          }
        }
      }
    }

    char x[1];
    for(int i=0, k=0; i<=162; i+=18, k++)
    {
      if((ranking[i]=='0')&&(ranking[i+1]=='0'))
      {
        break;
      }
      else
      {
        sprintf(x, "%d", k);
        ranking[i] = x[0];
      }
    }

    return ranking;
}
//--- SetRanking --- DONE
void SetRanking()
{
	fresult = f_mount(&FatFs, "", 0);
	fresult = f_open(&file, "Ranking.txt", FA_READ);
	if(f==NULL)
	{
		char ranking[180];
		for(int i=0; i<180; i++)
			ranking[i]='0';
		WriteToRanking(ranking);
		fresult = f_close(&file);
	}
	else fresult = f_close(&file);
}
//--- WriteToRanking --- DONE
void WriteToRanking(char* ranking)
{
	fresult = f_mount(&FatFs, "", 0);
	fresult = f_open(&file, "Ranking.txt", FA_OPEN_ALWAYS | FA_WRITE);
	int len = sprintf(buffer, ranking);
	fresult = f_write(&file, buffer, len, &bytes_written);
	fresult = f_close (&file);
}
//--- NewRecordInRanking --- DONE
void NewRecordInRanking(char nick[10], char ranking[180], int mytime, int hp)
{
    int FirstFreePosition = 0;
    for(int i=0; i<=162; i+=18)
    {
        if((ranking[i]=='0')&&(ranking[i+1]=='0'))
        {
            FirstFreePosition = i;
            break;
        }
        else if((i==162) && (ranking[i]!='0'))
        {
            return;
        }
    }
    int elo = FirstFreePosition;
    char x[1];
    sprintf(x, "%d", (elo/18));
    ranking[FirstFreePosition] = x[0];
    for(int i=1; i<=10; i++)
    {
        if(nick[i-1]!=NULL)
        {
            ranking[FirstFreePosition+i] = nick[i-1];
        }
        else
        {
            ranking[FirstFreePosition+i] = '0';
        }
    }
    char t1[1];
    char t2[2];
    char t3[3];
    if(mytime < 10)
    {
        sprintf(t1, "%d", mytime);
        ranking[FirstFreePosition+11] = '0';
        ranking[FirstFreePosition+12] = '0';
        ranking[FirstFreePosition+13] = t1[0];
    }
    else if((mytime >= 10) && (mytime < 100))
    {
        sprintf(t2, "%d", mytime);
        ranking[FirstFreePosition+11] = '0';
        ranking[FirstFreePosition+12] = t2[0];
        ranking[FirstFreePosition+13] = t2[1];
    }
    else
    {
        sprintf(t3, "%d", mytime);
        ranking[FirstFreePosition+11] = t3[0];
        ranking[FirstFreePosition+12] = t3[1];
        ranking[FirstFreePosition+13] = t3[2];
    }
    char hp1[1];
    sprintf(hp1, "%d", hp);
    ranking[FirstFreePosition+14] = hp1[0];
    char points3[3];
    int pointsForTime = 500-(2*mytime);
    int pointsForHP = hp*100;
    int points = 150 + pointsForTime + pointsForHP;
    sprintf(points3, "%d", points);
    ranking[FirstFreePosition+15] = points3[0];
    ranking[FirstFreePosition+16] = points3[1];
    ranking[FirstFreePosition+17] = points3[2];
    sprintf(ranking, "%s", SortRanking(ranking));

    WriteToRanking(ranking);
}
//--- ReadFromRanking --- DONE
char* ReadFromRanking()
{
	fresult = f_mount(&FatFs, "", 0);
	fresult = f_open(&file, "Ranking.txt", FA_READ);
	fresult = f_read(&file, buffer, 16, &bytes_read);
	sprintf(ranking, buffer);
	fresult = f_close(&file);
	return ranking;
}


//--- SetUI --- DONE
void SetUI(int HP, int speedValue, int miniMap, int info)
{
	ili9325_FillRect(0, 0, 320, 240, 65535);
	UpdateHP(HP);
	UpdateSpeedValue(speedValue);
	UpdateMiniMap(miniMap);
	PrintInfo(info);
}
//--- PositionUpdata --- DONE
void PositionUpdate(float accX, int speed, int *X, int *Y)
{
	accX = accX/100;
	if(accX < -2)
	{
		*X += accX;
		DrawSkier(1, *X, *Y);
	}
	else if(accX > 2)
	{
		*X += accX/100;
		DrawSkier(2, *X, *Y);
	}
	else DrawSkier(3, *X, *Y);
	HAL_Delay(speed);
}
//--- UpdateArrow --- DONE
void UpdateArrow(int distance)
{
	ili9325_WritePixel(distance+175, 231, 65535);
	ili9325_WritePixel(distance+176, 231, 65535);
	ili9325_WritePixel(distance+177, 231, 65535);

	ili9325_WritePixel(distance+175, 230, 65535);
	ili9325_WritePixel(distance+176, 230, 65535);
	ili9325_WritePixel(distance+177, 230, 65535);
	ili9325_WritePixel(distance+178, 230, 65535);
	ili9325_WritePixel(distance+179, 230, 65535);

	ili9325_WritePixel(distance+177, 229, 65535);
	ili9325_WritePixel(distance+178, 229, 65535);
	ili9325_WritePixel(distance+179, 229, 65535);
	ili9325_WritePixel(distance+180, 229, 65535);
	ili9325_WritePixel(distance+181, 229, 65535);

	ili9325_WritePixel(distance+179, 228, 65535);
	ili9325_WritePixel(distance+180, 228, 65535);
	ili9325_WritePixel(distance+181, 228, 65535);
	ili9325_WritePixel(distance+182, 228, 65535);
	ili9325_WritePixel(distance+183, 228, 65535);

	ili9325_WritePixel(distance+181, 227, 65535);
	ili9325_WritePixel(distance+182, 227, 65535);
	ili9325_WritePixel(distance+183, 227, 65535);
	ili9325_WritePixel(distance+184, 227, 65535);

	ili9325_WritePixel(distance+183, 226, 65535);
	ili9325_WritePixel(distance+184, 226, 65535);
	ili9325_WritePixel(distance+185, 226, 65535);

	ili9325_WritePixel(distance+183, 225, 65535);
	ili9325_WritePixel(distance+184, 225, 65535);
	ili9325_WritePixel(distance+185, 225, 65535);

	ili9325_WritePixel(distance+181, 224, 65535);
	ili9325_WritePixel(distance+182, 224, 65535);
	ili9325_WritePixel(distance+183, 224, 65535);
	ili9325_WritePixel(distance+184, 224, 65535);

	ili9325_WritePixel(distance+179, 223, 65535);
	ili9325_WritePixel(distance+180, 223, 65535);
	ili9325_WritePixel(distance+181, 223, 65535);
	ili9325_WritePixel(distance+182, 223, 65535);
	ili9325_WritePixel(distance+183, 223, 65535);

	ili9325_WritePixel(distance+177, 222, 65535);
	ili9325_WritePixel(distance+178, 222, 65535);
	ili9325_WritePixel(distance+179, 222, 65535);
	ili9325_WritePixel(distance+180, 222, 65535);
	ili9325_WritePixel(distance+181, 222, 65535);

	ili9325_WritePixel(distance+175, 221, 65535);
	ili9325_WritePixel(distance+176, 221, 65535);
	ili9325_WritePixel(distance+177, 221, 65535);
	ili9325_WritePixel(distance+178, 221, 65535);
	ili9325_WritePixel(distance+179, 221, 65535);

	ili9325_WritePixel(distance+175, 220, 65535);
	ili9325_WritePixel(distance+176, 220, 65535);
	ili9325_WritePixel(distance+177, 220, 65535);
}
//--- UpdateMiniMap --- DONE
void UpdateMiniMap(int distance)
{
	for(int i=156; i<320; i++)
		for(int j=0; j<30; j++)
			ili9325_WritePixel(1+i,240-j,1567);
	ili9325_WritePixel(173, 231, 2021);
	ili9325_WritePixel(174, 231, 2021);
	ili9325_WritePixel(173, 230, 2021);
	ili9325_WritePixel(174, 230, 2021);
	ili9325_WritePixel(173, 229, 2021);
	ili9325_WritePixel(174, 229, 2021);
	ili9325_WritePixel(173, 228, 2021);
	ili9325_WritePixel(174, 228, 2021);
	ili9325_WritePixel(173, 227, 2021);
	ili9325_WritePixel(174, 227, 2021);
	ili9325_WritePixel(173, 226, 2021);
	ili9325_WritePixel(174, 226, 2021);
	ili9325_WritePixel(173, 225, 2021);
	ili9325_WritePixel(174, 225, 2021);
	ili9325_WritePixel(173, 224, 2021);
	ili9325_WritePixel(174, 224, 2021);
	ili9325_WritePixel(173, 223, 2021);
	ili9325_WritePixel(174, 223, 2021);
	ili9325_WritePixel(173, 222, 2021);
	ili9325_WritePixel(174, 222, 2021);
	ili9325_WritePixel(173, 221, 2021);
	ili9325_WritePixel(174, 221, 2021);
	ili9325_WritePixel(173, 220, 2021);
	ili9325_WritePixel(174, 220, 2021);
	for(int i=0; i<128; i++)
	{
		ili9325_WritePixel(i+175, 227, 1012);
		ili9325_WritePixel(i+175, 226, 1012);
		ili9325_WritePixel(i+175, 225, 1012);
		ili9325_WritePixel(i+175, 224, 1012);
	}
	ili9325_WritePixel(303, 231, 2021);
	ili9325_WritePixel(304, 231, 2021);
	ili9325_WritePixel(303, 230, 2021);
	ili9325_WritePixel(304, 230, 2021);
	ili9325_WritePixel(303, 229, 2021);
	ili9325_WritePixel(304, 229, 2021);
	ili9325_WritePixel(303, 228, 2021);
	ili9325_WritePixel(304, 228, 2021);
	ili9325_WritePixel(303, 227, 2021);
	ili9325_WritePixel(304, 227, 2021);
	ili9325_WritePixel(303, 226, 2021);
	ili9325_WritePixel(304, 226, 2021);
	ili9325_WritePixel(303, 225, 2021);
	ili9325_WritePixel(304, 225, 2021);
	ili9325_WritePixel(303, 224, 2021);
	ili9325_WritePixel(304, 224, 2021);
	ili9325_WritePixel(303, 223, 2021);
	ili9325_WritePixel(304, 223, 2021);
	ili9325_WritePixel(303, 222, 2021);
	ili9325_WritePixel(304, 222, 2021);
	ili9325_WritePixel(303, 221, 2021);
	ili9325_WritePixel(304, 221, 2021);
	ili9325_WritePixel(303, 220, 2021);
	ili9325_WritePixel(304, 220, 2021);
	UpdateArrow(distance);
}
//--- PressStartButton --- DONE
void PressStartButton()
{
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
			break;
	}
	PrintInfo(2);
}
//--- PressPauseButton --- DONE
void PressPauseButton()
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
	{
		PrintInfo(1);
		PressStartButton();
	}
}
//--- SetSnowman --- DONE
void SetSnowman(uint16_t X, uint16_t Y)
{
	for(int i=13; i<=18; i++)
		ili9325_WritePixel(X+i, Y,0);

	ili9325_WritePixel(X+11, Y+1,0);
	ili9325_WritePixel(X+12, Y+1,0);
	for(int i=13; i<=18; i++)
		ili9325_WritePixel(X+i, Y+1,65535);
	ili9325_WritePixel(X+19, Y+1,0);
	ili9325_WritePixel(X+20, Y+1,0);

	ili9325_WritePixel(X+10, Y+2,0);
	for(int i=11; i<=20; i++)
		ili9325_WritePixel(X+i, Y+2,65535);
	ili9325_WritePixel(X+21, Y+2,0);
	
	ili9325_WritePixel(X+9, Y+3,0);
	for(int i=10; i<=14; i++)
		ili9325_WritePixel(X+i, Y+3,65535);
	ili9325_WritePixel(X+15, Y+3,0);
	ili9325_WritePixel(X+16, Y+3,0);
	for(int i=17; i<=21; i++)
		ili9325_WritePixel(X+i, Y+3,65535);
	ili9325_WritePixel(X+22, Y+3,0);

	ili9325_WritePixel(X+9, Y+4,0);
	for(int i=10; i<=14; i++)
		ili9325_WritePixel(X+i, Y+4,65535);
	ili9325_WritePixel(X+15, Y+4,0);
	ili9325_WritePixel(X+16, Y+4,0);
	for(int i=17; i<=21; i++)
		ili9325_WritePixel(X+i, Y+4,65535);
	ili9325_WritePixel(X+22, Y+4,0);

	ili9325_WritePixel(X+9, Y+5,0);
	for(int i=10; i<=21; i++)
		ili9325_WritePixel(X+i, Y+5,65535);
	ili9325_WritePixel(X+22, Y+5,0);

	ili9325_WritePixel(X+3, Y+6,0xF945);
	ili9325_WritePixel(X+4, Y+6,0xF945);
	ili9325_WritePixel(X+9, Y+6,65535);
	for(int i=10; i<=14; i++)
		ili9325_WritePixel(X+i, Y+6,65535);
	ili9325_WritePixel(X+15, Y+6,65535);
	ili9325_WritePixel(X+16, Y+6,65535);
	for(int i=17; i<=21; i++)
		ili9325_WritePixel(X+i, Y+6,65535);
	ili9325_WritePixel(X+22, Y+6,65535);

	ili9325_WritePixel(X+3, Y+7,0xF945);
	ili9325_WritePixel(X+4, Y+7,0xF945);
	ili9325_WritePixel(X+9, Y+7,65535);
	for(int i=10; i<=14; i++)
		ili9325_WritePixel(X+i, Y+7,65535);
	ili9325_WritePixel(X+15, Y+7,65535);
	ili9325_WritePixel(X+16, Y+7,65535);
	for(int i=17; i<=21; i++)
		ili9325_WritePixel(X+i, Y+7,65535);
	ili9325_WritePixel(X+22, Y+7,65535);

	ili9325_WritePixel(X+3, Y+8,0xF945);
	ili9325_WritePixel(X+4, Y+8,0xF945);
	ili9325_WritePixel(X+6, Y+8,0x71A3);
	ili9325_WritePixel(X+7, Y+8,0x71A3);
	ili9325_WritePixel(X+8, Y+8,0x71A3);
	ili9325_WritePixel(X+9, Y+8,0);
	for(int i=10; i<=21; i++)
		ili9325_WritePixel(X+i, Y+8,65535);
	ili9325_WritePixel(X+22, Y+8,0);
	ili9325_WritePixel(X+23, Y+8,0x71A3);
	ili9325_WritePixel(X+24, Y+8,0x71A3);
	
	ili9325_WritePixel(X+3, Y+9,0xF945);
	ili9325_WritePixel(X+4, Y+9,0xF945);
	ili9325_WritePixel(X+5, Y+9,0x71A3);
	ili9325_WritePixel(X+6, Y+9,0x71A3);
	ili9325_WritePixel(X+7, Y+9,0x71A3);
	ili9325_WritePixel(X+8, Y+9,0x71A3);
	ili9325_WritePixel(X+9, Y+9,0);
	for(int i=10; i<=14; i++)
		ili9325_WritePixel(X+i, Y+9,65535);
	ili9325_WritePixel(X+15, Y+9,0);
	ili9325_WritePixel(X+16, Y+9,0);
	for(int i=17; i<=21; i++)
		ili9325_WritePixel(X+i, Y+9,65535);
	ili9325_WritePixel(X+22, Y+9,0);
	ili9325_WritePixel(X+23, Y+9,0xF945);
	ili9325_WritePixel(X+24, Y+9,0xF945);
	ili9325_WritePixel(X+25, Y+9,0x71A3);

	ili9325_WritePixel(X+3, Y+10,0xF945);
	ili9325_WritePixel(X+4, Y+10,0xF945);
	ili9325_WritePixel(X+5, Y+10,0x71A3);
	ili9325_WritePixel(X+9, Y+10,0);
	for(int i=10; i<=14; i++)
		ili9325_WritePixel(X+i, Y+10,65535);
	ili9325_WritePixel(X+15, Y+10,0);
	ili9325_WritePixel(X+16, Y+10,0);
	for(int i=17; i<=21; i++)
		ili9325_WritePixel(X+i, Y+10,65535);
	ili9325_WritePixel(X+22, Y+10,0);
	ili9325_WritePixel(X+23, Y+10,0xF945);
	ili9325_WritePixel(X+24, Y+10,0xF945);
	ili9325_WritePixel(X+25, Y+10,0x71A3);
	ili9325_WritePixel(X+26, Y+10,0x71A3);

	ili9325_WritePixel(X+2, Y+11,0x71A3);
	ili9325_WritePixel(X+3, Y+11,0xF945);
	ili9325_WritePixel(X+4, Y+11,0xF945);
	ili9325_WritePixel(X+10, Y+10,0);
	for(int i=11; i<=21; i++)
		ili9325_WritePixel(X+i, Y+10,65535);
	ili9325_WritePixel(X+22, Y+11,0xF945);
	ili9325_WritePixel(X+23, Y+11,0xF945);
	ili9325_WritePixel(X+24, Y+11,0xF945);
	ili9325_WritePixel(X+25, Y+11,0x71A3);
	ili9325_WritePixel(X+26, Y+11,0x71A3);
	ili9325_WritePixel(X+27, Y+11,0x71A3);

	ili9325_WritePixel(X+3, Y+12,0xF945);
	ili9325_WritePixel(X+4, Y+12,0xF945);
	ili9325_WritePixel(X+11, Y+12,0);
	for(int i=12; i<=20; i++)
		ili9325_WritePixel(X+i, Y+10,65535);
	ili9325_WritePixel(X+21, Y+12,0xF945);
	ili9325_WritePixel(X+22, Y+12,0xF945);
	ili9325_WritePixel(X+23, Y+12,0xF945);
	ili9325_WritePixel(X+27, Y+12,0x71A3);

	ili9325_WritePixel(X+3, Y+13,0xF945);
	ili9325_WritePixel(X+4, Y+13,0xF945);
	for(int i=11; i<=22; i++)
		ili9325_WritePixel(X+i, Y+13,0xF945);

	ili9325_WritePixel(X+3, Y+14,0xF945);
	ili9325_WritePixel(X+4, Y+14,0xF945);
	for(int i=11; i<=21; i++)
		ili9325_WritePixel(X+i, Y+13,0xF945);

	ili9325_WritePixel(X+3, Y+15,0xF945);
	ili9325_WritePixel(X+4, Y+15,0xF945);
	ili9325_WritePixel(X+11, Y+15,0);
	for(int i=12; i<=19; i++)
		ili9325_WritePixel(X+i, Y+15,65535);
	ili9325_WritePixel(X+20, Y+15,0);

	ili9325_WritePixel(X+3, Y+16,0xF945);
	ili9325_WritePixel(X+4, Y+16,0xF945);
	ili9325_WritePixel(X+11, Y+16,0);
	ili9325_WritePixel(X+12, Y+16,65535);
	ili9325_WritePixel(X+13, Y+16,65535);
	ili9325_WritePixel(X+14, Y+16,65535);
	ili9325_WritePixel(X+15, Y+16,0);
	ili9325_WritePixel(X+16, Y+16,0);
	ili9325_WritePixel(X+17, Y+16,65535);
	ili9325_WritePixel(X+18, Y+16,65535);
	ili9325_WritePixel(X+19, Y+16,65535);
	ili9325_WritePixel(X+20, Y+16,0);

	ili9325_WritePixel(X+1, Y+17,0xF945);
	ili9325_WritePixel(X+2, Y+17,0xF945);
	ili9325_WritePixel(X+3, Y+17,0xF945);
	ili9325_WritePixel(X+4, Y+17,0xF945);
	ili9325_WritePixel(X+10, Y+17,0);
	ili9325_WritePixel(X+11, Y+17,65535);
	ili9325_WritePixel(X+12, Y+17,65535);
	ili9325_WritePixel(X+13, Y+17,65535);
	ili9325_WritePixel(X+14, Y+17,0);
	ili9325_WritePixel(X+15, Y+17,65535);
	ili9325_WritePixel(X+16, Y+17,65535);
	ili9325_WritePixel(X+17, Y+17,0);
	ili9325_WritePixel(X+18, Y+17,65535);
	ili9325_WritePixel(X+19, Y+17,65535);
	ili9325_WritePixel(X+20, Y+17,65535);
	ili9325_WritePixel(X+21, Y+17,0);

	ili9325_WritePixel(X+2, Y+18,0xF945);
	ili9325_WritePixel(X+3, Y+18,0xF945);
	ili9325_WritePixel(X+10, Y+18,0);
	ili9325_WritePixel(X+11, Y+18,65535);
	ili9325_WritePixel(X+12, Y+18,65535);
	ili9325_WritePixel(X+13, Y+18,0xFCA0);
	ili9325_WritePixel(X+14, Y+18,0xFCA0);
	ili9325_WritePixel(X+15, Y+18,0xFCA0);
	for(int i=16; i<=20; i++)
		ili9325_WritePixel(X+i, Y+18,65535);
	ili9325_WritePixel(X+21, Y+18,0);

	ili9325_WritePixel(X+10, Y+19,0);
	ili9325_WritePixel(X+11, Y+19,65535);
	ili9325_WritePixel(X+12, Y+19,65535);
	ili9325_WritePixel(X+13, Y+19,65535);
	ili9325_WritePixel(X+14, Y+19,65535);
	ili9325_WritePixel(X+15, Y+19,0xFCA0);
	for(int i=16; i<=20; i++)
		ili9325_WritePixel(X+i, Y+19,65535);
	ili9325_WritePixel(X+21, Y+19,0);

	ili9325_WritePixel(X+10, Y+20,0);
	ili9325_WritePixel(X+11, Y+20,65535);
	ili9325_WritePixel(X+12, Y+20,65535);
	ili9325_WritePixel(X+13, Y+20,0);
	ili9325_WritePixel(X+14, Y+20,0);
	ili9325_WritePixel(X+15, Y+20,65535);
	ili9325_WritePixel(X+16, Y+20,65535);
	ili9325_WritePixel(X+17, Y+20,0);
	ili9325_WritePixel(X+18, Y+20,0);
	ili9325_WritePixel(X+19, Y+20,65535);
	ili9325_WritePixel(X+20, Y+20,65535);
	ili9325_WritePixel(X+21, Y+20,0);

	ili9325_WritePixel(X+11, Y+21,0);
	ili9325_WritePixel(X+12, Y+21,65535);
	ili9325_WritePixel(X+13, Y+21,65535);
	ili9325_WritePixel(X+14, Y+21,0);
	ili9325_WritePixel(X+15, Y+21,65535);
	ili9325_WritePixel(X+16, Y+21,65535);
	ili9325_WritePixel(X+17, Y+21,0);
	ili9325_WritePixel(X+18, Y+21,65535);
	ili9325_WritePixel(X+19, Y+21,65535);
	ili9325_WritePixel(X+20, Y+21,0);

	ili9325_WritePixel(X+11, Y+22,0);
	for(int i=12; i<=19; i++)
		ili9325_WritePixel(X+i, Y+22,65535);
	ili9325_WritePixel(X+20, Y+22,0);

	ili9325_WritePixel(X+12, Y+23,0);
	ili9325_WritePixel(X+13, Y+23,0);
	for(int i=14; i<=17; i++)
		ili9325_WritePixel(X+i, Y+23,65535);
	ili9325_WritePixel(X+18, Y+23,0);
	ili9325_WritePixel(X+19, Y+23,0);

	ili9325_WritePixel(X+10, Y+24,0);
	ili9325_WritePixel(X+11, Y+24,0);
	for(int i=12; i<=19; i++)
		ili9325_WritePixel(X+i, Y+24,0xF945);
	ili9325_WritePixel(X+20, Y+24,0);
	ili9325_WritePixel(X+21, Y+24,0);

	for(int i=12; i<=19; i++)
		ili9325_WritePixel(X+i, Y+25,0xF945);

	for(int i=12; i<=19; i++)
		ili9325_WritePixel(X+i, Y+26,0);

		for(int i=12; i<=19; i++)
		ili9325_WritePixel(X+i, Y+27,0);
}
//--- SetRock --- DONE
void SetRock(uint16_t X, uint16_t Y)
{
	for(int i=7; i<=19; i++)
		ili9325_WritePixel(X+i, Y,0);

	ili9325_WritePixel(X+6, Y+1,0);
	ili9325_WritePixel(X+7, Y+1,0xA4B2);
	ili9325_WritePixel(X+8, Y+1,0xA4B2);
	ili9325_WritePixel(X+9, Y+1,0xA4B2);
	ili9325_WritePixel(X+10, Y+1,0xD618);
	ili9325_WritePixel(X+11, Y+1,0xD618);
	ili9325_WritePixel(X+12, Y+1,0xD618);
	ili9325_WritePixel(X+13, Y+1,0xD618);
	ili9325_WritePixel(X+14, Y+1,0xD618);
	ili9325_WritePixel(X+15, Y+1,0xD618);
	ili9325_WritePixel(X+16, Y+1,0x4A08);
	ili9325_WritePixel(X+17, Y+1,0x4A08);
	ili9325_WritePixel(X+18, Y+1,0x4A08);
	ili9325_WritePixel(X+19, Y+1,0x4A08);
	ili9325_WritePixel(X+20, Y+1,0);
	ili9325_WritePixel(X+21, Y+1,0);

	ili9325_WritePixel(X+2, Y+2,0);
	ili9325_WritePixel(X+3, Y+2,0);
	ili9325_WritePixel(X+4, Y+2,0);
	ili9325_WritePixel(X+5, Y+2,0);
	ili9325_WritePixel(X+6, Y+2,0x4A08);
	ili9325_WritePixel(X+7, Y+2,0xA4B2);
	ili9325_WritePixel(X+8, Y+2,0xD618);
	ili9325_WritePixel(X+9, Y+2,0xD618);
	ili9325_WritePixel(X+10, Y+2,0xD618);
	ili9325_WritePixel(X+11, Y+2,0xA4B2);
	ili9325_WritePixel(X+12, Y+2,0xA4B2);
	ili9325_WritePixel(X+13, Y+2,0xD618);
	ili9325_WritePixel(X+14, Y+2,0xD618);
	ili9325_WritePixel(X+15, Y+2,0xD618);
	ili9325_WritePixel(X+16, Y+2,0xD618);
	ili9325_WritePixel(X+17, Y+2,0x4A08);
	ili9325_WritePixel(X+18, Y+2,0x4A08);
	ili9325_WritePixel(X+19, Y+2,0x4A08);
	ili9325_WritePixel(X+20, Y+2,0x4A08);
	ili9325_WritePixel(X+21, Y+2,0x4A08);
	ili9325_WritePixel(X+22, Y+2,0);

	ili9325_WritePixel(X+1, Y+3,0);
	ili9325_WritePixel(X+2, Y+3,0x4A08);
	ili9325_WritePixel(X+3, Y+3,0x4A08);
	ili9325_WritePixel(X+4, Y+3,0x4A08);
	ili9325_WritePixel(X+5, Y+3,0xD618);
	ili9325_WritePixel(X+6, Y+3,0x4A08);
	ili9325_WritePixel(X+7, Y+3,0xD618);
	ili9325_WritePixel(X+8, Y+3,0xD618);
	ili9325_WritePixel(X+9, Y+3,0xA4B2);
	ili9325_WritePixel(X+10, Y+3,0xA4B2);
	ili9325_WritePixel(X+11, Y+3,0xD618);
	ili9325_WritePixel(X+12, Y+3,0xA4B2);
	ili9325_WritePixel(X+13, Y+3,0xA4B2);
	ili9325_WritePixel(X+14, Y+3,0xA4B2);
	ili9325_WritePixel(X+15, Y+3,0xA4B2);
	ili9325_WritePixel(X+16, Y+3,0xA4B2);
	ili9325_WritePixel(X+17, Y+3,0xA4B2);
	ili9325_WritePixel(X+18, Y+3,0xD618);
	ili9325_WritePixel(X+19, Y+3,0xD618);
	ili9325_WritePixel(X+20, Y+3,0x4A08);
	ili9325_WritePixel(X+21, Y+3,0x4A08);
	ili9325_WritePixel(X+22, Y+3,0x4A08);
	ili9325_WritePixel(X+23, Y+3,0);

	ili9325_WritePixel(X+1, Y+4,0);
	ili9325_WritePixel(X+2, Y+4,0x4A08);
	ili9325_WritePixel(X+3, Y+4,0x4A08);
	ili9325_WritePixel(X+4, Y+4,0xD618);
	ili9325_WritePixel(X+5, Y+4,0xD618);
	ili9325_WritePixel(X+6, Y+4,0x4A08);
	for(int i=7; i<=21; i++)
		ili9325_WritePixel(X+i, Y+4,0xD618);
	ili9325_WritePixel(X+22, Y+4,0x4A08);
	ili9325_WritePixel(X+23, Y+4,0x4A08);
	ili9325_WritePixel(X+24, Y+4,0);

	ili9325_WritePixel(X+1, Y+5,0);
	ili9325_WritePixel(X+2, Y+5,0x4A08);
	ili9325_WritePixel(X+3, Y+5,0xD618);
	ili9325_WritePixel(X+4, Y+5,0xD618);
	ili9325_WritePixel(X+5, Y+5,0x4A08);
	ili9325_WritePixel(X+6, Y+5,0x4A08);
	ili9325_WritePixel(X+7, Y+5,0xA4B2);
	for(int i=8; i<=21; i++)
		ili9325_WritePixel(X+i, Y+5,0xD618);
	ili9325_WritePixel(X+9, Y+5,0x4A08);
	ili9325_WritePixel(X+10, Y+5,0x4A08);
	ili9325_WritePixel(X+11, Y+5,0);

	ili9325_WritePixel(X+1, Y+6,0);
	ili9325_WritePixel(X+2, Y+6,0xD618);
	ili9325_WritePixel(X+3, Y+6,0xD618);
	ili9325_WritePixel(X+4, Y+6,0xD618);
	ili9325_WritePixel(X+5, Y+6,0xD618);
	ili9325_WritePixel(X+6, Y+6,0x4A08);
	ili9325_WritePixel(X+7, Y+6,0xA4B2);
	ili9325_WritePixel(X+8, Y+6,0xA4B2);
	ili9325_WritePixel(X+9, Y+6,0xA4B2);
	ili9325_WritePixel(X+10, Y+6,0xA4B2);
	for(int i=11; i<=21; i++)
		ili9325_WritePixel(X+i, Y+6,0xD618);
	ili9325_WritePixel(X+22, Y+6,0xA4B2);
	ili9325_WritePixel(X+23, Y+6,0);

	ili9325_WritePixel(X+1, Y+7,0);
	ili9325_WritePixel(X+2, Y+7,0xD618);
	ili9325_WritePixel(X+3, Y+7,0xD618);
	ili9325_WritePixel(X+4, Y+7,0xD618);
	ili9325_WritePixel(X+5, Y+7,0xD618);
	ili9325_WritePixel(X+6, Y+7,0x4A08);
	ili9325_WritePixel(X+7, Y+7,0xA4B2);
	ili9325_WritePixel(X+8, Y+7,0xD618);
	ili9325_WritePixel(X+9, Y+7,0xD618);
	ili9325_WritePixel(X+10, Y+7,0xD618);
	ili9325_WritePixel(X+11, Y+7,0xA4B2);
	ili9325_WritePixel(X+12, Y+7,0xA4B2);
	ili9325_WritePixel(X+13, Y+7,0xA4B2);
	ili9325_WritePixel(X+14, Y+7,0xA4B2);
	for(int i=15; i<=21; i++)
		ili9325_WritePixel(X+i, Y+7,0xD618);
	ili9325_WritePixel(X+22, Y+7,0xA4B2);
	ili9325_WritePixel(X+23, Y+7,0);

	ili9325_WritePixel(X+1, Y+8,0);
	ili9325_WritePixel(X+2, Y+8,0xA4B2);
	ili9325_WritePixel(X+3, Y+8,0xD618);
	ili9325_WritePixel(X+4, Y+8,0xD618);
	ili9325_WritePixel(X+5, Y+8,0xD618);
	ili9325_WritePixel(X+6, Y+8,0xD618);
	ili9325_WritePixel(X+7, Y+8,0x4A08);
	for(int i=8; i<=14; i++)
		ili9325_WritePixel(X+i, Y+8,0xD618);
	ili9325_WritePixel(X+15, Y+8,0xA4B2);
	for(int i=16; i<=21; i++)
		ili9325_WritePixel(X+i, Y+8,0xD618);
	ili9325_WritePixel(X+22, Y+8,0xA4B2);
	ili9325_WritePixel(X+23, Y+8,0);

	ili9325_WritePixel(X+2, Y+9,0);
	ili9325_WritePixel(X+3, Y+9,0xA4B2);
	ili9325_WritePixel(X+4, Y+9,0xD618);
	ili9325_WritePixel(X+5, Y+9,0xD618);
	ili9325_WritePixel(X+6, Y+9,0xD618);
	ili9325_WritePixel(X+7, Y+9,0x4A08);
	ili9325_WritePixel(X+8, Y+9,0xA4B2);
	for(int i=9; i<=14; i++)
		ili9325_WritePixel(X+i, Y+9,0xD618);
	ili9325_WritePixel(X+15, Y+9,0xA4B2);
	ili9325_WritePixel(X+16, Y+9,0xD618);
	ili9325_WritePixel(X+17, Y+9,0xD618);
	ili9325_WritePixel(X+18, Y+9,0xD618);
	ili9325_WritePixel(X+19, Y+9,0x4A08);
	ili9325_WritePixel(X+20, Y+9,0xA4B2);
	ili9325_WritePixel(X+21, Y+9,0xD618);
	ili9325_WritePixel(X+22, Y+9,0);

	ili9325_WritePixel(X+2, Y+10,0);
	ili9325_WritePixel(X+3, Y+10,0xA4B2);
	ili9325_WritePixel(X+4, Y+10,0xD618);
	ili9325_WritePixel(X+5, Y+10,0xD618);
	ili9325_WritePixel(X+6, Y+10,0xD618);
	ili9325_WritePixel(X+7, Y+10,0x4A08);
	for(int i=8; i<=12; i++)
		ili9325_WritePixel(X+i, Y+10,0xA4B2);
	ili9325_WritePixel(X+13, Y+10,0xD618);
	ili9325_WritePixel(X+14, Y+10,0xD618);
	ili9325_WritePixel(X+15, Y+10,0xA4B2);
	ili9325_WritePixel(X+16, Y+10,0xD618);
	ili9325_WritePixel(X+17, Y+10,0xD618);
	ili9325_WritePixel(X+18, Y+10,0xD618);
	ili9325_WritePixel(X+19, Y+10,0xD618);
	ili9325_WritePixel(X+20, Y+10,0xA4B2);
	ili9325_WritePixel(X+21, Y+10,0x4A08);
	ili9325_WritePixel(X+22, Y+10,0);

	ili9325_WritePixel(X+2, Y+11,0);
	ili9325_WritePixel(X+3, Y+11,0x4A08);
	ili9325_WritePixel(X+4, Y+11,0xD618);
	ili9325_WritePixel(X+5, Y+11,0xD618);
	ili9325_WritePixel(X+6, Y+11,0xD618);
	ili9325_WritePixel(X+7, Y+11,0x4A08);
	ili9325_WritePixel(X+8, Y+11,0xA4B2);
	ili9325_WritePixel(X+9, Y+11,0xD618);
	ili9325_WritePixel(X+10, Y+11,0xD618);
	ili9325_WritePixel(X+11, Y+11,0xA4B2);
	for(int i=12; i<=20; i++)
		ili9325_WritePixel(X+i, Y+11,0xD618);
	ili9325_WritePixel(X+21, Y+11,0x4A08);
	ili9325_WritePixel(X+22, Y+11,0);

	ili9325_WritePixel(X+3, Y+12,0);
	ili9325_WritePixel(X+4, Y+12,0xD618);
	ili9325_WritePixel(X+5, Y+12,0xD618);
	ili9325_WritePixel(X+6, Y+12,0xA4B2);
	ili9325_WritePixel(X+7, Y+12,0x4A08);
	ili9325_WritePixel(X+8, Y+12,0xA4B2);
	ili9325_WritePixel(X+9, Y+12,0xD618);
	ili9325_WritePixel(X+10, Y+12,0xD618);
	ili9325_WritePixel(X+11, Y+12,0xD618);
	ili9325_WritePixel(X+12, Y+12,0xA4B2);
	ili9325_WritePixel(X+13, Y+12,0xA4B2);
	for(int i=14; i<=20; i++)
		ili9325_WritePixel(X+i, Y+12,0xD618);
	ili9325_WritePixel(X+21, Y+12,0x4A08);
	ili9325_WritePixel(X+22, Y+12,0);

	ili9325_WritePixel(X+3, Y+13,0);
	ili9325_WritePixel(X+4, Y+13,0xD618);
	ili9325_WritePixel(X+5, Y+13,0xD618);
	ili9325_WritePixel(X+6, Y+13,0xA4B2);
	ili9325_WritePixel(X+7, Y+13,0x4A08);
	for(int i=8; i<=14; i++)
		ili9325_WritePixel(X+i, Y+13,0xD618);
	ili9325_WritePixel(X+15, Y+13,0xA4B2);
	for(int i=16; i<=20; i++)
		ili9325_WritePixel(X+i, Y+13,0xD618);
	ili9325_WritePixel(X+21, Y+13,0);

	ili9325_WritePixel(X+3, Y+14,0);
	ili9325_WritePixel(X+4, Y+14,0xD618);
	ili9325_WritePixel(X+5, Y+14,0xD618);
	ili9325_WritePixel(X+6, Y+14,0xA4B2);
	ili9325_WritePixel(X+7, Y+14,0xA4B2);
	for(int i=8; i<=14; i++)
		ili9325_WritePixel(X+i, Y+14,0xD618);
	ili9325_WritePixel(X+15, Y+14,0xA4B2);
	for(int i=16; i<=19; i++)
		ili9325_WritePixel(X+i, Y+14,0xD618);
	ili9325_WritePixel(X+20, Y+14,0x4A08);
	ili9325_WritePixel(X+21, Y+14,0);

	ili9325_WritePixel(X+4, Y+15,0);
	ili9325_WritePixel(X+5, Y+15,0xD618);
	ili9325_WritePixel(X+6, Y+15,0xD618);
	ili9325_WritePixel(X+7, Y+15,0xA4B2);
	ili9325_WritePixel(X+8, Y+15,0xA4B2);
	for(int i=9; i<=14; i++)
		ili9325_WritePixel(X+i, Y+15,0xD618);
	ili9325_WritePixel(X+15, Y+15,0xA4B2);
	ili9325_WritePixel(X+16, Y+15,0xD618);
	ili9325_WritePixel(X+17, Y+15,0xD618);
	ili9325_WritePixel(X+18, Y+15,0xD618);
	ili9325_WritePixel(X+19, Y+15,0xD618);
	ili9325_WritePixel(X+20, Y+15,0xA4B2);
	ili9325_WritePixel(X+21, Y+15,0);

	ili9325_WritePixel(X+4, Y+16,0);
	ili9325_WritePixel(X+5, Y+16,0x4A08);
	ili9325_WritePixel(X+6, Y+16,0xD618);
	ili9325_WritePixel(X+7, Y+16,0xD618);
	ili9325_WritePixel(X+8, Y+16,0xA4B2);
	for(int i=9; i<=14; i++)
		ili9325_WritePixel(X+i, Y+16,0xD618);
	ili9325_WritePixel(X+15, Y+16,0xA4B2);
	ili9325_WritePixel(X+16, Y+16,0xA4B2);
	ili9325_WritePixel(X+17, Y+16,0xD618);
	ili9325_WritePixel(X+18, Y+16,0xD618);
	ili9325_WritePixel(X+19, Y+16,0x4A08);
	ili9325_WritePixel(X+20, Y+16,0x4A08);
	ili9325_WritePixel(X+21, Y+16,0);

	ili9325_WritePixel(X+5, Y+17,0);
	ili9325_WritePixel(X+6, Y+17,0x4A08);
	for(int i=7; i<=11; i++)
		ili9325_WritePixel(X+i, Y+17,0xD618);
	ili9325_WritePixel(X+12, Y+17,0xA4B2);
	ili9325_WritePixel(X+13, Y+17,0xD618);
	ili9325_WritePixel(X+14, Y+17,0xD618);
	ili9325_WritePixel(X+15, Y+17,0x4A08);
	ili9325_WritePixel(X+16, Y+17,0xA4B2);
	ili9325_WritePixel(X+17, Y+17,0xD618);
	ili9325_WritePixel(X+18, Y+17,0x4A08);
	ili9325_WritePixel(X+19, Y+17,0x4A08);
	ili9325_WritePixel(X+20, Y+17,0);

	ili9325_WritePixel(X+6, Y+18,0);
	ili9325_WritePixel(X+7, Y+18,0);
	ili9325_WritePixel(X+8, Y+18,0);
	ili9325_WritePixel(X+9, Y+18,0x4A08);
	for(int i=10; i<=14; i++)
		ili9325_WritePixel(X+i, Y+18,0xD618);
	ili9325_WritePixel(X+15, Y+18,0xA4B2);
	ili9325_WritePixel(X+16, Y+18,0xD618);
	ili9325_WritePixel(X+17, Y+18,0xD618);
	ili9325_WritePixel(X+18, Y+18,0xD618);
	ili9325_WritePixel(X+19, Y+18,0x4A08);
	ili9325_WritePixel(X+20, Y+18,0);

	ili9325_WritePixel(X+9, Y+19,0);
	ili9325_WritePixel(X+10, Y+19,0x4A08);
	ili9325_WritePixel(X+11, Y+19,0xD618);
	ili9325_WritePixel(X+12, Y+19,0xD618);
	ili9325_WritePixel(X+13, Y+19,0xD618);
	ili9325_WritePixel(X+14, Y+19,0xA4B2);
	ili9325_WritePixel(X+15, Y+19,0xA4B2);
	ili9325_WritePixel(X+16, Y+19,0xD618);
	ili9325_WritePixel(X+17, Y+19,0xD618);
	ili9325_WritePixel(X+18, Y+19,0xD618);
	ili9325_WritePixel(X+19, Y+19,0);

	ili9325_WritePixel(X+10, Y+20,0);
	for(int i=11; i<=15; i++)
		ili9325_WritePixel(X+i, Y+20,0xD618);
	ili9325_WritePixel(X+16, Y+20,0x4A08);
	ili9325_WritePixel(X+17, Y+20,0);
	ili9325_WritePixel(X+18, Y+20,0);

	ili9325_WritePixel(X+11, Y+21,0);
	ili9325_WritePixel(X+12, Y+21,0xD618);
	ili9325_WritePixel(X+13, Y+21,0xD618);
	ili9325_WritePixel(X+14, Y+21,0xD618);
	ili9325_WritePixel(X+15, Y+21,0x4A08);
	ili9325_WritePixel(X+16, Y+21,0);

	for(int i=12; i<=15; i++)
		ili9325_WritePixel(X+i, Y+22,0);
}
//--- SetBowman --- DONE
void SetBowman(uint16_t X, uint16_t Y)
{
	ili9325_WritePixel(X+1, Y+1, 0);
	ili9325_WritePixel(X+2, Y+1, 17639);
	ili9325_WritePixel(X+3, Y+1, 17639);
	ili9325_WritePixel(X+4, Y+1, 17639);
	ili9325_WritePixel(X+5, Y+1, 17639);
	ili9325_WritePixel(X+6, Y+1, 17639);	//3008 ciemny zielony
	ili9325_WritePixel(X+7, Y+1, 0);
	ili9325_WritePixel(X+15, Y+1, 0);
	ili9325_WritePixel(X+16, Y+1, 17639);
	ili9325_WritePixel(X+17, Y+1, 17639);
	ili9325_WritePixel(X+18, Y+1, 17639);
	ili9325_WritePixel(X+19, Y+1, 17639);
	ili9325_WritePixel(X+20, Y+1, 0);

	ili9325_WritePixel(X+2, Y+2, 0);
	ili9325_WritePixel(X+3, Y+2, 17639);
	ili9325_WritePixel(X+4, Y+2, 17639);
	ili9325_WritePixel(X+5, Y+2, 17639);
	ili9325_WritePixel(X+6, Y+2, 17639);
	ili9325_WritePixel(X+7, Y+2, 3008);
	ili9325_WritePixel(X+8, Y+2, 0);
	ili9325_WritePixel(X+15, Y+2, 0);
	ili9325_WritePixel(X+16, Y+2, 3008);
	ili9325_WritePixel(X+17, Y+2, 0);
	ili9325_WritePixel(X+18, Y+2, 0);
	ili9325_WritePixel(X+19, Y+2, 0);
	ili9325_WritePixel(X+20, Y+2, 0);

	ili9325_WritePixel(X+3, Y+3, 0);
	ili9325_WritePixel(X+4, Y+3, 17639);
	ili9325_WritePixel(X+5, Y+3, 17639);
	ili9325_WritePixel(X+6, Y+3, 17639);
	ili9325_WritePixel(X+7, Y+3, 17639);
	ili9325_WritePixel(X+8, Y+3, 17639);
	ili9325_WritePixel(X+9, Y+3, 0);
	ili9325_WritePixel(X+14, Y+3, 0);
	ili9325_WritePixel(X+15, Y+3, 3008);
	ili9325_WritePixel(X+16, Y+3, 0);
	ili9325_WritePixel(X+17, Y+3, 50712);
	ili9325_WritePixel(X+18, Y+3, 50712);
	ili9325_WritePixel(X+19, Y+3, 27144);
	ili9325_WritePixel(X+20, Y+3, 27144);
	ili9325_WritePixel(X+21, Y+3, 0);

	ili9325_WritePixel(X+4, Y+4, 0);
	ili9325_WritePixel(X+5, Y+4, 17639);
	ili9325_WritePixel(X+6, Y+4, 17639);
	ili9325_WritePixel(X+7, Y+4, 17639);
	ili9325_WritePixel(X+8, Y+4, 17639);
	ili9325_WritePixel(X+8, Y+4, 3008);
	ili9325_WritePixel(X+9, Y+4, 0);
	ili9325_WritePixel(X+10, Y+4, 0);
	ili9325_WritePixel(X+11, Y+4, 0);
	ili9325_WritePixel(X+12, Y+4, 0);
	ili9325_WritePixel(X+13, Y+4, 0);
	ili9325_WritePixel(X+14, Y+4, 0);
	ili9325_WritePixel(X+15, Y+4, 50712);
	ili9325_WritePixel(X+16, Y+4, 50712);
	ili9325_WritePixel(X+17, Y+4, 50712);
	ili9325_WritePixel(X+18, Y+4, 27144);
	ili9325_WritePixel(X+19, Y+4, 27144);
	ili9325_WritePixel(X+20, Y+4, 27144);
	ili9325_WritePixel(X+21, Y+4, 0);

	ili9325_WritePixel(X+5, Y+5, 0);
	ili9325_WritePixel(X+6, Y+5, 17639);
	ili9325_WritePixel(X+7, Y+5, 17639);
	ili9325_WritePixel(X+8, Y+5, 17639);
	ili9325_WritePixel(X+9, Y+5, 17639);
	ili9325_WritePixel(X+10, Y+5, 17639);
	ili9325_WritePixel(X+11, Y+5, 17639);
	ili9325_WritePixel(X+12, Y+5, 17639);
	ili9325_WritePixel(X+13, Y+5, 3008);
	ili9325_WritePixel(X+14, Y+5, 0);
	ili9325_WritePixel(X+15, Y+5, 50712);
	ili9325_WritePixel(X+16, Y+5, 50712);
	ili9325_WritePixel(X+17, Y+5, 0);
	ili9325_WritePixel(X+18, Y+5, 0);
	ili9325_WritePixel(X+19, Y+5, 0);
	ili9325_WritePixel(X+20, Y+5, 27144);
	ili9325_WritePixel(X+21, Y+5, 27144);
	ili9325_WritePixel(X+22, Y+5, 27144);
	ili9325_WritePixel(X+23, Y+5, 0);

	ili9325_WritePixel(X+6, Y+6, 0);
	ili9325_WritePixel(X+7, Y+6, 17639);
	ili9325_WritePixel(X+8, Y+6, 17639);
	ili9325_WritePixel(X+9, Y+6, 17639);
	ili9325_WritePixel(X+10, Y+6, 17639);
	ili9325_WritePixel(X+11, Y+6, 17639);
	ili9325_WritePixel(X+12, Y+6, 3008);
	ili9325_WritePixel(X+13, Y+6, 0);
	ili9325_WritePixel(X+14, Y+6, 50712);
	ili9325_WritePixel(X+15, Y+6, 50712);
	ili9325_WritePixel(X+16, Y+6, 0);
	ili9325_WritePixel(X+17, Y+6, 3008);
	ili9325_WritePixel(X+18, Y+6, 0);
	ili9325_WritePixel(X+20, Y+6, 0);
	ili9325_WritePixel(X+21, Y+6, 27144);
	ili9325_WritePixel(X+22, Y+6, 27144);
	ili9325_WritePixel(X+23, Y+6, 0);

	ili9325_WritePixel(X+6, Y+7, 0);
	ili9325_WritePixel(X+7, Y+7, 3008);
	ili9325_WritePixel(X+8, Y+7, 17639);
	ili9325_WritePixel(X+9, Y+7, 17639);
	ili9325_WritePixel(X+10, Y+7, 17639);
	ili9325_WritePixel(X+11, Y+7, 3008);
	ili9325_WritePixel(X+12, Y+7, 0);
	ili9325_WritePixel(X+13, Y+7, 50712);
	ili9325_WritePixel(X+14, Y+7, 50712);
	ili9325_WritePixel(X+15, Y+7, 0);
	ili9325_WritePixel(X+16, Y+7, 3008);
	ili9325_WritePixel(X+17, Y+7, 0);
	ili9325_WritePixel(X+21, Y+7, 0);
	ili9325_WritePixel(X+22, Y+7, 27144);
	ili9325_WritePixel(X+23, Y+7, 27144);
	ili9325_WritePixel(X+24, Y+7, 0);

	ili9325_WritePixel(X+6, Y+8, 0);
	ili9325_WritePixel(X+7, Y+8, 3008);
	ili9325_WritePixel(X+8, Y+8, 17639);
	ili9325_WritePixel(X+9, Y+8, 17639);
	ili9325_WritePixel(X+10, Y+8, 17639);
	ili9325_WritePixel(X+11, Y+8, 0);
	ili9325_WritePixel(X+12, Y+8, 50712);
	ili9325_WritePixel(X+13, Y+8, 50712);
	ili9325_WritePixel(X+14, Y+8, 0);
	ili9325_WritePixel(X+15, Y+8, 17639);
	ili9325_WritePixel(X+16, Y+8, 0);
	ili9325_WritePixel(X+21, Y+8, 0);
	ili9325_WritePixel(X+22, Y+8, 27144);
	ili9325_WritePixel(X+23, Y+8, 27144);
	ili9325_WritePixel(X+24, Y+8, 0);

	ili9325_WritePixel(X+6, Y+9, 0);
	ili9325_WritePixel(X+7, Y+9, 3008);
	ili9325_WritePixel(X+8, Y+9, 17639);
	ili9325_WritePixel(X+9, Y+9, 17639);
	ili9325_WritePixel(X+10, Y+9, 0);
	ili9325_WritePixel(X+11, Y+9, 50712);
	ili9325_WritePixel(X+12, Y+9, 50712);
	ili9325_WritePixel(X+13, Y+9, 0);
	ili9325_WritePixel(X+14, Y+9, 17639);
	ili9325_WritePixel(X+15, Y+9, 17639);
	ili9325_WritePixel(X+16, Y+9, 0);
	ili9325_WritePixel(X+21, Y+9, 0);
	ili9325_WritePixel(X+22, Y+9, 27144);
	ili9325_WritePixel(X+23, Y+9, 27144);
	ili9325_WritePixel(X+24, Y+9, 0);

	ili9325_WritePixel(X+6, Y+10, 0);
	ili9325_WritePixel(X+7, Y+10, 3008);
	ili9325_WritePixel(X+8, Y+10, 17639);
	ili9325_WritePixel(X+9, Y+10, 0);
	ili9325_WritePixel(X+10, Y+10, 50712);
	ili9325_WritePixel(X+11, Y+10, 50712);
	ili9325_WritePixel(X+12, Y+10, 0);
	ili9325_WritePixel(X+13, Y+10, 17639);
	ili9325_WritePixel(X+14, Y+10, 17639);
	ili9325_WritePixel(X+15, Y+10, 17639);
	ili9325_WritePixel(X+16, Y+10, 0);
	ili9325_WritePixel(X+17, Y+10, 0);
	ili9325_WritePixel(X+18, Y+10, 0);
	ili9325_WritePixel(X+19, Y+10, 0);
	ili9325_WritePixel(X+20, Y+10, 0);
	ili9325_WritePixel(X+21, Y+10, 0);
	ili9325_WritePixel(X+22, Y+10, 27144);
	ili9325_WritePixel(X+23, Y+10, 27144);
	ili9325_WritePixel(X+24, Y+10, 0);

	ili9325_WritePixel(X+2, Y+11, 0);
	ili9325_WritePixel(X+3, Y+11, 0);
	ili9325_WritePixel(X+4, Y+11, 0);
	ili9325_WritePixel(X+5, Y+11, 0);
	ili9325_WritePixel(X+6, Y+11, 0);
	ili9325_WritePixel(X+7, Y+11, 0);
	ili9325_WritePixel(X+8, Y+11, 0);
	ili9325_WritePixel(X+9, Y+11, 0);
	ili9325_WritePixel(X+10, Y+11, 0);
	ili9325_WritePixel(X+11, Y+11, 0);
	ili9325_WritePixel(X+12, Y+11, 0);
	ili9325_WritePixel(X+13, Y+11, 3008);
	ili9325_WritePixel(X+14, Y+11, 17639);
	ili9325_WritePixel(X+15, Y+11, 17639);
	ili9325_WritePixel(X+16, Y+11, 3008);
	ili9325_WritePixel(X+17, Y+11, 3008);
	ili9325_WritePixel(X+18, Y+11, 17639);
	ili9325_WritePixel(X+19, Y+11, 17639);
	ili9325_WritePixel(X+20, Y+11, 17639);
	ili9325_WritePixel(X+21, Y+11, 65077);
	ili9325_WritePixel(X+22, Y+11, 65077);
	ili9325_WritePixel(X+23, Y+11, 65077);
	ili9325_WritePixel(X+24, Y+11, 0);

	ili9325_WritePixel(X+1, Y+12, 0);
	ili9325_WritePixel(X+2, Y+12, 3008);
	ili9325_WritePixel(X+3, Y+12, 3008);
	ili9325_WritePixel(X+4, Y+12, 3008);
	ili9325_WritePixel(X+5, Y+12, 3008);
	ili9325_WritePixel(X+6, Y+12, 3008);
	ili9325_WritePixel(X+7, Y+12, 3008);
	ili9325_WritePixel(X+8, Y+12, 3008);
	ili9325_WritePixel(X+9, Y+12, 17639);
	ili9325_WritePixel(X+10, Y+12, 65077);
	ili9325_WritePixel(X+11, Y+12, 65077);
	ili9325_WritePixel(X+12, Y+12, 65077);
	ili9325_WritePixel(X+13, Y+12, 0);
	ili9325_WritePixel(X+14, Y+12, 3008);
	ili9325_WritePixel(X+15, Y+12, 3008);
	ili9325_WritePixel(X+16, Y+12, 3008);
	ili9325_WritePixel(X+17, Y+12, 3008);
	ili9325_WritePixel(X+18, Y+12, 3008);
	ili9325_WritePixel(X+19, Y+12, 3008);
	ili9325_WritePixel(X+20, Y+12, 3008);
	ili9325_WritePixel(X+21, Y+12, 65077);
	ili9325_WritePixel(X+22, Y+12, 65077);
	ili9325_WritePixel(X+23, Y+12, 65077);
	ili9325_WritePixel(X+24, Y+12, 0);
	ili9325_WritePixel(X+28, Y+12, 0);
	ili9325_WritePixel(X+29, Y+12, 0);//50712 szary //27144 brazowy //65077 kolor skóry

	ili9325_WritePixel(X+1, Y+13, 0);
	ili9325_WritePixel(X+2, Y+13, 3008);
	ili9325_WritePixel(X+3, Y+13, 17639);
	ili9325_WritePixel(X+4, Y+13, 17639);
	ili9325_WritePixel(X+5, Y+13, 17639);
	ili9325_WritePixel(X+6, Y+13, 17639);
	ili9325_WritePixel(X+7, Y+13, 17639);
	ili9325_WritePixel(X+8, Y+13, 17639);
	ili9325_WritePixel(X+9, Y+13, 17639);
	ili9325_WritePixel(X+10, Y+13, 65077);
	ili9325_WritePixel(X+11, Y+13, 65077);
	ili9325_WritePixel(X+12, Y+13, 65077);
	ili9325_WritePixel(X+13, Y+13, 0);
	ili9325_WritePixel(X+14, Y+13, 0);
	ili9325_WritePixel(X+15, Y+13, 0);
	ili9325_WritePixel(X+16, Y+13, 0);
	ili9325_WritePixel(X+17, Y+13, 0);
	ili9325_WritePixel(X+18, Y+13, 0);
	ili9325_WritePixel(X+19, Y+13, 0);
	ili9325_WritePixel(X+20, Y+13, 0);
	ili9325_WritePixel(X+21, Y+13, 0);
	ili9325_WritePixel(X+22, Y+13, 0);
	ili9325_WritePixel(X+23, Y+13, 0);
	ili9325_WritePixel(X+24, Y+13, 0);
	ili9325_WritePixel(X+25, Y+13, 0);
	ili9325_WritePixel(X+26, Y+13, 0);
	ili9325_WritePixel(X+27, Y+13, 0);
	ili9325_WritePixel(X+28, Y+13, 50712);
	ili9325_WritePixel(X+29, Y+13, 50712);
	ili9325_WritePixel(X+30, Y+13, 0);

	ili9325_WritePixel(X+1, Y+14, 0);
	ili9325_WritePixel(X+2, Y+14, 17639);
	ili9325_WritePixel(X+3, Y+14, 17639);
	ili9325_WritePixel(X+4, Y+14, 17639);
	ili9325_WritePixel(X+5, Y+14, 17639);
	ili9325_WritePixel(X+6, Y+14, 17639);
	ili9325_WritePixel(X+7, Y+14, 17639);
	ili9325_WritePixel(X+8, Y+14, 17639);
	ili9325_WritePixel(X+9, Y+14, 17639);
	ili9325_WritePixel(X+10, Y+14, 50712);
	ili9325_WritePixel(X+11, Y+14, 50712);
	ili9325_WritePixel(X+12, Y+14, 50712);
	ili9325_WritePixel(X+13, Y+14, 44040);	//jasny brązowy
	ili9325_WritePixel(X+14, Y+14, 44040);
	ili9325_WritePixel(X+15, Y+14, 44040);
	ili9325_WritePixel(X+16, Y+14, 44040);
	ili9325_WritePixel(X+17, Y+14, 44040);
	ili9325_WritePixel(X+18, Y+14, 44040);
	ili9325_WritePixel(X+19, Y+14, 44040);
	ili9325_WritePixel(X+20, Y+14, 44040);
	ili9325_WritePixel(X+21, Y+14, 44040);
	ili9325_WritePixel(X+22, Y+14, 44040);
	ili9325_WritePixel(X+23, Y+14, 44040);
	ili9325_WritePixel(X+24, Y+14, 44040);
	ili9325_WritePixel(X+25, Y+14, 44040);
	ili9325_WritePixel(X+26, Y+14, 44040);
	ili9325_WritePixel(X+27, Y+14, 44040);
	ili9325_WritePixel(X+28, Y+14, 50712);
	ili9325_WritePixel(X+29, Y+14, 50712);
	ili9325_WritePixel(X+30, Y+14, 50712);
	ili9325_WritePixel(X+31, Y+14, 0);

	ili9325_WritePixel(X+2, Y+15, 0);
	ili9325_WritePixel(X+3, Y+15, 17639);
	ili9325_WritePixel(X+4, Y+15, 17639);
	ili9325_WritePixel(X+5, Y+15, 17639);
	ili9325_WritePixel(X+6, Y+15, 3008);
	ili9325_WritePixel(X+7, Y+15, 3008);
	ili9325_WritePixel(X+8, Y+15, 3008);
	ili9325_WritePixel(X+9, Y+15, 0);
	ili9325_WritePixel(X+10, Y+15, 0);
	ili9325_WritePixel(X+11, Y+15, 0);
	ili9325_WritePixel(X+12, Y+15, 0);
	ili9325_WritePixel(X+13, Y+15, 0);
	ili9325_WritePixel(X+14, Y+15, 0);
	ili9325_WritePixel(X+15, Y+15, 0);
	ili9325_WritePixel(X+16, Y+15, 0);
	ili9325_WritePixel(X+17, Y+15, 0);
	ili9325_WritePixel(X+18, Y+15, 0);
	ili9325_WritePixel(X+19, Y+15, 0);
	ili9325_WritePixel(X+20, Y+15, 0);
	ili9325_WritePixel(X+21, Y+15, 0);
	ili9325_WritePixel(X+22, Y+15, 0);
	ili9325_WritePixel(X+23, Y+15, 0);
	ili9325_WritePixel(X+24, Y+15, 0);
	ili9325_WritePixel(X+25, Y+15, 0);
	ili9325_WritePixel(X+26, Y+15, 0);
	ili9325_WritePixel(X+27, Y+15, 0);
	ili9325_WritePixel(X+28, Y+15, 50712);
	ili9325_WritePixel(X+29, Y+15, 50712);
	ili9325_WritePixel(X+30, Y+15, 0);

	ili9325_WritePixel(X+3, Y+16, 0);
	ili9325_WritePixel(X+4, Y+16, 3008);
	ili9325_WritePixel(X+5, Y+16, 3008);
	ili9325_WritePixel(X+6, Y+16, 0);
	ili9325_WritePixel(X+7, Y+16, 0);
	ili9325_WritePixel(X+8, Y+16, 0);
	ili9325_WritePixel(X+9, Y+16, 0);
	ili9325_WritePixel(X+10, Y+16, 50712);
	ili9325_WritePixel(X+11, Y+16, 50712);
	ili9325_WritePixel(X+12, Y+16, 0);
	ili9325_WritePixel(X+13, Y+16, 0);
	ili9325_WritePixel(X+14, Y+16, 0);
	ili9325_WritePixel(X+21, Y+16, 0);
	ili9325_WritePixel(X+22, Y+16, 27114);
	ili9325_WritePixel(X+23, Y+16, 27114);
	ili9325_WritePixel(X+24, Y+16, 0);
	ili9325_WritePixel(X+28, Y+16, 0);
	ili9325_WritePixel(X+29, Y+16, 0);

	ili9325_WritePixel(X+4, Y+17, 0);
	ili9325_WritePixel(X+5, Y+17, 0);
	ili9325_WritePixel(X+6, Y+17, 65077);
	ili9325_WritePixel(X+7, Y+17, 65077);
	ili9325_WritePixel(X+8, Y+17, 65077);
	ili9325_WritePixel(X+9, Y+17, 65077);
	ili9325_WritePixel(X+10, Y+17, 0);
	ili9325_WritePixel(X+11, Y+17, 50712);
	ili9325_WritePixel(X+12, Y+17, 50712);
	ili9325_WritePixel(X+13, Y+17, 65077);
	ili9325_WritePixel(X+14, Y+17, 0);
	ili9325_WritePixel(X+20, Y+17, 0);
	ili9325_WritePixel(X+21, Y+17, 27114);
	ili9325_WritePixel(X+22, Y+17, 27114);
	ili9325_WritePixel(X+23, Y+17, 0);

	ili9325_WritePixel(X+4, Y+18, 0);
	ili9325_WritePixel(X+5, Y+18, 65077);
	ili9325_WritePixel(X+6, Y+18, 65077);
	ili9325_WritePixel(X+7, Y+18, 65077);
	ili9325_WritePixel(X+8, Y+18, 65077);
	ili9325_WritePixel(X+9, Y+18, 60591); //usta
	ili9325_WritePixel(X+10, Y+18, 60591);
	ili9325_WritePixel(X+11, Y+18, 0);
	ili9325_WritePixel(X+12, Y+18, 50712);
	ili9325_WritePixel(X+13, Y+18, 50712);
	ili9325_WritePixel(X+14, Y+18, 0);
	ili9325_WritePixel(X+15, Y+18, 0);
	ili9325_WritePixel(X+21, Y+18, 0);
	ili9325_WritePixel(X+22, Y+18, 27114);
	ili9325_WritePixel(X+23, Y+18, 27114);
	ili9325_WritePixel(X+24, Y+18, 0);

	ili9325_WritePixel(X+4, Y+19, 0);
	ili9325_WritePixel(X+5, Y+19, 65077);
	ili9325_WritePixel(X+6, Y+19, 65077);
	ili9325_WritePixel(X+7, Y+19, 65077);
	ili9325_WritePixel(X+8, Y+19, 60591);
	ili9325_WritePixel(X+9, Y+19, 60591);
	ili9325_WritePixel(X+10, Y+19, 60591);
	ili9325_WritePixel(X+11, Y+19, 60591);
	ili9325_WritePixel(X+12, Y+19, 0);
	ili9325_WritePixel(X+13, Y+19, 50712);
	ili9325_WritePixel(X+14, Y+19, 50712);
	ili9325_WritePixel(X+15, Y+19, 0);
	ili9325_WritePixel(X+21, Y+19, 0);
	ili9325_WritePixel(X+22, Y+19, 27114);
	ili9325_WritePixel(X+23, Y+19, 27114);
	ili9325_WritePixel(X+24, Y+19, 0);

	ili9325_WritePixel(X+4, Y+20, 0);
	ili9325_WritePixel(X+5, Y+20, 65077);
	ili9325_WritePixel(X+6, Y+20, 65077);
	ili9325_WritePixel(X+7, Y+20, 65077);
	ili9325_WritePixel(X+8, Y+20, 65077);
	ili9325_WritePixel(X+9, Y+20, 65077);
	ili9325_WritePixel(X+10, Y+20, 65077);
	ili9325_WritePixel(X+11, Y+20, 65077);
	ili9325_WritePixel(X+12, Y+20, 65077);
	ili9325_WritePixel(X+13, Y+20, 0);
	ili9325_WritePixel(X+14, Y+20, 50712);
	ili9325_WritePixel(X+15, Y+20, 50712);
	ili9325_WritePixel(X+16, Y+20, 0);
	ili9325_WritePixel(X+21, Y+20, 0);
	ili9325_WritePixel(X+22, Y+20, 27114);
	ili9325_WritePixel(X+23, Y+20, 27114);
	ili9325_WritePixel(X+24, Y+20, 0);

	ili9325_WritePixel(X+3, Y+21, 0);
	ili9325_WritePixel(X+4, Y+21, 65077);
	ili9325_WritePixel(X+5, Y+21, 65077);
	ili9325_WritePixel(X+6, Y+21, 65077);
	ili9325_WritePixel(X+7, Y+21, 65077);
	ili9325_WritePixel(X+8, Y+21, 65077);
	ili9325_WritePixel(X+9, Y+21, 65077);
	ili9325_WritePixel(X+10, Y+21, 65077);
	ili9325_WritePixel(X+11, Y+21, 65077);
	ili9325_WritePixel(X+12, Y+21, 65077);
	ili9325_WritePixel(X+13, Y+21, 65077);
	ili9325_WritePixel(X+14, Y+21, 0);
	ili9325_WritePixel(X+15, Y+21, 50712);
	ili9325_WritePixel(X+16, Y+21, 50712);
	ili9325_WritePixel(X+17, Y+21, 0);
	ili9325_WritePixel(X+20, Y+21, 0);
	ili9325_WritePixel(X+21, Y+21, 27114);
	ili9325_WritePixel(X+22, Y+21, 27114);
	ili9325_WritePixel(X+23, Y+21, 0);

	ili9325_WritePixel(X+2, Y+22, 0);
	ili9325_WritePixel(X+3, Y+22, 0);
	ili9325_WritePixel(X+4, Y+22, 65077);
	ili9325_WritePixel(X+5, Y+22, 65077);
	ili9325_WritePixel(X+6, Y+22, 65077);
	ili9325_WritePixel(X+7, Y+22, 65077);
	ili9325_WritePixel(X+8, Y+22, 0);
	ili9325_WritePixel(X+9, Y+22, 65077);
	ili9325_WritePixel(X+10, Y+22, 65077);
	ili9325_WritePixel(X+11, Y+22, 65077);
	ili9325_WritePixel(X+12, Y+22, 0);
	ili9325_WritePixel(X+13, Y+22, 65077);
	ili9325_WritePixel(X+14, Y+22, 65077);
	ili9325_WritePixel(X+15, Y+22, 0);
	ili9325_WritePixel(X+16, Y+22, 50712);
	ili9325_WritePixel(X+17, Y+22, 50712);
	ili9325_WritePixel(X+18, Y+22, 0);
	ili9325_WritePixel(X+20, Y+22, 0);
	ili9325_WritePixel(X+21, Y+22, 27114);
	ili9325_WritePixel(X+22, Y+22, 27114);
	ili9325_WritePixel(X+23, Y+22, 0);

	ili9325_WritePixel(X+1, Y+23, 0);
	ili9325_WritePixel(X+2, Y+23, 57638);	//czerwone
	ili9325_WritePixel(X+3, Y+23, 57638);
	ili9325_WritePixel(X+4, Y+23, 0);
	ili9325_WritePixel(X+5, Y+23, 65077);
	ili9325_WritePixel(X+6, Y+23, 65077);
	ili9325_WritePixel(X+7, Y+23, 65077);
	ili9325_WritePixel(X+8, Y+23, 0);
	ili9325_WritePixel(X+9, Y+23, 65077);
	ili9325_WritePixel(X+10, Y+23, 65077);
	ili9325_WritePixel(X+11, Y+23, 65077);
	ili9325_WritePixel(X+12, Y+23, 0);
	ili9325_WritePixel(X+13, Y+23, 65077);
	ili9325_WritePixel(X+14, Y+23, 65077);
	ili9325_WritePixel(X+15, Y+23, 0);
	ili9325_WritePixel(X+16, Y+23, 0);
	ili9325_WritePixel(X+17, Y+23, 50712);
	ili9325_WritePixel(X+18, Y+23, 50712);
	ili9325_WritePixel(X+19, Y+23, 0);
	ili9325_WritePixel(X+20, Y+23, 27114);
	ili9325_WritePixel(X+21, Y+23, 27114);
	ili9325_WritePixel(X+22, Y+23, 0);

	ili9325_WritePixel(X+1, Y+24, 0);
	ili9325_WritePixel(X+2, Y+24, 57638);
	ili9325_WritePixel(X+3, Y+24, 57638);
	ili9325_WritePixel(X+4, Y+24, 0);
	ili9325_WritePixel(X+5, Y+24, 0);
	ili9325_WritePixel(X+6, Y+24, 0);
	ili9325_WritePixel(X+7, Y+24, 0);
	ili9325_WritePixel(X+8, Y+24, 0);
	ili9325_WritePixel(X+9, Y+24, 0);
	ili9325_WritePixel(X+10, Y+24, 0);
	ili9325_WritePixel(X+11, Y+24, 0);
	ili9325_WritePixel(X+12, Y+24, 0);
	ili9325_WritePixel(X+13, Y+24, 0);
	ili9325_WritePixel(X+14, Y+24, 0);
	ili9325_WritePixel(X+15, Y+24, 0);
	ili9325_WritePixel(X+17, Y+24, 0);
	ili9325_WritePixel(X+18, Y+24, 50712);
	ili9325_WritePixel(X+19, Y+24, 27114);
	ili9325_WritePixel(X+20, Y+24, 27114);
	ili9325_WritePixel(X+21, Y+24, 27114);
	ili9325_WritePixel(X+22, Y+24, 0);

	ili9325_WritePixel(X+2, Y+25, 0);
	ili9325_WritePixel(X+3, Y+25, 57638);
	ili9325_WritePixel(X+4, Y+25, 0);
	ili9325_WritePixel(X+5, Y+25, 57638);
	ili9325_WritePixel(X+6, Y+25, 57638);
	ili9325_WritePixel(X+7, Y+25, 57638);
	ili9325_WritePixel(X+8, Y+25, 57638);
	ili9325_WritePixel(X+9, Y+25, 57638);
	ili9325_WritePixel(X+10, Y+25, 57638);
	ili9325_WritePixel(X+11, Y+25, 57638);
	ili9325_WritePixel(X+12, Y+25, 57638);
	ili9325_WritePixel(X+13, Y+25, 57638);
	ili9325_WritePixel(X+14, Y+25, 57638);
	ili9325_WritePixel(X+15, Y+25, 0);
	ili9325_WritePixel(X+18, Y+25, 0);
	ili9325_WritePixel(X+19, Y+25, 27114);
	ili9325_WritePixel(X+20, Y+25, 27114);
	ili9325_WritePixel(X+21, Y+25, 0);

	ili9325_WritePixel(X+1, Y+26, 0);
	ili9325_WritePixel(X+2, Y+26, 57638);
	ili9325_WritePixel(X+3, Y+26, 57638);
	ili9325_WritePixel(X+4, Y+26, 0);
	ili9325_WritePixel(X+5, Y+26, 0);
	ili9325_WritePixel(X+6, Y+26, 0);
	ili9325_WritePixel(X+7, Y+26, 0);
	ili9325_WritePixel(X+8, Y+26, 0);
	ili9325_WritePixel(X+9, Y+26, 0);
	ili9325_WritePixel(X+10, Y+26, 0);
	ili9325_WritePixel(X+11, Y+26, 0);
	ili9325_WritePixel(X+12, Y+26, 0);
	ili9325_WritePixel(X+13, Y+26, 0);
	ili9325_WritePixel(X+14, Y+26, 0);
	ili9325_WritePixel(X+15, Y+26, 0);
	ili9325_WritePixel(X+19, Y+26, 0);
	ili9325_WritePixel(X+20, Y+26, 0);

	ili9325_WritePixel(X+1, Y+27, 0);
	ili9325_WritePixel(X+2, Y+27, 57638);
	ili9325_WritePixel(X+3, Y+27, 57638);
	ili9325_WritePixel(X+4, Y+27, 0);
	ili9325_WritePixel(X+5, Y+27, 65320); //żółty
	ili9325_WritePixel(X+5, Y+27, 65320);
	ili9325_WritePixel(X+6, Y+27, 65061); //ciemny żółty
	ili9325_WritePixel(X+7, Y+27, 65061);
	ili9325_WritePixel(X+8, Y+27, 65061);
	ili9325_WritePixel(X+9, Y+27, 65061);
	ili9325_WritePixel(X+10, Y+27, 65061);
	ili9325_WritePixel(X+11, Y+27, 65061);
	ili9325_WritePixel(X+12, Y+27, 65061);
	ili9325_WritePixel(X+13, Y+27, 65061);
	ili9325_WritePixel(X+14, Y+27, 65061);
	ili9325_WritePixel(X+15, Y+27, 0);

	ili9325_WritePixel(X+1, Y+28, 0);
	ili9325_WritePixel(X+2, Y+28, 0);
	ili9325_WritePixel(X+3, Y+28, 0);
	ili9325_WritePixel(X+5, Y+28, 0);
	ili9325_WritePixel(X+6, Y+28, 65320);
	ili9325_WritePixel(X+7, Y+28, 65320);
	ili9325_WritePixel(X+8, Y+28, 65061);
	ili9325_WritePixel(X+9, Y+28, 65061);
	ili9325_WritePixel(X+10, Y+28, 65061);
	ili9325_WritePixel(X+11, Y+28, 65320);
	ili9325_WritePixel(X+12, Y+28, 65320);
	ili9325_WritePixel(X+13, Y+28, 65320);
	ili9325_WritePixel(X+14, Y+28, 65320);
	ili9325_WritePixel(X+15, Y+28, 65320);
	ili9325_WritePixel(X+16, Y+28, 0);

	ili9325_WritePixel(X+6, Y+29, 0);
	ili9325_WritePixel(X+7, Y+29, 65320);
	ili9325_WritePixel(X+8, Y+29, 65320);
	ili9325_WritePixel(X+9, Y+29, 65320);
	ili9325_WritePixel(X+10, Y+29, 65320);
	ili9325_WritePixel(X+11, Y+29, 65320);
	ili9325_WritePixel(X+12, Y+29, 65320);
	ili9325_WritePixel(X+13, Y+29, 65320);
	ili9325_WritePixel(X+14, Y+29, 65320);
	ili9325_WritePixel(X+15, Y+29, 65320);
	ili9325_WritePixel(X+16, Y+29, 0);

	ili9325_WritePixel(X+7, Y+30, 0);
	ili9325_WritePixel(X+8, Y+30, 0);
	ili9325_WritePixel(X+9, Y+30, 0);
	ili9325_WritePixel(X+10, Y+30, 0);
	ili9325_WritePixel(X+11, Y+30, 0);
	ili9325_WritePixel(X+12, Y+30, 0);
	ili9325_WritePixel(X+13, Y+30, 0);
	ili9325_WritePixel(X+14, Y+30, 0);
	ili9325_WritePixel(X+15, Y+30, 0);
}
//--- SetTree --- DONE
void SetTree(uint16_t X, uint16_t Y)
{
	ili9325_WritePixel(X+12, Y+1, 14690);	//ciemny brąz
	ili9325_WritePixel(X+16, Y+1, 14690);
	ili9325_WritePixel(X+17, Y+1, 14690);

	ili9325_WritePixel(X+11, Y+2, 14690);
	ili9325_WritePixel(X+12, Y+2, 14690);
	ili9325_WritePixel(X+13, Y+2, 14690);
	ili9325_WritePixel(X+14, Y+2, 14690);
	ili9325_WritePixel(X+15, Y+2, 14690);
	ili9325_WritePixel(X+16, Y+2, 14690);

	ili9325_WritePixel(X+12, Y+3, 14690);
	ili9325_WritePixel(X+13, Y+3, 14690);
	ili9325_WritePixel(X+14, Y+3, 14690);
	ili9325_WritePixel(X+15, Y+3, 14690);

	ili9325_WritePixel(X+13, Y+4, 14690);
	ili9325_WritePixel(X+14, Y+4, 14690);
	ili9325_WritePixel(X+15, Y+4, 14690);

	ili9325_WritePixel(X+13, Y+5, 14690);
	ili9325_WritePixel(X+14, Y+5, 14690);
	ili9325_WritePixel(X+15, Y+5, 27265); //jasny brąz

	ili9325_WritePixel(X+13, Y+6, 14690);
	ili9325_WritePixel(X+14, Y+6, 27265);
	ili9325_WritePixel(X+15, Y+6, 27265);

	ili9325_WritePixel(X+13, Y+7, 27265);
	ili9325_WritePixel(X+14, Y+7, 27265);
	ili9325_WritePixel(X+15, Y+7, 27265);

	ili9325_WritePixel(X+4, Y+8, 8710);
	ili9325_WritePixel(X+5, Y+8, 8710);
	ili9325_WritePixel(X+13, Y+8, 27265);
	ili9325_WritePixel(X+14, Y+8, 27265);
	ili9325_WritePixel(X+15, Y+8, 27265);
	ili9325_WritePixel(X+19, Y+8, 8710);

	ili9325_WritePixel(X+2, Y+9, 8710);
	ili9325_WritePixel(X+5, Y+9, 8710);
	ili9325_WritePixel(X+7, Y+9, 8710);
	ili9325_WritePixel(X+10, Y+9, 8710);
	ili9325_WritePixel(X+11, Y+9, 8710);
	ili9325_WritePixel(X+13, Y+9, 8710);
	ili9325_WritePixel(X+14, Y+9, 36524); //jasny zielony
	ili9325_WritePixel(X+15, Y+9, 36524);
	ili9325_WritePixel(X+16, Y+9, 36524);
	ili9325_WritePixel(X+17, Y+9, 36524);
	ili9325_WritePixel(X+18, Y+9, 8710);
	ili9325_WritePixel(X+19, Y+9, 36524);
	ili9325_WritePixel(X+20, Y+9, 8710);
	ili9325_WritePixel(X+21, Y+9, 8710);
	ili9325_WritePixel(X+22, Y+9, 36524);
	ili9325_WritePixel(X+23, Y+9, 36524);
	ili9325_WritePixel(X+24, Y+9, 36524);

	ili9325_WritePixel(X+1, Y+10, 8710);
	ili9325_WritePixel(X+2, Y+10, 8710);
	ili9325_WritePixel(X+3, Y+10, 8710);
	ili9325_WritePixel(X+4, Y+10, 8710);
	ili9325_WritePixel(X+5, Y+10, 8710);
	ili9325_WritePixel(X+6, Y+10, 8710);
	ili9325_WritePixel(X+7, Y+10, 8710);
	ili9325_WritePixel(X+8, Y+10, 8710);
	ili9325_WritePixel(X+9, Y+10, 8710);
	ili9325_WritePixel(X+10, Y+10, 8710);
	ili9325_WritePixel(X+11, Y+10, 8710);
	ili9325_WritePixel(X+12, Y+10, 8710);
	ili9325_WritePixel(X+13, Y+10, 8710);
	ili9325_WritePixel(X+14, Y+10, 36524);
	ili9325_WritePixel(X+15, Y+10, 36524);
	ili9325_WritePixel(X+16, Y+10, 8710);
	ili9325_WritePixel(X+17, Y+10, 8710);
	ili9325_WritePixel(X+18, Y+10, 8710);
	ili9325_WritePixel(X+19, Y+10, 8710);
	ili9325_WritePixel(X+20, Y+10, 36524);
	ili9325_WritePixel(X+21, Y+10, 36524);
	ili9325_WritePixel(X+22, Y+10, 36524);
	ili9325_WritePixel(X+23, Y+10, 36524);
	ili9325_WritePixel(X+24, Y+10, 36524);

	ili9325_WritePixel(X+3, Y+11, 8710);
	ili9325_WritePixel(X+4, Y+11, 8710);
	ili9325_WritePixel(X+5, Y+11, 8710);
	ili9325_WritePixel(X+6, Y+11, 36524);
	ili9325_WritePixel(X+7, Y+11, 36524);
	ili9325_WritePixel(X+8, Y+11, 8710);
	ili9325_WritePixel(X+9, Y+11, 8710);
	ili9325_WritePixel(X+10, Y+11, 8710);
	ili9325_WritePixel(X+11, Y+11, 8710);
	ili9325_WritePixel(X+12, Y+11, 8710);
	ili9325_WritePixel(X+13, Y+11, 8710);
	ili9325_WritePixel(X+14, Y+11, 36524);
	ili9325_WritePixel(X+15, Y+11, 36524);
	ili9325_WritePixel(X+16, Y+11, 36524);
	ili9325_WritePixel(X+17, Y+11, 8710);
	ili9325_WritePixel(X+18, Y+11, 36524);
	ili9325_WritePixel(X+19, Y+11, 8710);
	ili9325_WritePixel(X+20, Y+11, 36524);
	ili9325_WritePixel(X+21, Y+11, 36524);
	ili9325_WritePixel(X+22, Y+11, 36524);
	ili9325_WritePixel(X+23, Y+11, 36524);
	ili9325_WritePixel(X+24, Y+11, 36524);

	ili9325_WritePixel(X+3, Y+12, 8710);
	ili9325_WritePixel(X+4, Y+12, 8710);
	ili9325_WritePixel(X+5, Y+12, 8710);
	ili9325_WritePixel(X+6, Y+12, 8710);
	ili9325_WritePixel(X+7, Y+12, 36524);
	ili9325_WritePixel(X+8, Y+12, 36524);
	ili9325_WritePixel(X+9, Y+12, 8710);
	ili9325_WritePixel(X+10, Y+12, 8710);
	ili9325_WritePixel(X+11, Y+12, 8710);
	ili9325_WritePixel(X+12, Y+12, 8710);
	ili9325_WritePixel(X+13, Y+12, 36524);
	ili9325_WritePixel(X+14, Y+12, 36524);
	ili9325_WritePixel(X+15, Y+12, 36524);
	ili9325_WritePixel(X+16, Y+12, 36524);
	ili9325_WritePixel(X+17, Y+12, 8710);
	ili9325_WritePixel(X+18, Y+12, 36524);
	ili9325_WritePixel(X+19, Y+12, 36524);
	ili9325_WritePixel(X+20, Y+12, 36524);
	ili9325_WritePixel(X+21, Y+12, 36524);
	ili9325_WritePixel(X+22, Y+12, 36524);
	ili9325_WritePixel(X+23, Y+12, 36524);
	ili9325_WritePixel(X+24, Y+12, 36524);

	ili9325_WritePixel(X+4, Y+13, 36524);
	ili9325_WritePixel(X+5, Y+13, 36524);
	ili9325_WritePixel(X+6, Y+13, 36524);
	ili9325_WritePixel(X+7, Y+13, 8710);
	ili9325_WritePixel(X+8, Y+13, 8710);
	ili9325_WritePixel(X+9, Y+13, 8710);
	ili9325_WritePixel(X+10, Y+13, 36524);
	ili9325_WritePixel(X+11, Y+13, 36524);
	ili9325_WritePixel(X+12, Y+13, 8710);
	ili9325_WritePixel(X+13, Y+13, 8710);
	ili9325_WritePixel(X+14, Y+13, 8710);
	ili9325_WritePixel(X+15, Y+13, 8710);
	ili9325_WritePixel(X+16, Y+13, 8710);
	ili9325_WritePixel(X+17, Y+13, 36524);
	ili9325_WritePixel(X+18, Y+13, 8710);
	ili9325_WritePixel(X+19, Y+13, 36524);
	ili9325_WritePixel(X+20, Y+13, 36524);
	ili9325_WritePixel(X+21, Y+13, 36524);
	ili9325_WritePixel(X+22, Y+13, 36524);
	ili9325_WritePixel(X+23, Y+13, 36524);

	ili9325_WritePixel(X+4, Y+14, 36524);
	ili9325_WritePixel(X+5, Y+14, 36524);
	ili9325_WritePixel(X+6, Y+14, 36524);
	ili9325_WritePixel(X+7, Y+14, 36524);
	ili9325_WritePixel(X+8, Y+14, 8710);
	ili9325_WritePixel(X+9, Y+14, 8710);
	ili9325_WritePixel(X+10, Y+14, 36524);
	ili9325_WritePixel(X+11, Y+14, 36524);
	ili9325_WritePixel(X+12, Y+14, 8710);
	ili9325_WritePixel(X+13, Y+14, 8710);
	ili9325_WritePixel(X+14, Y+14, 8710);
	ili9325_WritePixel(X+15, Y+14, 36524);
	ili9325_WritePixel(X+16, Y+14, 8710);
	ili9325_WritePixel(X+17, Y+14, 36524);
	ili9325_WritePixel(X+18, Y+14, 36524);
	ili9325_WritePixel(X+19, Y+14, 8710);
	ili9325_WritePixel(X+20, Y+14, 8710);
	ili9325_WritePixel(X+21, Y+14, 36524);
	ili9325_WritePixel(X+22, Y+14, 36524);

	ili9325_WritePixel(X+6, Y+15, 36524);
	ili9325_WritePixel(X+7, Y+15, 36524);
	ili9325_WritePixel(X+8, Y+15, 36524);
	ili9325_WritePixel(X+9, Y+15, 8710);
	ili9325_WritePixel(X+10, Y+15, 8710);
	ili9325_WritePixel(X+11, Y+15, 8710);
	ili9325_WritePixel(X+12, Y+15, 8710);
	ili9325_WritePixel(X+13, Y+15, 8710);
	ili9325_WritePixel(X+14, Y+15, 36524);
	ili9325_WritePixel(X+15, Y+15, 36524);
	ili9325_WritePixel(X+16, Y+15, 8710);
	ili9325_WritePixel(X+17, Y+15, 36524);
	ili9325_WritePixel(X+18, Y+15, 36524);
	ili9325_WritePixel(X+19, Y+15, 36524);
	ili9325_WritePixel(X+20, Y+15, 36524);
	ili9325_WritePixel(X+21, Y+15, 8710);
	ili9325_WritePixel(X+22, Y+15, 36524);

	ili9325_WritePixel(X+6, Y+16, 36524);
	ili9325_WritePixel(X+7, Y+16, 8710);
	ili9325_WritePixel(X+8, Y+16, 8710);
	ili9325_WritePixel(X+9, Y+16, 8710);
	ili9325_WritePixel(X+10, Y+16, 8710);
	ili9325_WritePixel(X+11, Y+16, 8710);
	ili9325_WritePixel(X+12, Y+16, 8710);
	ili9325_WritePixel(X+13, Y+16, 36524);
	ili9325_WritePixel(X+14, Y+16, 36524);
	ili9325_WritePixel(X+15, Y+16, 36524);
	ili9325_WritePixel(X+16, Y+16, 36524);
	ili9325_WritePixel(X+17, Y+16, 36524);
	ili9325_WritePixel(X+18, Y+16, 8710);
	ili9325_WritePixel(X+19, Y+16, 36524);
	ili9325_WritePixel(X+20, Y+16, 36524);
	ili9325_WritePixel(X+21, Y+16, 8710);
	ili9325_WritePixel(X+22, Y+16, 36524);

	ili9325_WritePixel(X+6, Y+17, 36524);
	ili9325_WritePixel(X+7, Y+17, 8710);
	ili9325_WritePixel(X+8, Y+17, 36524);
	ili9325_WritePixel(X+9, Y+17, 36524);
	ili9325_WritePixel(X+10, Y+17, 36524);
	ili9325_WritePixel(X+11, Y+17, 36524);
	ili9325_WritePixel(X+12, Y+17, 36524);
	ili9325_WritePixel(X+13, Y+17, 36524);
	ili9325_WritePixel(X+14, Y+17, 8710);
	ili9325_WritePixel(X+15, Y+17, 36524);
	ili9325_WritePixel(X+16, Y+17, 36524);
	ili9325_WritePixel(X+17, Y+17, 36524);
	ili9325_WritePixel(X+18, Y+17, 36524);
	ili9325_WritePixel(X+19, Y+17, 36524);
	ili9325_WritePixel(X+20, Y+17, 36524);
	ili9325_WritePixel(X+21, Y+17, 36524);
	ili9325_WritePixel(X+22, Y+17, 36524);

	ili9325_WritePixel(X+6, Y+18, 8710);
	ili9325_WritePixel(X+7, Y+18, 36524);
	ili9325_WritePixel(X+8, Y+18, 36524);
	ili9325_WritePixel(X+9, Y+18, 36524);
	ili9325_WritePixel(X+10, Y+18, 36524);
	ili9325_WritePixel(X+11, Y+18, 36524);
	ili9325_WritePixel(X+12, Y+18, 8710);
	ili9325_WritePixel(X+13, Y+18, 8710);
	ili9325_WritePixel(X+14, Y+18, 36524);
	ili9325_WritePixel(X+15, Y+18, 36524);
	ili9325_WritePixel(X+16, Y+18, 36524);
	ili9325_WritePixel(X+17, Y+18, 8710);
	ili9325_WritePixel(X+18, Y+18, 36524);
	ili9325_WritePixel(X+19, Y+18, 36524);
	ili9325_WritePixel(X+20, Y+18, 36524);
	ili9325_WritePixel(X+21, Y+18, 36524);

	ili9325_WritePixel(X+6, Y+19, 8710);
	ili9325_WritePixel(X+7, Y+19, 8710);
	ili9325_WritePixel(X+8, Y+19, 8710);
	ili9325_WritePixel(X+9, Y+19, 8710);
	ili9325_WritePixel(X+10, Y+19, 8710);
	ili9325_WritePixel(X+11, Y+19, 8710);
	ili9325_WritePixel(X+12, Y+19, 8710);
	ili9325_WritePixel(X+13, Y+19, 36524);
	ili9325_WritePixel(X+14, Y+19, 36524);
	ili9325_WritePixel(X+15, Y+19, 8710);
	ili9325_WritePixel(X+16, Y+19, 8710);
	ili9325_WritePixel(X+17, Y+19, 36524);
	ili9325_WritePixel(X+18, Y+19, 36524);
	ili9325_WritePixel(X+19, Y+19, 36524);
	ili9325_WritePixel(X+20, Y+19, 36524);
	ili9325_WritePixel(X+21, Y+19, 36524);

	ili9325_WritePixel(X+7, Y+20, 8710);
	ili9325_WritePixel(X+8, Y+20, 36524);
	ili9325_WritePixel(X+9, Y+20, 36524);
	ili9325_WritePixel(X+10, Y+20, 8710);
	ili9325_WritePixel(X+11, Y+20, 8710);
	ili9325_WritePixel(X+12, Y+20, 36524);
	ili9325_WritePixel(X+13, Y+20, 36524);
	ili9325_WritePixel(X+14, Y+20, 8710);
	ili9325_WritePixel(X+15, Y+20, 36524);
	ili9325_WritePixel(X+16, Y+20, 36524);
	ili9325_WritePixel(X+17, Y+20, 36524);
	ili9325_WritePixel(X+18, Y+20, 36524);
	ili9325_WritePixel(X+19, Y+20, 36524);
	ili9325_WritePixel(X+20, Y+20, 36524);
	ili9325_WritePixel(X+21, Y+20, 36524);

	ili9325_WritePixel(X+7, Y+21, 8710);
	ili9325_WritePixel(X+8, Y+21, 8710);
	ili9325_WritePixel(X+9, Y+21, 8710);
	ili9325_WritePixel(X+10, Y+21, 36524);
	ili9325_WritePixel(X+11, Y+21, 36524);
	ili9325_WritePixel(X+12, Y+21, 8710);
	ili9325_WritePixel(X+13, Y+21, 36524);
	ili9325_WritePixel(X+14, Y+21, 36524);
	ili9325_WritePixel(X+15, Y+21, 36524);
	ili9325_WritePixel(X+16, Y+21, 36524);
	ili9325_WritePixel(X+17, Y+21, 36524);
	ili9325_WritePixel(X+18, Y+21, 36524);
	ili9325_WritePixel(X+19, Y+21, 36524);
	ili9325_WritePixel(X+20, Y+21, 36524);

	ili9325_WritePixel(X+8, Y+22, 8710);
	ili9325_WritePixel(X+9, Y+22, 36524);
	ili9325_WritePixel(X+10, Y+22, 36524);
	ili9325_WritePixel(X+11, Y+22, 36524);
	ili9325_WritePixel(X+12, Y+22, 36524);
	ili9325_WritePixel(X+13, Y+22, 36524);
	ili9325_WritePixel(X+14, Y+22, 8710);
	ili9325_WritePixel(X+15, Y+22, 36524);
	ili9325_WritePixel(X+16, Y+22, 36524);
	ili9325_WritePixel(X+17, Y+22, 36524);
	ili9325_WritePixel(X+18, Y+22, 36524);
	ili9325_WritePixel(X+19, Y+22, 36524);

	ili9325_WritePixel(X+8, Y+23, 8710);
	ili9325_WritePixel(X+9, Y+23, 36524);
	ili9325_WritePixel(X+10, Y+23, 36524);
	ili9325_WritePixel(X+11, Y+23, 36524);
	ili9325_WritePixel(X+12, Y+23, 36524);
	ili9325_WritePixel(X+13, Y+23, 36524);
	ili9325_WritePixel(X+14, Y+23, 8710);
	ili9325_WritePixel(X+15, Y+23, 36524);
	ili9325_WritePixel(X+16, Y+23, 36524);
	ili9325_WritePixel(X+17, Y+23, 36524);
	ili9325_WritePixel(X+18, Y+23, 36524);
	ili9325_WritePixel(X+19, Y+23, 36524);

	ili9325_WritePixel(X+8, Y+24, 8710);
	ili9325_WritePixel(X+9, Y+24, 36524);
	ili9325_WritePixel(X+10, Y+24, 8710);
	ili9325_WritePixel(X+11, Y+24, 36524);
	ili9325_WritePixel(X+12, Y+24, 36524);
	ili9325_WritePixel(X+13, Y+24, 36524);
	ili9325_WritePixel(X+14, Y+24, 36524);
	ili9325_WritePixel(X+15, Y+24, 8710);
	ili9325_WritePixel(X+16, Y+24, 36524);
	ili9325_WritePixel(X+17, Y+24, 36524);
	ili9325_WritePixel(X+18, Y+24, 8710);
	ili9325_WritePixel(X+19, Y+24, 36524);

	ili9325_WritePixel(X+9, Y+25, 8710);
	ili9325_WritePixel(X+10, Y+25, 36524);
	ili9325_WritePixel(X+11, Y+25, 8710);
	ili9325_WritePixel(X+12, Y+25, 8710);
	ili9325_WritePixel(X+13, Y+25, 36524);
	ili9325_WritePixel(X+14, Y+25, 36524);
	ili9325_WritePixel(X+15, Y+25, 8710);
	ili9325_WritePixel(X+16, Y+25, 36524);
	ili9325_WritePixel(X+17, Y+25, 36524);
	ili9325_WritePixel(X+18, Y+25, 36524);
	ili9325_WritePixel(X+19, Y+25, 36524);

	ili9325_WritePixel(X+9, Y+26, 8710);
	ili9325_WritePixel(X+10, Y+26, 36524);
	ili9325_WritePixel(X+11, Y+26, 36524);
	ili9325_WritePixel(X+12, Y+26, 36524);
	ili9325_WritePixel(X+13, Y+26, 36524);
	ili9325_WritePixel(X+14, Y+26, 36524);
	ili9325_WritePixel(X+15, Y+26, 8710);
	ili9325_WritePixel(X+16, Y+26, 36524);
	ili9325_WritePixel(X+17, Y+26, 36524);
	ili9325_WritePixel(X+18, Y+26, 36524);

	ili9325_WritePixel(X+10, Y+27, 8710);
	ili9325_WritePixel(X+11, Y+27, 36524);
	ili9325_WritePixel(X+12, Y+27, 36524);
	ili9325_WritePixel(X+13, Y+27, 36524);
	ili9325_WritePixel(X+14, Y+27, 36524);
	ili9325_WritePixel(X+15, Y+27, 36524);
	ili9325_WritePixel(X+16, Y+27, 36524);
	ili9325_WritePixel(X+17, Y+27, 36524);
	ili9325_WritePixel(X+18, Y+27, 36524);

	ili9325_WritePixel(X+10, Y+28, 36524);
	ili9325_WritePixel(X+11, Y+28, 36524);
	ili9325_WritePixel(X+12, Y+28, 36524);
	ili9325_WritePixel(X+13, Y+28, 36524);
	ili9325_WritePixel(X+14, Y+28, 36524);
	ili9325_WritePixel(X+15, Y+28, 8710);
	ili9325_WritePixel(X+16, Y+28, 8710);
	ili9325_WritePixel(X+17, Y+28, 36524);

	ili9325_WritePixel(X+11, Y+29, 36524);
	ili9325_WritePixel(X+12, Y+29, 36524);
	ili9325_WritePixel(X+13, Y+29, 36524);
	ili9325_WritePixel(X+14, Y+29, 36524);
	ili9325_WritePixel(X+15, Y+29, 36524);
	ili9325_WritePixel(X+16, Y+29, 36524);
	ili9325_WritePixel(X+17, Y+29, 36524);

	ili9325_WritePixel(X+11, Y+30, 36524);
	ili9325_WritePixel(X+12, Y+30, 36524);
	ili9325_WritePixel(X+13, Y+30, 36524);
	ili9325_WritePixel(X+14, Y+30, 36524);
	ili9325_WritePixel(X+15, Y+30, 36524);
	ili9325_WritePixel(X+16, Y+30, 36524);

	ili9325_WritePixel(X+12, Y+31, 8710);
	ili9325_WritePixel(X+13, Y+31, 36524);
	ili9325_WritePixel(X+14, Y+31, 36524);
	ili9325_WritePixel(X+15, Y+31, 36524);

	ili9325_WritePixel(X+12, Y+32, 8710);
	ili9325_WritePixel(X+13, Y+32, 36524);
	ili9325_WritePixel(X+14, Y+32, 36524);
	ili9325_WritePixel(X+15, Y+32, 36524);

	ili9325_WritePixel(X+12, Y+33, 36524);
	ili9325_WritePixel(X+13, Y+33, 36524);
	ili9325_WritePixel(X+14, Y+33, 36524);
}
//--- DrawSkier --- DONE
void DrawSkier(int position, int X, int Y)
{
	switch(position)
	{
		case 1:
			SetSkierFront(X,Y);
		break;
		case 2:
			SetSkierLeft(X,Y);
		break;
		case 3:
			SetSkierRight(X,Y);
		break;
	}
}
//--- SetSkierFront --- DONE
void SetSkierFront(uint16_t X, uint16_t Y)
{
	ili9325_WritePixel(X+8, Y+1, 19343);
	ili9325_WritePixel(X+9, Y+1, 19343);
	ili9325_WritePixel(X+10, Y+1, 19343);
	ili9325_WritePixel(X+11, Y+1, 19343);
	ili9325_WritePixel(X+15, Y+1, 19343);
	ili9325_WritePixel(X+16, Y+1, 19343);
	ili9325_WritePixel(X+17, Y+1, 19343);
	ili9325_WritePixel(X+18, Y+1, 19343);

	ili9325_WritePixel(X+8, Y+2, 19343);
	ili9325_WritePixel(X+9, Y+2, 19343);
	ili9325_WritePixel(X+10, Y+2, 19343);
	ili9325_WritePixel(X+11, Y+2, 19343);
	ili9325_WritePixel(X+15, Y+2, 19343);
	ili9325_WritePixel(X+16, Y+2, 19343);
	ili9325_WritePixel(X+17, Y+2, 19343);
	ili9325_WritePixel(X+18, Y+2, 19343);

	ili9325_WritePixel(X+8, Y+3, 19343);
	ili9325_WritePixel(X+9, Y+3, 19343);
	ili9325_WritePixel(X+10, Y+3, 19343);
	ili9325_WritePixel(X+11, Y+3, 19343);
	ili9325_WritePixel(X+15, Y+3, 19343);
	ili9325_WritePixel(X+16, Y+3, 19343);
	ili9325_WritePixel(X+17, Y+3, 19343);
	ili9325_WritePixel(X+18, Y+3, 19343);

	ili9325_WritePixel(X+8, Y+4, 19343);
	ili9325_WritePixel(X+9, Y+4, 19343);
	ili9325_WritePixel(X+10, Y+4, 19343);
	ili9325_WritePixel(X+11, Y+4, 19343);
	ili9325_WritePixel(X+15, Y+4, 19343);
	ili9325_WritePixel(X+16, Y+4, 19343);
	ili9325_WritePixel(X+17, Y+4, 19343);
	ili9325_WritePixel(X+18, Y+4, 19343);

	ili9325_WritePixel(X+8, Y+5, 19343);
	ili9325_WritePixel(X+9, Y+5, 19343);
	ili9325_WritePixel(X+10, Y+5, 19343);
	ili9325_WritePixel(X+11, Y+5, 19343);
	ili9325_WritePixel(X+15, Y+5, 19343);
	ili9325_WritePixel(X+16, Y+5, 19343);
	ili9325_WritePixel(X+17, Y+5, 19343);
	ili9325_WritePixel(X+18, Y+5, 19343);

	ili9325_WritePixel(X+7, Y+6, 19343);
	ili9325_WritePixel(X+8, Y+6, 19343);
	ili9325_WritePixel(X+9, Y+6, 19343);
	ili9325_WritePixel(X+10, Y+6, 19343);
	ili9325_WritePixel(X+11, Y+6, 19343);
	ili9325_WritePixel(X+12, Y+6, 19343);
	ili9325_WritePixel(X+14, Y+6, 19343);
	ili9325_WritePixel(X+15, Y+6, 19343);
	ili9325_WritePixel(X+16, Y+6, 19343);
	ili9325_WritePixel(X+17, Y+6, 19343);
	ili9325_WritePixel(X+18, Y+6, 19343);
	ili9325_WritePixel(X+19, Y+6, 19343);

	ili9325_WritePixel(X+7, Y+7, 19343);
	ili9325_WritePixel(X+8, Y+7, 19343);
	ili9325_WritePixel(X+9, Y+7, 19343);
	ili9325_WritePixel(X+10, Y+7, 19343);
	ili9325_WritePixel(X+11, Y+7, 19343);
	ili9325_WritePixel(X+12, Y+7, 19343);
	ili9325_WritePixel(X+14, Y+7, 19343);
	ili9325_WritePixel(X+15, Y+7, 19343);
	ili9325_WritePixel(X+16, Y+7, 19343);
	ili9325_WritePixel(X+17, Y+7, 19343);
	ili9325_WritePixel(X+18, Y+7, 19343);
	ili9325_WritePixel(X+19, Y+7, 19343);	//jaśniejszy niebieskie

	ili9325_WritePixel(X+7, Y+8, 19343);
	ili9325_WritePixel(X+8, Y+8, 57021);
	ili9325_WritePixel(X+9, Y+8, 57021);
	ili9325_WritePixel(X+10, Y+8, 57021);
	ili9325_WritePixel(X+11, Y+8, 57021);
	ili9325_WritePixel(X+12, Y+8, 19343);
	ili9325_WritePixel(X+14, Y+8, 19343);
	ili9325_WritePixel(X+15, Y+8, 57021);
	ili9325_WritePixel(X+16, Y+8, 57021);
	ili9325_WritePixel(X+17, Y+8, 57021);	//szary
	ili9325_WritePixel(X+18, Y+8, 57021);
	ili9325_WritePixel(X+19, Y+8, 19343);

	ili9325_WritePixel(X+7, Y+9, 19343);
	ili9325_WritePixel(X+8, Y+9, 57021);
	ili9325_WritePixel(X+9, Y+9, 57021);
	ili9325_WritePixel(X+10, Y+9, 57021);
	ili9325_WritePixel(X+11, Y+9, 57021);
	ili9325_WritePixel(X+12, Y+9, 19343);
	ili9325_WritePixel(X+14, Y+9, 19343);
	ili9325_WritePixel(X+15, Y+9, 57021);
	ili9325_WritePixel(X+16, Y+9, 57021);
	ili9325_WritePixel(X+17, Y+9, 57021);
	ili9325_WritePixel(X+18, Y+9, 57021);
	ili9325_WritePixel(X+19, Y+9, 19343);

	ili9325_WritePixel(X+7, Y+10, 19343);
	ili9325_WritePixel(X+8, Y+10, 45056); //czerwony
	ili9325_WritePixel(X+9, Y+10, 45056);
	ili9325_WritePixel(X+10, Y+10, 45056);
	ili9325_WritePixel(X+11, Y+10, 45056);
	ili9325_WritePixel(X+12, Y+10, 19343);
	ili9325_WritePixel(X+14, Y+10, 19343);
	ili9325_WritePixel(X+15, Y+10, 45056);
	ili9325_WritePixel(X+16, Y+10, 45056);
	ili9325_WritePixel(X+17, Y+10, 45056);
	ili9325_WritePixel(X+18, Y+10, 45056);
	ili9325_WritePixel(X+19, Y+10, 19343);

	ili9325_WritePixel(X+7, Y+11, 19343);
	ili9325_WritePixel(X+8, Y+11, 45056);
	ili9325_WritePixel(X+9, Y+11, 45056);
	ili9325_WritePixel(X+10, Y+11, 45056);
	ili9325_WritePixel(X+11, Y+11, 45056);
	ili9325_WritePixel(X+12, Y+11, 19343);
	ili9325_WritePixel(X+14, Y+11, 19343);
	ili9325_WritePixel(X+15, Y+11, 45056);
	ili9325_WritePixel(X+16, Y+11, 45056);
	ili9325_WritePixel(X+17, Y+11, 45056);
	ili9325_WritePixel(X+18, Y+11, 45056);
	ili9325_WritePixel(X+19, Y+11, 19343);

	ili9325_WritePixel(X+7, Y+12, 19343);
	ili9325_WritePixel(X+8, Y+12, 45056);
	ili9325_WritePixel(X+9, Y+12, 45056);
	ili9325_WritePixel(X+10, Y+12, 45056);
	ili9325_WritePixel(X+11, Y+12, 45056);
	ili9325_WritePixel(X+12, Y+12, 45056);
	ili9325_WritePixel(X+14, Y+12, 45056);
	ili9325_WritePixel(X+15, Y+12, 45056);
	ili9325_WritePixel(X+16, Y+12, 45056);
	ili9325_WritePixel(X+17, Y+12, 45056);
	ili9325_WritePixel(X+18, Y+12, 45056);
	ili9325_WritePixel(X+19, Y+12, 19343);

	ili9325_WritePixel(X+7, Y+13, 19343);
	ili9325_WritePixel(X+8, Y+13, 45056);
	ili9325_WritePixel(X+9, Y+13, 45056);
	ili9325_WritePixel(X+10, Y+13, 45056);
	ili9325_WritePixel(X+11, Y+13, 45056);
	ili9325_WritePixel(X+12, Y+13, 45056);
	ili9325_WritePixel(X+14, Y+13, 45056);
	ili9325_WritePixel(X+15, Y+13, 45056);
	ili9325_WritePixel(X+16, Y+13, 45056);
	ili9325_WritePixel(X+17, Y+13, 45056);
	ili9325_WritePixel(X+18, Y+13, 45056);
	ili9325_WritePixel(X+19, Y+13, 19343);

	ili9325_WritePixel(X+7, Y+14, 19343);
	ili9325_WritePixel(X+8, Y+14, 45056);
	ili9325_WritePixel(X+9, Y+14, 45056);
	ili9325_WritePixel(X+10, Y+14, 45056);
	ili9325_WritePixel(X+11, Y+14, 45056);
	ili9325_WritePixel(X+12, Y+14, 45056);
	ili9325_WritePixel(X+13, Y+14, 45056);
	ili9325_WritePixel(X+14, Y+14, 45056);
	ili9325_WritePixel(X+15, Y+14, 45056);
	ili9325_WritePixel(X+16, Y+14, 45056);
	ili9325_WritePixel(X+17, Y+14, 45056);
	ili9325_WritePixel(X+18, Y+14, 45056);
	ili9325_WritePixel(X+19, Y+14, 19343);

	ili9325_WritePixel(X+7, Y+15, 19343);
	ili9325_WritePixel(X+8, Y+15, 45056);
	ili9325_WritePixel(X+9, Y+15, 45056);
	ili9325_WritePixel(X+10, Y+15, 45056);
	ili9325_WritePixel(X+11, Y+15, 45056);
	ili9325_WritePixel(X+12, Y+15, 45056);
	ili9325_WritePixel(X+13, Y+15, 45056);
	ili9325_WritePixel(X+14, Y+15, 45056);
	ili9325_WritePixel(X+15, Y+15, 45056);
	ili9325_WritePixel(X+16, Y+15, 45056);
	ili9325_WritePixel(X+17, Y+15, 45056);
	ili9325_WritePixel(X+18, Y+15, 45056);
	ili9325_WritePixel(X+19, Y+15, 19343);

	ili9325_WritePixel(X+7, Y+16, 19343);
	ili9325_WritePixel(X+8, Y+16, 45056);
	ili9325_WritePixel(X+9, Y+16, 45056);
	ili9325_WritePixel(X+10, Y+16, 45056);
	ili9325_WritePixel(X+11, Y+16, 45056);
	ili9325_WritePixel(X+12, Y+16, 45056);
	ili9325_WritePixel(X+13, Y+16, 45056);
	ili9325_WritePixel(X+14, Y+16, 45056);
	ili9325_WritePixel(X+15, Y+16, 45056);
	ili9325_WritePixel(X+16, Y+16, 45056);
	ili9325_WritePixel(X+17, Y+16, 5186);
	ili9325_WritePixel(X+18, Y+16, 5186); //zielony
	ili9325_WritePixel(X+19, Y+16, 19343);

	ili9325_WritePixel(X+6, Y+17, 57021);
	ili9325_WritePixel(X+7, Y+17, 57021);
	ili9325_WritePixel(X+8, Y+17, 57021);
	ili9325_WritePixel(X+9, Y+17, 45056);
	ili9325_WritePixel(X+10, Y+17, 45056);
	ili9325_WritePixel(X+11, Y+17, 45056);
	ili9325_WritePixel(X+12, Y+17, 45056);
	ili9325_WritePixel(X+13, Y+17, 45056);
	ili9325_WritePixel(X+14, Y+17, 45056);
	ili9325_WritePixel(X+15, Y+17, 45056);
	ili9325_WritePixel(X+16, Y+17, 5186);
	ili9325_WritePixel(X+17, Y+17, 5186);
	ili9325_WritePixel(X+18, Y+17, 57021);
	ili9325_WritePixel(X+19, Y+17, 57021);
	ili9325_WritePixel(X+20, Y+17, 57021);

	ili9325_WritePixel(X+6, Y+18, 57021);
	ili9325_WritePixel(X+7, Y+18, 5186);
	ili9325_WritePixel(X+8, Y+18, 57021);
	ili9325_WritePixel(X+9, Y+18, 5186);
	ili9325_WritePixel(X+10, Y+18, 5186);
	ili9325_WritePixel(X+11, Y+18, 5186);
	ili9325_WritePixel(X+12, Y+18, 5186);
	ili9325_WritePixel(X+13, Y+18, 5186);
	ili9325_WritePixel(X+14, Y+18, 5186);
	ili9325_WritePixel(X+15, Y+18, 5186);
	ili9325_WritePixel(X+16, Y+18, 5186);
	ili9325_WritePixel(X+17, Y+18, 5186);
	ili9325_WritePixel(X+18, Y+18, 57021);
	ili9325_WritePixel(X+19, Y+18, 5186);
	ili9325_WritePixel(X+20, Y+18, 57021);

	ili9325_WritePixel(X+6, Y+19, 57021);
	ili9325_WritePixel(X+7, Y+19, 5186);
	ili9325_WritePixel(X+8, Y+19, 57021);
	ili9325_WritePixel(X+9, Y+19, 5186);
	ili9325_WritePixel(X+10, Y+19, 5186);
	ili9325_WritePixel(X+11, Y+19, 5186);
	ili9325_WritePixel(X+12, Y+19, 5186);
	ili9325_WritePixel(X+13, Y+19, 5186);
	ili9325_WritePixel(X+14, Y+19, 5186);
	ili9325_WritePixel(X+15, Y+19, 5186);
	ili9325_WritePixel(X+16, Y+19, 5186);
	ili9325_WritePixel(X+17, Y+19, 5186);
	ili9325_WritePixel(X+18, Y+19, 57021);
	ili9325_WritePixel(X+19, Y+19, 5186);
	ili9325_WritePixel(X+20, Y+19, 57021);

	ili9325_WritePixel(X+5, Y+20, 4930);
	ili9325_WritePixel(X+6, Y+20, 57021);
	ili9325_WritePixel(X+7, Y+20, 5186);
	ili9325_WritePixel(X+8, Y+20, 57021);
	ili9325_WritePixel(X+9, Y+20, 5186);
	ili9325_WritePixel(X+10, Y+20, 5186);
	ili9325_WritePixel(X+11, Y+20, 5186);
	ili9325_WritePixel(X+12, Y+20, 5186);
	ili9325_WritePixel(X+13, Y+20, 5186);
	ili9325_WritePixel(X+14, Y+20, 5186);
	ili9325_WritePixel(X+15, Y+20, 5186);
	ili9325_WritePixel(X+16, Y+20, 5186);
	ili9325_WritePixel(X+17, Y+20, 5186);
	ili9325_WritePixel(X+18, Y+20, 57021);
	ili9325_WritePixel(X+19, Y+20, 5186);
	ili9325_WritePixel(X+20, Y+20, 57021);
	ili9325_WritePixel(X+21, Y+20, 4930);

	ili9325_WritePixel(X+5, Y+21, 4930);
	ili9325_WritePixel(X+6, Y+21, 6765);
	ili9325_WritePixel(X+7, Y+21, 4930);
	ili9325_WritePixel(X+8, Y+21, 4930);
	ili9325_WritePixel(X+9, Y+21, 4930);
	ili9325_WritePixel(X+10, Y+21, 5186);
	ili9325_WritePixel(X+11, Y+21, 5186);
	ili9325_WritePixel(X+12, Y+21, 5186);
	ili9325_WritePixel(X+13, Y+21, 5186);
	ili9325_WritePixel(X+14, Y+21, 5186);
	ili9325_WritePixel(X+15, Y+21, 5186);
	ili9325_WritePixel(X+16, Y+21, 5186);
	ili9325_WritePixel(X+17, Y+21, 4930);
	ili9325_WritePixel(X+18, Y+21, 4930);
	ili9325_WritePixel(X+19, Y+21, 4930);
	ili9325_WritePixel(X+20, Y+21, 6765);
	ili9325_WritePixel(X+21, Y+21, 4930);

	ili9325_WritePixel(X+5, Y+22, 4930);
	ili9325_WritePixel(X+6, Y+22, 6765);
	ili9325_WritePixel(X+7, Y+22, 5186);
	ili9325_WritePixel(X+8, Y+22, 5186);
	ili9325_WritePixel(X+9, Y+22, 4930);
	ili9325_WritePixel(X+10, Y+22, 5186);
	ili9325_WritePixel(X+11, Y+22, 5186);
	ili9325_WritePixel(X+12, Y+22, 5186);
	ili9325_WritePixel(X+13, Y+22, 5186);
	ili9325_WritePixel(X+14, Y+22, 5186);
	ili9325_WritePixel(X+15, Y+22, 5186);
	ili9325_WritePixel(X+16, Y+22, 5186);
	ili9325_WritePixel(X+17, Y+22, 4930);
	ili9325_WritePixel(X+18, Y+22, 5186);
	ili9325_WritePixel(X+19, Y+22, 5186);
	ili9325_WritePixel(X+20, Y+22, 6765);
	ili9325_WritePixel(X+21, Y+22, 4930);

	ili9325_WritePixel(X+5, Y+23, 4930);
	ili9325_WritePixel(X+6, Y+23, 6765);
	ili9325_WritePixel(X+7, Y+23, 4930);
	ili9325_WritePixel(X+8, Y+23, 4930);
	ili9325_WritePixel(X+9, Y+23, 4930);
	ili9325_WritePixel(X+10, Y+23, 5186);
	ili9325_WritePixel(X+11, Y+23, 5186);
	ili9325_WritePixel(X+12, Y+23, 5186);
	ili9325_WritePixel(X+13, Y+23, 5186);
	ili9325_WritePixel(X+14, Y+23, 5186);
	ili9325_WritePixel(X+15, Y+23, 5186);
	ili9325_WritePixel(X+16, Y+23, 5186);
	ili9325_WritePixel(X+17, Y+23, 4930);
	ili9325_WritePixel(X+18, Y+23, 4930);
	ili9325_WritePixel(X+19, Y+23, 4930);
	ili9325_WritePixel(X+20, Y+23, 6765);
	ili9325_WritePixel(X+21, Y+23, 4930);

	ili9325_WritePixel(X+5, Y+24, 4930);
	ili9325_WritePixel(X+6, Y+24, 5186);
	ili9325_WritePixel(X+7, Y+24, 5186);
	ili9325_WritePixel(X+8, Y+24, 5186);
	ili9325_WritePixel(X+9, Y+24, 5186);
	ili9325_WritePixel(X+10, Y+24, 5186);
	ili9325_WritePixel(X+11, Y+24, 5186);
	ili9325_WritePixel(X+12, Y+24, 5186);
	ili9325_WritePixel(X+13, Y+24, 5186);
	ili9325_WritePixel(X+14, Y+24, 5186);
	ili9325_WritePixel(X+15, Y+24, 5186);
	ili9325_WritePixel(X+16, Y+24, 5186);
	ili9325_WritePixel(X+17, Y+24, 5186);
	ili9325_WritePixel(X+18, Y+24, 5186);
	ili9325_WritePixel(X+19, Y+24, 5186);
	ili9325_WritePixel(X+20, Y+24, 5186);
	ili9325_WritePixel(X+21, Y+24, 4930);

	ili9325_WritePixel(X+5, Y+25, 4930);
	ili9325_WritePixel(X+6, Y+25, 5186);
	ili9325_WritePixel(X+7, Y+25, 5186);
	ili9325_WritePixel(X+8, Y+25, 5186);
	ili9325_WritePixel(X+9, Y+25, 5186);
	ili9325_WritePixel(X+10, Y+25, 5186);
	ili9325_WritePixel(X+11, Y+25, 5186);
	ili9325_WritePixel(X+12, Y+25, 5186);
	ili9325_WritePixel(X+13, Y+25, 5186);
	ili9325_WritePixel(X+14, Y+25, 5186);
	ili9325_WritePixel(X+15, Y+25, 5186);
	ili9325_WritePixel(X+16, Y+25, 5186);
	ili9325_WritePixel(X+17, Y+25, 5186);
	ili9325_WritePixel(X+18, Y+25, 5186);
	ili9325_WritePixel(X+19, Y+25, 5186);
	ili9325_WritePixel(X+20, Y+25, 5186);
	ili9325_WritePixel(X+21, Y+25, 4930);

	ili9325_WritePixel(X+5, Y+26, 4930);
	ili9325_WritePixel(X+6, Y+26, 5186);
	ili9325_WritePixel(X+7, Y+26, 5186);
	ili9325_WritePixel(X+8, Y+26, 5186);
	ili9325_WritePixel(X+9, Y+26, 5186);
	ili9325_WritePixel(X+10, Y+26, 5186);
	ili9325_WritePixel(X+11, Y+26, 5186);
	ili9325_WritePixel(X+12, Y+26, 5186);
	ili9325_WritePixel(X+13, Y+26, 5186);
	ili9325_WritePixel(X+14, Y+26, 5186);
	ili9325_WritePixel(X+15, Y+26, 5186);
	ili9325_WritePixel(X+16, Y+26, 5186);
	ili9325_WritePixel(X+17, Y+26, 5186);
	ili9325_WritePixel(X+18, Y+26, 5186);
	ili9325_WritePixel(X+19, Y+26, 5186);
	ili9325_WritePixel(X+20, Y+26, 5186);
	ili9325_WritePixel(X+21, Y+26, 4930);

	ili9325_WritePixel(X+5, Y+27, 4930);
	ili9325_WritePixel(X+6, Y+27, 5186);
	ili9325_WritePixel(X+7, Y+27, 5186);
	ili9325_WritePixel(X+8, Y+27, 5186);
	ili9325_WritePixel(X+9, Y+27, 5186);
	ili9325_WritePixel(X+10, Y+27, 5186);
	ili9325_WritePixel(X+11, Y+27, 5186);
	ili9325_WritePixel(X+12, Y+27, 5186);
	ili9325_WritePixel(X+13, Y+27, 5186);
	ili9325_WritePixel(X+14, Y+27, 5186);
	ili9325_WritePixel(X+15, Y+27, 5186);
	ili9325_WritePixel(X+16, Y+27, 5186);
	ili9325_WritePixel(X+17, Y+27, 5186);
	ili9325_WritePixel(X+18, Y+27, 5186);
	ili9325_WritePixel(X+19, Y+27, 5186);
	ili9325_WritePixel(X+20, Y+27, 5186);
	ili9325_WritePixel(X+21, Y+27, 4930);

	ili9325_WritePixel(X+3, Y+28, 6765);
	ili9325_WritePixel(X+4, Y+28, 6765);
	ili9325_WritePixel(X+6, Y+28, 4930);
	ili9325_WritePixel(X+7, Y+28, 4930);
	ili9325_WritePixel(X+8, Y+28, 4930);
	ili9325_WritePixel(X+9, Y+28, 5186);
	ili9325_WritePixel(X+10, Y+28, 5186);
	ili9325_WritePixel(X+11, Y+28, 5186);
	ili9325_WritePixel(X+12, Y+28, 5186);
	ili9325_WritePixel(X+13, Y+28, 5186);
	ili9325_WritePixel(X+14, Y+28, 5186);
	ili9325_WritePixel(X+15, Y+28, 5186);
	ili9325_WritePixel(X+16, Y+28, 5186);
	ili9325_WritePixel(X+17, Y+28, 5186);
	ili9325_WritePixel(X+18, Y+28, 5186);
	ili9325_WritePixel(X+19, Y+28, 5186);
	ili9325_WritePixel(X+20, Y+28, 4930);
	ili9325_WritePixel(X+21, Y+28, 4930);
	ili9325_WritePixel(X+22, Y+28, 4930);
	ili9325_WritePixel(X+23, Y+28, 6765);
	ili9325_WritePixel(X+24, Y+28, 6765);

	ili9325_WritePixel(X+3, Y+29, 6765);
	ili9325_WritePixel(X+4, Y+29, 6765);
	ili9325_WritePixel(X+8, Y+29, 4930);
	ili9325_WritePixel(X+9, Y+29, 5186);
	ili9325_WritePixel(X+10, Y+29, 5186);
	ili9325_WritePixel(X+11, Y+29, 45056);	//czerwony
	ili9325_WritePixel(X+12, Y+29, 45056);
	ili9325_WritePixel(X+13, Y+29, 45056);
	ili9325_WritePixel(X+14, Y+29, 57021);
	ili9325_WritePixel(X+15, Y+29, 45056);
	ili9325_WritePixel(X+16, Y+29, 45056);
	ili9325_WritePixel(X+17, Y+29, 57021);
	ili9325_WritePixel(X+18, Y+29, 4930);
	ili9325_WritePixel(X+22, Y+29, 6765);
	ili9325_WritePixel(X+23, Y+29, 6765);

	ili9325_WritePixel(X+3, Y+30, 6765);
	ili9325_WritePixel(X+4, Y+30, 6765);
	ili9325_WritePixel(X+8, Y+30, 45056);
	ili9325_WritePixel(X+9, Y+30, 45056);
	ili9325_WritePixel(X+10, Y+30, 45056);
	ili9325_WritePixel(X+11, Y+30, 45056);
	ili9325_WritePixel(X+12, Y+30, 45056);
	ili9325_WritePixel(X+13, Y+30, 57021);	//szary
	ili9325_WritePixel(X+14, Y+30, 45056);
	ili9325_WritePixel(X+15, Y+30, 45056);
	ili9325_WritePixel(X+16, Y+30, 57021);
	ili9325_WritePixel(X+17, Y+30, 57021);
	ili9325_WritePixel(X+18, Y+30, 45056);
	ili9325_WritePixel(X+19, Y+30, 45056);
	ili9325_WritePixel(X+22, Y+30, 6765);
	ili9325_WritePixel(X+23, Y+30, 6765);

	ili9325_WritePixel(X+2, Y+31, 6765);
	ili9325_WritePixel(X+3, Y+31, 6765);
	ili9325_WritePixel(X+9, Y+31, 45056);
	ili9325_WritePixel(X+10, Y+31, 45056);
	ili9325_WritePixel(X+11, Y+31, 45056);
	ili9325_WritePixel(X+12, Y+31, 57021);
	ili9325_WritePixel(X+13, Y+31, 45056);
	ili9325_WritePixel(X+14, Y+31, 45056);
	ili9325_WritePixel(X+15, Y+31, 57021);
	ili9325_WritePixel(X+16, Y+31, 57021);
	ili9325_WritePixel(X+17, Y+31, 45056);
	ili9325_WritePixel(X+18, Y+31, 45056);
	ili9325_WritePixel(X+19, Y+31, 57021);
	ili9325_WritePixel(X+20, Y+31, 45056);
	ili9325_WritePixel(X+23, Y+31, 6765);
	ili9325_WritePixel(X+24, Y+31, 6765);

	ili9325_WritePixel(X+2, Y+32, 6765);
	ili9325_WritePixel(X+3, Y+32, 6765);
	ili9325_WritePixel(X+9, Y+32, 65077);
	ili9325_WritePixel(X+10, Y+32, 65077);
	ili9325_WritePixel(X+11, Y+32, 65077);
	ili9325_WritePixel(X+12, Y+32, 57021);
	ili9325_WritePixel(X+13, Y+32, 65077);
	ili9325_WritePixel(X+14, Y+32, 65077);
	ili9325_WritePixel(X+15, Y+32, 57021);
	ili9325_WritePixel(X+16, Y+32, 65077);
	ili9325_WritePixel(X+17, Y+32, 45056);
	ili9325_WritePixel(X+18, Y+32, 57021);
	ili9325_WritePixel(X+19, Y+32, 45056);
	ili9325_WritePixel(X+20, Y+32, 45056);
	ili9325_WritePixel(X+23, Y+32, 6765);
	ili9325_WritePixel(X+24, Y+32, 6765);

	ili9325_WritePixel(X+2, Y+33, 6765);
	ili9325_WritePixel(X+3, Y+33, 6765);
	ili9325_WritePixel(X+9, Y+33, 65077);
	ili9325_WritePixel(X+10, Y+33, 65077);
	ili9325_WritePixel(X+11, Y+33, 65077);
	ili9325_WritePixel(X+12, Y+33, 65077);
	ili9325_WritePixel(X+13, Y+33, 65077);
	ili9325_WritePixel(X+14, Y+33, 65077);
	ili9325_WritePixel(X+15, Y+33, 65077);
	ili9325_WritePixel(X+16, Y+33, 65077);
	ili9325_WritePixel(X+17, Y+33, 65077);
	ili9325_WritePixel(X+18, Y+33, 57021);
	ili9325_WritePixel(X+19, Y+33, 45056);
	ili9325_WritePixel(X+20, Y+33, 57021);
	ili9325_WritePixel(X+21, Y+33, 45056);
	ili9325_WritePixel(X+23, Y+33, 6765);
	ili9325_WritePixel(X+34, Y+33, 6765);

	ili9325_WritePixel(X+1, Y+34, 6765);
	ili9325_WritePixel(X+9, Y+34, 65077);
	ili9325_WritePixel(X+10, Y+34, 65077);
	ili9325_WritePixel(X+11, Y+34, 6765);
	ili9325_WritePixel(X+12, Y+34, 6765);
	ili9325_WritePixel(X+13, Y+34, 65077);
	ili9325_WritePixel(X+14, Y+34, 6765);
	ili9325_WritePixel(X+15, Y+34, 6765);
	ili9325_WritePixel(X+16, Y+34, 65077);
	ili9325_WritePixel(X+17, Y+34, 65077);
	ili9325_WritePixel(X+18, Y+34, 57021);
	ili9325_WritePixel(X+19, Y+34, 45056);
	ili9325_WritePixel(X+20, Y+34, 57021);
	ili9325_WritePixel(X+21, Y+34, 45056);
	ili9325_WritePixel(X+25, Y+34, 6765);

	ili9325_WritePixel(X+1, Y+35, 6765);
	ili9325_WritePixel(X+9, Y+35, 65077);
	ili9325_WritePixel(X+10, Y+35, 65077);
	ili9325_WritePixel(X+11, Y+35, 6765);
	ili9325_WritePixel(X+12, Y+35, 6765);
	ili9325_WritePixel(X+13, Y+35, 65077);
	ili9325_WritePixel(X+14, Y+35, 6765);
	ili9325_WritePixel(X+15, Y+35, 6765);
	ili9325_WritePixel(X+16, Y+35, 65077);
	ili9325_WritePixel(X+17, Y+35, 65077);
	ili9325_WritePixel(X+20, Y+35, 57021);
	ili9325_WritePixel(X+25, Y+35, 6765);

	ili9325_WritePixel(X+1, Y+36, 6765);
	ili9325_WritePixel(X+9, Y+36, 65077);
	ili9325_WritePixel(X+10, Y+36, 65077);
	ili9325_WritePixel(X+11, Y+36, 6765);
	ili9325_WritePixel(X+12, Y+36, 6765);
	ili9325_WritePixel(X+13, Y+36, 6765);
	ili9325_WritePixel(X+14, Y+36, 6765);
	ili9325_WritePixel(X+15, Y+36, 6765);
	ili9325_WritePixel(X+16, Y+36, 45056);
	ili9325_WritePixel(X+17, Y+36, 45056);
	ili9325_WritePixel(X+25, Y+36, 6765);

	ili9325_WritePixel(X+1, Y+37, 6765);
	ili9325_WritePixel(X+9, Y+37, 45056);
	ili9325_WritePixel(X+10, Y+37, 45056);
	ili9325_WritePixel(X+11, Y+37, 57021);
	ili9325_WritePixel(X+12, Y+37, 57021);
	ili9325_WritePixel(X+13, Y+37, 57021);
	ili9325_WritePixel(X+14, Y+37, 57021);
	ili9325_WritePixel(X+15, Y+37, 45056);
	ili9325_WritePixel(X+16, Y+37, 45056);
	ili9325_WritePixel(X+17, Y+37, 57021);
	ili9325_WritePixel(X+25, Y+37, 6765);

	ili9325_WritePixel(X+1, Y+38, 6765);
	ili9325_WritePixel(X+9, Y+38, 45056);
	ili9325_WritePixel(X+10, Y+38, 45056);
	ili9325_WritePixel(X+11, Y+38, 45056);
	ili9325_WritePixel(X+12, Y+38, 45056);
	ili9325_WritePixel(X+13, Y+38, 45056);
	ili9325_WritePixel(X+14, Y+38, 45056);
	ili9325_WritePixel(X+15, Y+38, 57021);
	ili9325_WritePixel(X+16, Y+38, 57021);
	ili9325_WritePixel(X+17, Y+38, 57021);
	ili9325_WritePixel(X+25, Y+38, 6765);

	ili9325_WritePixel(X+1, Y+39, 6765);
	ili9325_WritePixel(X+10, Y+39, 57021);
	ili9325_WritePixel(X+11, Y+39, 57021);
	ili9325_WritePixel(X+12, Y+39, 57021);
	ili9325_WritePixel(X+13, Y+39, 57021);
	ili9325_WritePixel(X+14, Y+39, 57021);
	ili9325_WritePixel(X+15, Y+39, 45056);
	ili9325_WritePixel(X+16, Y+39, 45056);
	ili9325_WritePixel(X+17, Y+39, 45056);
	ili9325_WritePixel(X+25, Y+39, 6765);

	ili9325_WritePixel(X+11, Y+40, 45056);
	ili9325_WritePixel(X+12, Y+40, 45056);
	ili9325_WritePixel(X+13, Y+40, 45056);
	ili9325_WritePixel(X+14, Y+40, 45056);
	ili9325_WritePixel(X+15, Y+40, 45056);
	ili9325_WritePixel(X+16, Y+40, 45056);
	ili9325_WritePixel(X+17, Y+40, 57021);
	ili9325_WritePixel(X+18, Y+40, 57021);

	ili9325_WritePixel(X+12, Y+41, 57021);
	ili9325_WritePixel(X+13, Y+41, 57021);
	ili9325_WritePixel(X+14, Y+41, 57021);
	ili9325_WritePixel(X+15, Y+41, 57021);
	ili9325_WritePixel(X+16, Y+41, 57021);
	ili9325_WritePixel(X+17, Y+41, 45056);
	ili9325_WritePixel(X+18, Y+41, 45056);

	ili9325_WritePixel(X+13, Y+42, 45056);
	ili9325_WritePixel(X+14, Y+42, 45056);
	ili9325_WritePixel(X+15, Y+42, 45056);
	ili9325_WritePixel(X+16, Y+42, 45056);
	ili9325_WritePixel(X+17, Y+42, 45056);
	ili9325_WritePixel(X+18, Y+42, 57021);
	ili9325_WritePixel(X+19, Y+42, 57021);

	ili9325_WritePixel(X+14, Y+43, 57021);
	ili9325_WritePixel(X+15, Y+43, 45056);
	ili9325_WritePixel(X+16, Y+43, 45056);
	ili9325_WritePixel(X+17, Y+43, 57021);
	ili9325_WritePixel(X+18, Y+43, 57021);
	ili9325_WritePixel(X+19, Y+43, 57021);

	ili9325_WritePixel(X+16, Y+44, 57021);
	ili9325_WritePixel(X+17, Y+44, 57021);
	ili9325_WritePixel(X+18, Y+44, 57021);
	ili9325_WritePixel(X+19, Y+44, 57021);
}
//--- SetSkierLeft --- DONE
void SetSkierLeft(uint16_t X, uint16_t Y)
{
	ili9325_WritePixel(X+7, Y+1, 19343);
	ili9325_WritePixel(X+8, Y+1, 19343);
	ili9325_WritePixel(X+9, Y+1, 19343);

	ili9325_WritePixel(X+7, Y+2, 19343);
	ili9325_WritePixel(X+8, Y+2, 19343);
	ili9325_WritePixel(X+9, Y+2, 19343);
	ili9325_WritePixel(X+10, Y+2, 19343);

	ili9325_WritePixel(X+1, Y+3, 19343);
	ili9325_WritePixel(X+2, Y+3, 19343);
	ili9325_WritePixel(X+3, Y+3, 19343);
	ili9325_WritePixel(X+7, Y+3, 19343);
	ili9325_WritePixel(X+9, Y+3, 19343);
	ili9325_WritePixel(X+10, Y+3, 19343);
	ili9325_WritePixel(X+11, Y+3, 19343);

	ili9325_WritePixel(X+1, Y+4, 19343);
	ili9325_WritePixel(X+2, Y+4, 19343);
	ili9325_WritePixel(X+3, Y+4, 19343);
	ili9325_WritePixel(X+4, Y+4, 19343);
	ili9325_WritePixel(X+10, Y+4, 19343);
	ili9325_WritePixel(X+11, Y+4, 19343);
	ili9325_WritePixel(X+12, Y+4, 19343);

	ili9325_WritePixel(X+1, Y+5, 19343);
	ili9325_WritePixel(X+3, Y+5, 19343);
	ili9325_WritePixel(X+4, Y+5, 19343);
	ili9325_WritePixel(X+5, Y+5, 19343);
	ili9325_WritePixel(X+11, Y+5, 19343);
	ili9325_WritePixel(X+12, Y+5, 19343);
	ili9325_WritePixel(X+13, Y+5, 19343);

	ili9325_WritePixel(X+4, Y+6, 19343);
	ili9325_WritePixel(X+5, Y+6, 19343);
	ili9325_WritePixel(X+6, Y+6, 19343);
	ili9325_WritePixel(X+12, Y+6, 19343);
	ili9325_WritePixel(X+13, Y+6, 19343);
	ili9325_WritePixel(X+14, Y+6, 19343);

	ili9325_WritePixel(X+5, Y+7, 19343);
	ili9325_WritePixel(X+6, Y+7, 19343);
	ili9325_WritePixel(X+7, Y+7, 19343);
	ili9325_WritePixel(X+13, Y+7, 19343);
	ili9325_WritePixel(X+14, Y+7, 19343);
	ili9325_WritePixel(X+15, Y+7, 19343);

	ili9325_WritePixel(X+6, Y+8, 19343);
	ili9325_WritePixel(X+7, Y+8, 19343);
	ili9325_WritePixel(X+8, Y+8, 19343);
	ili9325_WritePixel(X+14, Y+8, 19343);
	ili9325_WritePixel(X+15, Y+8, 19343);
	ili9325_WritePixel(X+16, Y+8, 19343);

	ili9325_WritePixel(X+7, Y+9, 19343);
	ili9325_WritePixel(X+8, Y+9, 19343);
	ili9325_WritePixel(X+9, Y+9, 19343);
	ili9325_WritePixel(X+14, Y+9, 50712);
	ili9325_WritePixel(X+15, Y+9, 50712);
	ili9325_WritePixel(X+16, Y+9, 50712);
	ili9325_WritePixel(X+17, Y+9, 50712);

	ili9325_WritePixel(X+7, Y+10, 50712);
	ili9325_WritePixel(X+8, Y+10, 50712);
	ili9325_WritePixel(X+9, Y+10, 50712);
	ili9325_WritePixel(X+10, Y+10, 50712);
	ili9325_WritePixel(X+14, Y+10, 50712);
	ili9325_WritePixel(X+15, Y+10, 50712);
	ili9325_WritePixel(X+16, Y+10, 50712);
	ili9325_WritePixel(X+17, Y+10, 50712);
	ili9325_WritePixel(X+18, Y+10, 19343);

	ili9325_WritePixel(X+7, Y+11, 50712);
	ili9325_WritePixel(X+8, Y+11, 50712);
	ili9325_WritePixel(X+9, Y+11, 50712);
	ili9325_WritePixel(X+10, Y+11, 50712);	//szary
	ili9325_WritePixel(X+11, Y+11, 19343);	//niebieski
	ili9325_WritePixel(X+14, Y+11, 45056);	//czerwony
	ili9325_WritePixel(X+15, Y+11, 45056);
	ili9325_WritePixel(X+16, Y+11, 45056);
	ili9325_WritePixel(X+17, Y+11, 45056);
	ili9325_WritePixel(X+18, Y+11, 19343);
	ili9325_WritePixel(X+19, Y+11, 19343);

	ili9325_WritePixel(X+7, Y+12, 45056);
	ili9325_WritePixel(X+8, Y+12, 45056);
	ili9325_WritePixel(X+9, Y+12, 45056);
	ili9325_WritePixel(X+10, Y+12, 45056);
	ili9325_WritePixel(X+11, Y+12, 19343);
	ili9325_WritePixel(X+12, Y+12, 19343);
	ili9325_WritePixel(X+14, Y+12, 45056);
	ili9325_WritePixel(X+15, Y+12, 45056);
	ili9325_WritePixel(X+16, Y+12, 45056);
	ili9325_WritePixel(X+17, Y+12, 45056);
	ili9325_WritePixel(X+18, Y+12, 19343);
	ili9325_WritePixel(X+19, Y+12, 19343);
	ili9325_WritePixel(X+20, Y+12, 19343);

	ili9325_WritePixel(X+7, Y+13, 45056);
	ili9325_WritePixel(X+8, Y+13, 45056);
	ili9325_WritePixel(X+9, Y+13, 45056);
	ili9325_WritePixel(X+10, Y+13, 45056);
	ili9325_WritePixel(X+11, Y+13, 19343);
	ili9325_WritePixel(X+12, Y+13, 19343);
	ili9325_WritePixel(X+13, Y+13, 19343);
	ili9325_WritePixel(X+14, Y+13, 45056);
	ili9325_WritePixel(X+15, Y+13, 45056);
	ili9325_WritePixel(X+16, Y+13, 45056);
	ili9325_WritePixel(X+17, Y+13, 45056);
	ili9325_WritePixel(X+19, Y+13, 19343);
	ili9325_WritePixel(X+20, Y+13, 19343);
	ili9325_WritePixel(X+21, Y+13, 19343);

	ili9325_WritePixel(X+7, Y+14, 45056);
	ili9325_WritePixel(X+8, Y+14, 45056);
	ili9325_WritePixel(X+9, Y+14, 45056);
	ili9325_WritePixel(X+10, Y+14, 45056);
	ili9325_WritePixel(X+12, Y+14, 19343);
	ili9325_WritePixel(X+13, Y+14, 19343);
	ili9325_WritePixel(X+14, Y+14, 45056);
	ili9325_WritePixel(X+15, Y+14, 45056);
	ili9325_WritePixel(X+16, Y+14, 45056);
	ili9325_WritePixel(X+17, Y+14, 45056);
	ili9325_WritePixel(X+20, Y+14, 19343);
	ili9325_WritePixel(X+21, Y+14, 19343);
	ili9325_WritePixel(X+22, Y+14, 19343);

	ili9325_WritePixel(X+7, Y+15, 45056);
	ili9325_WritePixel(X+8, Y+15, 45056);
	ili9325_WritePixel(X+9, Y+15, 45056);
	ili9325_WritePixel(X+10, Y+15, 45056);
	ili9325_WritePixel(X+13, Y+15, 19343);
	ili9325_WritePixel(X+14, Y+15, 45056);
	ili9325_WritePixel(X+15, Y+15, 45056);
	ili9325_WritePixel(X+16, Y+15, 45056);
	ili9325_WritePixel(X+17, Y+15, 45056);
	ili9325_WritePixel(X+21, Y+15, 19343);
	ili9325_WritePixel(X+22, Y+15, 19343);

	ili9325_WritePixel(X+7, Y+16, 45056);
	ili9325_WritePixel(X+8, Y+16, 45056);
	ili9325_WritePixel(X+9, Y+16, 45056);
	ili9325_WritePixel(X+10, Y+16, 45056);
	ili9325_WritePixel(X+14, Y+16, 45056);
	ili9325_WritePixel(X+15, Y+16, 45056);
	ili9325_WritePixel(X+16, Y+16, 45056);
	ili9325_WritePixel(X+17, Y+16, 45056);

	ili9325_WritePixel(X+7, Y+17, 45056);
	ili9325_WritePixel(X+8, Y+17, 45056);
	ili9325_WritePixel(X+9, Y+17, 45056);
	ili9325_WritePixel(X+10, Y+17, 45056);
	ili9325_WritePixel(X+14, Y+17, 45056);
	ili9325_WritePixel(X+15, Y+17, 45056);
	ili9325_WritePixel(X+16, Y+17, 45056);
	ili9325_WritePixel(X+17, Y+17, 45056);

	ili9325_WritePixel(X+7, Y+18, 45056);
	ili9325_WritePixel(X+8, Y+18, 45056);
	ili9325_WritePixel(X+9, Y+18, 45056);
	ili9325_WritePixel(X+10, Y+18, 45056);
	ili9325_WritePixel(X+13, Y+18, 5186);
	ili9325_WritePixel(X+14, Y+18, 5186);
	ili9325_WritePixel(X+15, Y+18, 5186);
	ili9325_WritePixel(X+16, Y+18, 5186);
	ili9325_WritePixel(X+17, Y+18, 5186); //zielony

	ili9325_WritePixel(X+7, Y+19, 45056);
	ili9325_WritePixel(X+8, Y+19, 45056);
	ili9325_WritePixel(X+9, Y+19, 5186);
	ili9325_WritePixel(X+10, Y+19, 5186);
	ili9325_WritePixel(X+11, Y+19, 5186);
	ili9325_WritePixel(X+12, Y+19, 5186);
	ili9325_WritePixel(X+13, Y+19, 5186);
	ili9325_WritePixel(X+14, Y+19, 5186);
	ili9325_WritePixel(X+15, Y+19, 5186);
	ili9325_WritePixel(X+16, Y+19, 5186);
	ili9325_WritePixel(X+17, Y+19, 5186);

	ili9325_WritePixel(X+7, Y+20, 5186);
	ili9325_WritePixel(X+8, Y+20, 5186);
	ili9325_WritePixel(X+9, Y+20, 5186);
	ili9325_WritePixel(X+10, Y+20, 5186);
	ili9325_WritePixel(X+11, Y+20, 5186);
	ili9325_WritePixel(X+12, Y+20, 5186);
	ili9325_WritePixel(X+13, Y+20, 5186);
	ili9325_WritePixel(X+14, Y+20, 5186);
	ili9325_WritePixel(X+15, Y+20, 5186);
	ili9325_WritePixel(X+16, Y+20, 5186);
	ili9325_WritePixel(X+17, Y+20, 5186);

	ili9325_WritePixel(X+7, Y+21, 5186);
	ili9325_WritePixel(X+8, Y+21, 5186);
	ili9325_WritePixel(X+9, Y+21, 5186);
	ili9325_WritePixel(X+10, Y+21, 5186);
	ili9325_WritePixel(X+11, Y+21, 5186);
	ili9325_WritePixel(X+12, Y+21, 5186);
	ili9325_WritePixel(X+13, Y+21, 5186);
	ili9325_WritePixel(X+14, Y+21, 5186);
	ili9325_WritePixel(X+15, Y+21, 5186);
	ili9325_WritePixel(X+16, Y+21, 5186);
	ili9325_WritePixel(X+17, Y+21, 5186);

	ili9325_WritePixel(X+7, Y+22, 5186);
	ili9325_WritePixel(X+8, Y+22, 5186);
	ili9325_WritePixel(X+9, Y+22, 5186);
	ili9325_WritePixel(X+10, Y+22, 5186);
	ili9325_WritePixel(X+11, Y+22, 5186);
	ili9325_WritePixel(X+12, Y+22, 5186);
	ili9325_WritePixel(X+13, Y+22, 5186);
	ili9325_WritePixel(X+14, Y+22, 5186);
	ili9325_WritePixel(X+15, Y+22, 5186);
	ili9325_WritePixel(X+16, Y+22, 5186);
	ili9325_WritePixel(X+17, Y+22, 5186);

	ili9325_WritePixel(X+7, Y+23, 5186);
	ili9325_WritePixel(X+8, Y+23, 5186);
	ili9325_WritePixel(X+9, Y+23, 5186);
	ili9325_WritePixel(X+10, Y+23, 5186);
	ili9325_WritePixel(X+11, Y+23, 5186);
	ili9325_WritePixel(X+12, Y+23, 5186);
	ili9325_WritePixel(X+13, Y+23, 50712);
	ili9325_WritePixel(X+14, Y+23, 50712);
	ili9325_WritePixel(X+15, Y+23, 19343);
	ili9325_WritePixel(X+16, Y+23, 5186);
	ili9325_WritePixel(X+17, Y+23, 5186);

	ili9325_WritePixel(X+7, Y+24, 5186);
	ili9325_WritePixel(X+8, Y+24, 5186);
	ili9325_WritePixel(X+9, Y+24, 5186);
	ili9325_WritePixel(X+10, Y+24, 5186);
	ili9325_WritePixel(X+11, Y+24, 5186);
	ili9325_WritePixel(X+12, Y+24, 5186);
	ili9325_WritePixel(X+13, Y+24, 50712);
	ili9325_WritePixel(X+14, Y+24, 5186);
	ili9325_WritePixel(X+15, Y+24, 19343);
	ili9325_WritePixel(X+16, Y+24, 5186);
	ili9325_WritePixel(X+16, Y+24, 5186);

	ili9325_WritePixel(X+7, Y+25, 5186);
	ili9325_WritePixel(X+8, Y+25, 5186);
	ili9325_WritePixel(X+9, Y+25, 5186);
	ili9325_WritePixel(X+10, Y+25, 5186);
	ili9325_WritePixel(X+11, Y+25, 5186);
	ili9325_WritePixel(X+12, Y+25, 5186);
	ili9325_WritePixel(X+13, Y+25, 50712);
	ili9325_WritePixel(X+14, Y+25, 5186);
	ili9325_WritePixel(X+15, Y+25, 19343);
	ili9325_WritePixel(X+16, Y+25, 19343);
	ili9325_WritePixel(X+17, Y+25, 19343);

	ili9325_WritePixel(X+7, Y+26, 5186);
	ili9325_WritePixel(X+8, Y+26, 5186);
	ili9325_WritePixel(X+9, Y+26, 5186);
	ili9325_WritePixel(X+10, Y+26, 5186);
	ili9325_WritePixel(X+11, Y+26, 5186);
	ili9325_WritePixel(X+12, Y+26, 5186);
	ili9325_WritePixel(X+13, Y+26, 3008);
	ili9325_WritePixel(X+14, Y+26, 5186);
	ili9325_WritePixel(X+15, Y+26, 3008);
	ili9325_WritePixel(X+16, Y+26, 19343);
	ili9325_WritePixel(X+17, Y+26, 19343);

	ili9325_WritePixel(X+7, Y+27, 5186);
	ili9325_WritePixel(X+8, Y+27, 5186);
	ili9325_WritePixel(X+9, Y+27, 5186);
	ili9325_WritePixel(X+10, Y+27, 5186);
	ili9325_WritePixel(X+11, Y+27, 5186);
	ili9325_WritePixel(X+12, Y+27, 5186);
	ili9325_WritePixel(X+13, Y+27, 3008);
	ili9325_WritePixel(X+14, Y+27, 5186);
	ili9325_WritePixel(X+15, Y+27, 3008);
	ili9325_WritePixel(X+16, Y+27, 19343);
	ili9325_WritePixel(X+17, Y+27, 19343);
	ili9325_WritePixel(X+18, Y+27, 19343);
	ili9325_WritePixel(X+19, Y+27, 19343);

	ili9325_WritePixel(X+7, Y+28, 5186);
	ili9325_WritePixel(X+8, Y+28, 5186);
	ili9325_WritePixel(X+9, Y+28, 5186);
	ili9325_WritePixel(X+10, Y+28, 5186);
	ili9325_WritePixel(X+11, Y+28, 5186);
	ili9325_WritePixel(X+12, Y+28, 5186);
	ili9325_WritePixel(X+13, Y+28, 3008);
	ili9325_WritePixel(X+14, Y+28, 5186);
	ili9325_WritePixel(X+15, Y+28, 3008);
	ili9325_WritePixel(X+16, Y+28, 5186);
	ili9325_WritePixel(X+17, Y+28, 5186);
	ili9325_WritePixel(X+18, Y+28, 19343);
	ili9325_WritePixel(X+19, Y+28, 19343);

	ili9325_WritePixel(X+7, Y+29, 5186);
	ili9325_WritePixel(X+8, Y+29, 5186);
	ili9325_WritePixel(X+9, Y+29, 5186);
	ili9325_WritePixel(X+10, Y+29, 5186);
	ili9325_WritePixel(X+11, Y+29, 5186);
	ili9325_WritePixel(X+12, Y+29, 5186);
	ili9325_WritePixel(X+13, Y+29, 3008);
	ili9325_WritePixel(X+14, Y+29, 3008);
	ili9325_WritePixel(X+15, Y+29, 3008);
	ili9325_WritePixel(X+16, Y+29, 5186);
	ili9325_WritePixel(X+17, Y+29, 5186);
	ili9325_WritePixel(X+18, Y+29, 19343);
	ili9325_WritePixel(X+19, Y+29, 19343);
	ili9325_WritePixel(X+20, Y+29, 19343);

	ili9325_WritePixel(X+7, Y+30, 5186);
	ili9325_WritePixel(X+8, Y+30, 5186);
	ili9325_WritePixel(X+9, Y+30, 5186);
	ili9325_WritePixel(X+10, Y+30, 5186);
	ili9325_WritePixel(X+11, Y+30, 5186);
	ili9325_WritePixel(X+12, Y+30, 5186);
	ili9325_WritePixel(X+13, Y+30, 5186);
	ili9325_WritePixel(X+14, Y+30, 5186);
	ili9325_WritePixel(X+15, Y+30, 5186);
	ili9325_WritePixel(X+16, Y+30, 5186);
	ili9325_WritePixel(X+17, Y+30, 5186);
	ili9325_WritePixel(X+20, Y+30, 19343);
	ili9325_WritePixel(X+21, Y+30, 19343);

	ili9325_WritePixel(X+8, Y+31, 5186);
	ili9325_WritePixel(X+9, Y+31, 5186);
	ili9325_WritePixel(X+10, Y+31, 45056);
	ili9325_WritePixel(X+11, Y+31, 45056);
	ili9325_WritePixel(X+12, Y+31, 45056);
	ili9325_WritePixel(X+13, Y+31, 50712);
	ili9325_WritePixel(X+14, Y+31, 45056);
	ili9325_WritePixel(X+15, Y+31, 45056);
	ili9325_WritePixel(X+16, Y+31, 45056);
	ili9325_WritePixel(X+17, Y+31, 50712);
	ili9325_WritePixel(X+21, Y+31, 19343);
	ili9325_WritePixel(X+22, Y+31, 19343);

	ili9325_WritePixel(X+9, Y+32, 45056);
	ili9325_WritePixel(X+10, Y+32, 45056);
	ili9325_WritePixel(X+11, Y+32, 45056);
	ili9325_WritePixel(X+12, Y+32, 50712);
	ili9325_WritePixel(X+13, Y+32, 45056);
	ili9325_WritePixel(X+14, Y+32, 45056);
	ili9325_WritePixel(X+15, Y+32, 50712);
	ili9325_WritePixel(X+16, Y+32, 50712);
	ili9325_WritePixel(X+17, Y+32, 45056);
	ili9325_WritePixel(X+18, Y+32, 50712);
	ili9325_WritePixel(X+22, Y+32, 19343);
	ili9325_WritePixel(X+23, Y+32, 19343);

	ili9325_WritePixel(X+9, Y+33, 50712);
	ili9325_WritePixel(X+10, Y+33, 50712);
	ili9325_WritePixel(X+11, Y+33, 50712);
	ili9325_WritePixel(X+12, Y+33, 45056);
	ili9325_WritePixel(X+13, Y+33, 45056);
	ili9325_WritePixel(X+14, Y+33, 50712);
	ili9325_WritePixel(X+15, Y+33, 50712);
	ili9325_WritePixel(X+16, Y+33, 45056);
	ili9325_WritePixel(X+17, Y+33, 50712);
	ili9325_WritePixel(X+18, Y+33, 50712);
	ili9325_WritePixel(X+19, Y+33, 50712);
	ili9325_WritePixel(X+23, Y+33, 19343);

	ili9325_WritePixel(X+10, Y+34, 65077);
	ili9325_WritePixel(X+11, Y+34, 65077);
	ili9325_WritePixel(X+12, Y+34, 65077);
	ili9325_WritePixel(X+13, Y+34, 65077);
	ili9325_WritePixel(X+14, Y+34, 65077);
	ili9325_WritePixel(X+15, Y+34, 45056);
	ili9325_WritePixel(X+16, Y+34, 50712);
	ili9325_WritePixel(X+17, Y+34, 50712);
	ili9325_WritePixel(X+18, Y+34, 45056);
	ili9325_WritePixel(X+19, Y+34, 45056);
	ili9325_WritePixel(X+20, Y+34, 50712);
	ili9325_WritePixel(X+23, Y+34, 19343);

	ili9325_WritePixel(X+10, Y+35, 65077);
	ili9325_WritePixel(X+11, Y+35, 65077);
	ili9325_WritePixel(X+12, Y+35, 65077);
	ili9325_WritePixel(X+13, Y+35, 65077);
	ili9325_WritePixel(X+14, Y+35, 65077);
	ili9325_WritePixel(X+15, Y+35, 50712);
	ili9325_WritePixel(X+16, Y+35, 50712);
	ili9325_WritePixel(X+17, Y+35, 45056);
	ili9325_WritePixel(X+18, Y+35, 50712);
	ili9325_WritePixel(X+19, Y+35, 50712);
	ili9325_WritePixel(X+20, Y+35, 45056);
	ili9325_WritePixel(X+23, Y+35, 19343);

	ili9325_WritePixel(X+10, Y+36, 19343);
	ili9325_WritePixel(X+11, Y+36, 65077);
	ili9325_WritePixel(X+12, Y+36, 19343);
	ili9325_WritePixel(X+13, Y+36, 19343);
	ili9325_WritePixel(X+14, Y+36, 65077);
	ili9325_WritePixel(X+15, Y+36, 50712);
	ili9325_WritePixel(X+16, Y+36, 65077);
	ili9325_WritePixel(X+17, Y+36, 45056);
	ili9325_WritePixel(X+18, Y+36, 50712);
	ili9325_WritePixel(X+19, Y+36, 45056);
	ili9325_WritePixel(X+20, Y+36, 50712);
	ili9325_WritePixel(X+23, Y+36, 19343);

	ili9325_WritePixel(X+10, Y+37, 19343);
	ili9325_WritePixel(X+11, Y+37, 19343);
	ili9325_WritePixel(X+12, Y+37, 19343);
	ili9325_WritePixel(X+13, Y+37, 19343);
	ili9325_WritePixel(X+14, Y+37, 65077);
	ili9325_WritePixel(X+15, Y+37, 65077);
	ili9325_WritePixel(X+16, Y+37, 65077);
	ili9325_WritePixel(X+18, Y+37, 50712);
	ili9325_WritePixel(X+19, Y+37, 45056);

	ili9325_WritePixel(X+10, Y+38, 19343);
	ili9325_WritePixel(X+11, Y+38, 19343);
	ili9325_WritePixel(X+12, Y+38, 19343);
	ili9325_WritePixel(X+13, Y+38, 19343);
	ili9325_WritePixel(X+14, Y+38, 45056);
	ili9325_WritePixel(X+15, Y+38, 45056);
	ili9325_WritePixel(X+16, Y+38, 45056);

	ili9325_WritePixel(X+10, Y+39, 45056);
	ili9325_WritePixel(X+11, Y+39, 45056);
	ili9325_WritePixel(X+12, Y+39, 45056);
	ili9325_WritePixel(X+13, Y+39, 45056);
	ili9325_WritePixel(X+14, Y+39, 45056);
	ili9325_WritePixel(X+15, Y+39, 50712);
	ili9325_WritePixel(X+16, Y+39, 50712);

	ili9325_WritePixel(X+10, Y+40, 45056);
	ili9325_WritePixel(X+11, Y+40, 45056);
	ili9325_WritePixel(X+12, Y+40, 45056);
	ili9325_WritePixel(X+13, Y+40, 45056);
	ili9325_WritePixel(X+14, Y+40, 50712);
	ili9325_WritePixel(X+15, Y+40, 45056);
	ili9325_WritePixel(X+16, Y+40, 45056);

	ili9325_WritePixel(X+11, Y+41, 50712);
	ili9325_WritePixel(X+12, Y+41, 50712);
	ili9325_WritePixel(X+13, Y+41, 50712);
	ili9325_WritePixel(X+14, Y+41, 45056);
	ili9325_WritePixel(X+15, Y+41, 45056);
	ili9325_WritePixel(X+16, Y+41, 50712);
	ili9325_WritePixel(X+17, Y+41, 50712);

	ili9325_WritePixel(X+12, Y+42, 45056);
	ili9325_WritePixel(X+13, Y+42, 45056);
	ili9325_WritePixel(X+14, Y+42, 45056);
	ili9325_WritePixel(X+15, Y+42, 50712);
	ili9325_WritePixel(X+16, Y+42, 45056);
	ili9325_WritePixel(X+17, Y+42, 45056);

	ili9325_WritePixel(X+14, Y+43, 50712);
	ili9325_WritePixel(X+15, Y+43, 45056);
	ili9325_WritePixel(X+16, Y+43, 45056);
	ili9325_WritePixel(X+17, Y+43, 50712);
	ili9325_WritePixel(X+18, Y+43, 50712);

	ili9325_WritePixel(X+16, Y+44, 50712);
	ili9325_WritePixel(X+17, Y+44, 50712);
	ili9325_WritePixel(X+18, Y+44, 50712);
}
//--- SetSkierLeft --- DONE
void SetSkierRight(uint16_t X, uint16_t Y)
{
	ili9325_WritePixel(X+17, Y+1, 19343);
	ili9325_WritePixel(X+16, Y+1, 19343);
	ili9325_WritePixel(X+15, Y+1, 19343);

	ili9325_WritePixel(X+17, Y+2, 19343);
	ili9325_WritePixel(X+16, Y+2, 19343);
	ili9325_WritePixel(X+15, Y+2, 19343);
	ili9325_WritePixel(X+14, Y+2, 19343);

	ili9325_WritePixel(X+23, Y+3, 19343);
	ili9325_WritePixel(X+22, Y+3, 19343);
	ili9325_WritePixel(X+21, Y+3, 19343);
	ili9325_WritePixel(X+17, Y+3, 19343);
	ili9325_WritePixel(X+15, Y+3, 19343);
	ili9325_WritePixel(X+14, Y+3, 19343);
	ili9325_WritePixel(X+13, Y+3, 19343);

	ili9325_WritePixel(X+23, Y+4, 19343);
	ili9325_WritePixel(X+22, Y+4, 19343);
	ili9325_WritePixel(X+21, Y+4, 19343);
	ili9325_WritePixel(X+20, Y+4, 19343);
	ili9325_WritePixel(X+14, Y+4, 19343);
	ili9325_WritePixel(X+13, Y+4, 19343);
	ili9325_WritePixel(X+12, Y+4, 19343);

	ili9325_WritePixel(X+23, Y+5, 19343);
	ili9325_WritePixel(X+21, Y+5, 19343);
	ili9325_WritePixel(X+20, Y+5, 19343);
	ili9325_WritePixel(X+19, Y+5, 19343);
	ili9325_WritePixel(X+13, Y+5, 19343);
	ili9325_WritePixel(X+12, Y+5, 19343);
	ili9325_WritePixel(X+11, Y+5, 19343);

	ili9325_WritePixel(X+20, Y+6, 19343);
	ili9325_WritePixel(X+19, Y+6, 19343);
	ili9325_WritePixel(X+18, Y+6, 19343);
	ili9325_WritePixel(X+12, Y+6, 19343);
	ili9325_WritePixel(X+11, Y+6, 19343);
	ili9325_WritePixel(X+10, Y+6, 19343);

	ili9325_WritePixel(X+19, Y+7, 19343);
	ili9325_WritePixel(X+18, Y+7, 19343);
	ili9325_WritePixel(X+17, Y+7, 19343);
	ili9325_WritePixel(X+11, Y+7, 19343);
	ili9325_WritePixel(X+10, Y+7, 19343);
	ili9325_WritePixel(X+9, Y+7, 19343);

	ili9325_WritePixel(X+18, Y+8, 19343);
	ili9325_WritePixel(X+17, Y+8, 19343);
	ili9325_WritePixel(X+16, Y+8, 19343);
	ili9325_WritePixel(X+10, Y+8, 19343);
	ili9325_WritePixel(X+9, Y+8, 19343);
	ili9325_WritePixel(X+8, Y+8, 19343);

	ili9325_WritePixel(X+17, Y+9, 19343);
	ili9325_WritePixel(X+16, Y+9, 19343);
	ili9325_WritePixel(X+15, Y+9, 19343);
	ili9325_WritePixel(X+10, Y+9, 50712);
	ili9325_WritePixel(X+9, Y+9, 50712);
	ili9325_WritePixel(X+8, Y+9, 50712);
	ili9325_WritePixel(X+7, Y+9, 50712);

	ili9325_WritePixel(X+17, Y+10, 50712);
	ili9325_WritePixel(X+16, Y+10, 50712);
	ili9325_WritePixel(X+15, Y+10, 50712);
	ili9325_WritePixel(X+14, Y+10, 50712);
	ili9325_WritePixel(X+10, Y+10, 50712);
	ili9325_WritePixel(X+9, Y+10, 50712);
	ili9325_WritePixel(X+8, Y+10, 50712);
	ili9325_WritePixel(X+7, Y+10, 50712);
	ili9325_WritePixel(X+6, Y+10, 19343);

	ili9325_WritePixel(X+17, Y+11, 50712);
	ili9325_WritePixel(X+16, Y+11, 50712);
	ili9325_WritePixel(X+15, Y+11, 50712);
	ili9325_WritePixel(X+14, Y+11, 50712);	//szary
	ili9325_WritePixel(X+13, Y+11, 19343);	//niebieski
	ili9325_WritePixel(X+10, Y+11, 45056);	//czerwony
	ili9325_WritePixel(X+9, Y+11, 45056);
	ili9325_WritePixel(X+8, Y+11, 45056);
	ili9325_WritePixel(X+7, Y+11, 45056);
	ili9325_WritePixel(X+6, Y+11, 19343);
	ili9325_WritePixel(X+5, Y+11, 19343);

	ili9325_WritePixel(X+17, Y+12, 45056);
	ili9325_WritePixel(X+16, Y+12, 45056);
	ili9325_WritePixel(X+15, Y+12, 45056);
	ili9325_WritePixel(X+14, Y+12, 45056);
	ili9325_WritePixel(X+13, Y+12, 19343);
	ili9325_WritePixel(X+12, Y+12, 19343);
	ili9325_WritePixel(X+10, Y+12, 45056);
	ili9325_WritePixel(X+9, Y+12, 45056);
	ili9325_WritePixel(X+8, Y+12, 45056);
	ili9325_WritePixel(X+7, Y+12, 45056);
	ili9325_WritePixel(X+6, Y+12, 19343);
	ili9325_WritePixel(X+5, Y+12, 19343);
	ili9325_WritePixel(X+4, Y+12, 19343);

	ili9325_WritePixel(X+17, Y+13, 45056);
	ili9325_WritePixel(X+16, Y+13, 45056);
	ili9325_WritePixel(X+15, Y+13, 45056);
	ili9325_WritePixel(X+14, Y+13, 45056);
	ili9325_WritePixel(X+13, Y+13, 19343);
	ili9325_WritePixel(X+12, Y+13, 19343);
	ili9325_WritePixel(X+11, Y+13, 19343);
	ili9325_WritePixel(X+10, Y+13, 45056);
	ili9325_WritePixel(X+9, Y+13, 45056);
	ili9325_WritePixel(X+8, Y+13, 45056);
	ili9325_WritePixel(X+7, Y+13, 45056);
	ili9325_WritePixel(X+5, Y+13, 19343);
	ili9325_WritePixel(X+4, Y+13, 19343);
	ili9325_WritePixel(X+3, Y+13, 19343);

	ili9325_WritePixel(X+17, Y+14, 45056);
	ili9325_WritePixel(X+16, Y+14, 45056);
	ili9325_WritePixel(X+15, Y+14, 45056);
	ili9325_WritePixel(X+14, Y+14, 45056);
	ili9325_WritePixel(X+12, Y+14, 19343);
	ili9325_WritePixel(X+11, Y+14, 19343);
	ili9325_WritePixel(X+10, Y+14, 45056);
	ili9325_WritePixel(X+9, Y+14, 45056);
	ili9325_WritePixel(X+8, Y+14, 45056);
	ili9325_WritePixel(X+7, Y+14, 45056);
	ili9325_WritePixel(X+4, Y+14, 19343);
	ili9325_WritePixel(X+3, Y+14, 19343);
	ili9325_WritePixel(X+2, Y+14, 19343);

	ili9325_WritePixel(X+17, Y+15, 45056);
	ili9325_WritePixel(X+16, Y+15, 45056);
	ili9325_WritePixel(X+15, Y+15, 45056);
	ili9325_WritePixel(X+14, Y+15, 45056);
	ili9325_WritePixel(X+11, Y+15, 19343);
	ili9325_WritePixel(X+10, Y+15, 45056);
	ili9325_WritePixel(X+9, Y+15, 45056);
	ili9325_WritePixel(X+8, Y+15, 45056);
	ili9325_WritePixel(X+7, Y+15, 45056);
	ili9325_WritePixel(X+3, Y+15, 19343);
	ili9325_WritePixel(X+2, Y+15, 19343);

	ili9325_WritePixel(X+17, Y+16, 45056);
	ili9325_WritePixel(X+16, Y+16, 45056);
	ili9325_WritePixel(X+15, Y+16, 45056);
	ili9325_WritePixel(X+14, Y+16, 45056);
	ili9325_WritePixel(X+10, Y+16, 45056);
	ili9325_WritePixel(X+9, Y+16, 45056);
	ili9325_WritePixel(X+8, Y+16, 45056);
	ili9325_WritePixel(X+7, Y+16, 45056);

	ili9325_WritePixel(X+17, Y+17, 45056);
	ili9325_WritePixel(X+16, Y+17, 45056);
	ili9325_WritePixel(X+15, Y+17, 45056);
	ili9325_WritePixel(X+14, Y+17, 45056);
	ili9325_WritePixel(X+10, Y+17, 45056);
	ili9325_WritePixel(X+11, Y+17, 45056);
	ili9325_WritePixel(X+12, Y+17, 45056);
	ili9325_WritePixel(X+13, Y+17, 45056);

	ili9325_WritePixel(X+17, Y+18, 45056);
	ili9325_WritePixel(X+16, Y+18, 45056);
	ili9325_WritePixel(X+15, Y+18, 45056);
	ili9325_WritePixel(X+14, Y+18, 45056);
	ili9325_WritePixel(X+11, Y+18, 5186);
	ili9325_WritePixel(X+10, Y+18, 5186);
	ili9325_WritePixel(X+9, Y+18, 5186);
	ili9325_WritePixel(X+8, Y+18, 5186);
	ili9325_WritePixel(X+7, Y+18, 5186); //zielony

	ili9325_WritePixel(X+17, Y+19, 45056);
	ili9325_WritePixel(X+16, Y+19, 45056);
	ili9325_WritePixel(X+15, Y+19, 5186);
	ili9325_WritePixel(X+14, Y+19, 5186);
	ili9325_WritePixel(X+13, Y+19, 5186);
	ili9325_WritePixel(X+12, Y+19, 5186);
	ili9325_WritePixel(X+11, Y+19, 5186);
	ili9325_WritePixel(X+10, Y+19, 5186);
	ili9325_WritePixel(X+9, Y+19, 5186);
	ili9325_WritePixel(X+8, Y+19, 5186);
	ili9325_WritePixel(X+7, Y+19, 5186);

	ili9325_WritePixel(X+17, Y+20, 5186);
	ili9325_WritePixel(X+16, Y+20, 5186);
	ili9325_WritePixel(X+15, Y+20, 5186);
	ili9325_WritePixel(X+14, Y+20, 5186);
	ili9325_WritePixel(X+13, Y+20, 5186);
	ili9325_WritePixel(X+12, Y+20, 5186);
	ili9325_WritePixel(X+11, Y+20, 5186);
	ili9325_WritePixel(X+10, Y+20, 5186);
	ili9325_WritePixel(X+9, Y+20, 5186);
	ili9325_WritePixel(X+8, Y+20, 5186);
	ili9325_WritePixel(X+7, Y+20, 5186);

	ili9325_WritePixel(X+17, Y+21, 5186);
	ili9325_WritePixel(X+16, Y+21, 5186);
	ili9325_WritePixel(X+15, Y+21, 5186);
	ili9325_WritePixel(X+14, Y+21, 5186);
	ili9325_WritePixel(X+13, Y+21, 5186);
	ili9325_WritePixel(X+12, Y+21, 5186);
	ili9325_WritePixel(X+11, Y+21, 5186);
	ili9325_WritePixel(X+10, Y+21, 5186);
	ili9325_WritePixel(X+9, Y+21, 5186);
	ili9325_WritePixel(X+8, Y+21, 5186);
	ili9325_WritePixel(X+7, Y+21, 5186);

	ili9325_WritePixel(X+17, Y+22, 5186);
	ili9325_WritePixel(X+16, Y+22, 5186);
	ili9325_WritePixel(X+15, Y+22, 5186);
	ili9325_WritePixel(X+14, Y+22, 5186);
	ili9325_WritePixel(X+13, Y+22, 5186);
	ili9325_WritePixel(X+12, Y+22, 5186);
	ili9325_WritePixel(X+11, Y+22, 5186);
	ili9325_WritePixel(X+10, Y+22, 5186);
	ili9325_WritePixel(X+9, Y+22, 5186);
	ili9325_WritePixel(X+8, Y+22, 5186);
	ili9325_WritePixel(X+7, Y+22, 5186);

	ili9325_WritePixel(X+17, Y+23, 5186);
	ili9325_WritePixel(X+16, Y+23, 5186);
	ili9325_WritePixel(X+15, Y+23, 5186);
	ili9325_WritePixel(X+14, Y+23, 5186);
	ili9325_WritePixel(X+13, Y+23, 5186);
	ili9325_WritePixel(X+12, Y+23, 5186);
	ili9325_WritePixel(X+11, Y+23, 50712);
	ili9325_WritePixel(X+10, Y+23, 50712);
	ili9325_WritePixel(X+9, Y+23, 19343);
	ili9325_WritePixel(X+8, Y+23, 5186);
	ili9325_WritePixel(X+7, Y+23, 5186);

	ili9325_WritePixel(X+17, Y+24, 5186);
	ili9325_WritePixel(X+16, Y+24, 5186);
	ili9325_WritePixel(X+15, Y+24, 5186);
	ili9325_WritePixel(X+14, Y+24, 5186);
	ili9325_WritePixel(X+13, Y+24, 5186);
	ili9325_WritePixel(X+12, Y+24, 5186);
	ili9325_WritePixel(X+11, Y+24, 50712);
	ili9325_WritePixel(X+10, Y+24, 5186);
	ili9325_WritePixel(X+9, Y+24, 19343);
	ili9325_WritePixel(X+8, Y+24, 5186);
	ili9325_WritePixel(X+7, Y+24, 5186);

	ili9325_WritePixel(X+17, Y+25, 5186);
	ili9325_WritePixel(X+16, Y+25, 5186);
	ili9325_WritePixel(X+15, Y+25, 5186);
	ili9325_WritePixel(X+14, Y+25, 5186);
	ili9325_WritePixel(X+13, Y+25, 5186);
	ili9325_WritePixel(X+12, Y+25, 5186);
	ili9325_WritePixel(X+11, Y+25, 50712);
	ili9325_WritePixel(X+10, Y+25, 5186);
	ili9325_WritePixel(X+9, Y+25, 19343);
	ili9325_WritePixel(X+8, Y+25, 19343);
	ili9325_WritePixel(X+7, Y+25, 19343);

	ili9325_WritePixel(X+17, Y+26, 5186);
	ili9325_WritePixel(X+16, Y+26, 5186);
	ili9325_WritePixel(X+15, Y+26, 5186);
	ili9325_WritePixel(X+14, Y+26, 5186);
	ili9325_WritePixel(X+13, Y+26, 5186);
	ili9325_WritePixel(X+12, Y+26, 5186);
	ili9325_WritePixel(X+11, Y+26, 3008);
	ili9325_WritePixel(X+10, Y+26, 5186);
	ili9325_WritePixel(X+9, Y+26, 3008);
	ili9325_WritePixel(X+8, Y+26, 19343);
	ili9325_WritePixel(X+7, Y+26, 19343);

	ili9325_WritePixel(X+19, Y+27, 5186);
	ili9325_WritePixel(X+18, Y+27, 5186);
	ili9325_WritePixel(X+17, Y+27, 5186);
	ili9325_WritePixel(X+16, Y+27, 5186);
	ili9325_WritePixel(X+15, Y+27, 5186);
	ili9325_WritePixel(X+14, Y+27, 5186);
	ili9325_WritePixel(X+13, Y+27, 3008);
	ili9325_WritePixel(X+12, Y+27, 5186);
	ili9325_WritePixel(X+11, Y+27, 3008);
	ili9325_WritePixel(X+10, Y+27, 19343);
	ili9325_WritePixel(X+9, Y+27, 19343);
	ili9325_WritePixel(X+8, Y+27, 19343);
	ili9325_WritePixel(X+7, Y+27, 19343);

	ili9325_WritePixel(X+19, Y+28, 5186);
	ili9325_WritePixel(X+18, Y+28, 5186);
	ili9325_WritePixel(X+17, Y+28, 5186);
	ili9325_WritePixel(X+16, Y+28, 5186);
	ili9325_WritePixel(X+15, Y+28, 5186);
	ili9325_WritePixel(X+14, Y+28, 5186);
	ili9325_WritePixel(X+13, Y+28, 3008);
	ili9325_WritePixel(X+12, Y+28, 5186);
	ili9325_WritePixel(X+11, Y+28, 3008);
	ili9325_WritePixel(X+10, Y+28, 5186);
	ili9325_WritePixel(X+9, Y+28, 5186);
	ili9325_WritePixel(X+8, Y+28, 19343);
	ili9325_WritePixel(X+7, Y+28, 19343);

	ili9325_WritePixel(X+20, Y+29, 5186);
	ili9325_WritePixel(X+19, Y+29, 5186);
	ili9325_WritePixel(X+18, Y+29, 5186);
	ili9325_WritePixel(X+17, Y+29, 5186);
	ili9325_WritePixel(X+16, Y+29, 5186);
	ili9325_WritePixel(X+15, Y+29, 5186);
	ili9325_WritePixel(X+14, Y+29, 3008);
	ili9325_WritePixel(X+13, Y+29, 3008);
	ili9325_WritePixel(X+12, Y+29, 3008);
	ili9325_WritePixel(X+11, Y+29, 5186);
	ili9325_WritePixel(X+10, Y+29, 5186);
	ili9325_WritePixel(X+9, Y+29, 19343);
	ili9325_WritePixel(X+8, Y+29, 19343);
	ili9325_WritePixel(X+7, Y+29, 19343);

	ili9325_WritePixel(X+17, Y+30, 5186);
	ili9325_WritePixel(X+16, Y+30, 5186);
	ili9325_WritePixel(X+15, Y+30, 5186);
	ili9325_WritePixel(X+14, Y+30, 5186);
	ili9325_WritePixel(X+13, Y+30, 5186);
	ili9325_WritePixel(X+12, Y+30, 5186);
	ili9325_WritePixel(X+11, Y+30, 5186);
	ili9325_WritePixel(X+10, Y+30, 5186);
	ili9325_WritePixel(X+9, Y+30, 5186);
	ili9325_WritePixel(X+8, Y+30, 5186);
	ili9325_WritePixel(X+7, Y+30, 5186);
	ili9325_WritePixel(X+4, Y+30, 19343);
	ili9325_WritePixel(X+3, Y+30, 19343);

	ili9325_WritePixel(X+16, Y+31, 5186);
	ili9325_WritePixel(X+15, Y+31, 5186);
	ili9325_WritePixel(X+14, Y+31, 45056);
	ili9325_WritePixel(X+13, Y+31, 45056);
	ili9325_WritePixel(X+12, Y+31, 45056);
	ili9325_WritePixel(X+11, Y+31, 50712);
	ili9325_WritePixel(X+10, Y+31, 45056);
	ili9325_WritePixel(X+9, Y+31, 45056);
	ili9325_WritePixel(X+8, Y+31, 45056);
	ili9325_WritePixel(X+7, Y+31, 50712);
	ili9325_WritePixel(X+3, Y+31, 19343);
	ili9325_WritePixel(X+2, Y+31, 19343);

	ili9325_WritePixel(X+15, Y+32, 45056);
	ili9325_WritePixel(X+14, Y+32, 45056);
	ili9325_WritePixel(X+13, Y+32, 45056);
	ili9325_WritePixel(X+12, Y+32, 50712);
	ili9325_WritePixel(X+11, Y+32, 45056);
	ili9325_WritePixel(X+10, Y+32, 45056);
	ili9325_WritePixel(X+9, Y+32, 50712);
	ili9325_WritePixel(X+8, Y+32, 50712);
	ili9325_WritePixel(X+7, Y+32, 45056);
	ili9325_WritePixel(X+6, Y+32, 50712);
	ili9325_WritePixel(X+2, Y+32, 19343);
	ili9325_WritePixel(X+1, Y+32, 19343);

	ili9325_WritePixel(X+15, Y+33, 50712);
	ili9325_WritePixel(X+14, Y+33, 50712);
	ili9325_WritePixel(X+13, Y+33, 50712);
	ili9325_WritePixel(X+12, Y+33, 45056);
	ili9325_WritePixel(X+11, Y+33, 45056);
	ili9325_WritePixel(X+10, Y+33, 50712);
	ili9325_WritePixel(X+9, Y+33, 50712);
	ili9325_WritePixel(X+8, Y+33, 45056);
	ili9325_WritePixel(X+7, Y+33, 50712);
	ili9325_WritePixel(X+6, Y+33, 50712);
	ili9325_WritePixel(X+5, Y+33, 50712);
	ili9325_WritePixel(X+1, Y+33, 19343);

	ili9325_WritePixel(X+14, Y+34, 65077);
	ili9325_WritePixel(X+13, Y+34, 65077);
	ili9325_WritePixel(X+12, Y+34, 65077);
	ili9325_WritePixel(X+11, Y+34, 65077);
	ili9325_WritePixel(X+10, Y+34, 65077);
	ili9325_WritePixel(X+9, Y+34, 45056);
	ili9325_WritePixel(X+8, Y+34, 50712);
	ili9325_WritePixel(X+7, Y+34, 50712);
	ili9325_WritePixel(X+6, Y+34, 45056);
	ili9325_WritePixel(X+5, Y+34, 45056);
	ili9325_WritePixel(X+4, Y+34, 50712);
	ili9325_WritePixel(X+1, Y+34, 19343);

	ili9325_WritePixel(X+14, Y+35, 65077);
	ili9325_WritePixel(X+13, Y+35, 65077);
	ili9325_WritePixel(X+12, Y+35, 65077);
	ili9325_WritePixel(X+11, Y+35, 65077);
	ili9325_WritePixel(X+10, Y+35, 65077);
	ili9325_WritePixel(X+9, Y+35, 50712);
	ili9325_WritePixel(X+8, Y+35, 50712);
	ili9325_WritePixel(X+7, Y+35, 45056);
	ili9325_WritePixel(X+6, Y+35, 50712);
	ili9325_WritePixel(X+5, Y+35, 50712);
	ili9325_WritePixel(X+4, Y+35, 45056);
	ili9325_WritePixel(X+1, Y+35, 19343);

	ili9325_WritePixel(X+14, Y+36, 19343);
	ili9325_WritePixel(X+13, Y+36, 65077);
	ili9325_WritePixel(X+12, Y+36, 19343);
	ili9325_WritePixel(X+11, Y+36, 19343);
	ili9325_WritePixel(X+10, Y+36, 65077);
	ili9325_WritePixel(X+9, Y+36, 50712);
	ili9325_WritePixel(X+8, Y+36, 65077);
	ili9325_WritePixel(X+7, Y+36, 45056);
	ili9325_WritePixel(X+6, Y+36, 50712);
	ili9325_WritePixel(X+5, Y+36, 45056);
	ili9325_WritePixel(X+4, Y+36, 50712);
	ili9325_WritePixel(X+1, Y+36, 19343);

	ili9325_WritePixel(X+14, Y+37, 19343);
	ili9325_WritePixel(X+13, Y+37, 19343);
	ili9325_WritePixel(X+12, Y+37, 19343);
	ili9325_WritePixel(X+11, Y+37, 19343);
	ili9325_WritePixel(X+10, Y+37, 65077);
	ili9325_WritePixel(X+9, Y+37, 65077);
	ili9325_WritePixel(X+8, Y+37, 65077);
	ili9325_WritePixel(X+6, Y+37, 50712);
	ili9325_WritePixel(X+5, Y+37, 45056);

	ili9325_WritePixel(X+14, Y+38, 19343);
	ili9325_WritePixel(X+13, Y+38, 19343);
	ili9325_WritePixel(X+12, Y+38, 19343);
	ili9325_WritePixel(X+11, Y+38, 19343);
	ili9325_WritePixel(X+10, Y+38, 45056);
	ili9325_WritePixel(X+9, Y+38, 45056);
	ili9325_WritePixel(X+8, Y+38, 45056);

	ili9325_WritePixel(X+14, Y+39, 45056);
	ili9325_WritePixel(X+13, Y+39, 45056);
	ili9325_WritePixel(X+12, Y+39, 45056);
	ili9325_WritePixel(X+11, Y+39, 45056);
	ili9325_WritePixel(X+10, Y+39, 45056);
	ili9325_WritePixel(X+9, Y+39, 50712);
	ili9325_WritePixel(X+8, Y+39, 50712);

	ili9325_WritePixel(X+14, Y+40, 45056);
	ili9325_WritePixel(X+13, Y+40, 45056);
	ili9325_WritePixel(X+12, Y+40, 45056);
	ili9325_WritePixel(X+11, Y+40, 45056);
	ili9325_WritePixel(X+10, Y+40, 50712);
	ili9325_WritePixel(X+9, Y+40, 45056);
	ili9325_WritePixel(X+8, Y+40, 45056);

	ili9325_WritePixel(X+13, Y+41, 50712);
	ili9325_WritePixel(X+12, Y+41, 50712);
	ili9325_WritePixel(X+11, Y+41, 50712);
	ili9325_WritePixel(X+10, Y+41, 45056);
	ili9325_WritePixel(X+9, Y+41, 45056);
	ili9325_WritePixel(X+8, Y+41, 50712);
	ili9325_WritePixel(X+7, Y+41, 50712);

	ili9325_WritePixel(X+12, Y+42, 45056);
	ili9325_WritePixel(X+11, Y+42, 45056);
	ili9325_WritePixel(X+10, Y+42, 45056);
	ili9325_WritePixel(X+9, Y+42, 50712);
	ili9325_WritePixel(X+8, Y+42, 45056);
	ili9325_WritePixel(X+7, Y+42, 45056);

	ili9325_WritePixel(X+10, Y+43, 50712);
	ili9325_WritePixel(X+9, Y+43, 45056);
	ili9325_WritePixel(X+8, Y+43, 45056);
	ili9325_WritePixel(X+7, Y+43, 50712);
	ili9325_WritePixel(X+6, Y+43, 50712);

	ili9325_WritePixel(X+8, Y+44, 50712);
	ili9325_WritePixel(X+7, Y+44, 50712);
	ili9325_WritePixel(X+6, Y+44, 50712);
}
//--- SetHeartRed --- DONE
void SetHeartRed(uint16_t X, uint16_t Y)
{
	ili9325_WritePixel(X+10, Y+1, 0);
	ili9325_WritePixel(X+11, Y+1, 0);

	ili9325_WritePixel(X+9, Y+2, 0);
	ili9325_WritePixel(X+10, Y+2, 55556);
	ili9325_WritePixel(X+11, Y+2, 55556);
	ili9325_WritePixel(X+12, Y+2, 0);

	ili9325_WritePixel(X+8, Y+3, 0);
	ili9325_WritePixel(X+9, Y+3, 55556);
	ili9325_WritePixel(X+10, Y+3, 55556);
	ili9325_WritePixel(X+11, Y+3, 55556);
	ili9325_WritePixel(X+12, Y+3, 55556);
	ili9325_WritePixel(X+13, Y+3, 0);

	ili9325_WritePixel(X+7, Y+4, 0);
	ili9325_WritePixel(X+8, Y+4, 55556);
	ili9325_WritePixel(X+9, Y+4, 55556);
	ili9325_WritePixel(X+10, Y+4, 55556);
	ili9325_WritePixel(X+11, Y+4, 55556);
	ili9325_WritePixel(X+12, Y+4, 55556);
	ili9325_WritePixel(X+13, Y+4, 55556);
	ili9325_WritePixel(X+14, Y+4, 0);

	ili9325_WritePixel(X+6, Y+5, 0);
	ili9325_WritePixel(X+7, Y+5, 55556);
	ili9325_WritePixel(X+8, Y+5, 55556);
	ili9325_WritePixel(X+9, Y+5, 55556);
	ili9325_WritePixel(X+10, Y+5, 55556);
	ili9325_WritePixel(X+11, Y+5, 55556);
	ili9325_WritePixel(X+12, Y+5, 55556);
	ili9325_WritePixel(X+13, Y+5, 55556);
	ili9325_WritePixel(X+14, Y+5, 55556);
	ili9325_WritePixel(X+15, Y+5, 0);

	ili9325_WritePixel(X+5, Y+6, 0);
	ili9325_WritePixel(X+6, Y+6, 55556);
	ili9325_WritePixel(X+7, Y+6, 55556);
	ili9325_WritePixel(X+8, Y+6, 55556);
	ili9325_WritePixel(X+9, Y+6, 55556);
	ili9325_WritePixel(X+10, Y+6, 55556);
	ili9325_WritePixel(X+11, Y+6, 55556);
	ili9325_WritePixel(X+12, Y+6, 55556);
	ili9325_WritePixel(X+13, Y+6, 55556);
	ili9325_WritePixel(X+14, Y+6, 55556);
	ili9325_WritePixel(X+15, Y+6, 55556);
	ili9325_WritePixel(X+16, Y+6, 0);

	ili9325_WritePixel(X+4, Y+7, 0);
	ili9325_WritePixel(X+5, Y+7, 55556);
	ili9325_WritePixel(X+6, Y+7, 55556);
	ili9325_WritePixel(X+7, Y+7, 55556);
	ili9325_WritePixel(X+8, Y+7, 55556);
	ili9325_WritePixel(X+9, Y+7, 55556);
	ili9325_WritePixel(X+10, Y+7, 55556);
	ili9325_WritePixel(X+11, Y+7, 55556);
	ili9325_WritePixel(X+12, Y+7, 55556);
	ili9325_WritePixel(X+13, Y+7, 55556);
	ili9325_WritePixel(X+14, Y+7, 55556);
	ili9325_WritePixel(X+15, Y+7, 55556);
	ili9325_WritePixel(X+16, Y+7, 55556);
	ili9325_WritePixel(X+17, Y+7, 0);

	ili9325_WritePixel(X+3, Y+8, 0);
	ili9325_WritePixel(X+4, Y+8, 55556);
	ili9325_WritePixel(X+5, Y+8, 55556);
	ili9325_WritePixel(X+6, Y+8, 55556);
	ili9325_WritePixel(X+7, Y+8, 55556);
	ili9325_WritePixel(X+8, Y+8, 55556);
	ili9325_WritePixel(X+9, Y+8, 55556);
	ili9325_WritePixel(X+10, Y+8, 55556);
	ili9325_WritePixel(X+11, Y+8, 55556);
	ili9325_WritePixel(X+12, Y+8, 55556);
	ili9325_WritePixel(X+13, Y+8, 55556);
	ili9325_WritePixel(X+14, Y+8, 55556);
	ili9325_WritePixel(X+15, Y+8, 55556);
	ili9325_WritePixel(X+16, Y+8, 55556);
	ili9325_WritePixel(X+17, Y+8, 55556);
	ili9325_WritePixel(X+18, Y+8, 0);

	ili9325_WritePixel(X+2, Y+9, 0);
	ili9325_WritePixel(X+3, Y+9, 55556);
	ili9325_WritePixel(X+4, Y+9, 55556);
	ili9325_WritePixel(X+5, Y+9, 55556);
	ili9325_WritePixel(X+6, Y+9, 55556);
	ili9325_WritePixel(X+7, Y+9, 55556);
	ili9325_WritePixel(X+8, Y+9, 55556);
	ili9325_WritePixel(X+9, Y+9, 55556);
	ili9325_WritePixel(X+10, Y+9, 55556);
	ili9325_WritePixel(X+11, Y+9, 55556);
	ili9325_WritePixel(X+12, Y+9, 55556);
	ili9325_WritePixel(X+13, Y+9, 55556);
	ili9325_WritePixel(X+14, Y+9, 55556);
	ili9325_WritePixel(X+15, Y+9, 55556);
	ili9325_WritePixel(X+16, Y+9, 55556);
	ili9325_WritePixel(X+17, Y+9, 55556);
	ili9325_WritePixel(X+18, Y+9, 55556);
	ili9325_WritePixel(X+19, Y+9, 0);

	ili9325_WritePixel(X+2, Y+10, 0);
	ili9325_WritePixel(X+3, Y+10, 55556);
	ili9325_WritePixel(X+4, Y+10, 55556);
	ili9325_WritePixel(X+5, Y+10, 55556);
	ili9325_WritePixel(X+6, Y+10, 55556);
	ili9325_WritePixel(X+7, Y+10, 55556);
	ili9325_WritePixel(X+8, Y+10, 55556);
	ili9325_WritePixel(X+9, Y+10, 55556);
	ili9325_WritePixel(X+10, Y+10, 55556);
	ili9325_WritePixel(X+11, Y+10, 55556);
	ili9325_WritePixel(X+12, Y+10, 55556);
	ili9325_WritePixel(X+13, Y+10, 55556);
	ili9325_WritePixel(X+14, Y+10, 55556);
	ili9325_WritePixel(X+15, Y+10, 55556);
	ili9325_WritePixel(X+16, Y+10, 55556);
	ili9325_WritePixel(X+17, Y+10, 55556);
	ili9325_WritePixel(X+18, Y+10, 55556);
	ili9325_WritePixel(X+19, Y+10, 0);

	ili9325_WritePixel(X+2, Y+11, 0);
	ili9325_WritePixel(X+3, Y+11, 55556);
	ili9325_WritePixel(X+4, Y+11, 55556);
	ili9325_WritePixel(X+5, Y+11, 55556);
	ili9325_WritePixel(X+6, Y+11, 55556);
	ili9325_WritePixel(X+7, Y+11, 55556);
	ili9325_WritePixel(X+8, Y+11, 55556);
	ili9325_WritePixel(X+9, Y+11, 55556);
	ili9325_WritePixel(X+10, Y+11, 55556);
	ili9325_WritePixel(X+11, Y+11, 55556);
	ili9325_WritePixel(X+12, Y+11, 55556);
	ili9325_WritePixel(X+13, Y+11, 55556);
	ili9325_WritePixel(X+14, Y+11, 55556);
	ili9325_WritePixel(X+15, Y+11, 55556);
	ili9325_WritePixel(X+16, Y+11, 55556);
	ili9325_WritePixel(X+17, Y+11, 55556);
	ili9325_WritePixel(X+18, Y+11, 55556);
	ili9325_WritePixel(X+19, Y+11, 0);

	ili9325_WritePixel(X+1, Y+12, 0);
	ili9325_WritePixel(X+2, Y+12, 55556);
	ili9325_WritePixel(X+3, Y+12, 55556);
	ili9325_WritePixel(X+4, Y+12, 55556);
	ili9325_WritePixel(X+5, Y+12, 55556);
	ili9325_WritePixel(X+6, Y+12, 55556);
	ili9325_WritePixel(X+7, Y+12, 55556);
	ili9325_WritePixel(X+8, Y+12, 55556);
	ili9325_WritePixel(X+9, Y+12, 55556);
	ili9325_WritePixel(X+10, Y+12, 55556);
	ili9325_WritePixel(X+11, Y+12, 55556);
	ili9325_WritePixel(X+12, Y+12, 55556);
	ili9325_WritePixel(X+13, Y+12, 55556);
	ili9325_WritePixel(X+14, Y+12, 55556);
	ili9325_WritePixel(X+15, Y+12, 55556);
	ili9325_WritePixel(X+16, Y+12, 55556);
	ili9325_WritePixel(X+17, Y+12, 55556);
	ili9325_WritePixel(X+18, Y+12, 55556);
	ili9325_WritePixel(X+19, Y+12, 55556);
	ili9325_WritePixel(X+20, Y+12, 0);

	ili9325_WritePixel(X+1, Y+13, 0);
	ili9325_WritePixel(X+2, Y+13, 55556);
	ili9325_WritePixel(X+3, Y+13, 55556);
	ili9325_WritePixel(X+4, Y+13, 55556);
	ili9325_WritePixel(X+5, Y+13, 55556);
	ili9325_WritePixel(X+6, Y+13, 55556);
	ili9325_WritePixel(X+7, Y+13, 55556);
	ili9325_WritePixel(X+8, Y+13, 55556);
	ili9325_WritePixel(X+9, Y+13, 55556);
	ili9325_WritePixel(X+10, Y+13, 55556);
	ili9325_WritePixel(X+11, Y+13, 55556);
	ili9325_WritePixel(X+12, Y+13, 55556);
	ili9325_WritePixel(X+13, Y+13, 55556);
	ili9325_WritePixel(X+14, Y+13, 55556);
	ili9325_WritePixel(X+15, Y+13, 55556);
	ili9325_WritePixel(X+16, Y+13, 55556);
	ili9325_WritePixel(X+17, Y+13, 55556);
	ili9325_WritePixel(X+18, Y+13, 55556);
	ili9325_WritePixel(X+19, Y+13, 55556);
	ili9325_WritePixel(X+20, Y+13, 0);

	ili9325_WritePixel(X+1, Y+14, 0);
	ili9325_WritePixel(X+2, Y+14, 55556);
	ili9325_WritePixel(X+3, Y+14, 65535);
	ili9325_WritePixel(X+4, Y+14, 65535);
	ili9325_WritePixel(X+5, Y+14, 55556);
	ili9325_WritePixel(X+6, Y+14, 55556);
	ili9325_WritePixel(X+7, Y+14, 55556);
	ili9325_WritePixel(X+8, Y+14, 55556);
	ili9325_WritePixel(X+9, Y+14, 55556);
	ili9325_WritePixel(X+10, Y+14, 55556);
	ili9325_WritePixel(X+11, Y+14, 55556);
	ili9325_WritePixel(X+12, Y+14, 55556);
	ili9325_WritePixel(X+13, Y+14, 55556);
	ili9325_WritePixel(X+14, Y+14, 55556);
	ili9325_WritePixel(X+15, Y+14, 55556);
	ili9325_WritePixel(X+16, Y+14, 55556);
	ili9325_WritePixel(X+17, Y+14, 55556);
	ili9325_WritePixel(X+18, Y+14, 55556);
	ili9325_WritePixel(X+19, Y+14, 55556);
	ili9325_WritePixel(X+20, Y+14, 0);

	ili9325_WritePixel(X+1, Y+15, 0);
	ili9325_WritePixel(X+2, Y+15, 55556);
	ili9325_WritePixel(X+3, Y+15, 65535);
	ili9325_WritePixel(X+4, Y+15, 65535);
	ili9325_WritePixel(X+5, Y+15, 65535);
	ili9325_WritePixel(X+6, Y+15, 55556);
	ili9325_WritePixel(X+7, Y+15, 55556);
	ili9325_WritePixel(X+8, Y+15, 55556);
	ili9325_WritePixel(X+9, Y+15, 55556);
	ili9325_WritePixel(X+10, Y+15, 55556);
	ili9325_WritePixel(X+11, Y+15, 55556);
	ili9325_WritePixel(X+12, Y+15, 55556);
	ili9325_WritePixel(X+13, Y+15, 55556);
	ili9325_WritePixel(X+14, Y+15, 55556);
	ili9325_WritePixel(X+15, Y+15, 55556);
	ili9325_WritePixel(X+16, Y+15, 55556);
	ili9325_WritePixel(X+17, Y+15, 55556);
	ili9325_WritePixel(X+18, Y+15, 55556);
	ili9325_WritePixel(X+19, Y+15, 55556);
	ili9325_WritePixel(X+20, Y+15, 0);

	ili9325_WritePixel(X+1, Y+16, 0);
	ili9325_WritePixel(X+2, Y+16, 55556);
	ili9325_WritePixel(X+3, Y+16, 55556);
	ili9325_WritePixel(X+4, Y+16, 65535);
	ili9325_WritePixel(X+5, Y+16, 65535);
	ili9325_WritePixel(X+6, Y+16, 55556);
	ili9325_WritePixel(X+7, Y+16, 55556);
	ili9325_WritePixel(X+8, Y+16, 55556);
	ili9325_WritePixel(X+9, Y+16, 55556);
	ili9325_WritePixel(X+10, Y+16, 55556);
	ili9325_WritePixel(X+11, Y+16, 55556);
	ili9325_WritePixel(X+12, Y+16, 55556);
	ili9325_WritePixel(X+13, Y+16, 55556);
	ili9325_WritePixel(X+14, Y+16, 55556);
	ili9325_WritePixel(X+15, Y+16, 55556);
	ili9325_WritePixel(X+16, Y+16, 55556);
	ili9325_WritePixel(X+17, Y+16, 55556);
	ili9325_WritePixel(X+18, Y+16, 55556);
	ili9325_WritePixel(X+19, Y+16, 55556);
	ili9325_WritePixel(X+20, Y+16, 0);

	ili9325_WritePixel(X+2, Y+17, 0);
	ili9325_WritePixel(X+3, Y+17, 55556);
	ili9325_WritePixel(X+4, Y+17, 55556);
	ili9325_WritePixel(X+5, Y+17, 65535);
	ili9325_WritePixel(X+6, Y+17, 65535);
	ili9325_WritePixel(X+7, Y+17, 65535);
	ili9325_WritePixel(X+8, Y+17, 55556);
	ili9325_WritePixel(X+9, Y+17, 55556);
	ili9325_WritePixel(X+10, Y+17, 0);
	ili9325_WritePixel(X+11, Y+17, 0);
	ili9325_WritePixel(X+12, Y+17, 55556);
	ili9325_WritePixel(X+13, Y+17, 55556);
	ili9325_WritePixel(X+14, Y+17, 55556);
	ili9325_WritePixel(X+15, Y+17, 55556);
	ili9325_WritePixel(X+16, Y+17, 55556);
	ili9325_WritePixel(X+17, Y+17, 55556);
	ili9325_WritePixel(X+18, Y+17, 55556);
	ili9325_WritePixel(X+19, Y+17, 0);

	ili9325_WritePixel(X+3, Y+18, 0);
	ili9325_WritePixel(X+4, Y+18, 55556);
	ili9325_WritePixel(X+5, Y+18, 55556);
	ili9325_WritePixel(X+6, Y+18, 55556);
	ili9325_WritePixel(X+7, Y+18, 55556);
	ili9325_WritePixel(X+8, Y+18, 55556);
	ili9325_WritePixel(X+9, Y+18, 0);
	ili9325_WritePixel(X+12, Y+18, 0);
	ili9325_WritePixel(X+13, Y+18, 55556);
	ili9325_WritePixel(X+14, Y+18, 55556);
	ili9325_WritePixel(X+15, Y+18, 55556);
	ili9325_WritePixel(X+16, Y+18, 55556);
	ili9325_WritePixel(X+17, Y+18, 55556);
	ili9325_WritePixel(X+18, Y+18, 0);

	ili9325_WritePixel(X+4, Y+19, 0);
	ili9325_WritePixel(X+5, Y+19, 55556);
	ili9325_WritePixel(X+6, Y+19, 55556);
	ili9325_WritePixel(X+7, Y+19, 55556);
	ili9325_WritePixel(X+8, Y+19, 0);
	ili9325_WritePixel(X+13, Y+19, 0);
	ili9325_WritePixel(X+14, Y+19, 55556);
	ili9325_WritePixel(X+15, Y+19, 55556);
	ili9325_WritePixel(X+16, Y+19, 55556);
	ili9325_WritePixel(X+17, Y+19, 0);

	ili9325_WritePixel(X+5, Y+20, 0);
	ili9325_WritePixel(X+6, Y+20, 0);
	ili9325_WritePixel(X+7, Y+20, 0);
	ili9325_WritePixel(X+14, Y+20, 0);
	ili9325_WritePixel(X+15, Y+20, 0);
	ili9325_WritePixel(X+16, Y+20, 0);
}
//--- SetHeartGray --- DONE
void SetHeartGray(uint16_t X, uint16_t Y)
{
	ili9325_WritePixel(X+10, Y+1, 0);
	ili9325_WritePixel(X+11, Y+1, 0);

	ili9325_WritePixel(X+9, Y+2, 0);
	ili9325_WritePixel(X+10, Y+2, 33840);
	ili9325_WritePixel(X+11, Y+2, 33840);
	ili9325_WritePixel(X+12, Y+2, 0);

	ili9325_WritePixel(X+8, Y+3, 0);
	ili9325_WritePixel(X+9, Y+3, 33840);
	ili9325_WritePixel(X+10, Y+3, 33840);
	ili9325_WritePixel(X+11, Y+3, 33840);
	ili9325_WritePixel(X+12, Y+3, 33840);
	ili9325_WritePixel(X+13, Y+3, 0);

	ili9325_WritePixel(X+7, Y+4, 0);
	ili9325_WritePixel(X+8, Y+4, 33840);
	ili9325_WritePixel(X+9, Y+4, 33840);
	ili9325_WritePixel(X+10, Y+4, 33840);
	ili9325_WritePixel(X+11, Y+4, 33840);
	ili9325_WritePixel(X+12, Y+4, 33840);
	ili9325_WritePixel(X+13, Y+4, 33840);
	ili9325_WritePixel(X+14, Y+4, 0);

	ili9325_WritePixel(X+6, Y+5, 0);
	ili9325_WritePixel(X+7, Y+5, 33840);
	ili9325_WritePixel(X+8, Y+5, 33840);
	ili9325_WritePixel(X+9, Y+5, 33840);
	ili9325_WritePixel(X+10, Y+5, 33840);
	ili9325_WritePixel(X+11, Y+5, 33840);
	ili9325_WritePixel(X+12, Y+5, 33840);
	ili9325_WritePixel(X+13, Y+5, 33840);
	ili9325_WritePixel(X+14, Y+5, 33840);
	ili9325_WritePixel(X+15, Y+5, 0);

	ili9325_WritePixel(X+5, Y+6, 0);
	ili9325_WritePixel(X+6, Y+6, 33840);
	ili9325_WritePixel(X+7, Y+6, 33840);
	ili9325_WritePixel(X+8, Y+6, 33840);
	ili9325_WritePixel(X+9, Y+6, 33840);
	ili9325_WritePixel(X+10, Y+6, 33840);
	ili9325_WritePixel(X+11, Y+6, 33840);
	ili9325_WritePixel(X+12, Y+6, 33840);
	ili9325_WritePixel(X+13, Y+6, 33840);
	ili9325_WritePixel(X+14, Y+6, 33840);
	ili9325_WritePixel(X+15, Y+6, 33840);
	ili9325_WritePixel(X+16, Y+6, 0);

	ili9325_WritePixel(X+4, Y+7, 0);
	ili9325_WritePixel(X+5, Y+7, 33840);
	ili9325_WritePixel(X+6, Y+7, 33840);
	ili9325_WritePixel(X+7, Y+7, 33840);
	ili9325_WritePixel(X+8, Y+7, 33840);
	ili9325_WritePixel(X+9, Y+7, 33840);
	ili9325_WritePixel(X+10, Y+7, 33840);
	ili9325_WritePixel(X+11, Y+7, 33840);
	ili9325_WritePixel(X+12, Y+7, 33840);
	ili9325_WritePixel(X+13, Y+7, 33840);
	ili9325_WritePixel(X+14, Y+7, 33840);
	ili9325_WritePixel(X+15, Y+7, 33840);
	ili9325_WritePixel(X+16, Y+7, 33840);
	ili9325_WritePixel(X+17, Y+7, 0);

	ili9325_WritePixel(X+3, Y+8, 0);
	ili9325_WritePixel(X+4, Y+8, 33840);
	ili9325_WritePixel(X+5, Y+8, 33840);
	ili9325_WritePixel(X+6, Y+8, 33840);
	ili9325_WritePixel(X+7, Y+8, 33840);
	ili9325_WritePixel(X+8, Y+8, 33840);
	ili9325_WritePixel(X+9, Y+8, 33840);
	ili9325_WritePixel(X+10, Y+8, 33840);
	ili9325_WritePixel(X+11, Y+8, 33840);
	ili9325_WritePixel(X+12, Y+8, 33840);
	ili9325_WritePixel(X+13, Y+8, 33840);
	ili9325_WritePixel(X+14, Y+8, 33840);
	ili9325_WritePixel(X+15, Y+8, 33840);
	ili9325_WritePixel(X+16, Y+8, 33840);
	ili9325_WritePixel(X+17, Y+8, 33840);
	ili9325_WritePixel(X+18, Y+8, 0);

	ili9325_WritePixel(X+2, Y+9, 0);
	ili9325_WritePixel(X+3, Y+9, 33840);
	ili9325_WritePixel(X+4, Y+9, 33840);
	ili9325_WritePixel(X+5, Y+9, 33840);
	ili9325_WritePixel(X+6, Y+9, 33840);
	ili9325_WritePixel(X+7, Y+9, 33840);
	ili9325_WritePixel(X+8, Y+9, 33840);
	ili9325_WritePixel(X+9, Y+9, 33840);
	ili9325_WritePixel(X+10, Y+9, 33840);
	ili9325_WritePixel(X+11, Y+9, 33840);
	ili9325_WritePixel(X+12, Y+9, 33840);
	ili9325_WritePixel(X+13, Y+9, 33840);
	ili9325_WritePixel(X+14, Y+9, 33840);
	ili9325_WritePixel(X+15, Y+9, 33840);
	ili9325_WritePixel(X+16, Y+9, 33840);
	ili9325_WritePixel(X+17, Y+9, 33840);
	ili9325_WritePixel(X+18, Y+9, 33840);
	ili9325_WritePixel(X+19, Y+9, 0);

	ili9325_WritePixel(X+2, Y+10, 0);
	ili9325_WritePixel(X+3, Y+10, 33840);
	ili9325_WritePixel(X+4, Y+10, 33840);
	ili9325_WritePixel(X+5, Y+10, 33840);
	ili9325_WritePixel(X+6, Y+10, 33840);
	ili9325_WritePixel(X+7, Y+10, 33840);
	ili9325_WritePixel(X+8, Y+10, 33840);
	ili9325_WritePixel(X+9, Y+10, 33840);
	ili9325_WritePixel(X+10, Y+10, 33840);
	ili9325_WritePixel(X+11, Y+10, 33840);
	ili9325_WritePixel(X+12, Y+10, 33840);
	ili9325_WritePixel(X+13, Y+10, 33840);
	ili9325_WritePixel(X+14, Y+10, 33840);
	ili9325_WritePixel(X+15, Y+10, 33840);
	ili9325_WritePixel(X+16, Y+10, 33840);
	ili9325_WritePixel(X+17, Y+10, 33840);
	ili9325_WritePixel(X+18, Y+10, 33840);
	ili9325_WritePixel(X+19, Y+10, 0);

	ili9325_WritePixel(X+2, Y+11, 0);
	ili9325_WritePixel(X+3, Y+11, 33840);
	ili9325_WritePixel(X+4, Y+11, 33840);
	ili9325_WritePixel(X+5, Y+11, 33840);
	ili9325_WritePixel(X+6, Y+11, 33840);
	ili9325_WritePixel(X+7, Y+11, 33840);
	ili9325_WritePixel(X+8, Y+11, 33840);
	ili9325_WritePixel(X+9, Y+11, 33840);
	ili9325_WritePixel(X+10, Y+11, 33840);
	ili9325_WritePixel(X+11, Y+11, 33840);
	ili9325_WritePixel(X+12, Y+11, 33840);
	ili9325_WritePixel(X+13, Y+11, 33840);
	ili9325_WritePixel(X+14, Y+11, 33840);
	ili9325_WritePixel(X+15, Y+11, 33840);
	ili9325_WritePixel(X+16, Y+11, 33840);
	ili9325_WritePixel(X+17, Y+11, 33840);
	ili9325_WritePixel(X+18, Y+11, 33840);
	ili9325_WritePixel(X+19, Y+11, 0);

	ili9325_WritePixel(X+1, Y+12, 0);
	ili9325_WritePixel(X+2, Y+12, 33840);
	ili9325_WritePixel(X+3, Y+12, 33840);
	ili9325_WritePixel(X+4, Y+12, 33840);
	ili9325_WritePixel(X+5, Y+12, 33840);
	ili9325_WritePixel(X+6, Y+12, 33840);
	ili9325_WritePixel(X+7, Y+12, 33840);
	ili9325_WritePixel(X+8, Y+12, 33840);
	ili9325_WritePixel(X+9, Y+12, 33840);
	ili9325_WritePixel(X+10, Y+12, 33840);
	ili9325_WritePixel(X+11, Y+12, 33840);
	ili9325_WritePixel(X+12, Y+12, 33840);
	ili9325_WritePixel(X+13, Y+12, 33840);
	ili9325_WritePixel(X+14, Y+12, 33840);
	ili9325_WritePixel(X+15, Y+12, 33840);
	ili9325_WritePixel(X+16, Y+12, 33840);
	ili9325_WritePixel(X+17, Y+12, 33840);
	ili9325_WritePixel(X+18, Y+12, 33840);
	ili9325_WritePixel(X+19, Y+12, 33840);
	ili9325_WritePixel(X+20, Y+12, 0);

	ili9325_WritePixel(X+1, Y+13, 0);
	ili9325_WritePixel(X+2, Y+13, 33840);
	ili9325_WritePixel(X+3, Y+13, 33840);
	ili9325_WritePixel(X+4, Y+13, 33840);
	ili9325_WritePixel(X+5, Y+13, 33840);
	ili9325_WritePixel(X+6, Y+13, 33840);
	ili9325_WritePixel(X+7, Y+13, 33840);
	ili9325_WritePixel(X+8, Y+13, 33840);
	ili9325_WritePixel(X+9, Y+13, 33840);
	ili9325_WritePixel(X+10, Y+13, 33840);
	ili9325_WritePixel(X+11, Y+13, 33840);
	ili9325_WritePixel(X+12, Y+13, 33840);
	ili9325_WritePixel(X+13, Y+13, 33840);
	ili9325_WritePixel(X+14, Y+13, 33840);
	ili9325_WritePixel(X+15, Y+13, 33840);
	ili9325_WritePixel(X+16, Y+13, 33840);
	ili9325_WritePixel(X+17, Y+13, 33840);
	ili9325_WritePixel(X+18, Y+13, 33840);
	ili9325_WritePixel(X+19, Y+13, 33840);
	ili9325_WritePixel(X+20, Y+13, 0);

	ili9325_WritePixel(X+1, Y+14, 0);
	ili9325_WritePixel(X+2, Y+14, 33840);
	ili9325_WritePixel(X+3, Y+14, 54938);
	ili9325_WritePixel(X+4, Y+14, 54938);
	ili9325_WritePixel(X+5, Y+14, 33840);
	ili9325_WritePixel(X+6, Y+14, 33840);
	ili9325_WritePixel(X+7, Y+14, 33840);
	ili9325_WritePixel(X+8, Y+14, 33840);
	ili9325_WritePixel(X+9, Y+14, 33840);
	ili9325_WritePixel(X+10, Y+14, 33840);
	ili9325_WritePixel(X+11, Y+14, 33840);
	ili9325_WritePixel(X+12, Y+14, 33840);
	ili9325_WritePixel(X+13, Y+14, 33840);
	ili9325_WritePixel(X+14, Y+14, 33840);
	ili9325_WritePixel(X+15, Y+14, 33840);
	ili9325_WritePixel(X+16, Y+14, 33840);
	ili9325_WritePixel(X+17, Y+14, 33840);
	ili9325_WritePixel(X+18, Y+14, 33840);
	ili9325_WritePixel(X+19, Y+14, 33840);
	ili9325_WritePixel(X+20, Y+14, 0);

	ili9325_WritePixel(X+1, Y+15, 0);
	ili9325_WritePixel(X+2, Y+15, 33840);
	ili9325_WritePixel(X+3, Y+15, 54938);
	ili9325_WritePixel(X+4, Y+15, 54938);
	ili9325_WritePixel(X+5, Y+15, 54938);
	ili9325_WritePixel(X+6, Y+15, 33840);
	ili9325_WritePixel(X+7, Y+15, 33840);
	ili9325_WritePixel(X+8, Y+15, 33840);
	ili9325_WritePixel(X+9, Y+15, 33840);
	ili9325_WritePixel(X+10, Y+15, 33840);
	ili9325_WritePixel(X+11, Y+15, 33840);
	ili9325_WritePixel(X+12, Y+15, 33840);
	ili9325_WritePixel(X+13, Y+15, 33840);
	ili9325_WritePixel(X+14, Y+15, 33840);
	ili9325_WritePixel(X+15, Y+15, 33840);
	ili9325_WritePixel(X+16, Y+15, 33840);
	ili9325_WritePixel(X+17, Y+15, 33840);
	ili9325_WritePixel(X+18, Y+15, 33840);
	ili9325_WritePixel(X+19, Y+15, 33840);
	ili9325_WritePixel(X+20, Y+15, 0);

	ili9325_WritePixel(X+1, Y+16, 0);
	ili9325_WritePixel(X+2, Y+16, 33840);
	ili9325_WritePixel(X+3, Y+16, 33840);
	ili9325_WritePixel(X+4, Y+16, 54938);
	ili9325_WritePixel(X+5, Y+16, 54938);
	ili9325_WritePixel(X+6, Y+16, 33840);
	ili9325_WritePixel(X+7, Y+16, 33840);
	ili9325_WritePixel(X+8, Y+16, 33840);
	ili9325_WritePixel(X+9, Y+16, 33840);
	ili9325_WritePixel(X+10, Y+16, 33840);
	ili9325_WritePixel(X+11, Y+16, 33840);
	ili9325_WritePixel(X+12, Y+16, 33840);
	ili9325_WritePixel(X+13, Y+16, 33840);
	ili9325_WritePixel(X+14, Y+16, 33840);
	ili9325_WritePixel(X+15, Y+16, 33840);
	ili9325_WritePixel(X+16, Y+16, 33840);
	ili9325_WritePixel(X+17, Y+16, 33840);
	ili9325_WritePixel(X+18, Y+16, 33840);
	ili9325_WritePixel(X+19, Y+16, 33840);
	ili9325_WritePixel(X+20, Y+16, 0);

	ili9325_WritePixel(X+2, Y+17, 0);
	ili9325_WritePixel(X+3, Y+17, 33840);
	ili9325_WritePixel(X+4, Y+17, 33840);
	ili9325_WritePixel(X+5, Y+17, 54938);
	ili9325_WritePixel(X+6, Y+17, 54938);
	ili9325_WritePixel(X+7, Y+17, 54938);
	ili9325_WritePixel(X+8, Y+17, 33840);
	ili9325_WritePixel(X+9, Y+17, 33840);
	ili9325_WritePixel(X+10, Y+17, 0);
	ili9325_WritePixel(X+11, Y+17, 0);
	ili9325_WritePixel(X+12, Y+17, 33840);
	ili9325_WritePixel(X+13, Y+17, 33840);
	ili9325_WritePixel(X+14, Y+17, 33840);
	ili9325_WritePixel(X+15, Y+17, 33840);
	ili9325_WritePixel(X+16, Y+17, 33840);
	ili9325_WritePixel(X+17, Y+17, 33840);
	ili9325_WritePixel(X+18, Y+17, 33840);
	ili9325_WritePixel(X+19, Y+17, 0);

	ili9325_WritePixel(X+3, Y+18, 0);
	ili9325_WritePixel(X+4, Y+18, 33840);
	ili9325_WritePixel(X+5, Y+18, 33840);
	ili9325_WritePixel(X+6, Y+18, 33840);
	ili9325_WritePixel(X+7, Y+18, 33840);
	ili9325_WritePixel(X+8, Y+18, 33840);
	ili9325_WritePixel(X+9, Y+18, 0);
	ili9325_WritePixel(X+12, Y+18, 0);
	ili9325_WritePixel(X+13, Y+18, 33840);
	ili9325_WritePixel(X+14, Y+18, 33840);
	ili9325_WritePixel(X+15, Y+18, 33840);
	ili9325_WritePixel(X+16, Y+18, 33840);
	ili9325_WritePixel(X+17, Y+18, 33840);
	ili9325_WritePixel(X+18, Y+18, 0);

	ili9325_WritePixel(X+4, Y+19, 0);
	ili9325_WritePixel(X+5, Y+19, 33840);
	ili9325_WritePixel(X+6, Y+19, 33840);
	ili9325_WritePixel(X+7, Y+19, 33840);
	ili9325_WritePixel(X+8, Y+19, 0);
	ili9325_WritePixel(X+13, Y+19, 0);
	ili9325_WritePixel(X+14, Y+19, 33840);
	ili9325_WritePixel(X+15, Y+19, 33840);
	ili9325_WritePixel(X+16, Y+19, 33840);
	ili9325_WritePixel(X+17, Y+19, 0);

	ili9325_WritePixel(X+5, Y+20, 0);
	ili9325_WritePixel(X+6, Y+20, 0);
	ili9325_WritePixel(X+7, Y+20, 0);
	ili9325_WritePixel(X+14, Y+20, 0);
	ili9325_WritePixel(X+15, Y+20, 0);
	ili9325_WritePixel(X+16, Y+20, 0);
}
//--- UpdateHP --- DONE
void UpdateHP(int HP)
{
	for(int i=0; i<78; i++)
		for(int j=0; j<30; j++)
			ili9325_WritePixel(1+i,240-j,64203);
	switch(HP)
	{
	case 0:
		SetHeartGray(5,216);
		SetHeartGray(29,216);
		SetHeartGray(53,216);
		break;
	case 1:
		SetHeartRed(5,216);
		SetHeartGray(29,216);
		SetHeartGray(53,216);
		break;
	case 2:
		SetHeartRed(5,216);
		SetHeartRed(29,216);
		SetHeartGray(53,216);
		break;
	case 3:
		SetHeartRed(5,216);
		SetHeartRed(29,216);
		SetHeartRed(53,216);
		break;
	}
}
//--- SpeedUpdate --- DONE
int SpeedUpdate(int speed)
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) && speed<500)
	{
		speed+=10;
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) && speed>100)
	{
		speed-=10;
	}
	return speed;
}
//--- CreateHitboxY --- DONE
int *CreateSquareHitboxY(int Y, int r)
{
	int size = r*8;
	int *tab = (int*)malloc(size*sizeof(int));

	int i=0;
	int j=r;

	for(; i<r*2+1; i++)
		tab[i]=Y+r;
	while(j!=0)
	{
    j--;
    tab[i]=Y+j;
		i++;
	}
	while(j!=r)
	{
		j++;
    tab[i]=Y-j;
		i++;
	}
	for(; i<r*6+1; i++)
		tab[i]=Y-r;
	while(j!=0)
	{
    j--;
    tab[i]=Y-j;
    i++;
	}
	while(j!=r)
	{
		j++;
    tab[i]=Y+j;
		i++;
	}
	return tab;
}
//--- CreateHitboxX --- DONE
int *CreateSquareHitboxX(int X, int r)
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
		j--;
    tab[i]=X+j;
    i++;
	}
	while(j!=r)
	{
		j++;
    tab[i]=X-j;
		i++;
	}
	for(; i<r*8; i++)
		tab[i]=X-r;

  return tab;
}
//--- CreateRectangleHitboxY --- DONE
int *CreateRectangleHitboxY(int Y, int r1, int r2)
{
	int size = (r1*4+2)+(r2*4+2)-4;
	int *tab = (int*)malloc(size*sizeof(int));

	int i=0;
	int j1=r1;
	int j2=r2;

	for(; i<r1*2+1; i++)
		tab[i]=Y+r2;
	while(j2!=0)
	{
    j2--;
    tab[i]=Y+j2;
		i++;
	}
	while(j2!=r2)
	{
		j2++;
    tab[i]=Y-j2;
		i++;
	}
	for(; i<r1*2+1+r2*2+r1*2; i++)
		tab[i]=Y-r2;
	while(j2!=0)
	{
    j2--;
    tab[i]=Y-j2;
    i++;
	}
	while(j2!=r2)
	{
		j2++;
    tab[i]=Y+j2;
		i++;
	}
	return tab;
}
//--- CreateRectangleHitboxX --- DONE
int *CreateRectangleHitboxX(int X, int r1, int r2)
{
	int size = (r1*4+2)+(r2*4+2)-4;
	int *tab = (int*)malloc(size*sizeof(int));

	int i=0;
	int j1=r1;
	int j2=r2;

	tab[i]=X-j1;

	while(j1!=0)
	{
		i++;
		j1--;
		tab[i]=X-j1;
	}
	while(j1!=r1)
	{
		i++;
		j1++;
		tab[i]=X+j1;
	}
	i++;
	for(; i<r1*2+r2*2+1; i++)
		tab[i]=X+r1;
  while(j1!=0)
	{
		j1--;
    tab[i]=X+j1;
    i++;
	}
	while(j1!=r1)
	{
		j1++;
    tab[i]=X-j1;
		i++;
	}
  for(; i<r1*4+r2*4; i++)
		tab[i]=X-r1;

  return tab;
}
//--- Collision --- DONE
int Collision(int *X1, int *Y1, int r1a, int r1b, int *X2, int *Y2, int r2a, int r2b)
{
  int h1 = r1a*4+r1b*4;
  int h2 = r2a*4+r2b*4;
  for(int i=0; i<h1; i++)
  {
	  for(int j=0; j<h2; j++)
	  {
		  if(X1[i]==X2[j] && Y1[i]==Y2[j]) return 1;
	  }
  }
  return 0;
}
//--- PressContinueButton() --- DONE
void PressContinueButton()
{
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3))
			break;
	}
}
//--- BorderCollision --- DONE
int BorderCollision(int *X1, int *Y1, int r1a, int r1b, int *X2, int *Y2)
{
  int h1 = r1a*4+r1b*4;

  for(int i=0; i<h1; i++)
  {
	  for(int j=0; j<60; j++)
	  {
		  if(X1[i]==X2[j] && Y1[i]==Y2[j]) return 1;
	  }
  }
  return 0;
}
//--- SetObstacle --- DONE
void SetObstacle(int obs, int X, int Y)
{
	switch(obs)
	{
	case 1:
		SetSnowman(X, Y);
		break;
	case 2:
		SetRock(X, Y);
		break;
	case 3:
		SetBowman(X, Y);
		break;
	case 4:
		SetTree(X, Y);
		break;
	}
}
