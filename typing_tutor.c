#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

void gotoxy(int x,int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
struct node{
	char c;
	int x,y;
	struct node *next;
}*head,*tail;


void insertInList(char);
void deleteChar(char);
void display();
char randomChar();
void engine();
void result();

int score=0,loose=0;

int main(){
	system("cls");
	printf("\n\n\n\n\t\t\tChoose Mode\n");
	printf("\n\n\t\t\t1:Beginner\n");
	printf("\t\t\t2:Medium\n");
	printf("\t\t\t3:Expert\n");
	printf("\t\t\t4:Exit\n");
	int speed;
	scanf("%d",&speed);
	switch(speed){
		case 1:
			speed=1500;
			break;
		case 2:
			speed=1000;
			break;
		case 3:
			speed=500;
			break;
		case 4:
			exit(1);
		default:
			printf("Invalid Input\n");
			Sleep(3000);
			main();
	}

	system("cls");
	printf("\n\n\n\n\t\t\t1:All Capital Letters.\n");
	printf("\t\t\t2:All Small Letters.\n");
	printf("\t\t\t3:All Digits/Numbers(0-9).\n");
	printf("\t\t\t4:Mix Letters & Numbers.\n");
	int mode;
	scanf("%d",&mode);

	engine(mode,speed);
	return 0;
}


void engine(int mode,int speed){
	do{
		if(kbhit()){
			deleteChar(getch());	
		}

		insertInList(randomChar(mode));
		display();
		Sleep(speed);
		system("cls");

	}while(loose < 10 && score <=10);
	result();
}

void insertInList(char c){
	struct node *n = (struct node *)malloc(sizeof(struct node));
	n->c = c;
	n->x = rand()%80;
	n->y = 0;
	n->next = NULL;
	if(head == NULL){
		head=tail=n;
	}else{
		tail->next=n;
		tail=n;
		tail->next = NULL;
	}
}

void deleteChar(char c){
	struct node *current;
        struct node *temp;
        current=head;

    if(c==head->c)
    {
        score++;
        head=head->next;
    }
    else if(c==tail->c){
        while(current->next!=tail){
            current=current->next;
        }
        tail=current;
        tail->next=NULL;
    }
    else{
        do{
            if(current->next->c==c){
                temp=current->next->next;
                current->next=temp;
                score++;
                break;
            }
            else
                current=current->next;
        }while(current->next!=tail);
    }

}



char randomChar(int choice){
	switch(choice){
		case 1:
			return 65+rand()%26;
		break;
		case 2:
			return 97+rand()%26;
		break;
		case 3:
			return 48+rand()%9;
		break;
		case 4:
			randomChar(1+rand()%4);
		break;
	}
}

void display(){
	struct node *current;
    current=head;

    while(current!=NULL){
        gotoxy(current->x,current->y++);
        printf("%c",current->c);
        if(current->y>=20){
                loose++;
                head=head->next;
        }
        current->y=current->y;
        current=current->next;
		gotoxy(0,20);
    	printf("--------------------------------------------------------------------------------");
    	printf("Score:%d\t\t\t\t\t\t\tLoose:%d\n",score,loose);
		}

}

void result(){
	if(score>loose){
		printf("You Won!\n");
	}else{
		printf("You Loose!\n");
	}
	Sleep(5000);
	main();
}