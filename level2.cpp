#include "iGraphics.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
using namespace std;

#define screenWidth 1565
#define screenHight 850
#define backgroundSpeed 31
#define ROCKNUMBER 10

int mx = 0, my = 0;
int mposx, mposy;
int x = 470;
int y = 600;
int flag = 0;
int flag1 = 0;
int gameOver = 0;
int Score = 0;
int g_x;
int g_y;
int gift_duration = 100000000;
int gift_open_counter = 0;
int StarNumber = 0;
int GiftNumber = 0;
int SoundNumber = 0;
int Sound_Maximum = 25;
int HScore = 0;

int idx = 0;
int flying_idx = 0;
int flying_idx1 = 0;
int obstacle_idx = 0;
bool isFlapping = false;
bool collision = false;
bool flag_eb = false;
bool flag_cloud2 = false;
bool flag_cloud3 = false;
bool flag_cloud4 = false;
bool flag_gift1 = false;
bool flag_gift2 = false;
bool gift_collision = false;
bool timer_setup = false;
bool musicOn = true;

void change();
void setGift1();
char background_img[51][50] = {"E:\\Games\\Background\\Sky2\\tile000.bmp", "E:\\Games\\Background\\Sky2\\tile001.bmp", "E:\\Games\\Background\\Sky2\\tile002.bmp", "E:\\Games\\Background\\Sky2\\tile003.bmp", "E:\\Games\\Background\\Sky2\\tile004.bmp",
							   "E:\\Games\\Background\\Sky2\\tile005.bmp", "E:\\Games\\Background\\Sky2\\tile006.bmp", "E:\\Games\\Background\\Sky2\\tile007.bmp", "E:\\Games\\Background\\Sky2\\tile008.bmp", "E:\\Games\\Background\\Sky2\\tile009.bmp",
							   "E:\\Games\\Background\\Sky2\\tile010.bmp", "E:\\Games\\Background\\Sky2\\tile011.bmp", "E:\\Games\\Background\\Sky2\\tile012.bmp", "E:\\Games\\Background\\Sky2\\tile013.bmp", "E:\\Games\\Background\\Sky2\\tile014.bmp",
							   "E:\\Games\\Background\\Sky2\\tile015.bmp", "E:\\Games\\Background\\Sky2\\tile016.bmp", "E:\\Games\\Background\\Sky2\\tile017.bmp", "E:\\Games\\Background\\Sky2\\tile018.bmp", "E:\\Games\\Background\\Sky2\\tile019.bmp",
							   "E:\\Games\\Background\\Sky2\\tile020.bmp", "E:\\Games\\Background\\Sky2\\tile021.bmp", "E:\\Games\\Background\\Sky2\\tile022.bmp", "E:\\Games\\Background\\Sky2\\tile023.bmp", "E:\\Games\\Background\\Sky2\\tile024.bmp",
							   "E:\\Games\\Background\\Sky2\\tile025.bmp", "E:\\Games\\Background\\Sky2\\tile026.bmp", "E:\\Games\\Background\\Sky2\\tile027.bmp", "E:\\Games\\Background\\Sky2\\tile028.bmp", "E:\\Games\\Background\\Sky2\\tile029.bmp",
							   "E:\\Games\\Background\\Sky2\\tile030.bmp", "E:\\Games\\Background\\Sky2\\tile031.bmp", "E:\\Games\\Background\\Sky2\\tile032.bmp", "E:\\Games\\Background\\Sky2\\tile033.bmp", "E:\\Games\\Background\\Sky2\\tile034.bmp",
							   "E:\\Games\\Background\\Sky2\\tile035.bmp", "E:\\Games\\Background\\Sky2\\tile036.bmp", "E:\\Games\\Background\\Sky2\\tile037.bmp", "E:\\Games\\Background\\Sky2\\tile038.bmp", "E:\\Games\\Background\\Sky2\\tile039.bmp",
							   "E:\\Games\\Background\\Sky2\\tile040.bmp", "E:\\Games\\Background\\Sky2\\tile041.bmp", "E:\\Games\\Background\\Sky2\\tile042.bmp", "E:\\Games\\Background\\Sky2\\tile043.bmp", "E:\\Games\\Background\\Sky2\\tile044.bmp",
							   "E:\\Games\\Background\\Sky2\\tile045.bmp", "E:\\Games\\Background\\Sky2\\tile046.bmp", "E:\\Games\\Background\\Sky2\\tile047.bmp", "E:\\Games\\Background\\Sky2\\tile048.bmp", "E:\\Games\\Background\\Sky2\\tile049.bmp"};

