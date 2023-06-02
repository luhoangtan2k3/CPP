#include <stdio.h>
#define Size 50

void ReadData(int A[][Size], int *Num){
	FILE *File = fopen("Triangle.txt", "r");
	if(File==NULL){
		printf("Error!!!\n");
		return;
	}
	int i=0,j;
	while (!feof(File)){
		for(j=0; j<=i; j++){
			fscanf(File, "%d", &A[i][j]);
        }
		i++;
	}
	*Num=i;
	fclose(File);
}

void PrintData(int A[][Size], int n){
	int i,j;
	printf("\nTam giác số đã cho\n");
	for(i=0; i<n; i++){
		for(j=0; j<=i; j++){
			printf("%5d", A[i][j]);
		}
		printf("\n");
	}
}

int CS_max(int F[][Size], int i, int j){
	if (j==0){
		return (F[i-1][0]>F[i-1][1])? 0:1;
	}
	if (j==i){
		return i-1;
	}
	if (j==i-1){
		return (F[i-1][i-2]>F[i-1][i-1])? i-2:i-1;
	}
	if (F[i-1][j-1]>F[i-1][j]&&F[i-1][j-1]>F[i-1][j+1]){
		return j-1;
	}
	if (F[i-1][j]>F[i-1][j-1]&&F[i-1][j]>F[i-1][j+1]){
		return j;
	}
	if (F[i-1][j+1]>F[i-1][j]&&F[i-1][j+1]>F[i-1][j-1]){
		return j+1;
	}
}

void Tao_Bang(int a[][Size], int n, int F[][Size]){
 	int i, j;
 	F[0][0]= a[0][0];
 	F[1][0]= F[0][0] + a[1][0];
 	F[1][1]= F[0][0] + a[1][1];
	for(i=2; i<n; i++){
		for(j=0; j<=i; j++){
			int k=CS_max(F,i,j);
			F[i][j] = F[i-1][k] + a[i][j];
		}
	}
}

void In_Bang(int n, int F[][Size]){
	int i, j;
	printf("\nBảng F\n");
	for(i=0; i<n; i++){
		for(j=0; j<=i; j++){
		 	printf("%5d", F[i][j]);
		}
		printf("\n");
	}
}

int CS_max_dong_cuoi(int F[], int j){
	int Somax=F[0];
	int Maxindex=0;
	int k;
	for(k=1; k<=j; k++){
		if (F[k]>Somax){
			Somax=F[k];
			Maxindex=k;
		}
	}
	return Maxindex;
}
void Tra_Bang(int A[][Size], int n, int F[][Size], int PA[]){
	int i,j = CS_max_dong_cuoi(F[n-1],n-1);
	PA[n-1]=A[n-1][j];
	for(i=n-1; i>=1; i--){
		j = CS_max(F,i,j);
		PA[i-1]=A[i-1][j];
	}
}

int GiaPA(int PA[], int n){
	int i,Sum=0;
	for(i=0; i<n; i++){
		Sum+=PA[i];
	}
	return Sum;
}

void PrintPA(int PA[], int n){
	int i;
	printf("\nPhương án là đường đi qua các số: ");
	printf("%d", PA[0]);
	for(i=1; i<n; i++){
		printf(" => %d", PA[i]);
	}
	printf("\n\nTổng các số trên đường đi là %d\n", GiaPA(PA,n));
}

int main(){
	int A[Size][Size];
	int n;
	printf("\nBài toán tam giác số dùng quy hoạch động\n");
	ReadData(A,&n);
	PrintData(A,n);
	int PA[n],F[n][Size];
	Tao_Bang(A,n,F);
	In_Bang(n,F);
	Tra_Bang(A,n,F,PA);
	PrintPA(PA,n);
}