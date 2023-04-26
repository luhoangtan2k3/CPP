#include<stdio.h>
#define Maxlength 100
typedef int DataType;
struct Stack{
    DataType Elements[Maxlength];
    int TopIndex;
};
void Init(Stack &S){
    S.TopIndex = -1;
}
void Push(Stack &S,DataType Value){
    S.TopIndex++;
    S.Elements[S.TopIndex] = Value;
//S.Elements[++S.TopIndex] = Value;
}
int Pop(Stack &S){
    int Value = S.Elements[S.TopIndex];
    S.TopIndex--;
    return Value;
//return S.Elements[S.TopIndex--];
}
bool Empty(Stack &S){
    return S.TopIndex<0;
}
bool Full(Stack &S){
    return S.TopIndex==Maxlength-1;
}
void Output(Stack S){
    printf("Stack[]=");
    for(int i=0;i<=S.TopIndex;i++){
        printf("%d ",S.Elements[i]);
    }
}
void Input(Stack &S){
    int Amount;
    printf("Nhập vào số lượng phần tử\n");
    scanf("%d",&Amount);
    DataType Value;
    for(int i=0;i<Amount;i++){
        printf("Vị trí %d: ",i+1);
        scanf("%d",&Value);
        Push(S,Value);
    }
}
void Pops(Stack &S){
    printf("Nhập số phần tử cần lấy ra\n");
    int Amount;
    scanf("%d",&Amount);
    for(int i=Amount-1;i>=0;i--){
        Pop(S);
    }
    Output(S);
}
void RemoveInLocation(Stack &S){
    Stack T;
    Init(T);
    printf("Nhập vào vị trí cần xóa\n");
    int Locate;
    scanf("%d",&Locate);
    for(int i=S.TopIndex;i>Locate-1;i--){
        Push(T,Pop(S));
    }
    Pop(S);
    for(int i=T.TopIndex;i>=0;i--){
        Push(S,Pop(T));
    }
    Output(S);
}
void AddInLocation(Stack &S){
    Stack T;
    Init(T);
    printf("Nhập vị trí cần chèn thêm\n");
    int Locate;
    scanf("%d",&Locate);
    printf("Nhập vào giá trị cần chèn\n");
    int Value;
    scanf("%d",&Value);
    for(int i=S.TopIndex;i>=Locate-1;i--){
        Push(T,Pop(S));
    }
    Push(S,Value);
    for(int i=T.TopIndex;i>=0;i--){
        Push(S,Pop(T));
    }
    Output(S);
}
void ConvertDecimaltoBinary(int Value){
    Stack S;
    Init(S);
    if(Value<0){
        printf("Không tồn tại\n");
    } else {
        while(Value!=0){
            Push(S,Value%2);
            Value=Value/2;
        }
        printf("Số nhị phân: ");
        while(Empty(S)==false){
            printf("%d",Pop(S));
        }
    }
}
int main(){
    Stack S;
    DataType Value;
    int Options;
    Init(S);
    do{
        printf("1 - Nhập chuỗi số vào Stack\n");
        printf("2 - Lấy phần tử ra khỏi Stack\n");
        printf("3 - Tính số nhị phân phần tử\n");
        printf("4 - Xóa phần tử tại vị trí bất kỳ khỏi Stack\n");
        printf("5 - Thêm phần tử tại vị trí bất kỳ vào Stack\n");
        printf("Nhập thao tác của bạn\n");
        scanf("%d",&Options);
        switch(Options){
            case 1:
                Input(S);
                Output(S);
                break;
            case 2:
                Pops(S);
                break;
            case 3:
                printf("Nhập vào số bất kỳ\n");
                scanf("%d",&Value);
                ConvertDecimaltoBinary(Value);
                break;
            case 4:
                RemoveInLocation(S);
                break;
            case 5:
                AddInLocation(S);
                break;
        }
        printf("\n\n");
    }while(Options!=0);
}