char bird_flying[4][50] = {"E:\\Games\\Sprites\\Birds2\\tile000.bmp", "E:\\Games\\Sprites\\Birds2\\tile001.bmp", "E:\\Games\\Sprites\\Birds2\\tile002.bmp", "E:\\Games\\Sprites\\Birds2\\tile003.bmp"};
char dizzy_bird[50] = "E:\\Games\\Sprites\\BirdDizzy2.bmp";

char Star[6][50] = {"E:\\Games\\Home Menu\\Star.bmp", "E:\\Games\\Home Menu\\Star.bmp", "E:\\Games\\Home Menu\\Star.bmp", "E:\\Games\\Home Menu\\Star.bmp", "E:\\Games\\Home Menu\\Star.bmp", "E:\\Games\\Home Menu\\Star.bmp"};

char GiftClosed[5][50] = {"E:\\Games\\Sprites\\Gift.bmp", "E:\\Games\\Sprites\\Gift.bmp", "E:\\Games\\Sprites\\Gift.bmp", "E:\\Games\\Sprites\\Gift.bmp", "E:\\Games\\Sprites\\Gift.bmp"};
char GiftOpen[50] = "E:\\Games\\Sprites\\GiftOpen.bmp";

char cloud1[50] = "E:\\Games\\Sprites\\Clouds\\Cloud.bmp";
char cloud2[50] = "E:\\Games\\Sprites\\Clouds\\Cloud1.bmp";
char cloud3[50] = "E:\\Games\\Sprites\\Clouds\\Cloud2.bmp";
char cloud4[50] = "E:\\Games\\Sprites\\Clouds\\Cloud3.bmp";

char EnemyBird[8][50] = {"E:\\Games\\Sprites\\EnemyBird3\\tile000.bmp", "E:\\Games\\Sprites\\EnemyBird3\\tile001.bmp", "E:\\Games\\Sprites\\EnemyBird3\\tile002.bmp", "E:\\Games\\Sprites\\EnemyBird3\\tile003.bmp", "E:\\Games\\Sprites\\EnemyBird3\\tile004.bmp",
						 "E:\\Games\\Sprites\\EnemyBird3\\tile005.bmp", "E:\\Games\\Sprites\\EnemyBird3\\tile006.bmp", "E:\\Games\\Sprites\\EnemyBird3\\tile007.bmp"};

char ScoreBar[50] = "E:\\Games\\Home Menu\\ScoreBar3.bmp";
char StarBar[50] = "E:\\Games\\Home Menu\\StarBar2.bmp";
char GiftBar[50] = "E:\\Games\\Home Menu\\GiftBar.bmp";

struct background
{
	int bx;
	int by;
};

background Background[50];

