#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include<conio.h>

using namespace std;
bool gameOver;

// Border(Map)
const int width = 70;
const int height = 20;

// Coordinates
int x, y, fruitX, fruitY, score;
int TailX[100], TailY[100], nTail;

enum eDirection
{
    Stop = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = Stop;
    x = width / rand() % width;
    y = height / rand() % height;

    // rand() is a built-in function used to generate random numbers in our code.
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    // To clear terminal
    system("cls");
  
  //MAP
    //Top Border
    for (int i = 0; i < width+2; i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Left Border
            if (j == 0)
            {
                cout << "|";
            }

            //Snake's Coordinates
            if(i==y && j==x)
            {
                cout << "O";
            }

            //Fruit's Coordinates
            else if (i==fruitY && j==fruitX)
            {
                cout << "F";
            }
            
            else
            {
                //Tail's loop
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if(TailX[k]==j && TailY[k]==i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }
                

            //Right Border
            if (j == width-1)
                cout << "|";
        }
        cout << endl;
    }

    //Bottom Border
    for (int i = 0; i < width+2; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "Score:-" << score << endl;
}

void Input()
{
    // (_kbhit() :- It is a function which is used to determine if a key has been pressed or not.)
    if(_kbhit())
    {
        //getch() is used to hold the output screen for some time until the user passes a key from the keyboard to exit the console screen.
        switch(_getch())
        {
            case 'a':
            dir = LEFT;
            break;

            case 's':
            dir = DOWN;
            break;

            case 'd':
            dir = RIGHT;
            break;

            case 'w':
            dir = UP;
            break;

            case 'e':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;

    //  Logic for Tail in SEGMENTS
    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

//      Logic for the direction of Snake's Head
        switch (dir)
        {
        case LEFT:
        x--;
        break;

        case RIGHT:
        x++;
        break;

        case UP:
        y--;
        break;

        case DOWN:
        y++;
        break;

        default:
        break;
    }

//  If Head hits the wall
    if( x>width || x<0 || y>height || y<0)
    {
        gameOver = true;
    }

    if(x==fruitX && y==fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        // Sleep(); it will slow our game
    }
    return 0;
}