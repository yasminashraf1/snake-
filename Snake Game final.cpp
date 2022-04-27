//Welcome to our Snake game made by: Yasmin Ashraf-Nada Emad-Nada Faheem-Naiera Seifeldin
//Data Structure used is DLL
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
using namespace std;
//Dimensions of the window of game
int height=25;
int width=100;

//Declaration of used variables in game
int gameover1=0,gameover2=0;
int choice;
int score1,score2;
int lflag=0,rflag=0,uflag=0,dflag=0; //left-right-up-downs flags determines the movement of the snake for first player
int lflag2=0,rflag2=0,uflag2=0,dflag2=0; //left-right-up-downs flags determines the movement of the snake for second player
short fruitcounter; //maximum no. of fruit in 2 players case


class Snake
{
	int x,y,x2,y2; //coordinates of snake
	int fx,fy; //coordinates of fruit
	char playername[50],playername2[50];

	struct node //create a node for Double linkedlist
	{
		int nx,ny; //coordinates of every node of snake
		struct node *next; //next of node
		struct node *back; // previous of node
	};

	struct node *head=NULL; //head of first snake in case of single player
	struct node *head2=NULL; //head of second snake in case of two players
/*---------------------------------------------------------------------------*/
	void gotoxy(int x,int y) //function places the cursor at the desired location on the screen
	{
		COORD pos={x,y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}
/*---------------------------------------------------------------------------*/
	void nameandscore() //function to display names and scores of players
	{
		gotoxy(103,0); //out window of the game from right @height=0
		textcolour(10);
		cout<<"MADE BY=Yasmin,NadaE,NadaF,Naiera";
		textcolour(6);
		gotoxy(103,2); //out window of the game from right @height=2
		cout<<playername<<"'s SCORE = "<<score1*100;
		if(choice==2) //in case of 2 players will be executed
		{
			gotoxy(103,4);
			cout<<playername2<<"'s SCORE = "<<score2*100;
			gotoxy(103,6);
			cout<<"Remained Fruit :"; //in case of 2 conditions we have limited no. of fruits
			gotoxy(117,6); //out window of the game from right @ width= 117 and @height=2
			cout<<"  ";
			gotoxy(117,6);
			cout<<fruitcounter;
		}
	}
/*---------------------------------------------------------------------------*/
	void textcolour(int k) //function to define what color wanted to be used for text
	{
		HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,k);
	}
/*---------------------------------------------------------------------------*/
	public:

	void window() //function to print borders
	{
		if(choice==1)
		textcolour(4); //for single player window colour is red
		else
		textcolour(1); //for 2 players window colour is blue
			for(int i=0;i<=width;i++) // this loop prints upper and down borders of the window
		{
			gotoxy(i,0);
			cout<<"Û";
			gotoxy(i,height);
			cout<<"Û";
		}

		for(int i=0;i<=height;i++) // this loop prints right and left borders of the window
		{
			gotoxy(0,i);
			cout<<"Û";
			gotoxy(width,i);
			cout<<"Û";
		}
	}
/*---------------------------------------------------------------------------*/
	void box(int m1,int n1,int m2,int n2) //function to print borders of welcome window
	{
			for(int i=m1;i<=m2;i++) //loop prints upper and lower borders
		{
			gotoxy(i,n1);
			cout<<"//";
			gotoxy(i,n2);
			cout<<"//";
		}

		for(int i=n1;i<=n2;i++) //loop prints right and left borders
		{
			gotoxy(m1,i);
			cout<<"//";
			gotoxy(m2,i);
			cout<<"//";
		}
	}
/*---------------------------------------------------------------------------*/
	void welcome() //function to display welcome window
	{
		textcolour(5); //purple colour
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4); //sent values to box function
		textcolour(10); // light green colour
		gotoxy(width/2-20,height/2-10);
		cout<<"*** WELCOME TO OUR SNAKE GAME *** ";
		textcolour(9); //light blue colour
		gotoxy(width/2-16,height/2-3);
		cout<<"Press 1 For Single player \n";
		gotoxy(width/2-16,height/2-1);
		cout<<"Press 2 For Multiplayer \n";
		gotoxy(width/2-16,height/2);
		cin>>choice;
		system("cls"); //system(“cls”) which is used to make the screen/terminal clear, it send us to next screen depend on our choice
	}
