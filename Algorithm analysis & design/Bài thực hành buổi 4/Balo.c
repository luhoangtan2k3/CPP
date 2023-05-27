#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char TenDV[20];
	int TL, GT, PA;
} DoVat;

typedef int Table[50][100];

DoVat *ReadFromFile(int *W, int *n){
    FILE *File = fopen("Balo.txt", "r");
    fscanf(File, "%d",W);
	DoVat *DSDV = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
 	while (!feof(File)){
	    fscanf(File, "%d%d%[^\n]",&DSDV[i].TL,&DSDV[i].GT,&DSDV[i].TenDV);
	    DSDV[i].PA=0;
	    i++;
	    DSDV=(DoVat*)realloc(DSDV,sizeof(DoVat)*(i+1));
	 }
	*n=i;
    fclose(File);
    return DSDV;
}

void InDSDV(DoVat *DSDV ,int n, int W){
	int i, TongTL=0, TongGT=0;
	printf("\nCái balo dùng thuật toán quy hoạch động:\n");
		printf("|---|------------------|----------|---------|-----------|\n");
		printf("|STT|     Tên đồ vật   | Weight   | Giá trị | Phương án |\n");
		printf("|---|------------------|----------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-18s|%5d     |%5d    |%6d     |\n",
		i+1,DSDV[i].TenDV,DSDV[i].TL,DSDV[i].GT,DSDV[i].PA);
		TongTL=TongTL+DSDV[i].PA * DSDV[i].TL;
		TongGT=TongGT+DSDV[i].PA * DSDV[i].GT;
	}
	printf("|---|------------------|----------|---------|-----------|\n");
	printf("Trọng lượng balo = %-9d\n",W);
	printf("Tổng trọng lượng = %-9d\n",TongTL);
	printf("Tổng giá trị = %-9d\n",TongGT);
}

void TaoTable(DoVat *DSDV,int n,int W, Table F,Table X){
 	int xk, yk, k;
 	int FMax, XMax,V;
 	for(V= 0; V<=W; V++) {
 		X[0][V] = V/DSDV[0].TL;
 		F[0][V] = X[0][V] * DSDV[0].GT;
 	}
	for(k= 1; k<n; k++){
		for(V=0; V<=W; V++) {
			FMax = F[k-1][V] ;
			XMax = 0;
			yk = V/DSDV[k].TL;
			for(xk = 1; xk<=yk; xk++){
			    if(F[k-1][V-xk*DSDV[k].TL]+xk*DSDV[k].GT>FMax){
			 		FMax=F[k-1][V-xk*DSDV[k].TL]+xk*DSDV[k].GT;
			 		XMax= xk;
			 	}
            }
			F[k][V] = FMax;
			X[k][V] = XMax;
	 	}
    }
}

void InTable(int n, int W, Table F, Table X){
	int V, k;
	for(k=0; k<n; k++){
		for(V=0; V<=W; V++){
		 	printf("|%2d%2d",F[k][V], X[k][V]);
        }
		printf("\n");
	}
}

void TraTable(DoVat *DSDV, int n, int W, Table X){
	int V = W;
	for(int k = n-1; k >= 0; k--){
	 	DSDV[k].PA = X[k][V];
	 	V=V-X[k][V]*DSDV[k].TL;
	}
}
int main(int argc, char const *argv[]){
    int Num, W;
	Table X,F;
	DoVat *DSDV = ReadFromFile(&W, &Num);
	TaoTable(DSDV,Num,W,F,X);
	InTable(Num,W,F,X);
	printf("\n");
	TraTable(DSDV,Num,W,X);
	InDSDV(DSDV,Num,W);
	free(DSDV);
}