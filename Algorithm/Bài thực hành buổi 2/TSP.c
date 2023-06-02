#include <stdio.h>
#define Size 30

typedef struct {
	float Length;
	int u, v;
} Edge;

void ReadFile(char Filename[], Edge A[], int *Num){
	float Temp;
	FILE *File = fopen(Filename, "r");
	if (File==NULL){
		printf("Error!!!\n");
		return;
	}
	fscanf(File,"%d",Num);
	int k = 0;
	for(int i=0; i<*Num; i++){
		for(int j=i; j<*Num; j++){
			if(i==j){
                for(int t=0; t<=j; t++){
                    fscanf(File,"%f",&Temp);
                }
            } else {
				fscanf(File,"%f",&A[k].Length);
				A[k].u=i;
				A[k].v=j;
				k++;
			}
        }
    }
	fclose(File);
}

void PrintEdge(Edge A[], int m, int PA){
	int i;
	float Total=0.0;
	for(i=0; i<m; i++){
		printf("%3d %c%c = %8.2f\n", i+1, A[i].u+65, A[i].v+65, A[i].Length);
		if (PA){
			Total+= A[i].Length;
        }
	}
		if (PA){
			printf("Tổng độ dài các cạnh = %5.2f\n", Total);
        }
}

void Swap(Edge *x, Edge *y){
	Edge Temp= *x;
	*x = *y;
	*y = Temp;
}

void Sort(Edge A[], int n){
	int i,j;
	for(i=0; i<n-1; i++){
		for(j=n-1; j>i; j--){
			if(A[j].Length<A[j-1].Length){
				Swap(&A[j], &A[j-1]);
            }
        }
    }
}

int VerDeg3(Edge PA[], int k, Edge New){
	int i=0,Count=1;
	while(i<k && Count <3){
		if (New.u==PA[i].u || New.u==PA[i].v){
		    Count++;
        }
	    i++;
	}
	if (Count==3){
        return 1;
    }
	i=0,Count=1;
	while(i<k && Count <3){
		if (New.v==PA[i].u || New.v==PA[i].v){
		    Count++;
        }
	    i++;
	}
	return Count==3;
}

void InitForest(int Parent[], int n){
	int i;
	for(i=0; i<n; i++){
		Parent[i]=i;
    }
}

int FindRoot(int Parent[], int u){
	while (u != Parent[u]){
		u = Parent[u];
    }
	return u;
}

int Cycle(int RU, int RV){
	return (RU == RV);
}

void UpdateForest(int Parent[], int R1, int R2){
	Parent[R2]= R1;
}

void Greedy(Edge ListEdges[], int n, Edge PA[]){
	int i,j;
	int Parent[n];
	InitForest(Parent,n);
	int RU, RV;
	j = 0;
	for(i=0; i<n*(n-1)/2 && j<n-1; i++){
		RU= FindRoot(Parent, ListEdges[i].u);
		RV= FindRoot(Parent, ListEdges[i].v);
		if (!VerDeg3(PA,j, ListEdges[i]) && !Cycle(RU, RV)){
			PA[j]= ListEdges[i];
			j++;
			UpdateForest(Parent, RU, RV);
		}
	}
	for(; i<n*(n-1)/2; i++){
		RU= FindRoot(Parent, ListEdges[i].u);
		RV= FindRoot(Parent, ListEdges[i].v);
		if ((!VerDeg3(PA, n-1, ListEdges[i])) && (Cycle(RU, RV))){
			PA[n-1]= ListEdges[i];
			break;
		}
	}
}

int main(int argc, char const *argv[]){
    Edge ListEdges[Size];
	int n;

	printf("Phương án TSP dùng thuật toán tham ăn:\n");
	ReadFile("TSP.txt", ListEdges, &n);
	printf("Danh sách các cạnh của đồ thị:\n");
	PrintEdge(ListEdges, n*(n-1)/2, 0);

	Sort(ListEdges, n*(n-1)/2);
	printf("\nDanh sách các cạnh của đồ thị đã xắp sếp:\n");
	PrintEdge(ListEdges, n*(n-1)/2, 0);

	Edge PA[n];
	Greedy(ListEdges, n, PA);

	printf("\nPhương án:\n");
	PrintEdge(PA, n, 1);
    return 0;
}