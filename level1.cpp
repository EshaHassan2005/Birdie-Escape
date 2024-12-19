#include "iGraphics.h"
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>
using namespace std;

#define screenWidth 1550
#define screenHight 850
#define backgroundSpeed 43
#define ROCKNUMBER 10

int mx = 0, my = 0;
int mposx, mposy;
int x = 400;
int y = 600;
int flag = 0;
int flag1 = 0;
int gameOver = 0;
int Score = 0;
int CoinNumber = 0;
int SoundNumber = 0;
int Sound_Maximum = 25;
int HScore = 0;

int idx = 0;
int flying_idx = 0;
int obstacle_idx = 0;
bool isFlapping = false;
bool collision = false;
bool cloudInitialized = false;
bool soundOn = false;
bool hideDizzyBird = false;
bool musicOn = true;

void change();
char bird_flying[6][50] = {"E:\\Games\\Sprites\\Birds\\tile000.bmp", "E:\\Games\\Sprites\\Birds\\tile001.bmp", "E:\\Games\\Sprites\\Birds\\tile002.bmp", "E:\\Games\\Sprites\\Birds\\tile003.bmp", "E:\\Games\\Sprites\\Birds\\tile004.bmp", "E:\\Games\\Sprites\\Birds\\tile005.bmp"};

char background_img[41][50] = {"E:\\Games\\Background\\Sky1\\tile000.bmp", "E:\\Games\\Background\\Sky1\\tile001.bmp", "E:\\Games\\Background\\Sky1\\tile002.bmp", "E:\\Games\\Background\\Sky1\\tile003.bmp", "E:\\Games\\Background\\Sky1\\tile004.bmp",
							   "E:\\Games\\Background\\Sky1\\tile005.bmp", "E:\\Games\\Background\\Sky1\\tile006.bmp", "E:\\Games\\Background\\Sky1\\tile007.bmp", "E:\\Games\\Background\\Sky1\\tile008.bmp", "E:\\Games\\Background\\Sky1\\tile009.bmp",
							   "E:\\Games\\Background\\Sky1\\tile010.bmp", "E:\\Games\\Background\\Sky1\\tile011.bmp", "E:\\Games\\Background\\Sky1\\tile012.bmp", "E:\\Games\\Background\\Sky1\\tile013.bmp", "E:\\Games\\Background\\Sky1\\tile014.bmp",
							   "E:\\Games\\Background\\Sky1\\tile015.bmp", "E:\\Games\\Background\\Sky1\\tile016.bmp", "E:\\Games\\Background\\Sky1\\tile017.bmp", "E:\\Games\\Background\\Sky1\\tile018.bmp", "E:\\Games\\Background\\Sky1\\tile019.bmp",
							   "E:\\Games\\Background\\Sky1\\tile020.bmp", "E:\\Games\\Background\\Sky1\\tile021.bmp", "E:\\Games\\Background\\Sky1\\tile022.bmp", "E:\\Games\\Background\\Sky1\\tile023.bmp", "E:\\Games\\Background\\Sky1\\tile024.bmp",
							   "E:\\Games\\Background\\Sky1\\tile025.bmp", "E:\\Games\\Background\\Sky1\\tile026.bmp", "E:\\Games\\Background\\Sky1\\tile027.bmp", "E:\\Games\\Background\\Sky1\\tile028.bmp", "E:\\Games\\Background\\Sky1\\tile029.bmp",
							   "E:\\Games\\Background\\Sky1\\tile030.bmp", "E:\\Games\\Background\\Sky1\\tile031.bmp", "E:\\Games\\Background\\Sky1\\tile032.bmp", "E:\\Games\\Background\\Sky1\\tile033.bmp", "E:\\Games\\Background\\Sky1\\tile034.bmp",
							   "E:\\Games\\Background\\Sky1\\tile035.bmp", "E:\\Games\\Background\\Sky1\\tile036.bmp", "E:\\Games\\Background\\Sky1\\tile037.bmp", "E:\\Games\\Background\\Sky1\\tile038.bmp", "E:\\Games\\Background\\Sky1\\tile039.bmp", "E:\\Games\\Background\\Sky1\\tile040.bmp"};

