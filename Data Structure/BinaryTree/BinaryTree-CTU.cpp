#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef char DataType;
struct Node{
    DataType Elements;
    Node *Left;
    Node *Right;
};
typedef Node* Tree;
void MakeNullTree(Tree *T){
    (*T) = NULL;
}
bool EmptyTree(Tree T){
    return T==NULL;
}
Tree LeftChild(Tree T){
    if(!EmptyTree(T)){
        return T->Left;
    }else return NULL;
}
Tree RightChild(Tree T){
    if(!EmptyTree(T)){
        return T->Right;
    }else return NULL;
}
bool Infertility(Tree T){
    return !EmptyTree(T)&&T->Left==NULL&&T->Right==NULL;
}
bool HaveTwoChild(Tree T){
    return !EmptyTree(T)&&T->Left!=NULL&&T->Right!=NULL;
}
bool HaveOneChild(Tree T){
    return !EmptyTree(T)&&!Infertility(T)&&!HaveTwoChild(T);
}
void NLR(Tree T){
    if(!EmptyTree(T)){
        printf("%d ",T->Elements);
        NLR(LeftChild(T));
        NLR(RightChild(T));
    }
}
void LNR(Tree T){
    if(!EmptyTree(T)){
        LNR(LeftChild(T));
        printf("%c ",T->Elements);
        LNR(RightChild(T));
    }
}void LRN(Tree T){
    if(!EmptyTree(T)){
        LRN(LeftChild(T));
        LRN(RightChild(T));
        printf("%d ",T->Elements);
    }
}
int NumberofNode(Tree T){
    if(EmptyTree(T)){
        return 0;
    } else return NumberofNode(T->Left)+NumberofNode(T->Right)+1;
}
int Max(int Value1,int Value2){
    return (Value1>Value2)?Value1:Value2;
}
int TreeHeight(Tree T){
    int Height = 0;
    if(!EmptyTree(T)){
        if(Infertility(T)){
            Height = 0;
        }else{
            Height = Max(TreeHeight(LeftChild(T)),TreeHeight(RightChild(T)))+1;
        }
    }
    return Height;
}
int NumberofLeaf(Tree T){
    int Leaf = 0;
    if(!EmptyTree(T)){
        if(Infertility(T)){
            Leaf++;
        }else{
            Leaf = NumberofLeaf(LeftChild(T))+NumberofLeaf(RightChild(T));
        }
    }
    return Leaf;
}
Tree CreateTree(DataType Value,Tree Left,Tree Right){
    Tree New = (Node*)malloc(sizeof(Node));
    New->Elements = Value;
    New->Left = Left;
    New->Right = Right;
    return New;
}
//Hàm biến đổi cây gốc thành cây phản chiếu của nó
void Reverse1(Tree &T){
    Tree Temp = T->Right;
    T->Right = T->Left;
    T->Left = Temp;
    if(T->Left!=NULL){
        Reverse1(T->Left);
    }
    if(T->Right!=NULL){
        Reverse1(T->Right);
    }
}
//Hàm trả hoán đổi
void SwapTree(Tree &TreeLeft,Tree &TreeRight){
    Tree Temp = TreeLeft;
    TreeLeft = TreeRight;
    TreeRight = Temp;
}
// Hàm trả về cây phản chiếu nhưng ko biến đổi cây gốc
Tree Reverse2(Tree T) {
    Tree Mirror = T;
    if(EmptyTree(T)){
        return NULL;
    }
    if(Infertility(T)){
        return Mirror;
    }
    Mirror->Left = Reverse2(LeftChild(T));
    Mirror->Right = Reverse2(RightChild(T));
    SwapTree(Mirror->Left,Mirror->Right);
    return Mirror;
}
//Hàm tìm nút có giá trị lớn nhất trên cây nhị phân
DataType FindMax(Tree T) {
    DataType Max = T->Elements;
    if(Infertility(T)){
        return T->Elements;
    }
    if(LeftChild(T) != NULL){
        DataType Left = FindMax(LeftChild(T));
        if(Max < Left){
            Max = Left;
        }
    }
    if(RightChild(T) != NULL){
        DataType Right = FindMax(RightChild(T));
        if(Max < Right){
            Max = Right;
        }
    }
    return Max;
}
//Hàm tìm kiếm phần tử x trên cây nhị phân
Tree FindElement(DataType Value, Tree T) {
    if(EmptyTree(T)){
        return NULL;
    }else{
        if(T->Elements == Value){
            return T;
        }else{
            Tree A = FindElement(Value, LeftChild(T));
            Tree B = FindElement(Value, RightChild(T));
            if (!EmptyTree(A)){
                return A;
            }else{
                return B;
            }
        }
    }
}
//Hàm tính đường kính cây nhị phân đã cho.
int GetDiameter(Tree T, int *Diameter) {
    if(EmptyTree(T)){
        return 0;
    }else{
        int LeftDiameter = GetDiameter(LeftChild(T), Diameter);
        int RightDiameter = GetDiameter(RightChild(T), Diameter);
        if (LeftDiameter > RightDiameter) {
            if(*Diameter<(LeftDiameter+RightDiameter+2)){
                *Diameter=LeftDiameter+RightDiameter+1;
            }
            return LeftDiameter + 1;
        }else{
            if(*Diameter<(LeftDiameter+RightDiameter+2)){
                *Diameter=LeftDiameter+RightDiameter+1;
            }
            return RightDiameter + 1;
        }
    }
}
//Hàm kiểm tra xem 2 cây có là cây phản chiếu của nhau hay không
int IsMirrors(Tree T1, Tree T2) {
    if(EmptyTree(T1)&&EmptyTree(T2)){
        return 1;
    }
    if(EmptyTree(T1)||EmptyTree(T2)){
        return 0;
    }
    return IsMirrors(LeftChild(T1),RightChild(T2))&&IsMirrors(RightChild(T1),LeftChild(T2));
}
//In nội dung của mảng Path có độ dài Length.
void PrintArray(int Path[], int Length) {
	for(int i=0;i<Length;i++){
        printf("%d", Path[i]);
    }
    printf("\n");
}
//Hàm hiển thị tất cả các đường đi (từ nút gốc đến nút lá) và có độ dài đường đi thỏa điều kiện cho trước.
void PrintAllPaths(Tree T, int Path[], int Length, int PathLength){
    if(!EmptyTree(T)) {
        Path[Length] = T->Elements;
        PrintAllPaths(LeftChild(T),Path,Length + 1,PathLength);
        PrintAllPaths(RightChild(T),Path,Length + 1,PathLength);
        if(Length==PathLength&&Infertility(T)){
            PrintArray(Path,Length + 1);
        }
    }
}
void Find(Tree T,int Level,int &Maxlevel,int &Resuft){
    if(T!=NULL){
        Find(T->Left,++Level,Maxlevel,Resuft);
        if(Level>Maxlevel){
            Resuft = T->Elements;
            Maxlevel = Level;
        }
        Find(T->Right,Level,Maxlevel,Resuft);
    }
}
//Trả về giá trị của nốt sâu nhất trong cây nhị phân
int DeepestNode(Tree T){
    int Resuft = -1;
    int MaxLevel = -1;
    Find(T,0,MaxLevel,Resuft);
    return Resuft;
}
//Hàm tìm vị trí x trong danh sách duyệt trung tự (từ Start->End)
int FindIndex(DataType Value, DataType In[], int Start, int End){
    int Pin = Start;
    while(Pin <= End){
    	if(Value == In[Pin]){
            return Pin;
        }else Pin++;
   }
   return Pin;
}
// Đếm số nút có đủ 2 con trong cây nhị phân
int Full2Child(Tree T,int *Amount){
    if(EmptyTree(T)||Infertility(T)){
        return 0;
    }else{
        if(HaveTwoChild(T)){
            (*Amount)++;
        }
    }
    Full2Child(T->Left,Amount);
    Full2Child(T->Right,Amount);
    return *Amount;
}
//----------Dựng một cây nhị phân từ các biểu thức duyệt tiền tự và trung tự----------
/*Danh sách duyệt tiền tự gồm các phần tử A1,A2...An
Trong đó A1 là nút gốc(cấp 0)
A2(và A3) sẽ là con của A1(cấp 1)...
Danh sách duyệt trung tự có phạm vi trừ Start đến End
Sau mỗi bước ta sẽ xác định phạm vi này
->B1:Lấy 1 phần tử trong danh sách duyệt tiền tự làm dữ liệu cho nút N của cây khởi đầu à A1, sau đó đến phần tử kế tiếp
->B2:Tìm vị trí của giá trị của nút N trong danh sách duyệt trung tự, giả sử đó là Middle
->B3:Xây dụng cây con trái của N với nút gốc là phần tử kế tiếp trong danh sách duyệt tiền tự và phạm vi của danh sách duyệt trung tự từ Start đến Middle-1
->B4:Xây dựng cây con phải của nút N với nút gốc là phần tử kế tiếp trong danh sách duyệt tiền tự và phạm vi trong danh sách duyệt trung tự từ Middle+1 đến End
Lặp lại cho đến khi hết danh sách duyệt trung tự(End>Start)
Cấu trúc của nút N*/
int StartPre = 0;
int *PreIndex = &StartPre;
Tree CreateTree(DataType Pre[],DataType In[],int Start,int End){
	Tree Temp;
	MakeNullTree(&Temp);
	if (Start <= End) {
		Temp = (struct Node*)malloc(sizeof(struct Node));
		Temp->Elements = Pre[*PreIndex];
		(*PreIndex)++;
		int Middle = FindIndex(Temp->Elements,In,Start,End);
		Temp->Left = CreateTree(Pre,In,Start,Middle - 1);
		Temp->Right = CreateTree(Pre,In,Middle + 1,End);
	}
	return Temp;
}
int main(){
    Tree T,T1,T2,T3;
    T1 = CreateTree('*',CreateTree('3',NULL,NULL),CreateTree('5',NULL,NULL));
    T2 = CreateTree('/',CreateTree('7',NULL,NULL),CreateTree('2',NULL,NULL));
    T3 = CreateTree('+',T1,T2);
    T = CreateTree('-',T3,CreateTree('1',NULL,NULL));
    printf("Duyệt trung tự:\n");
    LNR(T);
    printf("\n");
}