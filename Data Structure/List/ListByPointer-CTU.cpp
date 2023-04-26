#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
struct Node{
    ElementType Element;
    struct Node *Next;
};
typedef Node* Position;
typedef Position List;
void MakeNull(List *Header){
    (*Header) = (Node*)malloc(sizeof(Node));
    (*Header)->Next = NULL;
}
int EmptyList(List L){
    return L->Next ==NULL;
}
void Insert(ElementType X,Position P,List *L){
    Position T = (Node*)malloc(sizeof(Node));
    T->Element = X;
    T->Next = P->Next;
    P->Next = T;
}
void Delete(Position P,List *L){
    Position T;
    if(P->Next!=NULL){
        T = P->Next;
        P->Next = T->Next;
        free(T);
    } else {
        printf("Danh sách rỗng");
    }
}
Position Locate(ElementType X,List L){
    Position P;
    int Found=0;
    while((P->Next!=NULL)&&(Found==0)){
        if(P->Next->Element == X){
            Found = 1;
        } else {
            P = P->Next;
        }
    }
    return P;
}
ElementType Retrieve(Position P,List L){
    if(P->Next!=NULL){
        return P->Next->Element;
    }
    return 0;
}
Position FirstList(List L){
    return L;
}
Position EndList(List L){
    Position P;
    P = FirstList(L);
    while(P->Next!=NULL){
        P = P->Next;
    }
    return P;
}
void ReadList(List *L){
    ElementType X;
    int Amount;
    printf("Nhập số lượng phần tử trong danh sách\n");
    scanf("%d",&Amount);
    for(int i=1;i<=Amount;i++){
        printf("Phần tử thứ %d:",i);
        scanf("%d",&X);
        Insert(X,FirstList(*L),L);
    }
}
void PrintList(List L){
    Position P;
    P = FirstList(L);
    while(P!=EndList(L)){
        printf("%d ",Retrieve(P,L));
        P = P->Next;
    }
}
int main(){
    List L;
    MakeNull(&L);
    ReadList(&L);
    PrintList(L);
}