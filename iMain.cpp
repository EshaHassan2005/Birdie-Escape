#include "iGraphics.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <ctime>

using namespace std;

void play_game1()
{
    system("level1.exe");
}

void play_game2()
{
    system("level2.exe");
}

#define screenWidth 1550
#define screenHight 800

struct buttonCoordinate
{
    int x;
    int y;
} bCoordinate[3];

int mposx, mposy;
bool musicOn = true;
int load_idx = 0;
int flag = 0;
int HScore_level1;
int HScore_level2;
int CScore_level1;
int CScore_level2;

char button[5][80] = {"E:\\Games\\Home Menu\\Button1.bmp", "E:\\Games\\Home Menu\\Button2.bmp", "E:\\Games\\Home Menu\\Button3.bmp"};
char HomePage[80] = "E:\\Games\\Home Menu\\Menu6.bmp";
char HomePage1[80] = "E:\\Games\\Home Menu\\HomePage2.bmp";
char Exit[80] = "E:\\Games\\Home Menu\\ExitButton.bmp";
char Exit1[80] = "E:\\Games\\Home Menu\\ExitButton1.bmp";
char Instruction[80] = "E:\\Games\\Home Menu\\InstructionPage.bmp";
char Arrow[80] = "E:\\Games\\Home Menu\\Arrow1.bmp";
char Loading[12][100] = {"E:\\Games\\Home Menu\\Loading\\tile000.bmp", "E:\\Games\\Home Menu\\Loading\\tile001.bmp", "E:\\Games\\Home Menu\\Loading\\tile002.bmp", "E:\\Games\\Home Menu\\Loading\\tile003.bmp",
                         "E:\\Games\\Home Menu\\Loading\\tile004.bmp", "E:\\Games\\Home Menu\\Loading\\tile005.bmp", "E:\\Games\\Home Menu\\Loading\\tile006.bmp", "E:\\Games\\Home Menu\\Loading\\tile007.bmp",
                         "E:\\Games\\Home Menu\\Loading\\tile008.bmp", "E:\\Games\\Home Menu\\Loading\\tile009.bmp", "E:\\Games\\Home Menu\\Loading\\tile010.bmp,"};

char PlayAgain[50] = "E:\\Games\\Home Menu\\PlayAgain1.bmp";
char Level[50] = "E:\\Games\\Home Menu\\Level1(2).bmp";
char ScoreBoard[50] = "E:\\Games\\Home Menu\\Scoreboard2.bmp";

