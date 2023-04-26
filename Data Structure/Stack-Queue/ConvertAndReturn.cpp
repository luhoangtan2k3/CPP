#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define Maxlength 100
typedef int DataType;
typedef char String;
struct Stack{
    DataType Elements[Maxlength];
    int TopIndex;
};
void Init(Stack &S){
    S.TopIndex = -1;
}
DataType TopIndex(Stack S){
    return S.Elements[S.TopIndex];
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
bool Empty(Stack S){
    return S.TopIndex<0;
}
bool Full(Stack S){
    return S.TopIndex==Maxlength-1;
}
void DeleteEnter(String String[]){
    size_t Length=strlen(String);
    if(String[Length-1]=='\n'){
        String[Length-1]='\0';
    }
}
// Độ ưu tiên của toán tử
int Precedence(String Char){
    if(Char=='+'||Char=='-'){
        return 1;
    }else if(Char=='*'||Char=='/'||Char=='%'){
        return 2;
    }else{
        return 0;
    }
}
// Chuyển biểu thức trung tố thành hậu tố.
void InfixToPostfix(String Infix[],String Postfix[]){
    Stack BlackBox;
    Init(BlackBox);
    String Temp;
    String Token;
    int i=0,j=0;
    for(i;Infix[i]!='\0';i++){
        if(Infix[i]==32) continue;
        Token = Infix[i];
        //Hàm isalnum(Token) kiểm tra xem Token có phải là ký tự chữ hoặc ký tự số hay không ???
        //Hàm isalnum() nằm trong thư viện ctype.h
        if(isalnum(Token)){
            Postfix[j++] = Token;
            Postfix[j++] = ' ';
        }else if(Token=='('){
            Push(BlackBox,Token);
        }else if(Token==')'){
            while((Temp=Pop(BlackBox))!='('){
                Postfix[j++] = Temp;
                Postfix[j++] = ' ';
            }
        }else{
            while((Precedence(Token)<=Precedence(TopIndex(BlackBox)))&&!Empty(BlackBox)){
                Temp = Pop(BlackBox);
                Postfix[j++] = Temp;
                Postfix[j++] = ' ';
            }
            Push(BlackBox,Token);
        }
    }
    while(!Empty(BlackBox)){
        Temp = Pop(BlackBox);
        Postfix[j++] = Temp;
        Postfix[j++] = ' ';
    }
    Postfix[j] = '\0';
}
DataType Calculate(DataType A,DataType B,String Operator){
    switch(Operator){
        case '+':
            return A+B;
        case '-':
            return A-B;
        case '*':
            return A*B;
        case '/':
            return A/B;
        case '%':
            return A%B;
    }
    return 0;
}
// Trả về giá trị của biểu thức hậu tố
DataType ReturnValue(String Postfix[]){
    Stack BlackBox;
    Init(BlackBox);
    DataType Top,Bot;
    String Token;
    size_t Length = strlen(Postfix);
    for(int i=0;i<Length;i++){
        Token = Postfix[i];
        if(Token==32) continue;
        // Hàm isdigit(Token) kiểm tra xem Token có phải là ký tự số hay không ???
        //Hàm isdigit() nằm trong thư viện ctype.h
        if(isdigit(Token)){
            Push(BlackBox,Token-48);
        }else{
            Top = Pop(BlackBox);
            Bot = Pop(BlackBox);
            Push(BlackBox,Calculate(Bot,Top,Token));
        }
    }
    return TopIndex(BlackBox);
}
// Kiểm tra dấu ngoặc '(' và ')' có hợp lệ hay không ???
bool CheckBracket(String Infix[]){
    Stack BlackBox;
    Init(BlackBox);
    size_t Length = strlen(Infix);
    for(int i=0;i<Length;i++){
        if(Infix[i]=='('||Infix[i]==')'){
            if(Infix[i]=='('){
                Push(BlackBox,Infix[i]);
            }else{
                if(Empty(BlackBox)||TopIndex(BlackBox)!='('){
                    return false;
                }
                Pop(BlackBox);
            }
        }else continue;
    }
    return Empty(BlackBox)==true;
}
int main(){
    String Infix[Maxlength],Postfix[Maxlength];
    printf("Nhập vào chuỗi trung tố:");
    fgets(Infix,Maxlength,stdin);
    DeleteEnter(Infix);
    if(CheckBracket(Infix)){
        InfixToPostfix(Infix,Postfix);
        printf("Chuỗi hậu tố:%s\n",Postfix);
        printf("Giá trị: %d",ReturnValue(Postfix));
    }else{
        printf("Dấu ngoặc không hợp lệ\n");
    }
}