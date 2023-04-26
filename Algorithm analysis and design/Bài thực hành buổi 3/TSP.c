#include <stdio.h>
#define Size 30

typedef struct {
	float Length;
	int u, v;
	int Used;
} Edge;

void ReadFile(char Filename[], Edge A[][Size], int *n){
	int i,j;
	FILE *File = fopen(Filename, "r");
	if (File==NULL){
		printf("Error!!!\n");
		return;
	}
	fscanf(File,"%d",n);

	for(i=0; i<*n; i++){
		for(j=0; j<*n; j++){
			fscanf(File,"%f",&A[i][j].Length);
			A[i][j].u=i;
			A[i][j].v=j;
			A[i][j].Used=0;;
		}
    }
	fclose(File);
}

void Matrix(Edge a[][Size], int n){
	int i,j;
	printf("\nMa trận trọng số của đồ thị\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf(" %c%c =%5.2f  ",a[i][j].u+65, a[i][j].v+65, a[i][j].Length);
        }
		printf("\n");
	}
}

void IN_PA(Edge PA[], int n){
	int i;
	float Sum=0.0;
	printf("\nPhương án tìm được:\n");
	for(i=0; i<n; i++){
		Sum+= PA[i].Length;
		printf(" Edge %c%c = %5.2f\n", PA[i].u+65, PA[i].v+65, PA[i].Length);
    }
    printf("Chu trình:");
	for(i=0; i<n; i++){
		printf("%c",PA[i].u+65);
		printf("-> ");
    }
	printf("%c",PA[0].u+65);
	printf("\nTổng độ dài các cạnh của chu trình = %5.2f\n", Sum);
}

float Edge_NN(Edge a[][Size], int n){
	float Cmin=3.40282e+38;
	int i,j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i!=j && !a[i][j].Used && a[i][j].Length<Cmin){
				Cmin= a[i][j].Length;
            }
        }
    }
	return Cmin;
}

float CanDuoi(Edge a[][Size], float TGT, int n, int i){
	return TGT+ (n-i)*Edge_NN(a,n);
}


void Cap_Nhat_PA_TNTT(Edge a[][Size], int n, float TGT, float *GNNTT, Edge x[], Edge PA[]){
	int i;
	x[n-1]=a[x[n-2].v][x[0].u];
	TGT= TGT + x[n-1].Length;
	if(*GNNTT > TGT){
		*GNNTT = TGT;
		for(i=0; i<n; i++){
		    PA[i]=x[i];
        }
	}
}

int IsCycle(Edge x[], int k, int Next){
	int i=0, IsCycle=0;
	while (i<k && !IsCycle){
		if(Next==x[i].u){
            IsCycle=1;
        } else {
            i++;
        }
    }
	return IsCycle;
}

void BranchandBound(Edge A[][Size], int n, int i, int u, float *TGT, float *CD, float *GNNTT, Edge X[], Edge PA[]){
	 int j;
	 for(j=0; j<n; j++){
	    if (u!=j && !A[u][j].Used && !IsCycle(X,i,j)){
            *TGT = *TGT + A[u][j].Length;
            *CD = CanDuoi(A, *TGT, n, i+1);
            if(*CD < *GNNTT){
                X[i] = A[u][j];
                A[u][j].Used=1;
                A[j][u].Used=1;
                if(i==n-2){
                    Cap_Nhat_PA_TNTT(A, n, *TGT, GNNTT, X, PA);
                }else{
                    BranchandBound(A, n, i+1, j, TGT, CD, GNNTT, X, PA);
                }
            }
            *TGT = *TGT - A[u][j].Length;
            A[u][j].Used=0;
            A[j][u].Used=0;
        }
    }
}

void Reset(Edge a[][Size], int n){
	int i,j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			a[i][j].Used=0;
}

int main(int argc, char const *argv[]){
    Edge A[Size][Size];
	int n;
	printf("\nPhương án TSP bằng phương pháp nhánh cận:\n");
	ReadFile("TSP.txt",A,&n);
	Edge PA[n];
	Edge X[n];
	char TPXP, YN;
	while (1){
		fflush(stdin);
		Matrix(A,n);
		float TGT=0.0, CD = 0.0, GNNTT = 3.40282e+38;
		printf("\nXuất phát từ thành phố nào?");
		printf("\nNhập 1 thành phố từ A đến %c: ", n-1+65);
		scanf("%c", &TPXP);
		BranchandBound(A, n, 0, TPXP-65, &TGT, &CD, &GNNTT, X, PA);
		IN_PA(PA,n);
		fflush(stdin);
		printf("\nTiếp tục Y/N? ");
		scanf("%c", &YN);
		if (YN == 'N' || YN == 'n'){
			break;
        }
		Reset(A,n);
    }
}