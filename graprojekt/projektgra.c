#include <stdio.h>
#include <stdlib.h>
#include "move.c"
#include "moveai.c"
#define x 10
#define y 10

struct wspolrzedne{
	int wx;
	int wy;
};
struct xy2 wilk={8,1};
struct xy1 gracz={1,8};
struct wspolrzedne wyzeruj;
struct wspolrzedne owca[4];

char getch();
void poruszanie(char,struct xy1*);
void pokaz(int t[][x],int *t2,struct xy1);
void available(int t[][x],int *t2,struct xy1);
void pawn(int t[][x],int *t2,struct xy1);
void moveai(int t[][x],struct xy2*,int*);
void destination_ai(int t[][x],struct xy2,int*);
void modul(int*);

void boldblue();
void green();
void cyan();
void resetcolor();

int main()
{
	owca[0].wx=1;owca[0].wy=8;
	owca[1].wx=3;owca[1].wy=8;
	owca[2].wx=5;owca[2].wy=8;
	owca[3].wx=7;owca[3].wy=8;
	int pole[y][x]={
		{4,4,4,4,4,4,4,4,4,4},
		{4,1,0,1,0,1,0,1,0,4},
		{4,0,1,0,1,0,1,0,1,4},
		{4,1,0,1,0,1,0,1,0,4},
		{4,0,1,0,1,0,1,0,1,4},
		{4,1,0,1,0,1,0,1,0,4},
		{4,0,1,0,1,0,1,0,1,4},
		{4,1,0,1,0,1,0,1,0,4},
		{4,0,1,0,1,0,1,0,1,4},
		{4,4,4,4,4,4,4,4,4,4} };
	int poledost[100];
	int pozwx,pozwy; //czy wilk moze sie ruszyc
	int koniecgry;
	for(int i=0;i<100;i++)
		poledost[i]=0;
	int tura,dx; //1-ruch bialych 0-ruch czarnych
	int blad,wartosc;
	char zn,trybgry='0';
	FILE *odczytpliku;
	FILE *save;	
	do {
		system("clear");
		printf("\n  Projekt w jezyku C\n\n  Gra Wilk i owce\n\n   1.Nowa gra\n   2.Wczytaj gre\n   3.Wyjscie\n");
		trybgry=getch();
		if(trybgry=='1' || trybgry=='2') {	
			koniecgry=0;dx=0;tura=0;
			if(trybgry=='1') {
				for(int i=0;i<4;i++) pole[owca[i].wy][owca[i].wx]=0;
				pole[wilk.wy][wilk.wx]=0;
				wilk.wx=8;wilk.wy=1;tura=0;
				owca[0].wx=1;owca[0].wy=8;
				owca[1].wx=3;owca[1].wy=8;
				owca[2].wx=5;owca[2].wy=8;
				owca[3].wx=7;owca[3].wy=8;
				for(int i=0;i<4;i++) pole[owca[i].wy][owca[i].wx]=2;
				pole[wilk.wy][wilk.wx]=3;
				pokaz(pole,poledost,gracz);
				printf("\n\nNacisnij dowolny klawisz,\nby rozpoczac...");
				getch();
			}			
			if(trybgry=='2') {
				odczytpliku=fopen("zapis.txt","r");
				if(odczytpliku==NULL) {
					printf("Blad");
					exit(1);
				}
				for(int i=0;i<4;i++) pole[owca[i].wy][owca[i].wx]=0;
				pole[wilk.wy][wilk.wx]=0;
				fscanf(odczytpliku,"%d%d",&wilk.wx,&wilk.wy);
				for(int i=0;i<4;i++) fscanf(odczytpliku,"%d%d",&owca[i].wx,&owca[i].wy);
				fscanf(odczytpliku,"%d",&tura);
				fclose(odczytpliku);
				for(int i=0;i<4;i++) pole[owca[i].wy][owca[i].wx]=2;
				pole[wilk.wy][wilk.wx]=3;
				pokaz(pole,poledost,gracz);
			}
			do {
				blad=0;
				if(tura==1) {
					zn=getch();
					poruszanie(zn,&gracz);
					if(zn==13) {
						wyzeruj.wx=gracz.wx;wyzeruj.wy=gracz.wy;wartosc=pole[gracz.wy][gracz.wx];
						for(int i=0;i<100;i++)
							poledost[i]=0;
						if(pole[wyzeruj.wy][wyzeruj.wx]==2) {
							available(pole,poledost,gracz);
							do {
								pokaz(pole,poledost,gracz);
								zn=getch();
								poruszanie(zn,&gracz);
							}
							while(zn!=13);
							if(poledost[(gracz.wy*10)+gracz.wx]==1) {
								for(int i=0;i<4;i++) {
									if(wyzeruj.wx==owca[i].wx && wyzeruj.wy==owca[i].wy) {
										owca[i].wx=gracz.wx;owca[i].wy=gracz.wy;
									}
								}																				
								pole[gracz.wy][gracz.wx]=wartosc;
								pole[wyzeruj.wy][wyzeruj.wx]=0;
								tura=(tura+1)%2;
							}
							else blad=2;
						} 
						else blad=1;
					}
				}
				if(tura==0) {
					zn='@';
					pozwx=wilk.wx;pozwy=wilk.wy;
					pole[wilk.wy][wilk.wx]=0;
					moveai(pole,&wilk,&dx);
					//getch();
					pole[wilk.wy][wilk.wx]=3;
					tura=(tura+1)%2;
				}
				for(int i=0;i<100;i++)
					poledost[i]=0;
				pokaz(pole,poledost,gracz);
				switch(blad) {
					case 1: printf("Nie mozesz wybrac tego pola\n");
					break;
					case 2: printf("Bledny ruch\n");
					break;
				}
				if(zn==27) koniecgry=1;
				if(wilk.wy==8 || (pole[1][2]==2 && pole[1][4]==2 && pole[1][6]==2 && pole[1][8]==2)) koniecgry=2;
				if(pozwx==wilk.wx && pozwy==wilk.wy) koniecgry=3;
				if(zn==36) koniecgry=4;
			} while(koniecgry==0);
			
			pokaz(pole,poledost,gracz);
			switch(koniecgry) {
				case 2: printf("Wilk wygral"); break;
				case 3: printf("Owce wygraly"); break;
				case 4: {
					save=fopen("zapis.txt","w");
					fprintf(save,"%d %d\n",wilk.wx,wilk.wy);
					for(int i=0;i<4;i++) {
						fprintf(save,"%d %d\n",owca[i].wx,owca[i].wy);
					}
					fprintf(save,"%d",tura);
					fclose(save);
				} break;
			}
			printf("\n\nNacisnij dowolny klawisz...");
			getch();			
		}

	} while(trybgry!='3');
	return 0;
}

char getch() {
	system ("/bin/stty raw");  
	char ret = getchar();
	system ("/bin/stty cooked");
	return ret;
}
