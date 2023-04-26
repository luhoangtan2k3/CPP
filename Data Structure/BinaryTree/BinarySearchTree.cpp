#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
struct Node{
    DataType Key;
    Node *Left;
    Node *Right;
};
typedef struct Node* Tree;

void MakeNullTree(Tree &T){
    T = NULL;
}

bool EmptyTree(Tree T){
    return T==NULL;
}

bool Infertility(Tree T){
    return !EmptyTree(T)&&T->Left==NULL&&T->Right==NULL;
}

bool HaveTwoChild(Tree T){
    return !EmptyTree(T)&&T->Left!=NULL&&T->Right!=NULL;
}

bool HaveOneChild(Tree T){
    return !Infertility(T)&&!HaveTwoChild(T);
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

void CreateNode(Tree &T,DataType Value){
    if(EmptyTree(T)){
        Node *NODE = new Node;
        NODE->Key = Value;
        NODE->Left = NULL;
        NODE->Right = NULL;
        T = NODE;
    }else{

        if(Value<T->Key){
            CreateNode(T->Left,Value);
        }else if(Value>T->Key){
            CreateNode(T->Right,Value);
        }
    }
}

void NLR(Tree T){
    if(!EmptyTree(T)){
        printf("%d ",T->Key);
        NLR(T->Left);
        NLR(T->Right);
    }
}

void LNR(Tree T){
    if(!EmptyTree(T)){
        LNR(T->Left);
        printf("%d ",T->Key);
        LNR(T->Right);
    }
}

void LRN(Tree T){
    if(!EmptyTree(T)){
        LRN(T->Left);
        LRN(T->Right);
        printf("%d ",T->Key);
    }
}

int AmountNode(Tree T){
    if(EmptyTree(T)){
        return 0;
    } else return AmountNode(T->Left)+AmountNode(T->Right)+1;
}

Tree SearchNode(DataType Value,Tree T){
    while(T!=NULL&&T->Key!=Value){
        if(Value<T->Key){
            T = T->Left;
        }else{
            T = T->Right;
        }
    }
    return T;
}

void ResuftSearch(Tree T,DataType Value){
    if(SearchNode(Value,T)!=NULL){
        printf("Tìm thấy Node có giá trị = %d\n",Value);
    }else{
        printf("Không tìm thấy Node nào trong cây!!!\n");
    }
}

void ListTwoChildren(Tree T){
    if(!EmptyTree(T)){
        if(T->Left!=NULL&&T->Right!=NULL){
            printf("%d ",T->Key);
        }
        ListTwoChildren(T->Left);
        ListTwoChildren(T->Right);
    }
}

void ListOneChildren(Tree T){
    if(!EmptyTree(T)){
        if((T->Left!=NULL&&T->Right==NULL)||(T->Left==NULL&&T->Right!=NULL)){
            printf("%d ",T->Key);
        }
        ListOneChildren(T->Left);
        ListOneChildren(T->Right);
    }
}

void ListInfertility(Tree T){
    if(!EmptyTree(T)){
        if(T->Left==NULL&&T->Right==NULL){
            printf("%d ",T->Key);
        }
        ListInfertility(T->Left);
        ListInfertility(T->Right);
    }
}

void NodeMax(Tree T){
    if(!EmptyTree(T)){
        if(T->Right==NULL){
            printf("Giá trị lớn nhất = %d\n",T->Key);
        }
        NodeMax(T->Right);
    }
}

void NodeMin(Tree T){
    if(!EmptyTree(T)){
        if(T->Left==NULL){
            printf("Giá trị nhỏ nhất = %d\n",T->Key);
        }
        NodeMin(T->Left);
    }
}

void DeleteNodeLeaf(Tree &Root,Tree &Parent){
    if(Root->Key<Parent->Key){
        Parent->Left = NULL;
    }else{
        Parent->Right = NULL;
    }
    printf("Node đã đc xóa khỏi cây nhị phân\n");
    delete Root;
}

void DeleteNodeOneChild(Tree &Root,Tree &Parent){
    if(Root->Left!=NULL&&Root->Right==NULL){
        if(Root->Key<Parent->Key){
            Parent->Left = Root->Left;
        }else{
            Parent->Right = Root->Left;
        }
    }else if(Root->Left==NULL&&Root->Right!=NULL){
        if(Root->Key<Parent->Key){
            Parent->Left = Root->Right;
        }else{
            Parent->Right = Root->Right;
        }
    }
    printf("Node đã đc xóa khỏi cây nhị phân\n");
    delete Root;
}

void DeleteNodeTwoChild(Tree &Root,Tree &Parent){
    Parent = Root;
    Tree Replace = Root->Right;
    while(Replace->Left!=NULL){
        Parent = Replace;
        Replace = Replace->Left;
    }
    Root->Key = Replace->Key;
    if(Replace->Left==NULL&&Replace->Right==NULL){
        DeleteNodeLeaf(Replace,Parent);
    }else{
        DeleteNodeOneChild(Replace,Parent);
    }
}

void DeleteNode(Tree &T,DataType Value){
    if(!EmptyTree(T)){
        Tree Root = T;
        Tree Parent = NULL;
        while(Root!=NULL&&Root->Key!=Value){
            Parent = Root;
            if(Value<Root->Key){
                Root = Root->Left;
            }else{
                Root = Root->Right;
            }
        }
        if(Root!=NULL){
            if(Infertility(Root)){
                DeleteNodeLeaf(Root,Parent);
            }else if(HaveOneChild(Root)){
                DeleteNodeOneChild(Root,Parent);
            }else{
                DeleteNodeTwoChild(Root,Parent);
            }
        }else{
            printf("Không tồn tại!!!\n");
        }
    }
}

DataType Array[100],Run=0;
void SaveinArray(Tree T){
    if(T!=NULL){
        SaveinArray(T->Left);
        Array[Run++] = T->Key;
        SaveinArray(T->Right);
    }
}

Tree GetNext(DataType Value,Tree T){
    for(int i=0;i<Run-1;i++){
        if(Array[i]==Value){
            return SearchNode(Array[i+1],T);
        }
    }
    return NULL;
}

void CreateTree(Tree &T){
    DataType Amount,Value;
    printf("Nhập vào số lượng Node\n");
    scanf("%d",&Amount);
    printf("Các Node nhập vào là: ");
    for(int i=0;i<Amount;i++){
        scanf("%d",&Value);
        CreateNode(T,Value);
    }
}

void PrintfTree(Tree T){
    printf("Duyệt tiền thứ tự\n");
    printf("Các giá trị của cây:");
    NLR(T);
    printf("\n");
    printf("Duyệt trung thứ tự\n");
    printf("Các giá trị của cây:");
    LNR(T);
    printf("\n");
    printf("Duyệt hậu thứ tự\n");
    printf("Các giá trị của cây:");
    LRN(T);
    printf("\n");
}