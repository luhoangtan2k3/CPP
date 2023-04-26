#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
struct Node{
    DataType Elements;
    struct Node *Next;
};
typedef Node *Position;
typedef struct{
    Position Front,Rear;
}Queue;
void CreateQueue(Queue *Q){
    Position Header = (Node*)malloc(sizeof(Node));
    Header->Next = NULL;
    Q->Front = Header;
    Q->Rear = Header;
}
int EmptyQueue(Queue Q){
    return Q.Front==Q.Rear;
}
DataType Front(Queue Q){
    if(EmptyQueue(Q)){
        printf("Rỗng\n");
    }else{
        return Q.Front->Next->Elements;
    }
    return 0;
}
void EnQueue(Queue *Q,DataType X){
    Q->Rear->Next = (Node*)malloc(sizeof(Node));
    Q->Rear = Q->Rear->Next;
    Q->Rear->Elements = X;
    Q->Rear->Next = NULL;
}
void DeQueue(Queue *Q){
    if(!EmptyQueue(*Q)){
        Position Temp = Q->Front;
        Q->Front = Q->Front->Next;
        free(Temp);
    }else{
        printf("Rỗng\n");
    }
}
void ReadQueue(Queue *Q){
    printf("Nhập vào số lượng phần tử\n");
    int Amount;
    scanf("%d",&Amount);
    DataType Value;
    for(int i=0;i<Amount;i++){
        printf("Phần tử thứ %d:",i+1);
        scanf("%d",&Value);
        EnQueue(Q,Value);
    }
}
void PrintQueue(Queue Q){
    if(EmptyQueue(Q)){
        printf("Hàm rỗng\n");
    }else{
        printf("Hàng đợi:");
        while(!EmptyQueue(Q)){
            printf("%d ",Front(Q));
            DeQueue(&Q);
        }
    }
}
int main(){
    Queue Q;
    CreateQueue(&Q);
    ReadQueue(&Q);
    PrintQueue(Q);
}