char dizzy_bird[50] = "E:\\Games\\Sprites\\BirdDizzy.bmp";
char obstacles1[6][80] = {"E:\\Games\\Sprites\\Obstacles\\cloud1.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud2.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud3.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud3.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud3.bmp"};
char obstacles2[7][80] = {"E:\\Games\\Sprites\\Obstacles\\tile005.bmp", "E:\\Games\\Sprites\\Obstacles\\tile006.bmp", "E:\\Games\\Sprites\\Obstacles\\tile007.bmp", "E:\\Games\\Sprites\\Obstacles\\tile008.bmp", "E:\\Games\\Sprites\\Obstacles\\tile009.bmp", "E:\\Games\\Sprites\\Obstacles\\tile000.bmp"};
char obstacles3[6][80] = {"E:\\Games\\Sprites\\Obstacles\\cloud1.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud2.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud3.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud2.bmp", "E:\\Games\\Sprites\\Obstacles\\cloud3.bmp"};
char cloud[50] = "E:\\Games\\Sprites\\Clouds\\Cloud.bmp";
char ScoreBoard1[50] = "E:\\Games\\Home Menu\\Scoreboard1.bmp";
char Coins[6][80] = {"E:\\Games\\Home Menu\\Coin.bmp", "E:\\Games\\Home Menu\\Coin.bmp", "E:\\Games\\Home Menu\\Coin.bmp", "E:\\Games\\Home Menu\\Coin.bmp", "E:\\Games\\Home Menu\\Coin.bmp"};
char ScoreBar[80] = "E:\\Games\\Home Menu\\ScoreBar.bmp";
char ScoreBar1[80] = "E:\\Games\\Home Menu\\ScoreBar2.bmp";
char Arrow[80] = "E:\\Games\\Home Menu\\Arrow2.bmp";
char CoinBar[50] = "E:\\Games\\Home Menu\\CoinBar.bmp";
struct background
{
	int bx;
	int by;
};

background Background[41];

void update_bird()
{
	flying_idx = (flying_idx + 1) % 6;
}

void HideDizzyBird()
{
	flag1 = 1;
}
struct Obstacle
{
	signed int rock_x;
	int rock_y;
	bool rock_show;
	int rock_idx;
};

struct Cloud
{
	int cl_x;
	int cl_y;
	bool cl_show;
} cloud1;

struct Coin
{
	int coin_x;
	int coin_y;
	bool coin_show;
	int coin_idx;
};

Obstacle enemy1, enemy2, enemy3;

Coin coin1, coin2;