/*---------------------------------------------------------------------------*/
	void welcome1() // function to display welcome window for single player mode
	{
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		textcolour(6);
		gotoxy(width/2-18,height/2-3);
		cout<<"WELCOME TO SNAKE GAME SINGLE PLAYER MODE ";
		textcolour(8);
		gotoxy(width/2-13,height/2);
		cout<<"Enter Your Name : ";
		cin>>playername;
		system("cls");
	}
/*---------------------------------------------------------------------------*/
	void welcome2() // function to display welcome window for 2 players mode
	{
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		textcolour(6);
		gotoxy(width/2-18,height/2-3);
		cout<<"WELCOME TO SNAKE GAME MULTIPLAYER MODE ";
		textcolour(8);
		gotoxy(width/2-13,height/2);
		cout<<"Enter Player1 Name : ";
		gotoxy(width/2-13,height/2+2);
		cout<<"Enter Player2 Name : ";
		gotoxy(width/2+7,height/2);
		cin>>playername;
		gotoxy(width/2+7,height/2+2);
		cin>>playername2;
		system("cls");
	}
/*---------------------------------------------------------------------------*/
	void setup() //function to set initial values in case of first snake
	{
		score1=0;
		gameover1=0;
		window();
		resetflag();
		nameandscore();
		head=new node;
		head->nx=width/2; //starting point of snake1
		head->ny=height/2;
		head->next=NULL;
		head->back=NULL;
		x=width/2; //move cursor to the middle of the screen
		y=height/2;
		srand(time(0));
		label1:
		fx=rand()%width;
		if(fx==0||fx==width) //To make sure the fruit is not on the borders of window
		goto label1;
		label2:
		fy=rand()%height;
		if(fy==0||fy==height)
		goto label2;
	}
/*---------------------------------------------------------------------------*/
	void setup2() //function to set initial values for the second snake in case of two players
	{
		resetflag2();
		gameover2=0;
		score2=0;
		fruitcounter=25;
		head2=new node;
		head2->nx=width/2+5; //starting point of snake 2
		head2->ny=height/2+5;
		head2->next=NULL;
		head2->back=NULL;
		x2=width/2+5; //move cursor to this position on the screen
		y2=height/2+5;

	}
/*---------------------------------------------------------------------------*/
	void drawsnake(struct node *h,int k) //function to draw the snake it takes two parameters the head and code of the colour
	{
		textcolour(k);
		struct node *ptr;
		ptr=h;
		while(ptr!=NULL) //Print loop for double linked list (snake)
		{
			gotoxy(ptr->nx,ptr->ny);
			cout<<"Û";
			ptr=ptr->next;
		}
	}
/*---------------------------------------------------------------------------*/
	void hidesnake(struct node *h) //function to delete snake from screen from certain position to draw it in another position to seem as a motion game
	{
		struct node *ptr;
		ptr=h;
		while(ptr!=NULL)
		{
			gotoxy(ptr->nx,ptr->ny);
			cout<<" ";
			ptr=ptr->next;
		}
	}
/*---------------------------------------------------------------------------*/
	void draw() //function responsible for the display of two snakes and fruit on screen
	{

		drawsnake(head,2); //colour code of first snake to be green
		drawsnake(head2,5); //colour code of second snake to be purple
		gotoxy(fx,fy);
		textcolour(4); //red code for fruit
		cout<<"@"; //fruit
		Sleep(70);
		hidesnake(head);
		hidesnake(head2);
	}
/*---------------------------------------------------------------------------*/
	void resetflag() //function to reset flags for each new game for first snake
	{
		uflag=0;
		dflag=0;
		lflag=0;
		rflag=0;
	}
