#include<stdio.h>
typedef int DataType;
struct Node{
    DataType Element;
    Node *Next;
};
struct Queue{
    Node *Head;
    Node *Tail;
};
void CreateNULL(Queue &Q){
    Q.Head=NULL;
    Q.Tail=NULL;
}
bool Empty(Queue &Q){
    return Q.Head==NULL;
}
int SizeQueue(Queue Q){
    Node *Temp = Q.Head;
    int Size = 0;
    while(Temp!=NULL){
        Size++;
        Temp = Temp->Next;
    }
    return Size;
}
Node *CreateNode(DataType Value){
    Node *NODE = new Node;
    if(NODE==NULL){
        printf("Cấp phát lỗi\n");
    }else{
        NODE->Element = Value;
        NODE->Next = NULL;
    }
    return NODE;
}
void Push(Queue &Q,DataType Value){
    Node *NODE = CreateNode(Value);
    if(Empty(Q)){
        Q.Head = NODE;
        Q.Tail = NODE;
    }else{
        NODE->Next = Q.Head;
        Q.Head = NODE;
    }
}
int Pop(Queue &Q){
    if(Empty(Q)){
        printf("Hàng đợi rỗng\n");
    }else{
        Node *Temp = Q.Head;
        Node *Prev = NULL;
        DataType Value = Q.Tail->Element;
        while(Temp->Next!=NULL){
            Prev = Temp;
            Temp = Temp->Next;
        }
        Q.Tail = Prev;
        Prev->Next = NULL;
        delete Temp;
        Temp = NULL;
        return Value;
    }
    return 0;
}
void Input(Queue &Q){
    DataType Value;
    printf("Nhập vào số lượng Node\n");
    int Amount;
    scanf("%d",&Amount);
    for(int i=1;i<=Amount;i++){
        printf("Node %d:",i);
        scanf("%d",&Value);
        Push(Q,Value);
    }
}
void Output(Queue Q){
    Node *Temp = Q.Head;
    if(Empty(Q)){
        printf("Danh sách rỗng\n");
    }else{
        printf("Danh sách Node:");
        while(Temp!=NULL){
            printf("%d ",Temp->Element);
            Temp = Temp->Next;
        }
    }
}
void Pops(Queue &Q){
    printf("Nhập số lượng cần xóa\n");
    int Amount;
    scanf("%d",&Amount);
    printf("Số Node lấy ra:");
    for(int i = Amount;i>0;i--){
        printf("%d ",Pop(Q));
    }
    printf("\n");
    Output(Q);
}
void FreeMemoryListNode(Queue &Q){
    printf("Thu hồi bộ nhớ cấp phát\n");
    while(Q.Head!=NULL){
        Node *Temp = Q.Head;
        Q.Head = Temp->Next;
        Temp->Next = NULL;
        printf("Đã xóa\n");
        delete Temp;
        Temp = NULL;
    }
    printf("Đã thu hồi tất cả bộ nhớ\n");
}
int main(){
    Queue Q;
    CreateNULL(Q);
    int Options;
    do{
        printf("1 - Thêm Node vào Queue\n");
        printf("2 - Lấy Node ra khỏi Queue\n");
        printf("Nhập vào lựa chọn của bạn\n");
        scanf("%d",&Options);
        printf("\n");
        switch(Options){
            case 1:
                Input(Q);
                Output(Q);
                break;
            case 2:
                Pops(Q);
                break;
            case 0:
                FreeMemoryListNode(Q);
                break;
        }
        printf("\n\n");
    }while(Options!=0);
}