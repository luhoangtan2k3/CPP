#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Item {
	char NameItem[20];
	float TL, GT, DG;
	int PA;
};

struct Item *ReadFile(float *W, int *Num){
	FILE *File = fopen64("Balo.txt","r");
	fscanf(File,"%f",W);
	struct Item *DSDV = (struct Item*)malloc(sizeof(struct Item));
	int i=0;
	while(!feof(File)){
		fscanf(File,"%f%f%[^\n]",&DSDV[i].TL,&DSDV[i].GT,&DSDV[i].NameItem);
		DSDV[i].DG = DSDV[i].GT/DSDV[i].TL;
		DSDV[i].PA = 0;
		i++;
		DSDV = (struct Item*)realloc(DSDV,sizeof(struct Item)*(i+1));
	}
	*Num = i;
	fclose(File);
	return DSDV;
}
void Swap(struct Item *x, struct Item *y){
	struct Item Temp;
	Temp = *x;
	*x   = *y;
	*y   = Temp;
}

void BubbleSort(struct Item *ListItems, int n){
	int i,j;
	for(i=0; i<=n-2; i++){
	    for (j=n-1; j>=i+1; j--){
	   	    if (ListItems[j].DG>ListItems[j-1].DG){
			    Swap(&ListItems[j],&ListItems[j-1]);
            }
	    }
    }
}

void InListItems(struct Item *ListItems, int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhương án cái balo dùng thuật toán tham ăn:\n");
	printf("\nTrọng lượng balo = %-9.2f\n",W);
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Tên đồ vật   |  Weight | Giá trị | Đơn giá | Phương án |\n");
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f|%6d     |\n",
		i+1,ListItems[i].NameItem,ListItems[i].TL,ListItems[i].GT,ListItems[i].DG,ListItems[i].PA);
		TongTL=TongTL+ListItems[i].PA * ListItems[i].TL;
		TongGT=TongGT+ListItems[i].PA * ListItems[i].GT;
	}
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("Phương án (theo thứ tự đơn giá giảm dần): X(");
	for(i=0; i<n-1; i++){
		printf("%d,", ListItems[i].PA);
	}
	printf("%d)", ListItems[n-1].PA);
	printf("\nTổng trọng lượng = %-9.2f\n",TongTL);
	printf("Tổng giá trị = %-9.2f\n",TongGT);
}

void Greedy(struct Item *ListItems,int n, float W){
  int i;
  for(i=0; i<n; i++) {
     ListItems[i].PA = (W/ListItems[i].TL);
     W = W-ListItems[i].PA * ListItems[i].TL;
  }
}

int main(int argc, char const *argv[]){
    int Num;
	float W;
	struct Item *ListItems = ReadFile(&W,&Num);
    BubbleSort(ListItems,Num);
	Greedy(ListItems,Num,W);
	InListItems(ListItems,Num,W);
	free(ListItems);
}