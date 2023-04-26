#include<stdio.h>
#define Maxlength 100
typedef int DataType;
typedef struct{
    DataType Elements[Maxlength];
    int TopIndex;
}Stack;
void CreateStack(Stack *S){
    S->TopIndex = Maxlength;
}
int Empty(Stack S){
    return S.TopIndex == Maxlength;
}
int Full(Stack S){
    return S.TopIndex == 0;
}
DataType Top(Stack S){
    if(Empty(S)){
        printf("Empty\n");
    }else{
        return S.Elements[S.TopIndex];
    }
    return 0;
}
void Push(Stack *S,DataType X){
    if(Full(*S)){
        printf("Full\n");
    }else{
        S->TopIndex--;
        S->Elements[S->TopIndex] = X;
    }
}
void Pop(Stack *S){
    if(Empty(*S)){
        printf("Empty\n");
    }else{
        S->TopIndex++;
    }
}
void ReadStack(Stack *S){
    CreateStack(S);
    DataType Value;
    printf("Nhập vào số lượng phần tử\n");
    int Amount;
    scanf("%d",&Amount);
    for(int i=0;i<Amount;i++){
        printf("Phần tử số %d:",i+1);
        scanf("%d",&Value);
        Push(S,Value);
    }
}
void PrintStack(Stack S){
    printf("Ngăn xếp:");
    while(!Empty(S)){
        printf("%d ",Top(S));
        Pop(&S);
    }
}
int main(){
    Stack S;
    ReadStack(&S);
    PrintStack(S);
}