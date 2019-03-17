#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
bool print;
const int heigth=20,width=20;
int x,y,fruitX,fruitY,score;
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
int i,j,k;
int tailX[100],tailY[100];
int nTail;

void Setup()
{
    gameOver=false;
    score=0;
    dir=STOP;
    x=width/2;
    y=heigth/2;
    fruitX=rand() % width;
    fruitY=rand() % heigth;
}
void Draw()
  {
    system("cls");
    for(i=0;i<width;i++)
        cout<<"#";
    cout<<endl;

  for(i=0;i<width;i++)
    {
        for(j=0;j<heigth;j++)
        {
            if(j==0||j==width-1)
                cout<<"#";
            else if(i==y&&j==x)
                cout<<"O";
            else if(j==fruitX&&i==fruitY)
                cout<<"F";
            else
              {
                print=false;
                for(k=0;k<nTail;k++)
                {
                    if(tailX[k]==j&&tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
               cout<<" ";

              }

        }
        cout<<endl;
    }


    for(i=0;i<width;i++)
        cout<<"#";

    cout<<endl;
    cout<<"SCORE: "<<score<<endl;

}
void Input()
{
    if (kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir=LEFT;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'x':
            gameOver=true;
            break;
        }
    }
}
void Logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(i=1;i<nTail;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;

    }
    switch(dir)
    {
        case UP:
            y--;
        break;
        case DOWN:
            y++;
        break;
        case LEFT:
            x--;
        break;
        case RIGHT:
            x++;
        break;
        default:
            break;
    }
    /*if(x<0||x>width||y<0||y>heigth)
        gameOver=true;*/

    if(x<0)
        x=width-1;
    if(x>=width)
        x=0;
    if(y<0)
        y=heigth-1;
    if(y>=heigth)
        y=0;

    for(i=0;i<nTail;i++)
        if(tailX[i]==x&&tailY[i]==y)
            gameOver=true;

    if(x==fruitX&&y==fruitY)
    {
        nTail++;
        score+=10;
        fruitX=rand() % width;
        fruitY=rand() % heigth;
    }
}
int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}