void saveScore(int score)
{
	FILE *fp;
	if ((fp = fopen("Score_level1.txt", "w")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}

	fprintf(fp, "%d\n", score);
	fclose(fp);
}

void getScore_level1(int &score)
{
	FILE *fp;
	if ((fp = fopen("Score_level1.txt", "r")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}
	fscanf(fp, "%d", &score);
	fclose(fp);
}

void playSound(char Sound[])
{
	char soundCommand[512];
	sprintf(soundCommand, "close sound%d", SoundNumber);
	mciSendString(soundCommand, NULL, 0, NULL);

	sprintf(soundCommand, "open \"%s\" type waveaudio alias sound%d", Sound, SoundNumber);
	mciSendString(soundCommand, NULL, 0, NULL);

	sprintf(soundCommand, "play sound%d", SoundNumber);
	mciSendString(soundCommand, NULL, 0, NULL);

	SoundNumber = (SoundNumber + 1) % Sound_Maximum;
}

void iDraw()
{

	iClear();

	for (int i = 0; i < 41; i++)
	{
		iShowBMP(Background[i].bx, Background[i].by, background_img[i]);
	}

	if (flag)
	{
		iShowBMP2(x, y, dizzy_bird, 0);
	}
	else
	{
		iShowBMP2(x, y, bird_flying[flying_idx], 0);
	}

	if (enemy1.rock_show)
		iShowBMP2(enemy1.rock_x, enemy1.rock_y, obstacles1[enemy1.rock_idx], 0);

	if (enemy2.rock_show)
		iShowBMP2(enemy2.rock_x, enemy2.rock_y, obstacles2[enemy2.rock_idx], 0);

	if (enemy3.rock_show)
		iShowBMP2(enemy3.rock_x, enemy3.rock_y, obstacles3[enemy3.rock_idx], 0);

	if (cloud1.cl_show)
		iShowBMP2(cloud1.cl_x, cloud1.cl_y, cloud, 0);

	if (coin1.coin_show)
		iShowBMP2(coin1.coin_x, coin1.coin_y, Coins[coin1.coin_idx], 0);
	if (coin2.coin_show)
		iShowBMP2(coin2.coin_x, coin2.coin_y, Coins[coin2.coin_idx], 0);

	iShowBMP2(600, 770, ScoreBar1, 0);
	char score1[80];
	sprintf(score1, "%d", Score);
	iSetColor(0, 0, 255);
	iText(720, 798, score1, GLUT_BITMAP_TIMES_ROMAN_24);

	iShowBMP2(350, 788, CoinBar, 0);
	char coinNum[80];
	sprintf(coinNum, "%d", CoinNumber);
	iSetColor(255, 255, 255);
	iText(432, 811, coinNum, GLUT_BITMAP_TIMES_ROMAN_24);

	char HighScore[80];
	sprintf(HighScore, "HIGHEST SCORE:: %d", HScore);
	iSetColor(0, 0, 0);
	iText(1265, 822, HighScore, GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(255, 0, 0);
	iRectangle(0, 0, screenWidth, screenHight);
}

void iKeyboard(unsigned char key)
{
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (!flag)
		{
			y += 80;
			Score += 2;
			isFlapping = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!flag)
		{
			y -= 30;
			Score += 2;
			isFlapping = true;
		}
	}

	if (flag1 && mx >= 920 && mx <= 1060 && my >= 195 && my <= 255)
	{
		exit(0);
	}
}
void iPassiveMouseMove(int x, int y)
{
	// put your code here
}
void iMouseMove(int x, int y)
{
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_F2)
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
		}
		else
		{
			musicOn = true;
			PlaySound("E:\\Games\\Music\\level1music1.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (!flag)
		{
			x -= 40;
			Score += 2;
			isFlapping = true;
		}
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (!flag)
		{
			x += 40;
			Score += 2;
			isFlapping = true;
		}
	}
	else if (key == GLUT_KEY_UP)
	{
		if (!flag)
		{
			y += 80;
			Score += 2;
			isFlapping = true;
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (!flag)
		{
			y -= 30;
			Score += 2;
			isFlapping = true;
		}
	}
}

void change()
{
	if (gameOver)
	{

		PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
		flag = 1;
		if (!hideDizzyBird)
		{
			iSetTimer(1000, HideDizzyBird);
			playSound("E:\\Games\\Music\\BirdCollided.wav");
			hideDizzyBird = true;
		}
	}

	if (flag1)
	{
		saveScore(Score);
		exit(0);
	}
	if (!isFlapping)
	{
		if (!flag)
			y -= 10;
	}
	else
	{
		isFlapping = false;
	}
	flying_idx++;
	if (flying_idx >= 6)
		flying_idx = 0;

	if (y >= (screenHight - 106) || y <= 0)
	{
		gameOver = 1;
	}

	for (int i = 0; i < 41; i++)
	{
		if (!flag)
			Background[i].bx -= backgroundSpeed;

		if (Background[i].bx <= 0)
		{
			Background[i].bx = screenWidth;
		}
	}

	srand(time(NULL));

	if ((((enemy1.rock_x + 40) >= (x + 10) && (enemy1.rock_x + 40) <= (x + 134)) || ((enemy1.rock_x + 180) >= (x + 10) && (enemy1.rock_x + 180) <= (x + 134)) || ((enemy1.rock_x + 100) >= (x + 10) && (enemy1.rock_x + 100) <= (x + 134))) && (((enemy1.rock_y + 40) >= (y + 34) && (enemy1.rock_y + 40) <= (y + 106)) || ((enemy1.rock_y + 120) >= (y + 34) && (enemy1.rock_y + 120) <= (y + 106)) || ((enemy1.rock_y + 40) <= (y + 70) && (enemy1.rock_y + 120) >= (y + 70))))
	{
		gameOver = 1;
	}
	if ((((enemy2.rock_x + 10) >= (x + 10) && (enemy2.rock_x + 10) <= (x + 138)) || ((enemy2.rock_x + 65) >= (x + 10) && (enemy2.rock_x + 65) <= (x + 138))) && (((enemy2.rock_y + 5) >= (y + 20) && (enemy2.rock_y + 10) <= (y + 116)) || ((enemy2.rock_y + 66) >= (y + 25) && (enemy2.rock_y + 66) <= (y + 116)) || ((enemy2.rock_y + 10) <= (y + 33) && (enemy2.rock_y + 66) >= (y + 33))))
	{
		gameOver = 1;
	}
	if ((((enemy3.rock_x + 40) >= (x + 10) && (enemy3.rock_x + 40) <= (x + 134)) || ((enemy3.rock_x + 180) >= (x + 10) && (enemy3.rock_x + 180) <= (x + 134)) || ((enemy3.rock_x + 100) >= (x + 10) && (enemy3.rock_x + 100) <= (x + 134))) && (((enemy3.rock_y + 40) >= (y + 34) && (enemy3.rock_y + 40) <= (y + 106)) || ((enemy3.rock_y + 120) >= (y + 34) && (enemy3.rock_y + 120) <= (y + 106)) || ((enemy3.rock_y + 40) <= (y + 70) && (enemy3.rock_y + 120) >= (y + 70))))
	{
		gameOver = 1;
	}

	else
	{

		if (!flag)
			enemy1.rock_x -= 25;
		if (enemy1.rock_x <= -200)
		{
			srand(time(NULL));
			enemy1.rock_show = false;
			enemy1.rock_x = screenWidth;
			enemy1.rock_y = 200 + (rand() % 200);
			enemy1.rock_idx = rand() % 5;
		}

		if (!flag)
			enemy2.rock_x -= 30;
		if (enemy2.rock_x <= -200)
		{
			srand(time(NULL));
			enemy2.rock_show = false;
			enemy2.rock_x = screenWidth;
			enemy2.rock_y = 100 + (rand() % 100);
			enemy2.rock_idx = rand() % 6;
		}

		if (!flag)
			enemy3.rock_x -= 15;
		if (enemy3.rock_x <= -200)
		{
			srand(time(NULL));
			enemy3.rock_show = false;
			enemy3.rock_x = screenWidth;
			enemy3.rock_y = 200 + (rand() % 550);
			enemy3.rock_idx = rand() % 5;
		}

		if (enemy1.rock_x >= -200 && enemy1.rock_x <= screenWidth)
			enemy1.rock_show = true;
		if (enemy2.rock_x >= -200 && enemy2.rock_x <= screenWidth)
			enemy2.rock_show = true;
		if (enemy3.rock_x >= -200 && enemy3.rock_x <= screenWidth)
			enemy3.rock_show = true;
	}

	if ((((cloud1.cl_x + 38) >= (x + 10) && (cloud1.cl_x + 38) <= (x + 134)) || ((cloud1.cl_x + 208) >= (x + 10) && (cloud1.cl_x + 208) <= (x + 134)) || ((cloud1.cl_x + 125) >= (x + 10) && (cloud1.cl_x + 125) <= (x + 134))) && (((cloud1.cl_y + 25) >= (y + 34) && (cloud1.cl_y + 25) <= (y + 106)) || ((cloud1.cl_y + 140) >= (y + 34) && (cloud1.cl_y + 140) <= (y + 106)) || ((cloud1.cl_y + 80) >= (y + 34) && (cloud1.cl_y + 80) <= (y + 106))))
	{
		gameOver = 1;
	}

	else
	{

		if (!flag)
			cloud1.cl_x -= 25;

		if (cloud1.cl_x < 0)
		{
			cloud1.cl_show = false;
		}

		if (cloud1.cl_x >= 0 && cloud1.cl_x <= screenWidth)
			cloud1.cl_show = true;
	}

	if ((coin1.coin_x >= (x + 10) && coin1.coin_x <= (x + 132) && coin1.coin_y >= (y + 60) && coin1.coin_y <= (y + 130)) || ((coin1.coin_x + 60) >= (x + 10) && (coin1.coin_x + 60) <= (x + 132) && (coin1.coin_y + 70) >= (y + 60) && (coin1.coin_y + 70) <= (y + 130)) || ((coin1.coin_x + 30) >= (x + 10) && (coin1.coin_x + 30) <= (x + 132) && (coin1.coin_y + 35) >= (y + 60) && (coin1.coin_y + 35) <= (y + 130)))
	{
		playSound("E:\\Games\\Music\\Coin_received1.wav");
		coin1.coin_show = false;
		Score += 10;
		CoinNumber += 1;
		coin1.coin_x = screenWidth;
		coin1.coin_y = 100 + rand() % 200;
		coin1.coin_idx = rand() % 5;
	}

	if ((coin2.coin_x >= (x + 10) && coin2.coin_x <= (x + 132) && coin2.coin_y >= (y + 60) && coin2.coin_y <= (y + 130)) || ((coin2.coin_x + 60) >= (x + 10) && (coin2.coin_x + 60) <= (x + 132) && (coin2.coin_y + 70) >= (y + 60) && (coin2.coin_y + 70) <= (y + 130)) || ((coin2.coin_x + 30) >= (x + 10) && (coin2.coin_x + 30) <= (x + 132) && (coin2.coin_y + 35) >= (y + 60) && (coin2.coin_y + 35) <= (y + 120)))
	{
		playSound("E:\\Games\\Music\\Coin_received1.wav");
		coin1.coin_show = false;
		Score += 10;
		CoinNumber += 1;
		coin2.coin_x = screenWidth;
		coin2.coin_y = 600 + rand() % 200;
		coin2.coin_idx = rand() % 5;
	}
	else
	{

		if (!flag)
		{
			coin1.coin_x -= 25;
			coin2.coin_x -= 35;
		}
		if (coin1.coin_x < 0)
		{
			coin1.coin_show = false;
			coin1.coin_x = screenWidth;
			coin1.coin_y = 100 + rand() % 200;
			coin1.coin_idx = rand() % 5;
		}
		if (coin2.coin_x < 0)
		{
			coin2.coin_show = false;
			coin2.coin_x = screenWidth;
			coin2.coin_y = 400 + rand() % 200;
			coin2.coin_idx = rand() % 5;
		}

		if (coin1.coin_x >= 0 && coin1.coin_x <= screenWidth)
			coin1.coin_show = true;
		if (coin2.coin_x >= 0 && coin2.coin_x <= screenWidth)
			coin2.coin_show = true;
	}
}

void setBackground()
{
	int sum = 88;
	for (int i = 0; i < 41; i++)
	{
		Background[i].by = 0;
		Background[i].bx = sum;
		sum += 43;
	}
}

void setEnemyVariables()
{

	srand(time(NULL));
	enemy1.rock_x = screenWidth;
	enemy1.rock_y = 200 + (rand() % 200);
	enemy2.rock_x = screenWidth;
	enemy2.rock_y = 50 + (rand() % 400);
	enemy3.rock_x = screenWidth;
	enemy3.rock_y = 500 + (rand() % 200);
	enemy1.rock_idx = 0;
	enemy2.rock_idx = 0;
	enemy3.rock_idx = 0;
	enemy1.rock_show = false;
	enemy2.rock_show = false;
	enemy3.rock_show = false;
}
void setCloudVariables1()
{
	if (cloudInitialized)
	{
		cloud1.cl_x = screenWidth;
		cloud1.cl_y = 100 + rand() % 700;
		cloud1.cl_show = true;
	}
}

void InitializeCloud1()
{
	srand(time(NULL));
	cloud1.cl_x = screenWidth;
	cloud1.cl_y = 100 + rand() % 700;
	cloud1.cl_show = true;
}

void InitializeCloud1_Once()
{
	if (!cloudInitialized)
	{
		InitializeCloud1();
		cloudInitialized = true;
	}
}

void setCoinVariables()
{
	coin1.coin_x = screenWidth;
	coin1.coin_y = 200 + rand() % 500;
	coin2.coin_x = screenWidth;
	coin2.coin_y = 300 + rand() % 200;
	coin1.coin_show = true;
	coin2.coin_show = true;
	coin1.coin_idx = 0;
	coin2.coin_idx = 0;
}
int main()
{

	srand(time(NULL));
	setBackground();
	setCoinVariables();
	setEnemyVariables();
	iSetTimer(20000, InitializeCloud1_Once);
	iSetTimer(10000, setCloudVariables1);
	iSetTimer(60, change);
	getScore_level1(HScore);
	if (musicOn)
		PlaySound("E:\\Games\\Music\\level1music1.wav", NULL, SND_LOOP | SND_ASYNC);
	// iInitialize(screenWidth, screenHight, "TestGame1");
	iInitialize(screenWidth, screenHight, "Birdie Escape");
	return 0;
}