void saveScore(int score)
{
	FILE *fp1;

	if ((fp1 = fopen("Score_level2.txt", "w")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}

	fprintf(fp1, "%d\n", score);
	fclose(fp1);
}

void update_bird()
{
	flying_idx = (flying_idx + 1) % 4;
}

void update_EnemyBird()
{
	flying_idx1 = (flying_idx1 + 1) % 8;
}

struct Enemybird
{
	int eb_x;
	int eb_y;
	bool eb_show;
} eb;

struct Clouds
{
	int cl_x;
	int cl_y;
	bool cl_show;
} cl2, cl3, cl4;

struct Stars
{
	int star_x;
	int star_y;
	int star_idx;
	bool star_show;
} star;

struct Gift
{
	int gift_x;
	int gift_y;
	bool gift_show;
	int gift_idx;
} gift1;

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

void getScore_level2(int &score)
{
	FILE *fp;
	if ((fp = fopen("Score_level2.txt", "r")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}
	fscanf(fp, "%d", &score);
	fclose(fp);
}

void iDraw()
{

	iClear();

	for (int i = 0; i < 50; i++)
	{
		iShowBMP(Background[i].bx, Background[i].by, background_img[i]);
	}

	if (eb.eb_show)
	{

		iShowBMP2(eb.eb_x, eb.eb_y, EnemyBird[flying_idx1], 0);
	}

	if (flag)
	{
		iShowBMP2(x, y, dizzy_bird, 0);
		flag1 = 1;
	}

	else
	{
		flag = 0;
		iShowBMP2(x, y, bird_flying[flying_idx], 0);
	}

	if (cl2.cl_show)
	{
		iShowBMP2(cl2.cl_x, cl2.cl_y, cloud2, 0);
	}

	if (cl3.cl_show)
	{
		iShowBMP2(cl3.cl_x, cl3.cl_y, cloud3, 0);
	}

	if (cl4.cl_show)
	{
		iShowBMP2(cl4.cl_x, cl4.cl_y, cloud4, 0);
	}

	if (star.star_show)
	{
		iShowBMP2(star.star_x, star.star_y, Star[star.star_idx], 0);
	}

	if (gift_collision)
	{
		gift1.gift_show = false;
		iShowBMP2(g_x, g_y, GiftOpen, 0);
	}

	else
	{
		gift_collision = false;
		iShowBMP2(gift1.gift_x, gift1.gift_y, GiftClosed[gift1.gift_idx], 0);
	}

	iShowBMP2(526, 780, ScoreBar, 0);
	char score1[80];
	sprintf(score1, "%d", Score);
	iSetColor(255, 255, 255);
	iText(770, 815, score1, GLUT_BITMAP_TIMES_ROMAN_24);

	iShowBMP2(83, 788, GiftBar, 0);
	char giftNum[80];
	sprintf(giftNum, "%d", GiftNumber);
	iSetColor(255, 255, 255);
	iText(155, 810, giftNum, GLUT_BITMAP_TIMES_ROMAN_24);

	iShowBMP2(280, 788, StarBar, 0);
	char starNum[80];
	sprintf(starNum, "%d", StarNumber);
	iSetColor(255, 255, 255);
	iText(360, 810, starNum, GLUT_BITMAP_TIMES_ROMAN_24);

	char HighScore[80];
	sprintf(HighScore, "HIGHEST SCORE:: %d", HScore);
	iSetColor(255, 255, 255);
	iText(1265, 822, HighScore, GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(255, 0, 255);
	iRectangle(8, 0, 1550, screenHight);
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
			y += 90;
			Score += 2;
			isFlapping = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!flag)
		{
			y -= 70;
			Score += 2;
			isFlapping = true;
		}
	}
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
			PlaySound("E:\\Games\\Music\\level2music1.wav", NULL, SND_LOOP | SND_ASYNC);
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
			y += 90;
			Score += 2;
			isFlapping = true;
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (!flag)
		{
			y -= 70;
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
		saveScore(Score);
	}

	if (flag1)
	{
		int i = 0;
		while (i < 100000000000)
		{
			i += 1;
			if (i == 1000000000)
			{
				exit(0);
			}
		}
	}

	if (!isFlapping)
	{
		if (!flag)
		{
			y -= 10;
		}
	}
	else
	{
		isFlapping = false;
	}

	flying_idx++;
	if (flying_idx >= 4)
		flying_idx = 0;
	if (!flag)
		flying_idx1++;
	if (flying_idx1 >= 8)
		flying_idx1 = 0;

	if (y > (screenHight - 20) || y < 0 || x > (screenWidth - 150) || x < 0)
	{
		playSound("E:\\Games\\Music\\BirdCollided.wav");
		gameOver = 1;
	}

	for (int i = 0; i < 50; i++)
	{
		if (!flag)
			Background[i].bx -= backgroundSpeed;

		if (Background[i].bx <= 0)
		{
			Background[i].bx = screenWidth - 38;
		}
	}

	// lx = left x, rx = right x, ly = lower y, uy = upper y

	int eb_lx = eb.eb_x + 25;
	int eb_rx = eb.eb_x + 110;
	int eb_ly = eb.eb_y + 50;
	int eb_uy = eb.eb_y + 102;
	if ((((x + 45) >= (eb_lx) && (x + 45) <= (eb_rx)) || ((x + 145) >= (eb_lx) && (x + 145) <= (eb_rx)) || ((x + 100) >= (eb_lx) && (x + 100) <= (eb_rx))) && (((y + 30) >= (eb_ly) && (y + 30) <= (eb_uy)) || ((y + 140) >= (eb_ly) && (y + 140) <= (eb_uy)) || ((y + 80) >= (eb_ly) && (y + 80) <= (eb_uy))))
	{
		playSound("E:\\Games\\Music\\BirdCollided.wav");
		gameOver = 1;
	}

	else
	{
		if (!flag)
		{
			eb.eb_x -= 75;
		}

		if (eb.eb_x < 0)
		{
			srand(time(NULL));
			eb.eb_x = screenWidth;
			eb.eb_y = 100 + rand() % 650;
		}
		if (eb.eb_x >= 0 && eb.eb_x <= screenWidth)
			eb.eb_show = true;
	}

	int cl2_lx = cl2.cl_x + 28;
	int cl2_rx = cl2.cl_x + 230;
	int cl2_ly = cl2.cl_y + 50;
	int cl2_uy = cl2.cl_y + 160;
	if ((((x + 45) >= (cl2_lx) && (x + 45) <= (cl2_rx)) || ((x + 145) >= (cl2_lx) && (x + 145) <= (cl2_rx))) && (((y + 30) >= (cl2_ly) && (y + 30) <= (cl2_uy)) || ((y + 135) >= (cl2_ly) && (y + 135) <= (cl2_uy))))
	{
		playSound("E:\\Games\\Music\\BirdCollided.wav");
		gameOver = 1;
	}

	else
	{
		if (!flag)
		{
			cl2.cl_x += 5;
			cl2.cl_y += 15;
		}
		if (flag_cloud2 && cl2.cl_y >= 0 && cl2.cl_y <= screenHight)
			cl2.cl_show = true;
	}

	int cl3_lx = cl3.cl_x + 20;
	int cl3_rx = cl3.cl_x + 196;
	int cl3_ly = cl3.cl_y + 40;
	int cl3_uy = cl3.cl_y + 165;
	if ((((x + 30) >= (cl3_lx) && (x + 30) <= (cl3_rx)) || ((x + 152) >= (cl3_lx) && (x + 152) <= (cl3_rx))) && (((y + 30) >= (cl3_ly) && (y + 30) <= (cl3_uy)) || ((y + 135) >= (cl3_ly) && (y + 135) <= (cl3_uy))))
	{
		playSound("E:\\Games\\Music\\BirdCollided.wav");
		gameOver = 1;
	}

	else
	{
		if (!flag)
		{
			cl3.cl_x -= 20;
			cl3.cl_y -= 10;
		}
		if (flag_cloud3 && cl3.cl_x >= 0 && cl3.cl_x <= screenWidth)
			cl3.cl_show = true;
	}

	int cl4_lx = cl4.cl_x + 15;
	int cl4_rx = cl4.cl_x + 240;
	int cl4_ly = cl4.cl_y + 25;
	int cl4_uy = cl4.cl_y + 165;
	if ((((x + 30) >= (cl4_lx) && (x + 30) <= (cl4_rx)) || ((x + 152) >= (cl4_lx) && (x + 152) <= (cl4_rx))) && (((y + 30) >= (cl4_ly) && (y + 30) <= (cl4_uy)) || ((y + 135) >= (cl4_ly) && (y + 135) <= (cl4_uy))))
	{
		playSound("E:\\Games\\Music\\BirdCollided.wav");
		gameOver = 1;
	}

	else
	{
		if (!flag)
		{
			cl4.cl_x -= 10;
			cl4.cl_y -= 15;
		}

		if (flag_cloud4 && cl4.cl_y >= 0 && cl4.cl_y <= screenHight)
			cl4.cl_show = true;
	}

	if (((star.star_x >= (x + 45) && star.star_x <= (x + 145)) || ((star.star_x + 45) >= (x + 45) && (star.star_x + 45) <= (x + 145))) && ((star.star_y >= (y + 25) && star.star_y <= (y + 145)) || ((star.star_y + 46) >= (y + 25) && (star.star_y + 46) <= (y + 145))))
	{
		playSound("E:\\Games\\Music\\Star_received.wav");
		star.star_show = false;
		Score += 20;
		StarNumber += 1;
		star.star_x = screenWidth;
		star.star_y = 100 + rand() % 200;
		star.star_idx = rand() % 6;
	}
	else
	{
		if (!flag)
			star.star_x -= 35;

		if (star.star_x < 0)
		{
			star.star_show = false;
			star.star_x = screenWidth;
			star.star_y = 200 + rand() % 600;
			star.star_idx = rand() % 6;
		}

		if (star.star_x >= 0 && star.star_x <= screenWidth)
			star.star_show = true;
	}

	if (((gift1.gift_x >= (x + 45) && gift1.gift_x <= (x + 145)) || ((gift1.gift_x + 75) >= (x + 45) && (gift1.gift_x + 75) <= (x + 145))) && (((gift1.gift_y + 10) >= (y + 25) && (gift1.gift_y + 10) <= (y + 145)) || ((gift1.gift_y + 70) >= (y + 25) && (gift1.gift_y + 70) <= (y + 145)) || ((gift1.gift_y + 35) >= (y + 25) && (gift1.gift_y + 35) <= (y + 145))))
	{
		playSound("E:\\Games\\Music\\Gift_collision.wav");
		g_x = gift1.gift_x;
		g_y = gift1.gift_y;
		gift1.gift_show = false;
		gift_collision = true;
		if (gift_collision)
		{
			gift_open_counter += 1;
			if (gift_open_counter > (gift_duration))
			{
				gift_collision = false;
			}
		}
		Score += 50;
		GiftNumber += 1;
		gift1.gift_x = screenWidth;
		gift1.gift_y = 200 + rand() % 600;
		gift1.gift_idx = rand() % 5;
	}

	else
	{

		gift_collision = false;

		if (!flag)
			gift1.gift_x -= 20;

		if (gift1.gift_x < 0)
		{
			gift1.gift_show = false;
		}

		else if (flag_gift1 && gift1.gift_x >= 0 && gift1.gift_x <= screenWidth)
			gift1.gift_show = true;
	}
}

void set_cloud2()
{

	cl2.cl_show = true;
	if (cl2.cl_y > screenHight)
	{
		cl2.cl_x = 100 + rand() % 1000;
		cl2.cl_y = 0;
	}
}

void set_cloud3()
{
	srand(time(NULL));
	cl3.cl_show = true;
	if (cl3.cl_x < 0 && cl3.cl_y < 0)
	{
		cl3.cl_x = 400 + rand() % 1000;
		cl3.cl_y = screenHight - rand() % 100;
	}
}

void set_cloud4()
{
	cl4.cl_show = true;
	if (cl4.cl_y < 0)
	{
		cl4.cl_x = 100 + rand() % 1200;
		cl4.cl_y = screenHight;
	}
}

void setBackground()
{
	int sum = 10;
	for (int i = 0; i < 50; i++)
	{
		Background[i].by = 0;
		Background[i].bx = sum;
		sum += 31;
	}
}

void Initialize_eb()
{
	srand(time(NULL));
	eb.eb_x = screenWidth;
	eb.eb_y = 100 + rand() % 650;
	eb.eb_show = true;
}
void Initialize_eb_once()
{
	if (!flag_eb)
	{
		Initialize_eb();
		flag_eb = true;
	}
}

void Initialize_cloud2()
{
	srand(time(NULL));
	cl2.cl_x = 100 + rand() % 1000;
	cl2.cl_y = 0;
	cl2.cl_show = true;
}
void Initialize_cloud2_once()
{
	if (!flag_cloud2)
	{
		Initialize_cloud2();
		flag_cloud2 = true;
	}
}

void Initialize_cloud3()
{
	srand(time(NULL));
	cl3.cl_x = 400 + rand() % 1000;
	cl3.cl_y = screenHight;
	cl3.cl_show = true;
}
void Initialize_cloud3_once()
{
	if (!flag_cloud3)
	{
		Initialize_cloud3();
		flag_cloud3 = true;
	}
}

void Initialize_cloud4()
{
	srand(time(NULL));
	cl4.cl_x = 100 + rand() % 1200;
	cl4.cl_y = screenHight;
	cl4.cl_show = true;
}
void Initialize_cloud4_once()
{
	if (!flag_cloud4)
	{
		Initialize_cloud4();
		flag_cloud4 = true;
	}
}

void setStarVariables()
{
	star.star_x = screenWidth;
	star.star_y = 200 + rand() % 500;
	star.star_show = true;
	star.star_idx = 0;
}

void InitializeGift1()
{
	srand(time(NULL));
	gift1.gift_x = screenWidth;
	gift1.gift_y = 200 + rand() % 600;
	gift1.gift_show = true;
	gift1.gift_idx = rand() % 5;
}

void Initialize_Gift1_Once()
{
	if (!flag_gift1 && !gift_collision)
	{
		InitializeGift1();
		flag_gift1 = true;
	}
}

void setGift1()
{
	if (flag_gift1 && !gift_collision)
	{
		srand(time(NULL));
		gift1.gift_show = true;
		if (gift1.gift_x < 0)
		{
			gift1.gift_x = screenWidth;
			gift1.gift_y = 200 + rand() % 500;
			gift1.gift_idx = rand() % 5;
		}
	}
}

int main()
{

	srand(time(NULL));
	setBackground();
	setStarVariables();
	iSetTimer(10000, Initialize_eb_once);
	iSetTimer(75, change);
	iSetTimer(40000, Initialize_cloud2_once);
	iSetTimer(10000, set_cloud2);
	iSetTimer(8000, Initialize_cloud3_once);
	iSetTimer(9000, set_cloud3);
	iSetTimer(20000, Initialize_cloud4_once);
	iSetTimer(12000, set_cloud4);
	iSetTimer(12000, Initialize_Gift1_Once);
	iSetTimer(18000, setGift1);
	getScore_level2(HScore);
	if (musicOn)
		PlaySound("E:\\Games\\Music\\level2music1.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(screenWidth, screenHight, "Birdie Escape");
	return 0;
}