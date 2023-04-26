#include<stdio.h>
#define Maxlength 100
typedef int Position;
typedef int DataType;
typedef struct{
    DataType Elements[Maxlength];
    Position Last;
}List;
void MakeNullList(List *L){
    L->Last = 0;
}
int EmptyList(List L){
    return L.Last==0;
}
int FullList(List L){
    return L.Last==Maxlength;
}
Position First(List L){
    return 1;
}
Position End(List L){
    return L.Last+1;
}
Position Next(List L,Position P){
    return P+1;
};
Position Prev(List L,Position P){
    return P-1;
}
DataType Retrieve(List L,Position P){
    return L.Elements[P-1];
}
void InsertList(List *L,Position P,DataType X){
    if(FullList(*L)){
        printf("Full\n");
    } else if(P<1||P>L->Last+1){
        printf("Error");
    } else {
        Position T;
        for(T=L->Last;T>=P;T--){
            L->Elements[T] = L->Elements[T-1];
        }
        L->Last++;
        L->Elements[P-1] = X;
    }
}
void DeleteList(List *L,Position P){
    if(EmptyList(*L)){
        printf("Empty\n");
    }else if(P<1||P>L->Last){
        printf("Error\n");
    }else {
        Position T;
        for(T=P;T<L->Last;T++){
            L->Elements[T-1] = L->Elements[T];
        }
        L->Last--;
    }
}
void ReadList(List *L){
    DataType Value;
    MakeNullList(L);
    printf("Nhập vào số lượng phần tử\n");
    int Amount;
    scanf("%d",&Amount);
    for(int i=0;i<Amount;i++){
    scanf("%d",&Value);
    InsertList(L,End(*L),Value);
    }
}
void PrintList(List L){
    Position P = First(L);
    while(P != End(L)){
        printf("%d ",Retrieve(L,P));
        P = Next(L,P);
    }
    printf("\n");
}
int main(){
    List L;
    ReadList(&L);
    PrintList(L);
}