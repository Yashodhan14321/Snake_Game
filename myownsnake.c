#include<stdio.h>
#include <stdlib.h>
//checking for operating system
#ifdef _WIN32
    //code for Windows (32-bit and 64-bit)
    #include <conio.h>
    #define CLEARSCREEN system("cls")
    #define CHECKKEY _kbhit()
    #define NBGETCHAR getch()

#elif __APPLE__
    //code for mac
    #define CLEARSCREEN system("clear")
    #define CHECKKEY 
    #define NBGETCHAR 

#elif __linux__
    //code for linux
    #define CLEARSCREEN system("clear")
    #define CHECKKEY 
    #define NBGETCHAR 
#else
#   error "Unknown compiler"
#endif

//global variables
//****board variables****
int bheight=30, bwidth=90;
int gotox=13;

//****fruit variables****
int fruitX, fruitY;
//****fruit variables****
int score, gameOver,flag;
//****co-ordinates****
int x,y;
//****mouth of snake****
char mouth='>';

int *tailX, *tailY;
int countTail;

int length;

//setting up values
void setup()
{
	printf("1");
	mouth ='>';
	free(tailX);
	free(tailY);
	tailX = (int*)malloc(2000*sizeof(int));
	tailY = (int*)malloc(2000*sizeof(int));
	length =0;

	gameOver=0;
	score =0;
	x=bheight/2;
	y=bwidth/6;

	label1:
	fruitX = rand()%29;
	if(fruitX==0)
	{
		goto label1;
	}

	label2:
	fruitY = rand()%89;
	if(fruitY==0)
	{
		goto label2;
	}
	countTail=0;
}
void loading()
{
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\tLoading ...\n\t\t\t\t");
	for(int i=0;i<25;i++)
	{
		printf(":");
		for(int j=0;j<20000;j++)
		{
			for(int k=0;k<10000;k++)
			{

			}
		}
	}
}

//board
void board()
{
	CLEARSCREEN;
	printf("\n\n\t\t\tPress W for ^ A for < S for v and d for > ....\n");
	printf("\n\tScore = %d \t\t\t\t\t\t Length = %d \n\n",score,length);
	int i=0;
	while(i<bheight)
	{
		int j=0;
		while(j<bwidth)
		{
			if(i==0||i==bheight-1||j==0||j==bwidth-1)
			{
				printf("#");
			}
			else
			{
				if(i==x && j==y)
				{
					printf("%c",mouth);
				}
				else if(i==fruitX && j==fruitY)
				{
					printf("@");
				}
				else
				{
					int bo=0;
						for(int k=0;k<countTail;k++)
						{
							if(i==tailX[k]&&j==tailY[k])
							{
								printf("o");
								bo=1;
							}
						}
						if(bo==0)
						{
							printf(" ");
						}
				}
			}
			j++;
		}
		printf("\n");
		i++;
	}
}
void input()
{
	if(CHECKKEY)
	{
		switch(NBGETCHAR)		
		{
			case 'a':
				flag=1;
				mouth='<';
				break;
			case 'd':
				flag=2;
				mouth='>';
				break;
			case 'w':
				flag=3;
				mouth='^';
				break;
			case 's':
				flag=4;
				mouth='v';
				break;
			case 'x':
				gameOver=1;
				break;
		}
	}
}
void MakeLogic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0]=x;
	tailY[0]=y;
	for(int i=1;i<countTail;i++)
	{
		prev2X=tailX[i];
		prev2Y=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y;
	}
	switch(flag)
	{
		case 1:
			y-=2;
			break;
		case 2:
			y+=2;
			break;
		case 3:
			x--;
			break;
		case 4:
			x++;
			break;
		default:
			break;
	}
	if(x<0||x>bheight||y<0||y>bwidth)
	{
		gameOver=1;
	}
	for(int j=0;j<countTail;j++)
	{
		if(x==tailX[j] && y==tailY[j])
		{
			gameOver=1;
		}
	}
	if(tailX[0]==bheight-1||tailY[0]==bwidth-1||tailX[0]==0||tailY[0]==0)
	{
		gameOver=1;
	}
	if(x==fruitX && y==fruitY|| x== fruitX && fruitY==y+1)
	{
		label1:
		fruitX = rand()%29;
		if(fruitX==0)
		{
			goto label1;
		}
 
		label2:
		fruitY = rand()%89;
		if(fruitY==0)
		{
			goto label2;
		}
		score+=10;
		length++;
		countTail++;
	}
}
int main()
{
	loading();
	while(1)
	{
		setup();
		while(!gameOver)
		{
			board();
			input();
			MakeLogic();
		}
		CLEARSCREEN;
		if(gameOver==1)
		{
			printf("\n");
			printf("\n\n\n\n\n\n\n\n");
			printf("\t   (()))      ()     ()      () (((((((      (()) (        ) ((((((  ()))))\n");
			printf("\t (     ))    (  )    ( )    ( ) (           (    ) (      )  (       ()   ))\n");
			printf("\t(           ((()))   (  )  (  ) ((((       (      ) (    )   (((     ()))))\n");
			printf("\t (  (((((  (      )  (   )(   ) (           (    )   (  )    (       ()   ))\n");
			printf("\t   ((  (( (        ) (        ) (((((((      (())     ()     ((((((  ()    ))\n");
		}
		printf("\n");
		printf("\n");
		char ch1;
		printf("\t\t\t\tPress Y to Play Again and N to Exit ::-- ");
		scanf("%c",&ch1);
		if(ch1 == 'y' || ch1 == 'Y')
		{
		}
		else
		{
			scanf("%c",&ch1);
			if(ch1 == 'y' || ch1 == 'Y')
			{
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}