#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
struct Node{
    ElementType Element;
    Node *Next;
    Node *Prev;
};
struct LISTNODE{
    Node *Head;
    Node *Tail;
};
void MaleNullList(LISTNODE &List){
    List.Head=NULL;
    List.Tail=NULL;
}
int SizeLast(LISTNODE List){
    Node *Temp = List.Head;
    int Size = 0;
    while(Temp!=NULL){
        Size++;
        Temp = Temp->Next;
    }
    return Size;
}
Node *CreateNode(ElementType Value){
    Node *NODE = new Node;
    if(NODE!=NULL){
        NODE->Element=Value;
        NODE->Next=NULL;
        NODE->Prev=NULL;
    } else {
        printf("Cấp phát lỗi\n");
    }
    return NODE;
}
void InsertFirst(LISTNODE &List,ElementType Value){
    Node *NODE = CreateNode(Value);
    if(List.Head==NULL){
        List.Head=NODE;
        List.Tail=NODE;
    } else {
        NODE->Next = List.Head;
        List.Head->Prev = NODE;
        List.Head = NODE;
    }
}
void InsertLast(LISTNODE &List,ElementType Value){
    Node *NODE = CreateNode(Value);
        if(List.Head==NULL){
            List.Head=NODE;
            List.Tail=NODE;
        } else {
            List.Tail->Next = NODE;
            NODE->Prev = List.Tail;
            List.Tail = NODE;
        }
}
void InsertMid(LISTNODE &List,ElementType Value,int Position){
    if(Position<1||Position>SizeLast(List)+1){
        printf("Vị trí không tồn tại\n");
    } else if(Position==1){
        InsertFirst(List,Value);
    } else if(Position==SizeLast(List)+1){
        InsertLast(List,Value);
    } else {
        Node *NODE = CreateNode(Value);
        Node *Temp = List.Head;
        int Move = 1;
        while(Temp!=NULL){
            if(Move==Position){
                break;
            }
            Temp = Temp->Next;
            Move++;
        }
        Temp->Prev->Next = NODE;
        NODE->Prev = Temp->Prev;
        NODE->Next = Temp;
        Temp->Prev = NODE;
    }
}
void RemoveNodeHead(LISTNODE &List,Node *Del){
    List.Head = List.Head->Next;
    List.Head->Prev = NULL;
    Del->Next = NULL;
    delete Del;
    Del = NULL;
}
void RemoveNodeTail(LISTNODE &List,Node *Del){
    List.Tail = List.Tail->Prev;
    List.Tail->Next = NULL;
    Del->Prev = NULL;
    delete Del;
    Del = NULL;
}
void RemoveNodeAny(LISTNODE &List,Node *Del){
    Del->Prev->Next = Del->Next;
    Del->Next->Prev = Del->Prev;
    Del->Next = NULL;
    Del->Prev = NULL;
    delete Del;
    Del = NULL;
}
void RemoveNodeByValue(LISTNODE &List,ElementType Value){
    Node *Del = List.Head;
    if(Del == NULL){
        printf("Danh sách rỗng\n");
    } else {
        while(Del!=NULL){
            if(Del->Element==Value){
                break;
            }
            Del = Del->Next;
        }
    }
    if(Del==NULL){
        printf("Không tìm thấy Node\n");
    } else {
        if(Del == List.Head){
            RemoveNodeHead(List,Del);
        } else if(Del == List.Tail) {
            RemoveNodeTail(List,Del);
        } else {
            RemoveNodeAny(List,Del);
        }
    }
}
void RemoveNodeByPosition(LISTNODE &List,int Position){
    Node *Del = List.Head;
    int Locate = 1;
    if(Del==NULL){
        printf("Danh sách rỗng\n");
    } else {
        while(Del!=NULL){
            if(Locate==Position){
                break;
            }
            Locate++;
            Del = Del->Next;
        }
    }
    if(Del==NULL){
        printf("Không tìm thấy Node\n");
    } else {
        if(Locate==1){
            RemoveNodeHead(List,Del);
        } else if(Locate==SizeLast(List)){
            RemoveNodeTail(List,Del);
        } else {
            RemoveNodeAny(List,Del);
        }
    }
}
void ReplaceNodeHead(LISTNODE &List,Node *NODE){
    Node *Temp = List.Head;
    NODE->Next = List.Head->Next;
    List.Head->Next->Prev = NODE;
    List.Head = NODE;
    Temp->Next = NULL;
    delete Temp;
    Temp = NULL;
}
void ReplaceNodeTail(LISTNODE &List,Node *NODE){
    Node *Temp = List.Tail;
    List.Tail->Prev->Next = NODE;
    NODE->Prev = List.Tail->Prev;
    List.Tail = NODE;
    Temp->Prev = NULL;
    delete Temp;
    Temp = NULL;
}
void ReplaceNodeAny(LISTNODE &List,Node *NODE,int Position){
    Node *Temp = List.Head;
    int Locate = 1;
    while(Temp!=NULL){
        if(Locate==Position){
            break;
        }
        Locate++;
        Temp = Temp->Next;
    }
    Temp->Prev->Next = NODE;
    NODE->Prev = Temp->Prev;
    NODE->Next = Temp->Next;
    Temp->Next->Prev = NODE;
    Temp->Next = NULL;
    Temp->Prev = NULL;
    delete Temp;
    Temp = NULL;
}
void ReplaceNode(LISTNODE &List,int Position,ElementType Value){
    Node *NODE = CreateNode(Value);
        if(Position>=1&&Position<=SizeLast(List)){
            if(Position==1){
                ReplaceNodeHead(List,NODE);
            } else if(Position==SizeLast(List)){
                    ReplaceNodeTail(List,NODE);
                } else {
                    ReplaceNodeAny(List,NODE,Position);
                }
        } else {
            printf("Vị trí thay thế không hợp lệ\n");
        }
}
void FreeMemoryListNode(LISTNODE &List){
    printf("Thu hồi bộ nhớ cấp phát\n");
    while(List.Head!=NULL){
        Node *Temp = List.Head;
        List.Head = Temp->Next;
        delete Temp;
        Temp = NULL;
        printf("Đã xóa\n");
    }
    printf("Đã thu hồi tất cả bộ nhớ\n");
}
void SortListNode(LISTNODE List){
    Node *Temp1=List.Head;
    for(Temp1;Temp1!=NULL;Temp1=Temp1->Next){
        Node *Temp2 =Temp1->Next;
        for(Temp2;Temp2!=NULL;Temp2=Temp2->Next){
            if(Temp1->Element>Temp2->Element){
                ElementType Pin = Temp1->Element;
                Temp1->Element = Temp2->Element;
                Temp2->Element = Pin;
            }
        }
    }
}
void PrintListNode(LISTNODE List){
    Node *Temp = List.Head;
    if(Temp==NULL){
        printf("Danh sách rỗng\n");
    } else {
        while(Temp!=NULL){
            printf("%d ",Temp->Element);
            Temp = Temp->Next;
        }
    }
}
int main(){
    LISTNODE List;MaleNullList(List);
    int Select,Position,Number,Value;
    Root:
    printf("1-Chèn Node vào đầu danh sách:\n");
    printf("2-Chèn Node vào cuối danh sách:\n");
    printf("3-Chèn Node vào vị trí bất kỳ:\n");
    printf("4-Xóa Node có giá trị chỉ định:\n");
    printf("5-Xóa Node tại vị trí chỉ định:\n");
    printf("6-Thay thế Node vị trí số n:\n");
    printf("7-Sắp xếp Node theo thứ tự:\n");
    printf("8-Tìm kiếm Node trong danh sách\n");
    printf("\nNhập vào thao tác để thực hiện:\n");;
    scanf("%d",&Select);
    switch(Select){
        case 1:
            printf("Nhập vào số lượng Node:\n");
            scanf("%d",&Number);
            printf("Input: ");
            for(int i=1;i<=Number;i++){
                scanf("%d",&Value);
                InsertFirst(List,Value);
            }
            printf("Output: ");
            PrintListNode(List);
            printf("\nCó %d Node\n",SizeLast(List));
            break;
        case 2:
            printf("Nhập vào số lượng Node:\n");
            scanf("%d",&Number);
            printf("Input: ");
            for(int i=1;i<=Number;i++){
                scanf("%d",&Value);
                InsertLast(List,Value);
            }
            printf("Output: ");
            PrintListNode(List);
            printf("\nCó %d Node\n",SizeLast(List));
            break;
        case 3:
            printf("Nhập vào chỉ số cần chèn\n");
            scanf("%d",&Position);
            printf("Nhập vào số lượng Node:\n");
            scanf("%d",&Number);
            printf("Input: ");
            for(int i=1;i<=Number;i++){
                scanf("%d",&Value);
                InsertMid(List,Value,Position);
            }
            printf("Output: ");
            PrintListNode(List);
            printf("\nCó %d Node\n",SizeLast(List));
            break;
        case 4:
            printf("Nhập vào giá trị cần xóa\n");
            scanf("%d",&Value);
            RemoveNodeByValue(List,Value);
            printf("Output: ");
            PrintListNode(List);
            printf("\nCó %d Node\n",SizeLast(List));
            break;
        case 5:
            printf("Nhập vào vị trí cần xóa\n");
            scanf("%d",&Position);
            RemoveNodeByPosition(List,Position);
            printf("Output: ");
            PrintListNode(List);
            printf("\nCó %d Node\n",SizeLast(List));
            break;
        case 6:
            printf("Nhập vào vị trí cần thay đổi:\n");
            scanf("%d",&Position);
            printf("Nhập vào giá trị thay thế\n");
            scanf("%d",&Value);
            ReplaceNode(List,Position,Value);
            printf("Output: ");
            PrintListNode(List);
            printf("\nCó %d Node\n",SizeLast(List));
            break;
        case 7:
            SortListNode(List);
            PrintListNode(List);
            printf("\nCó %d Node\n",SizeLast(List));
            break;
        case 0:
            FreeMemoryListNode(List);
            break;
    }
    if(Select!=0) goto Root;
}