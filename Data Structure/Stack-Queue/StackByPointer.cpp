#include<stdio.h>
typedef int DataType;
struct Node{
    DataType Element;
    Node *Next;
};
struct Stack{
    Node *TopIndex;
};
void CreateNULL(Stack &S){
    S.TopIndex = NULL;
}
Node *CreateNode(DataType Value){
    Node *NODE = new Node;
    if(NODE==NULL){
        printf("Không đủ bộ nhớ cấp phát\n");
    }else{
        NODE->Element = Value;
        NODE->Next = NULL;
    }
    return NODE;
}
bool Empty(Stack S){
    return S.TopIndex == NULL;
}
int SizeTop(Stack S){
    Node *Temp = S.TopIndex;
    int Size = 0;
    while(Temp!=NULL){
        Size++;
        Temp = Temp->Next;
    }
    return Size;
}
void Push(Stack &S,DataType Value){
    Node *NODE = CreateNode(Value);
    if(Empty(S)){
        S.TopIndex = NODE;
    }else{
        NODE->Next = S.TopIndex;
        S.TopIndex = NODE;
    }
}
int Pop(Stack &S){
    Node *Temp = S.TopIndex;
    DataType Value;
    if(Empty(S)){
        printf("Ngăn xếp rỗng\n");
    }else{
        Value = S.TopIndex->Element;
        S.TopIndex = S.TopIndex->Next;
        Temp->Next = NULL;
        delete Temp;
        Temp = NULL;
    }
    return Value;
}
void Input(Stack &S){
    DataType Value;
    printf("Nhập vào số lượng Node\n");
    int Amount;
    scanf("%d",&Amount);
    for(int i=1;i<=Amount;i++){
        printf("Node %d:",i);
        scanf("%d",&Value);
        Push(S,Value);
    }
}
void Output(Stack S){
    Node *Temp = S.TopIndex;
    if(Empty(S)){
        printf("Danh sách rỗng\n");
    }else{
        printf("Danh sách Node:");
        while(Temp!=NULL){
            printf("%d ",Temp->Element);
            Temp = Temp->Next;
        }
    }
}
void Pops(Stack &S){
    printf("Nhập vào số lượng Node cần lấy ra khỏi Stack\n");
    int Amount;
    scanf("%d",&Amount);
    printf("Số Node đã lấy ra:");
    for(int i=Amount;i>0;i--){
        printf("%d ",Pop(S));
    }
    printf("\n");
    Output(S);
}
void RemoveInLocation(Stack &S){
    Stack T;
    CreateNULL(T);
    printf("Nhập vào vị trí cần xóa\n");
    int Location;
    scanf("%d",&Location);
    if(Location<=SizeTop(S) && Location>=1){
        for(int i=SizeTop(S);i>Location;i--){
            Push(T,Pop(S));
        }
        Pop(S);
        for(int i=SizeTop(T);i>0;i--){
            Push(S,Pop(T));
        }
        Output(S);
    } else {
        printf("Vị trí không hợp lệ\n");
    }
}
void AddInLocation(Stack &S){
    Stack T;
    CreateNULL(T);
    printf("Nhập vào vị trí cần chèn\n");
    int Location;
    scanf("%d",&Location);
    if(Location<=SizeTop(S)+1 && Location>=1){
        printf("Nhập vào giá trị cần chèn\n");
        DataType Value;
        scanf("%d",&Value);
        for(int i=SizeTop(S);i>=Location;i--){
            Push(T,Pop(S));
        }
        Push(S,Value);
        for(int i=SizeTop(T);i>0;i--){
            Push(S,Pop(T));
        }
        Output(S);
    } else {
        printf("Vị trí không hợp lệ\n");
    }
}
void FreeMemoryListNode(Stack &S){
    printf("Thu hồi bộ nhớ cấp phát\n");
    while(S.TopIndex!=NULL){
        Node *Temp = S.TopIndex;
        S.TopIndex = Temp->Next;
        Temp->Next = NULL;
        printf("Đã xóa\n");
        delete Temp;
        Temp = NULL;
    }
    printf("Đã thu hồi tất cả bộ nhớ\n");
}
int main(){
    Stack S;
    CreateNULL(S);
    int Options;
    do{
        printf("1 - Thêm Node vào Stack\n");
        printf("2 - Lấy Node ra khỏi Stack\n");
        printf("3 - Xóa Node tại vị trí chỉ định\n");
        printf("4 - Chèn Node tại vị trí chỉ định\n");
        printf("Nhập vào lựa chọn của bạn\n");
        scanf("%d",&Options);
        printf("\n");
        switch(Options){
            case 1:
                Input(S);
                Output(S);
                break;
            case 2:
                Pops(S);
                break;
            case 3:
                RemoveInLocation(S);
                break;
            case 4:
                AddInLocation(S);
                break;
            case 0:
                FreeMemoryListNode(S);
                break;
        }
        printf("\n\n");
    }while(Options!=0);
}