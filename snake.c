#include<stdio.h>
#include<windows.h> //resetscreenposition
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define N 30
#define M 60

int i,j,field[N][M],x,y,Gy,Head,Tail,Game,Frogs,a,b,var,dir,score,HighScore,speed;
FILE *f;

void snakeinitialisation()
{
    f =fopen("highscore.txt","r");
    fscanf(f,"%d",&HighScore);
    fclose(f);

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            field[i][j] = 0;
        }
    }
    x=N/2;y=M/2;Gy = y;Head = 5;Tail = 1;Game = 0;Frogs = 0,dir = 'd',score = 0,speed = 99;

    for(i = 0;i<Head;i++)
    {
        Gy++;
        field[x][Gy - Head] = i+1;
    }

}




void print()
{
    for(i =0;i<=M+1;i++)
    {
        if(i==0)
        {
            printf("%c",201);
        }else if(i == M+1){
            printf("%c",187);
        }
        else{
            printf("%c",205);
        }
    }
    printf("    Current Score : %d   HighScore : %d ",score,HighScore);
    printf("\n");

    for(i=0;i<N;i++)
    {
        printf("%c",186);
        for(j=0;j<M;j++)
        {
            if(field[i][j] == 0) printf(" ");
            if(field[i][j]>0 && field[i][j]!=Head) printf("%c",176);
            if(field[i][j] == Head) printf("%c",178);
            if(field[i][j] == -1) printf("%c",15);
            if(j == M-1)printf("%c\n",186);
        }
    }
    for(i =0;i<=M+1;i++)
    {
        if(i==0)
        {
            printf("%c",200);
        }else if(i == M+1){
            printf("%c",188);
        }
        else{
            printf("%c",205);
        }
    }
}

void ResetScreenPosition(){
    HANDLE hOut;                //hOut is a variable of type HANDLE
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position); // resets the position to top left corner.


}

Random(){
     srand(time(0));                      //to randomize position of frog
     a = 1 + rand()%28;    // returns a random number from 0 to infinite
     b = 1 + rand()%58 ;     // adding 1 so that its not 0 . %58 cuz u don't want it on the border.
     if(Frogs == 0 && field[a][b] == 0) // adding a frog if there are no frogs
     {
         field[a][b] = -1;
         Frogs = 1;
         if(speed >10 && score != 0) speed = speed -15;
     }

}

int getch_noblock()
{
    if(_kbhit())
        return _getch();                // if keyboard is hit
    else
        return -1;
}

void movement()
{
    var = getch_noblock();
    var = tolower(var);
    if(((var == 'd' || var == 'a') || (var == 's' || var == 'w')) && (abs(dir - var)>5))           // so that it doesn't retrace its path while going backwards
    {
        dir = var;
    }
    if(dir == 's')
    {
        x++;
        if(field[x][y]!=0 && field[x][y]!= -1){  GameOver();}
        if(x == N-1) x= 0;
        if(field[x][y] == -1) {
            Frogs = 0;
            score +=50;
            Tail-=2;
        }
        Head++;
        field[x][y] = Head;
    }
    if(dir == 'd')
    {
        y++;
        if(field[x][y]!=0 && field[x][y]!= -1){  GameOver();}          // -1 is frog
        if(y == M-1)                                    // if not , it would go to the next line
        {
            y = 0;
        }
        if(field[x][y] == -1) {
            Frogs = 0;
            score +=50;
            Tail-=2;

        }
        Head++;
        field[x][y] = Head;
    }
    if(dir == 'a')
    {
        y--;
        if(field[x][y]!=0 && field[x][y]!= -1){  GameOver();}
        if(y ==0) y = M-1;
        if(field[x][y] == -1) {
            Frogs = 0;
            score +=50;
            Tail-=2;

        }
        Head++;
        field[x][y] = Head;
    }
    if(dir == 'w')
    {
        x--;
        if(field[x][y]!=0 && field[x][y]!= -1){  GameOver();}
        if(field[x][y] == -1) {
            Frogs = 0;
            score +=50;
            Tail-=2;

        }
        if(x == -1) x = N-1;
        Head++;
        field[x][y] = Head;
    }
}

void TailRemove()
{
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            if(field[i][j] == Tail)
            {
                field[i][j] = 0;
            }
        }
    }
    Tail++;
}
void GameOver()
{
    printf("\a");                   //    \a gives a beep sound in C
    Sleep(1500);
    system("Cls");

    if(score > HighScore){
        printf("NEW HIGHSCORE  %d!!!!!!!!!!\n\n",score);
        system("pause");
        f = fopen("highscore.txt","w");
        fprintf(f,"%d",score);
        fclose(f);
    }
    system("Cls");              //    clears the screen
    printf("     \n\n\n\n                     GAME OVER !!!!!!!!!!    \n");
    printf("                         Score : %d  \n\n",score);
    printf("                         Press Enter to play again or ESC to exit  ........ ");

    while(1)
    {

        var = getch_noblock();
    if(var == 13){                                                  // ASCII of ENter
        Game = 0;
        snakeinitialisation();
        break;
    }
    else if(var == 27){
        Game = 1;
        break;
    }
    }
    system("Cls");
}

void main()
{
    snakeinitialisation();

    while(Game == 0){
        print();
        ResetScreenPosition();
        Random();
        movement();
        TailRemove();
        Sleep(99);
    }

}






