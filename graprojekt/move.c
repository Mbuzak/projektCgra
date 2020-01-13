#include <stdio.h>
#include <stdlib.h>

struct xy1{
	int wx;
	int wy;
};

void boldblue() {
	printf("\033[1;34m");
}
void green() {
	printf("\033[0;32m");
}
void cyan() {
	printf("\033[0;36m");
}
void resetcolor() {
	printf("\033[0m");
}

void poruszanie(char kierunek,struct xy1 *gracz) {
	int x=10,y=10;
	switch(kierunek) {
		case 'w': if(gracz->wy>1) gracz->wy--;
		break;
		case 's': if(gracz->wy<y-2) gracz->wy++;
		break;
		case 'a': if(gracz->wx>1) gracz->wx--;
		break;
		case 'd': if(gracz->wx<x-2) gracz->wx++;
		break;
	}
}

void pawn(int t[][10],int *t2,struct xy1 gracz) {	
	if(t[gracz.wy-1][gracz.wx-1]==0) t2[(gracz.wy-1)*10+gracz.wx-1]=1;
	if(t[gracz.wy-1][gracz.wx+1]==0) t2[(gracz.wy-1)*10+gracz.wx+1]=1;
}
void pokaz(int t[][10],int *t2,struct xy1 gracz) {
	int x=10,y=10;
	system("clear");
	printf("\n Esc - wyjscie do menu\n wsad - poruszanie\n $ - zapis gry\n  ");
	for (int i=0; i<y; i++) {
		for (int j=0; j<x; j++) {
			if(i==gracz.wy && j==gracz.wx) green();
			else {
				if(t2[(i*10)+j]==1) cyan();
				else {
					if(t[i][j]==3) boldblue();
					else resetcolor();
				}
			}
			switch (t[i][j]) {
				case 0: printf("__"); break;
				case 1: printf("  "); break;              
				case 2: printf("OO"); break;
				case 3: printf("WW"); break;
				case 4: printf("##"); break;
			}
		}
		printf("\n  ");
	}
}
void available(int t[][10],int *t2,struct xy1 gracz) {
	int wp=t[gracz.wy][gracz.wx];
	if(wp==2) pawn(t,t2,gracz);
}


