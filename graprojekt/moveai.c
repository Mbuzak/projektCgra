
struct xy2{
	int wx;
	int wy;
};

void modul(int *a) {
	if(*a<0) (*a)=(*a)*(-1);
}

void destination_ai(int t[][10],struct xy2 wilk,int *dx2) {
	int x=10,y=10;
	int dx[x],min=10,odleglosc,war=0;
	for(int i=1;i<x-1;i++) {
		dx[i]=i;
		for(int j=1;j<y-1;j++) {
			if(t[j][i]==2) {
				if(t[j+1][i+1]==2 || t[j-1][i+1]==2) {
					dx[i]=0;dx[i+1]=0;i++; //owca po przekatnej
				}
			}
			if(t[j][i]==0 && j<8 && t[j+1][i+1]>1 && t[j+1][i-1]>1) {
				dx[i-1]=0;dx[i]=0;dx[i+1]=0;i++;
			}	
		}
	}
	for(int i=1;i<x;i++) {
		//printf("%d",dx[i]);
		odleglosc=wilk.wx-i;
		modul(&odleglosc);
		if(odleglosc<min && dx[i]!=0) {
			min=odleglosc;war=dx[i];
		}
	}
	if(min==1 || *dx2==0 || dx[war]!=0) *dx2=war;
}
void moveai(int t[][10],struct xy2 *wilk,int *dx) {
	destination_ai(t,*wilk,dx);
	//printf("*%d*\n",*dx);
	if(*dx==0) {
		if(wilk->wx<=4) {
			if(t[wilk->wy+1][wilk->wx+1]==0) {
				wilk->wy+=1;wilk->wx+=1;
			} 
			else {
				if(t[wilk->wy+1][wilk->wx-1]==0) {
					wilk->wy+=1;wilk->wx-=1;
				}
				else {
					if(t[wilk->wy-1][wilk->wx+1]==0) {
						wilk->wy-=1;wilk->wx+=1;
					}
					else if(t[wilk->wy-1][wilk->wx-1]==0) {
						wilk->wy-=1;wilk->wx-=1;
					}
				}
			}	
		}
		else {
			if(t[wilk->wy+1][wilk->wx-1]==0) {
				wilk->wy+=1;wilk->wx-=1;
			} 
			else {
				if(t[wilk->wy+1][wilk->wx+1]==0) {
					wilk->wy+=1;wilk->wx+=1;
				}
				else {
					if(t[wilk->wy-1][wilk->wx-1]==0) {
						wilk->wy-=1;wilk->wx-=1;
					}
					else if(t[wilk->wy-1][wilk->wx+1]==0) {
						wilk->wy-=1;wilk->wx+=1;
					}
				}
			}	
		}

	}
	else {
		if(wilk->wx>*dx) { // 1-ld 2-lg 3-pg 4-pd
			if(t[wilk->wy+1][wilk->wx-1]==0) {
				wilk->wy+=1;wilk->wx-=1;
			} 
			else {
				if(t[wilk->wy-1][wilk->wx-1]==0) {
					wilk->wy-=1;wilk->wx-=1;
				}
				else {
					if(t[wilk->wy-1][wilk->wx+1]==0) {
						wilk->wy-=1;wilk->wx+=1;
					}
					else if(t[wilk->wy+1][wilk->wx+1]==0) {
						wilk->wy+=1;wilk->wx+=1;
					}
				}
			}
		}
		else {
			if(wilk->wx<*dx) { // 1-pd 2-pg 3-lg 4-ld
				if(t[wilk->wy+1][wilk->wx+1]==0) {
					wilk->wy+=1;wilk->wx+=1;
				} 
				else {
					if(t[wilk->wy-1][wilk->wx+1]==0) {
						wilk->wy-=1;wilk->wx+=1;
					}
					else {
						if(t[wilk->wy-1][wilk->wx-1]==0) {
							wilk->wy-=1;wilk->wx-=1;
						}
						else if(t[wilk->wy+1][wilk->wx-1]==0) {
							wilk->wy+=1;wilk->wx-=1;
						}
					}
				}
			}
			else {
				if(wilk->wx==*dx) { // 1-ld 2-pd 3-lg 4-pg
					if(t[wilk->wy+1][wilk->wx-1]==0) {
						wilk->wy+=1;wilk->wx-=1;
					} 
					else {
						if(t[wilk->wy+1][wilk->wx+1]==0) {
							wilk->wy+=1;wilk->wx+=1;
						}
						else {
							if(t[wilk->wy-1][wilk->wx-1]==0) {
								wilk->wy-=1;wilk->wx-=1;
							}
							else if(t[wilk->wy-1][wilk->wx+1]==0) {
								wilk->wy-=1;wilk->wx+=1;
							}
						}
					}
				}
			}
		}	
	}
}
