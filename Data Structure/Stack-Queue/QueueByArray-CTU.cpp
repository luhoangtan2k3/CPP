#include<stdio.h>
#define MaxLength 100
typedef int DataType;
typedef struct{
    DataType Elements[MaxLength];
    int Front,Rear;
}Queue;
void CreateQueue(Queue *Q){
    Q->Front = -1;
    Q->Rear = -1;
}
int EmptyQueue(Queue Q){
    return Q.Front == -1;
}
int FullQueue(Queue Q){
    return (Q.Rear-Q.Front+1) == MaxLength;
}
DataType Front(Queue Q){
    if(EmptyQueue(Q)){
        printf("Hàm rỗng\n");
    }else{
        return Q.Elements[Q.Front];
    }
    return 0;
}
void DeQueue(Queue *Q){
    if(!EmptyQueue(*Q)){
        Q->Front++;
        if(Q->Front>Q->Rear){
            CreateQueue(Q);
        }
    }else{
        printf("Hàm rỗng\n");
    }
}
void EnQueue(Queue *Q,DataType X){
    if(!FullQueue(*Q)){
        if(EmptyQueue(*Q)){
            Q->Front = 0;
        }
        if(Q->Rear==MaxLength-1){
            for(int i=Q->Front;i<=Q->Rear;i++){
                Q->Elements[i-Q->Front]=Q->Elements[i];
            }
            Q->Front = 0;
            Q->Rear = Q->Rear - Q->Front;
        }
        Q->Rear++;
        Q->Elements[Q->Rear] = X;
    }else{
        printf("Hàm đầy\n");
    }
}
void ReadQueue(Queue *Q){
    CreateQueue(Q);
    DataType Value;
    printf("Nhập vào số lượng phần tử\n");
    int Amount;
    scanf("%d",&Amount);
    for(int i=0;i<Amount;i++){
        printf("Phần tử số %d:",i+1);
        scanf("%d",&Value);
        EnQueue(Q,Value);
    }
}
void PrintQueue(Queue Q){
    printf("Hàng đợi:");
    while(!EmptyQueue(Q)){
        printf("%d ",Front(Q));
        DeQueue(&Q);
    }
}