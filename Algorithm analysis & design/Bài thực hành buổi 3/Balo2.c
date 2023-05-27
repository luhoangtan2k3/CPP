#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char NameItem[20];
	float TL, GT, DG;
	int SL, PA;
} Item;

Item * ReadFromFile(float *W, int *Num){
     FILE *File = fopen("Balo.INP", "r");
     fscanf(File, "%f",W);
	 Item *ListItems;
	 ListItems=(Item*)malloc(sizeof(Item));
	 int i=0;
 	 while (!feof(File)){
	   fscanf(File, "%f%f%d%[^\n]",&ListItems[i].TL,&ListItems[i].GT,&ListItems[i].SL,&ListItems[i].NameItem);
	   ListItems[i].DG=ListItems[i].GT/ListItems[i].TL;
	   ListItems[i].PA=0;
	   i++;
	   ListItems=(Item*)realloc(ListItems, sizeof(Item)*(i+1));
	 }
	 *Num=i;
     fclose(File);
     return ListItems;
}

void Swap(Item *x, Item *y){
	Item Temp;
	Temp = *x;
	*x   = *y;
	*y   = Temp;
}

void BubbleSort(Item *ListItems, int n){
	int i,j;
	for(i=0; i<=n-2; i++){
	    for (j=n-1; j>=i+1; j--){
	   	    if (ListItems[j].DG>ListItems[j-1].DG){
		        Swap(&ListItems[j],&ListItems[j-1]);
            }
	    }
    }
}

void InListItems(Item *ListItems ,int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhương án cái balo dùng thuật toán nhánh cận:\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	printf("|STT|     Tên đồ vật     |  Weight | Giá trị |Số lượng | Đơn giá | Phương án |\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-20s|%9.2f|%9.2f|%5d    |%9.2f|%6d     |\n",
		i+1,ListItems[i].NameItem,ListItems[i].TL,ListItems[i].GT,ListItems[i].SL,ListItems[i].DG, ListItems[i].PA);
		TongTL=TongTL+ListItems[i].PA * ListItems[i].TL;
		TongGT=TongGT+ListItems[i].PA * ListItems[i].GT;
	}
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	printf("Trọng lượng của balo = %-9.2f\n",W);
	printf("Tổng trọng lượng = %-9.2f\n",TongTL);
	printf("Tổng giá trị = %-9.2f\n",TongGT);
}


void CreateRoot(float W, float *V, float *CT, float *GLNTT, float *TGT, float DG_Max){
	*TGT = 0.0;
	*V = W;
	*CT = *V * DG_Max;
	*GLNTT = 0.0;
}

void UpdateGLNTT(float TGT, float *GLNTT, int x[], Item *ListItems, int n){
	 int i;
	 if(*GLNTT < TGT){
		 *GLNTT = TGT;
		 for(i=0;i<n;i++){
		    ListItems[i].PA=x[i];
        }
	}
}

int Min(int a, int b){
	return a<b? a:b;
}

void BranchandBound(int i, float *TGT, float *CT, float *V, float *GLNTT, int x[], Item *ListItems, int n){
	 int j;
	 int m = Min(ListItems[i].SL, *V/ListItems[i].TL);
	 for(j = m; j>=0; j--){
		*TGT = *TGT + j*ListItems[i].GT;
		*V = *V - j*ListItems[i].TL;
		*CT = *TGT + *V * ListItems[i+1].DG;

		if(*CT > *GLNTT){
		    x[i] = j;
		 	if((i==n-1)||(*V==0)){
		 		UpdateGLNTT(*TGT, GLNTT, x, ListItems, n);
            }else{
		 		BranchandBound(i+1, TGT, CT, V, GLNTT, x, ListItems, n);
            }
	 	}
        x[i] = 0;
        *TGT = *TGT - j*ListItems[i].GT;
        *V = *V + j*ListItems[i].TL;
	}
}
int main(int argc, char const *argv[]){
	int n;
	float W,CT,TGT,V,GLNTT;

	Item *ListItems = ReadFromFile(&W, &n);

	int x[n];

	BubbleSort(ListItems,n);
	CreateRoot(W, &V, &CT, &GLNTT, &TGT, ListItems[0].DG);
	BranchandBound(0, &TGT, &CT, &V, &GLNTT, x, ListItems, n);
	InListItems(ListItems,n,W);

	free(ListItems);
}