/*---------------------------------------------------------------------------*/
		void resetflag2() //function to reset flags for each new game for second snake in case of 2 players
	{
		uflag2=0;
		dflag2=0;
		lflag2=0;
		rflag2=0;
	}
/*---------------------------------------------------------------------------*/
	void play() //function to dtermine direction of movement
	{
		int arrow; //variable takes the code of pressed key
		char ch;
		if(kbhit()) //to determine if a key has been pressed or not
		{

			ch=getch(); // predefined function which freezes the screen until a key is hit by the user
			arrow=ch;
			switch(arrow)
			{
				case 72:if(dflag!=1){resetflag();uflag=1;} //up arrow
				break;
				case 80:if(uflag!=1){resetflag();dflag=1;} //down arrow
				break;
				case 75:if(rflag!=1){resetflag();lflag=1;} //left arrow
				break;
				case 77:if(lflag!=1){resetflag();rflag=1;} //right arrow
				break;

				case 119:if(dflag2!=1){resetflag2();uflag2=1;} //w key
				break;
				case 115:if(uflag2!=1){resetflag2();dflag2=1;} //s key
				break;
				case 97:if(rflag2!=1){resetflag2();lflag2=1;} //A key
				break;
				case 100:if(lflag2!=1){resetflag2();rflag2=1;} //D key
				break;

				default:break;
			}
		}
	}

		char endwindow() //function to display end window of the game and return whether player will play again or not
	{
		char c;
		gotoxy(width/2-5,height/2-4);
		cout<<"GAME OVER \n";
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);

		textcolour(1);
		gotoxy(width/2-15,height/2-2);
		cout<<playername<<" You Scored : "<<score1*100;
		if(choice==2)
		{
			gotoxy(width/2-15,height/2);
			cout<<playername2<<" You Scored : "<<score2*100;
			textcolour(4);
			if(gameover1!=0)
			{
				gotoxy(width/2-15,height/2+2);
				cout<<playername<<" has lost !";
			}
			else
			{
				gotoxy(width/2-15,height/2+2);
				cout<<playername2 <<" has lost !";
			}
			if(fruitcounter==0)
			{
				textcolour(4);
				gotoxy(width/2-15,height/2+2);
				if(score1>score2)
				{
					cout<<playername<<" has WON !";
				}
				else
				{
					cout<<playername2<<" has WON !";
				}
			}
		}
		textcolour(6);
		gotoxy(width/2-15,height/2+4);
		cout<<"Want To Play Again ? (Y/N) : ";
		cin>>c;
		system("cls");
		return c;

	}
/*---------------------------------------------------------------------------*/
	void run() //function to change position of snake depend on our pressed keys on keyboard
	{
		if(uflag==1)
		y--;
		else if(dflag==1)
		y++;
		else if(lflag==1)
		x--;
		else if(rflag==1)
		x++;


			if(uflag2==1)
		y2--;
		else if(dflag2==1)
		y2++;
		else if(lflag2==1)
		x2--;
		else if(rflag2==1)
		x2++;

	}
/*---------------------------------------------------------------------------*/
	void movesnake(struct node *h,int pp,int qq) //function to move snake to new position depend on pressed keys
	{
		struct node *ptr,*prev;
		ptr=h;
		prev=h;

		while(ptr->next!=NULL) //Traverse the snake till end
		{
			prev=ptr;
			ptr=ptr->next;
		}
		while(prev!=h) //shift data in snake
		{
			ptr->nx=prev->nx;
			ptr->ny=prev->ny;
			prev=prev->back;
			ptr=ptr->back;
		}
		ptr->nx=prev->nx;
		ptr->ny=prev->ny;
		prev->nx=pp; //move head of snake to new position
		prev->ny=qq;
	}
/*---------------------------------------------------------------------------*/
	void drawagain() //function to draw the first snake again when it passes through one of 4 borders in case of 2 players mode
	{
		if(x==width) //if it passes through right border return it from left one
		{
			x=1;
		}
		if(x==0)
		{
			x=width-1;
		}
		if(y==0)
		{
			y=height-1;
		}
		if(y==height)
		{
			y=1;
		}
	}