void updateLoading()
{
    load_idx++;

    if (load_idx == 10)
    {
        flag = 1;
        load_idx = 0;
    }
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

void updateScore_level1(int score)
{
    FILE *fp;
    if ((fp = fopen("Score_level1.txt", "w")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(fp, "%d", score);
    fclose(fp);
}

void updateScore_level2(int score)
{
    FILE *fp;
    if ((fp = fopen("Score_level2.txt", "w")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(fp, "%d", score);
    fclose(fp);
}

void playSound()
{

    PlaySound("E:\\Games\\Music\\HomeMenuSound2.wav", NULL, SND_LOOP | SND_ASYNC);
}

void turnOffSound(bool musicOn)
{
    if (musicOn)
        PlaySound(0, 0, 0);
}

int gameState = -1;
void iDraw()
{
    iClear();

    if (gameState == -1)
    {
        flag = 0;
        iShowBMP(0, 0, HomePage1);
        for (int i = 0; i < 2; i++)
        {
            iShowBMP2(bCoordinate[i].x, bCoordinate[i].y, button[i], 0);
        }

        iShowBMP2(1474, 732, Exit, 0);
    }
    else if (gameState == 0)
    {
        iShowBMP(0, 0, Level);
        iShowBMP2(1472, 722, Exit1, 0);
    }
    else if (gameState == 1)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, 1550, 800);
        iShowBMP2(0, 0, Instruction, 0);
        iShowBMP2(0, 700, Arrow, 0);
    }
    else if (gameState == 2)
    {
        exit(0);
    }
    else if (gameState == 3)
    {

        iShowBMP(0, 0, ScoreBoard);
        char HScore1[50];
        sprintf(HScore1, "%d", HScore_level1);
        iSetColor(0, 0, 0);
        iText(832, 426, HScore1, GLUT_BITMAP_TIMES_ROMAN_24);

        char CScore1[50];
        sprintf(CScore1, "%d", CScore_level1);
        iSetColor(0, 0, 0);
        iText(780, 300, CScore1, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if (gameState == 4)
    {

        iShowBMP(0, 0, ScoreBoard);
        char HScore2[50];
        sprintf(HScore2, "%d", HScore_level2);
        iSetColor(0, 0, 0);
        iText(832, 426, HScore2, GLUT_BITMAP_TIMES_ROMAN_24);

        char CScore2[50];
        sprintf(CScore2, "%d", CScore_level2);
        iSetColor(0, 0, 0);
        iText(780, 300, CScore2, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    else if (gameState == 5)
    {

        PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
        iText(500, 300, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(380, 200, Loading[load_idx], 0);

        if (flag)
        {
            play_game1();
            getScore_level1(CScore_level1);
            if (HScore_level1 > CScore_level1)
            {
                updateScore_level1(HScore_level1);
            }
            else
            {
                HScore_level1 = CScore_level1;
            }
            gameState = 3;
            PlaySound("E:\\Games\\Music\\HomeMenuSound2.wav", NULL, SND_LOOP | SND_ASYNC);
            musicOn = true;
        }
        flag = 0;
    }

    else if (gameState == 6)
    {
        PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
        iText(500, 300, "LOADING...", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(380, 200, Loading[load_idx], 0);

        if (flag)
        {
            play_game2();
            getScore_level2(CScore_level2);
            if (HScore_level2 > CScore_level2)
            {
                updateScore_level2(HScore_level2);
            }
            else
            {
                HScore_level2 = CScore_level2;
            }
            gameState = 4;
            PlaySound("E:\\Games\\Music\\HomeMenuSound2.wav", NULL, SND_LOOP | SND_ASYNC);
            musicOn = true;
        }
        flag = 0;
    }
}

void iKeyboard(unsigned char key)
{
}

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (gameState == -1 && mx >= 1474 && mx <= 1550 && my >= 732 && my <= screenHight)
            gameState = 2;

        else if ((gameState == 3 || gameState == 4) && mx >= 827 && mx <= 1015 && my >= 160 && my <= 205)
        {
            flag = 0;
            gameState = -1;
        }

        else if (gameState == 0 && mx >= 1472 && mx <= 1547 && my >= 722 && my <= 797)
        {
            flag = 0;
            gameState = -1;
        }

        else
        {
            for (int i = 0; i < 2; i++)
            {

                if (gameState == -1 && mx >= bCoordinate[i].x && mx <= bCoordinate[i].x + 250 && my >= bCoordinate[i].y && my <= bCoordinate[i].y + 97)
                {
                    gameState = i;
                }
            }
        }
        if (gameState == 1 && mx >= 0 && mx <= 93 && my >= 700 && my <= 768)
        {
            gameState = -1;
        }

        if ((gameState == 3 || gameState == 4) && mx >= 665 && mx <= 898 && my >= 72 && my <= 114)
        {
            flag = 0;
            gameState = 0;
        }

        if (gameState == 3 && mx >= 542 && mx <= 735 && my >= 160 && my <= 205)
        {
            flag = 0;
            gameState = 5;
        }

        if (gameState == 4 && mx >= 542 && mx <= 735 && my >= 160 && my <= 205)
        {
            flag = 0;
            gameState = 6;
        }

        if (gameState == 0 && mx >= 200 && mx <= 468 && my >= 225 && my <= 336)
        {
            flag = 0;
            gameState = 5;
        }

        if (gameState == 0 && mx >= 1084 && mx <= 1346 && my >= 225 && my <= 330)
        {
            flag = 0;
            gameState = 6;
        }
    }
}

void iMouseMove(int x, int y)
{
}

void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_UP)
    {

        if (musicOn)
        {
            musicOn = false;
            PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
        }
        else
        {
            musicOn = true;
            PlaySound("E:\\Games\\Music\\HomeMenuSound2.wav", NULL, SND_LOOP | SND_ASYNC);
        }
    }
    else if (key == GLUT_KEY_LEFT)
    {
    }
    else if (key == GLUT_KEY_RIGHT)
    {
    }
    else if (key == GLUT_KEY_HOME)
    {
    }
    else if (key == GLUT_KEY_INSERT)
    {
    }
}

int main()
{
    int sum = 500;
    for (int i = 0; i < 2; i++)
    {
        bCoordinate[i].x = sum;
        bCoordinate[i].y = 80;
        sum += 300;
    }
    getScore_level1(HScore_level1);
    getScore_level2(HScore_level2);
    iSetTimer(330, updateLoading);

    if (musicOn)
    {
        PlaySound("E:\\Games\\Music\\HomeMenuSound2.wav", NULL, SND_LOOP | SND_ASYNC);
    }

    //iInitialize(screenWidth, screenHight, "TestGame1");
    iInitialize(screenWidth, screenHight, "Birdie Escape");
    return 0;
}
