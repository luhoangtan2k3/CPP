#include<stdio.h>
typedef struct{
    int DataLeft;
    float DataRight;
}Data;
void Swap(Data *D1, Data *D2){
    Data Temp = *D1;
    *D1 = *D2;
    *D2 = Temp;
}
void ReadFile(Data Arr[], int *Num){
    FILE *File = fopen("Sort.txt","r");
    if(File!=NULL){
        int i=0;
        while(!feof(File)){
            fscanf(File,"%d%f",&Arr[i].DataLeft,&Arr[i].DataRight);
            i++;
        }
        fclose(File);
        *Num = i;
    }else{
        printf("Error");
    }
}
void Print(Data Arr[], int Num){
    for(int i=0;i<Num;i++){
        printf("%3d %.2f\n",Arr[i].DataLeft,Arr[i].DataRight);
    }
}
void SelectionSort(Data Arr[], int Num){
    int Min = 0;
    for(int i=0;i<Num-1;i++){
        Min = i;
        for(int j=i+1;j<Num;j++){
            if(Arr[Min].DataLeft>Arr[j].DataLeft){
                Min = j;
            }
        }
        Swap(&Arr[Min],&Arr[i]);
    }
}
void BubbleSort(Data Arr[], int Num){
    for(int i=0;i<Num-1;i++){
        for(int j=Num-1;j>i;j--){
            if(Arr[j-1].DataLeft>Arr[j].DataLeft){
                Swap(&Arr[j-1],&Arr[j]);
            }
        }
    }
}
void InsertSort(Data Arr[], int Num){
    int i,j;
    for(i=1;i<Num;i++){
        j=i;
        while(j>0&&Arr[j-1].DataLeft>Arr[j].DataLeft){
            Swap(&Arr[j-1],&Arr[j]);
            j--;
        }
    }
}
int Partition(Data Arr[], int i, int j){
    int Pivot = Arr[i].DataLeft;
    int Left = i+1;
    int Right = j;
    while(Left<=Right){
        while(Left<=Right&&Arr[Left].DataLeft<=Pivot)
        Left++;
        while(Left<=Right&&Arr[Right].DataLeft>=Pivot)
        Right--;
        if(Left<Right){
            Swap(&Arr[Left],&Arr[Right]);
        }
    }
    Swap(&Arr[Right],&Arr[i]);
    return Right;
}
void QuickSort(Data Arr[], int i, int j){
    if(i<j){
        int Par = Partition(Arr,i,j);
        QuickSort(Arr,i,Par-1);
        QuickSort(Arr,Par+1,j);
    }
}
void PushDown(Data Arr[], int First, int Last){
    int Root = First;
    while(Root<(Last-1)/2){
        if(Last==2*Root+1){
            if(Arr[Root].DataLeft<Arr[Last].DataLeft){
                Swap(&Arr[Root],&Arr[Last]);
            }
            Root = Last;
        }else if(Arr[Root].DataLeft<Arr[2*Root+1].DataLeft&&Arr[2*Root+1].DataLeft>=Arr[2*Root+2].DataLeft){
            Swap(&Arr[Root],&Arr[2*Root+1]);
            Root = 2*Root+1;
        }else if(Arr[Root].DataLeft<Arr[2*Root+2].DataLeft){
            Swap(&Arr[Root],&Arr[2*Root+2]);
            Root = 2*Root+2;
        }else{
            Root = Last;
        }
    }
}
void HeapSort(Data Arr[], int Num){
    int i;
    for(i=(Num-2)/2;i>=0;i--){
        PushDown(Arr,i,Num-1);
    }
    for(i=Num-1;i>=2;i--){
        Swap(&Arr[0],&Arr[i]);
        PushDown(Arr,0,i-1);
    }
    Swap(&Arr[0],&Arr[1]);
}
int main(int argc, char const *argv[]){
    Data D[100];
    int Num;
    ReadFile(D,&Num);
    printf("Dữ liệu trước khi sắp xếp\n");
    Print(D,Num);
    printf("Dữ liệu sau khi sắp xếp\n");
    QuickSort(D,0,Num-1);
    Print(D,Num);
}