/*---------------------------------------------------------------------------*/
	void drawagain2() //function to draw the second snake again in case of 2 players when it passes through one of 4 borders
	{
		if(x2==width)
		{
			x2=1;
		}
		if(x2==0)
		{
			x2=width-1;
		}
		if(y2==0)
		{
			y2=height-1;
		}
		if(y2==height)
		{
			y2=1;
		}
	}
/*---------------------------------------------------------------------------*/
	void generatefruit() //function to generate fruit by random places on screen
	{
			srand(time(0));
			label1:
			fx=rand()%width;
			if(fx==0||fx==width)
			goto label1;
			label2:
			fy=rand()%height;
			if(fy==0||fy==height)
			goto label2;
	}
/*---------------------------------------------------------------------------*/
	void checkfcount() //function to calculate the fruit count in case of 2 players to end game when fruit reach max. value and know which player has won
	{
		if(fruitcounter==0)
		{
			gameover1=1;
			gameover2=1;
		}
	}
/*---------------------------------------------------------------------------*/
	void checkup() //test cases for single player
	{
		if(choice==1) //player in single player mode lose when he hit one of 4 borders (test case 1)
		{
			if(x==width||x==0)
			gameover1=1;
			if(y==height||y==0)
			gameover1=1;
		}
		drawagain();

		struct node *h;
		h=head->next;
		while(h!=NULL) //player lose when snake eat itself (test case 2)
		{
			if(x==h->nx&&y==h->ny) //when head = one of the nodes of the snake
			{
				gameover1=1;
				break;
			}
			h=h->next;
		}

		if(x==fx&&y==fy) //(test case 3) when the snake eats the fruits
		{
			if(choice==2)
			{
				fruitcounter--;
				checkfcount();
			}
			struct node *t,*ptr,*prev; //adding new node after each eaten fruit
			t=new node;
			t->next=NULL;
			t->back=NULL;
				ptr=head;
				prev=head;
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=t;
				t->back=ptr;
				generatefruit(); //generate new fruit
			score1++; //increase the score of first player
			nameandscore(); //change the number of displayed score
		}
			movesnake(head,x,y); // move the snake to the new position for second iteration
		}
/*---------------------------------------------------------------------------*/
		void checkup2() // test cases for second snake in second player mode
	{
		drawagain2();
		struct node *h;
		h=head2->next;
		while(h!=NULL)
		{
			if(x2==h->nx&&y2==h->ny) //player lose when snake eat itself (test case 2)
			{
				gameover2=1;
				break;
			}
			h=h->next;
		}

		if(x2==fx&&y2==fy)
		{
			fruitcounter--;
			checkfcount();
			struct node *t,*ptr,*prev;
			t=new node;
			t->next=NULL;
			t->back=NULL;
				ptr=head2;
				prev=head2;
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=t;
				t->back=ptr;
				generatefruit();
				score2++;
				nameandscore();
		}
			movesnake(head2,x2,y2);
		}
/*---------------------------------------------------------------------------*/
	void game1() //single player mode
	{
		char ch;
		welcome1();
		do{
			setup();
			window();
			while(!gameover1)
			{
				draw();
				play();
				run();
				checkup();
			}
			ch=endwindow();
			}while(ch=='y'||ch=='Y');
	}
/*---------------------------------------------------------------------------*/
	void game2() // 2 players mode
	{
		char ch;
		welcome2();
		do{

			setup2();
			setup();
			window();
		while(gameover1!=1&&gameover2!=1)
			{
				draw();
				play();
				run();
				checkup();
				checkup2();
			}ch=endwindow();
		}while(ch=='y'||ch=='Y');
	}

};


int main()
{
	Snake s;
	s.welcome();
	if(choice==1)
	{
		s.game1();
	}
	if(choice==2)
	{
		s.game2();
	}
	system("exit");
}

