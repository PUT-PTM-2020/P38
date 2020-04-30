# WINTER RACER
MAKSIM BRZEZINSKI & MIŁOSZ ORLIŃSKI

Winter Race to gra zręcznościowe, w której sterujemy narciarzem. Jego zdaniem jest jak najszybsze przebycie całej trasy, 
unikając przy tym różnych przeszkód, takich jak drzewa, kamienie, bałwany oraz łucznicy. Na końcu trasy znajduje się 
księżniczka porwana przez smoka, a gracz musi ją uratować.

### MODUŁY
* Wyświetlacz TFT LCD 3,2" HY32D ILI9325
* Płytka uruchomieniowa STM32F407G-DISC1
* Płytka Waveshare 8 Push Buttons
* Moduł czytnika microSD z kartą pamięci 4 GB SDHC
* Głośnik okrągły 78 mm, 1W YD78
* Wzmacniacz audio stereo PAM8403 5V 3W

### UPDATES

#### 24.03.2020
* Uzgodnienie szczegółowych założeń dotyczących projektu
* Zapisanie szkieletu części wykorzystywanych funkcji backendowcyh
#### 07.04.2020
* Funkcja rysująca planszę MENU
* Funkcja rysująca planszę RANKING
* Graficzna implementacja trzech przeszkód
#### 28.04.2020
* Podłączenie ekranu LCD
* Graficzna implementacja ostatniej przeszkody
* Graficzna implementacja narciarza w trzech pozycjach
* Podłączenie czytnika kart SD
* Funkcja wczytująca oraz zapisująca ranking na karcie SD
* Szkielet funkcji efektów dźwiękowych

### FUNKCJE
* void SetBowman(uint16_t X, uint16_t Y) - rysuje łucznika
* void SetTree(uint16_t X, uint16_t Y) - rysuje drzewo
* void SetSkierFront(uint16_t X, uint16_t Y) - rysuje narciarza jadącego na wprost
* void SetSkierLeft(uint16_t X, uint16_t Y) - rysuje narciarza skręcającego w lewo
* void SetSkierRight(uint16_t X, uint16_t Y) - rysuje narciarza skręcającego w prawo
* void WriteToRanking(char* ranking) - zapisuje ranking
* void ReadFromRanking(char* ranking) - wczytuje ranking
* void Sound(uint8_t option) - wywołuje odpowiedni dźwięk w zależności od eventu
* void DrawMenu(uint8_t Mode) - rysuje planszę MENU
* void ChangeTargetMenu(uint8_t option, uint8_t LastOption) - podświetla opcję w MENU, którą wybraliśmy
* void UseMenu() - odpowiada za sterowanie wyborem opcji w MENU
* void DrawRanking(uint8_t Mode) - rysuje planszę RANKING
* void ChangeTargetRanking(uint8_t option, uint8_t LastOption) - podświetla opcję na planszy RANKING, którą wybraliśmy
* void UseRanking() - odpowiada za sterowanie wyborem opcji na planszy RANKING
* void SetSnowman(uint16_t X, uint16_t Y) - rysuje bałwana
* void SetRock(uint16_t X, uint16_t Y) - rysuje skałę
* int *createHitbox_Y(int Y, int r) - tworzy hitbox obiektu
* void positionUpdate(float accX, float speed, int& X, int& Y) - aktualizuje położenie narciarza
* void drawSkier(int position) - dobiera i rysuje odpowiednią pozycję narciarza, w zależności od wychylenia akcelerometru
* void speedUpdate(float& speed) - aktualizuje prędkość przemieszczania się narciarza
* _Bool collision(X1, Y1, X2, Y2) - sprawdza, czy nastąpiła kolizja między obiektami

### GŁÓWNE BIBLIOTEKI
* ili9325.h
* bmp.h 
* lcd_io_gpio8.h 
* stm32_adafruit_lcd.h
* lcd.h
* fonts.h
* ff.h
* lis3dsh.h
* math.h
* stdlib.h

