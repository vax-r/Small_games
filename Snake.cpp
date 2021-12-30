#include <windows.h>
#include <iostream>
#include <cstdio>
#include<cstdlib>
#include <conio.h>
#include <ctime>
using namespace std ;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

bool gameover=false;

#define xsize 27
#define ysize 52
char Map[xsize][ysize];

struct coordinate{
	int x;
	int y;
};
typedef struct coordinate CoorD;

void setMap();
void ShowMap();

enum direction{
	STOP,UP,DOWN,LEFT,RIGHT
};

class apple{
	private:
		char looking;
		CoorD position;
	public:
		apple(){
			looking='O';
			srand(time(NULL));
			position.x=25*rand()/RAND_MAX+1;
			position.y=50*rand()/RAND_MAX+1;
		}
		apple(char looking,int x,int y){
			this->looking=looking;
			if(x<=26&&x>=1){
				position.x=x;
			}
			else{
				cout<<"Invalid x value"<<endl;
			}
			if(y<=51&&x>=1){
				position.y=y;
			}
			else{
				cout<<"Invalid y value"<<endl;
			}
		}
		
		void draw(){
			Map[position.x][position.y]=looking;
			
		}
		
		void setPos(CoorD *snakeB,int len){
			srand(time(NULL));
			position.x=23*rand()/RAND_MAX+2;
			position.y=48*rand()/RAND_MAX+2;
			for(int i=0;i<len-1;i++){
				if(Map[position.x][position.y]==Map[(snakeB+i)->x][(snakeB+i)->y]){
					position.x=23*rand()/RAND_MAX+2;
					position.y=48*rand()/RAND_MAX+2;
					i=0;
				}
			}
		}
		
		int getAppleX(){
			return position.x;
		}
		
		int getAppleY(){
			return position.y;
		}
};



class snake{
	private:
		char head,body;
		int length;
		CoorD head_position;
		CoorD *body_position;
		direction DIR;		
	public:
		snake(){
			length=1;
			head='@';
			body='B';
			head_position.x=xsize/2;
			head_position.y=ysize/2;
			body_position=new CoorD[99];
			DIR=STOP;
		}
		
		~snake(){
			delete[] body_position;
		}
		
		void Input();
		void DrawS();
		void Move();
		void setBody();
		
		int getSnakeX(){
			return head_position.x;
		}
		
		int getSnakeY(){
			return head_position.y;
		}
		int getSnakeLen(){
			return length;
		}
		void EAT(apple &);
		
};

void snake::EAT(apple &a){
	if(head_position.x==a.getAppleX()&&head_position.y==a.getAppleY()){
		a.setPos(body_position,length);
		length++;
	}
	
}

void snake::Input(){
	char console;
	
	if(kbhit()){
		console=getch();
		switch(console){
			case 'i':DIR=UP;break;
			case 'j':DIR=LEFT;break;
			case 'k':DIR=DOWN;break;
			case 'l':DIR=RIGHT;break;
			case 'q':gameover=true;break;
			
		}	
	}
}

void snake::DrawS(){
	
	if(head_position.x==0||head_position.x==xsize-1||head_position.y==0||head_position.y==ysize-1){
		gameover=true;
		exit(1);
	}
	else{
		Map[head_position.x][head_position.y]=head;
	}
	
	if(length>1){
		for(int i=0;i<length-1;i++){
			Map[(body_position+i)->x][(body_position+i)->y]=body;
		}
	}
	
}

void snake::Move(){
	setBody();
	
	switch(DIR){
		case UP:head_position.x--;break;
		case DOWN:head_position.x++;break;
		case LEFT:head_position.y--;break;
		case RIGHT:head_position.y++;break;
	}
	for(int i=0;i<length-1;i++){
		if(head_position.x==(body_position+i)->x&&head_position.y==(body_position+i)->y){
			gameover=true;
			exit(1);
		}
	}
}

void snake::setBody(){
	int prevX,prevY,prev2X,prev2Y;
	for(int i=0;i<length-1;i++){
		prev2X=prevX;
		prev2Y=prevY;
		prevX=(body_position+i)->x;
		prevY=(body_position+i)->y;
		if(i==0){
			(body_position+i)->x=head_position.x;
			(body_position+i)->y=head_position.y;
		}
		else{
			(body_position+i)->x=prev2X;
			(body_position+i)->y=prev2Y;
		}
	}
}




int main(int argc, char** argv) {
	
	
	apple a1;
	a1.draw();
	snake s1;
	
	while(!gameover){
		setMap();
		s1.DrawS();
		a1.draw();
		ShowMap();
		
		s1.Input();
		s1.EAT(a1);
		s1.Move();
	}
	
	
	system("pause");
	return 0;
}

void setMap(){
	int i,j;
	for(i=0;i<xsize;i++){
		for(j=0;j<ysize;j++){
			if(i==0||i==xsize-1){
				Map[i][j]='#';
			}
			else if(j==0||j==ysize-1){
				Map[i][j]='#';
			}
			else{
				Map[i][j]=' ';
			}
		}
	}
}

void ShowMap(){
	int i,j;
	system("cls");
	for(i=0;i<xsize;i++){
		for(j=0;j<ysize;j++){
			cout<<Map[i][j];
		}cout<<endl;
	}
}
