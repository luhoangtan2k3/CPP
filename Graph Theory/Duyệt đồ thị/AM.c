#include<stdio.h>
#define MaxElement 50
#define GRAY 1
#define WHITE 0
#define BLACK 2
int Color[MaxElement];
int MarkDFSRecursion[MaxElement];
struct Graph{
    int M[MaxElement][MaxElement];
    int Num;
};
void InitGraph(struct Graph *G,int Num){
    G->Num = Num;
    for(int i=1;i<=G->Num;i++){
        for(int j=1;j<=G->Num;j++){
            G->M[i][j] = 0;
        }
    }
}
void PrintGraph(struct Graph G){
    for(int i=1;i<=G.Num;i++){
        for(int j=1;j<=G.Num;j++){
            printf("%d ",G.M[i][j]);
        }
        printf("\n");
    }
}
void AddEdge(struct Graph *G,int x,int y){
    G->M[x][y] = 1;
    //G->M[y][x] = 1;
}
int Adjacent(struct Graph *G,int x,int y){
    return G->M[x][y] == 1;
}
int Degree(struct Graph G,int Number){
    int Count =0;
    for(int i=0;i<=G.Num;i++){
        if(G.M[i][Number]==1){
            Count++;
        }
    }
    return Count;
}
struct List{
	int A[MaxElement];
	int Size;
};
void MakeNullList(struct List *List){
	List->Size = 0;
}
void PushList(struct List *List,int x){
	List->A[List->Size] = x;
    List->Size++;
}
int ElementAt(struct List L,int x){
    return L.A[x-1];
}
struct List Neighbors(struct Graph G,int Element){
	struct List L;
	MakeNullList(&L);
	for(int i=1;i<=G.Num;i++){
		if(G.M[i][Element]==1){
			PushList(&L,i);
		}
	}
	return L;
}
void ListNeighbors(struct Graph G,int Num){
	for(int i=1;i<=Num;i++){
		printf("Neighbors(%d) = ",i);
		struct List List = Neighbors(G,i);
		for(int j=1;j<=List.Size;j++){
			printf("%d ",List.A[j-1]);
		}
		printf("\n");
	}
}
struct Stack{
    int Data[MaxElement];
    int Size;
};
void MakeNullStack(struct Stack *Stack){
    Stack->Size = 0;
}
void PushStack(struct Stack *Stack,int x){
    Stack->Data[Stack->Size++] = x;
}
int TopStack(struct Stack *Stack){
    return Stack->Data[Stack->Size-1];
}
void PopStack(struct Stack *Stack){
    Stack->Size--;
}
int EmptyStack(struct Stack Stack){
    return Stack.Size==0;
}
struct Queue{
	int Data[MaxElement];
	int Front, Rear;
};
void MakeNullQueue(struct Queue* Q) {
	Q->Front = 0;
	Q->Rear = -1;
}
void PushQueue(struct Queue* Q, int x) {
	Q->Rear++;
	Q->Data[Q->Rear] = x;
}
int TopQueue(struct Queue* Q) {
	return Q->Data[Q->Front];
}
void PopQueue(struct Queue* Q) {
	Q->Front++;
}
int EmptyQueue(struct Queue* Q) {
	return Q->Front > Q->Rear;
}
struct List DFSStack(struct Graph *Graph,int x,int Parent[]){
    struct Stack S;
    MakeNullStack(&S);
    PushStack(&S,x);
    Parent[x]=0;
    struct List ListDFS;
    MakeNullList(&ListDFS);
    int MarkDFS[MaxElement];
    for(int i=1;i<=Graph->Num;i++){
        MarkDFS[i]=0;
    }
    while(!EmptyStack(S)){
        int Token = TopStack(&S);
        PopStack(&S);
        if(MarkDFS[Token]==1){
            continue;
        }
        PushList(&ListDFS,Token);
        MarkDFS[Token]=1;
        struct List List = Neighbors(*Graph,Token);
        for(int i=1;i<=List.Size;i++){
            int Value = List.A[i-1];
            if(MarkDFS[Value]==0){
                PushStack(&S,Value);
                Parent[Value]=Token;
            }
        }
    }
    return ListDFS;
}
struct List BFS(struct Graph *G,int x,int Parent[]){
    struct Queue Q;
    MakeNullQueue(&Q);
    struct List ListBFS;
    MakeNullList(&ListBFS);
    int MarkBFS[MaxElement];
    for(int i=1;i<=G->Num;i++){
        MarkBFS[i]=0;
    }
    PushQueue(&Q,x);
    Parent[x]=0;
    while(!EmptyQueue(&Q)){
        int Top = TopQueue(&Q);
        PopQueue(&Q);
        if(MarkBFS[Top]==1){
            continue;
        }
        PushList(&ListBFS,Top);
        MarkBFS[Top]=1;
        struct List L;
        MakeNullList(&L);
        L = Neighbors(*G,Top);
        for(int i=1;i<=L.Size;i++){
            int Value = ElementAt(L,i);
            if(MarkBFS[Value]==0){
                PushQueue(&Q,Value);
                if(Parent[Value]==0){
                    Parent[Value]=Top;
                }
            }
        }
    }
    return ListBFS;
}
void DFSRecursion(struct Graph *G,int u){
    if(MarkDFSRecursion[u]==1){
        return;
    }
    printf("%d ",u);
    MarkDFSRecursion[u]=1;
    for(int i=1;i<=G->Num;i++){
        if(Adjacent(G,u,i)){
            DFSRecursion(G,i);
        }
    }
}
int Min(int A,int B){
    return (A<B)?A:B;
}
int MinNum[MaxElement];
int Num[MaxElement];
int OnStack[MaxElement];
int Pin=1;
struct Stack S;
void StrongConnet(struct Graph *G,int x){
    Num[x]=MinNum[x]=Pin;
    Pin++;
    PushStack(&S,x);
    OnStack[x]=1;
    struct List List = Neighbors(*G,x);
    for(int i=1;i<=List.Size;i++){
        int Value = ElementAt(List,i);
        if(Num[Value]<0){
            StrongConnet(G,Value);
            MinNum[x] = Min(MinNum[x],MinNum[Value]);
        }else if(OnStack[Value]==1){
            MinNum[x] = Min(MinNum[x],Num[Value]);
        }
    }
    printf("MinNum[%d] = %d\n",x,MinNum[x]);
    if(Num[x]==MinNum[x]){
        printf("%d là đỉnh khớp\n",x);
        int Token;
        do{
            Token = TopStack(&S);
            PopStack(&S);
            OnStack[Token]=0;
        }while(Token!=x);
    }
}
int Divide = 0;
void Colorize(struct Graph *G,int u,int c){
    Color[u] = c;
    for(int i=1;i<=G->Num;i++){
        if(Adjacent(G,i,u)){
            if(Color[i]==WHITE){
                Colorize(G,i,3-c);
            }else{
                if(Color[i]==Color[u]){
                    Divide = 1;
                }
            }
        }
    }
}
int HasCircle=0;
void DFSDirectionless(struct Graph *G, int u, int p){
    Color[u] = GRAY;
    for(int i=1;i<=G->Num;i++){
        if(Adjacent(G,u,i)){
            if(i == p){
                continue;
            }
            if(Color[i] == WHITE){
                DFSDirectionless(G, i, u);
            }else{
                if(Color[i] == GRAY){
                    HasCircle = 1;
                }
            }
        }
    }
    Color[u] = BLACK;
}
int HasCycle=0;
void DFSDirected(struct Graph *G, int u){
    Color[u] = GRAY;
    for(int i=1;i<=G->Num;i++){
        if(Adjacent(G,u,i)){
            if(Color[i] == WHITE){
                DFSDirected(G,i);
            }else{
                if(Color[i] == GRAY){
                    HasCycle = 1;
                }
            }
        }
    }
    Color[u] = BLACK;
}
void Topo(struct Graph *G, struct List *L){
    int D[MaxElement];
    for(int u=1;u<=G->Num;u++){
        D[u] = 0;
        for(int x=1;x<=G->Num;x++){
            if(G->M[x][u]!=0){
                D[u]++;
            }
        }
    }
    struct Queue Q;
    MakeNullQueue(&Q);
    for(int u=1;u<=G->Num;u++){
        if(D[u]==0){
            PushQueue(&Q,u);
        }
    }
    MakeNullList(L);
    while(!EmptyQueue(&Q)){
        int u = TopQueue(&Q);
        PopQueue(&Q);
        PushList(L,u);
        for (int v = 1; v <= G->Num; v++){
            if (G->M[u][v] != 0) {
                D[v]--;
                if (D[v] == 0){
                    PushQueue(&Q,v);
                }
            }
        }
    }
}
void CopyList(struct List *S1, struct List *S2) {
	 int i;
	 MakeNullList(S1);
	 for(i = 1; i <= S2->Size; i++) {
	 	PushList(S1, S2->A[i-1]);
	 }
}
int R[MaxElement];
void Rank(struct Graph *G){
    int D[MaxElement];
    for(int u=1;u<=G->Num;u++){
        D[u] = 0;
        for(int x=1;x<=G->Num;x++){
            if(G->M[x][u]!=0){
                D[u]++;
            }
        }
    }
    struct List L1,L2;
    MakeNullList(&L1);
    for(int u=1;u<=G->Num;u++){
        if(D[u]==0){
            PushList(&L1,u);
        }
    }
    int k = 0;
    while(L1.Size>0){
        MakeNullList(&L2);
        for(int i=1;i<=L1.Size;i++){
            int u = ElementAt(L1,i);
            R[u] = k;
            for(int v=1;v<=G->Num;v++){
                if(G->M[u][v]!=0){
                    D[v]--;
                    if(D[v]==0){
                        PushList(&L2,v);
                    }
                }
            }
        }
        CopyList(&L1,&L2);
        k++;
    }
}
void PrintDFSStack(struct Graph G){
    int MarkDFS[MaxElement],Parent[MaxElement];
    for(int i=1;i<=G.Num;i++){
        MarkDFS[i]=0;
        Parent[i]=0;
    }
    printf("Duyệt theo chiều sâu\n(Con - Cha): ");
    for(int i=1;i<=G.Num;i++){
        if(MarkDFS[i]==0){
            struct List List = DFSStack(&G,i,Parent);
            for(int j=1;j<=List.Size;j++){
                int Value = ElementAt(List,j);
                printf("(%d - %d) ",Value,Parent[Value]);
                MarkDFS[Value] = 1;
            }
        }
    }
}
void PrintBFS(struct Graph G){
    int MarkBFS[MaxElement],Parent[MaxElement];
    for(int i=1;i<=G.Num;i++){
        MarkBFS[i]=0;
        Parent[i]=0;
    }
    printf("Duyệt theo chiều rộng\n(Con - Cha): ");
    for(int i=1;i<=G.Num;i++){
        if(MarkBFS[i]==0){
            struct List List = BFS(&G,i,Parent);
            for(int j=1;j<=List.Size;j++){
                int Value = ElementAt(List,j);
                printf("(%d - %d) ",Value,Parent[Value]);
                MarkBFS[Value] = 1;
            }
        }
    }
}
void PrintDFSRecursion(struct Graph G){
    for(int i=1;i<=G.Num;i++){
        MarkDFSRecursion[i]=0;
    }
    printf("DFS(đệ quy): ");
    for(int i=1;i<=G.Num;i++){
        if(MarkDFSRecursion[i]==0){
            DFSRecursion(&G,i);
        }
    }
}
void RunStrongStack(struct Graph G){
    for(int i=1;i<=G.Num;i++){
        Num[i]=-1;
        MinNum[i]=-1;
        OnStack[i]=0;
    }
    MakeNullStack(&S);
    for(int i=1;i<=G.Num;i++){
        if(Num[i]==-1){
            StrongConnet(&G,i);
        }
    }
}
void IsDivide(struct Graph *G){
    for(int i=1;i<=G->Num;i++){
        Color[i] = WHITE;
    }
    Colorize(G,1,GRAY);
    if(Divide==0){
        int HomeA = 0;
        int HomeB = 0;
        for(int i=1;i<=G->Num;i++){
            if(Color[i]==GRAY){
                HomeA++;
            }else{
                HomeB++;
            }
        }
        printf("Home A có %d thành viên: ",HomeA);
        for(int i=1;i<=G->Num;i++){
            if(Color[i]==GRAY){
                printf("%d ",i);
            }
        }
        printf("\n");
        printf("Home B có %d thành viên: ",HomeB);
        for(int i=1;i<=G->Num;i++){
            if(Color[i]==BLACK){
                printf("%d ",i);
            }
        }
    }else{
        printf("Không thể phân chia được");
    }
}
void IsCycleGraphDirectionless(struct Graph *G){
    for(int i=1;i<=G->Num;i++){
        Color[i] = WHITE;
    }
    for(int i=1;i<=G->Num;i++){
        if(Color[i] == WHITE){
            DFSDirectionless(G,i,-1);
        }
    }
    if(HasCircle==1){
        printf("Có chứa chu trình");
    }else{
        printf("Không chứa chu trình");
    }
}
void IsCycleGraphDirected(struct Graph *G){
    for(int i=1;i<=G->Num;i++){
        Color[i] = WHITE;
    }
    for(int i=1;i<=G->Num;i++){
        if(Color[i] == WHITE){
            DFSDirected(G,i);
        }
    }
    if(HasCycle==0){
        printf("Không chứa chu trình");
    }else{
        printf("Có chứa chu trình");
    }
}
void PrintRank(struct Graph G){
    Rank(&G);
    for(int i=1;i<=G.Num;i++){
        printf("Rank[%d] = %d\n",i,R[i]);
    }
}
void PrintTopo(struct Graph G){
    struct List L;
    Topo(&G,&L);
    for(int i=1;i<=L.Size;i++){
        printf("%d ",ElementAt(L,i));
    }
}
int main(int argc, char const *argv[]){
    struct Graph G;
    freopen("Data.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    InitGraph(&G,n);
    int u,v;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        AddEdge(&G,u,v);
    }
    return 0;
}