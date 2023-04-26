
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Tien {
	char TenTien[25];
	int MG, PA;
};


struct Tien * ReadFromFile(int *Num){
     FILE *File;
     File=fopen("ATM.TXT", "r");
	 struct Tien *DSLT;
	 DSLT=(struct Tien*)malloc(sizeof(struct Tien));
	 int i=0;
 	 while (!feof(File)){
	   fscanf(File, "%d",&DSLT[i].MG);
	   fgets(DSLT[i].TenTien,25,File);
	   DSLT[i].TenTien[strlen(DSLT[i].TenTien)-1]='\0';
	   DSLT[i].PA=0;
	   i++;
	   DSLT=(struct Tien*)realloc(DSLT, sizeof(struct Tien)*(i+1));
	 }
	 *Num=i;
     fclose(File);
     return DSLT;
}

void Swap(struct Tien *x, struct Tien *y){
	struct Tien Temp;
	Temp = *x;
	*x   = *y;
	*y   = Temp;
}
void BubbleSort(struct Tien *DSLT, int n){
	int i,j;
	for(i=0; i<=n-2; i++)
	   for (j=n-1; j>=i+1; j--){
	   	 if (DSLT[j].MG>DSLT[j-1].MG)
			Swap(&DSLT[j],&DSLT[j-1]);
	  }
}

void InDS(struct Tien *DSLT ,int n, int TienCanRut){
	int i;
	int TongTienTra=0;
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n", "STT", "     Loại tiền   ","Mệnh giá", "Số tờ","Thành tiền");
	printf("|---|-------------------------|---------|---------|----------|\n");
	for(i=0;i<n;i++){
		printf("|%-3d",i+1);
		printf("|%-25s",DSLT[i].TenTien);
		printf("|%-9d",DSLT[i].MG);
		printf("|%-9d",DSLT[i].PA);
		printf("|%-10d|\n",DSLT[i].MG*DSLT[i].PA);
		TongTienTra=TongTienTra+DSLT[i].PA * DSLT[i].MG;
	}
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("Số tiền cần rút = %9d\n",TienCanRut);
	printf("Số tiền đã rút = %9d\n", TongTienTra);
}

void Greedy(struct Tien *DSLT,int n, int TienCanRut){
  int i=0;
  while(i<n&&TienCanRut>0) {
     DSLT[i].PA= TienCanRut/DSLT[i].MG;
     TienCanRut = TienCanRut-DSLT[i].PA * DSLT[i].MG;
     i++;
  }
}
int main(int argc, char const *argv[]){
    int Num,TienCanRut;
	printf("Nhập số tiền cần rút: ");
    scanf("%d",&TienCanRut);
	struct Tien *DSLT = ReadFromFile(&Num);
    BubbleSort(DSLT,Num);
	Greedy(DSLT,Num,TienCanRut);
	InDS(DSLT,Num,TienCanRut);
	free(DSLT);
    return 0;
}