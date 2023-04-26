#include"AM.c"

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
    PrintDFSRecursion(G);
}