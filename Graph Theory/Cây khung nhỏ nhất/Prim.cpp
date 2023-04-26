#include<stdio.h>
#define MaxElement 50
#define MaxVertices MaxElement
#define MaxLength MaxElement
#define NOEDGE 0
struct Graph{
    int M[MaxVertices][MaxVertices];
    int NumberOf;
};
void InitGraph(Graph *G,int NumberOf){
    G->NumberOf = NumberOf;
    for(int i=1;i<=G->NumberOf;i++){
        for(int j=1;j<=G->NumberOf;j++){
            G->M[i][j] = NOEDGE;
        }
    }
}
void AddEdge(Graph *G,int x,int y,int w){
    G->M[x][y] = w;
    G->M[y][x] = w;
}
int Adjacent(Graph G,int x,int y){
    return G.M[x][y] == 1;
}
int Degree(Graph G,int Number){
    int Count =0;
    for(int i=0;i<=G.NumberOf;i++){
        if(G.M[i][Number]==1){
            Count++;
        }
    }
    return Count;
}
#define OO 99999
int Mark[MaxElement]; // Mảng đánh dấu các đỉnh đã được thêm
int Pi[MaxElement]; // Mảng lưu giá trị Pi của các đỉnh
int P[MaxElement]; // Mảng lưu đỉnh cha của các đỉnh
int Prim(Graph *G,Graph *T,int s){
    int i,u,v,x;
    // Khởi tạo các mảng Pi, P, và Mark
    for(u=1;u<=G->NumberOf;u++){
        Pi[u] = OO;
        P[u] = -1;
        Mark[u] =0;
    }
    // Đặt Pi[s] bằng 0
    Pi[s] = 0;
    // Lặp lại n-1 lần
    for(i=1;i<G->NumberOf;i++){
        int MinDistance = OO;
        // Tìm đỉnh u có giá trị Pi[u] nhỏ nhất
        for(x=1;x<=G->NumberOf;x++){
            if(Mark[x]==0&&Pi[x]<MinDistance){
                MinDistance = Pi[x];
                u = x;
            }
        }
        // Đánh dấu đỉnh u đã được thêm
        Mark[u] = 1;
        // Cập nhật giá trị Pi và P cho tất cả các đỉnh kề với u
        for(v=1;v<=G->NumberOf;v++){
            if(G->M[u][v]!=NOEDGE){
                if(Mark[v]==0&&Pi[v]>G->M[u][v]){
                    Pi[v] = G->M[u][v];
                    P[v] = u;
                }
            }
        }
    }
    // Tạo một đồ thị mới T
    InitGraph(T,G->NumberOf);
    int SumWeight =0;
    // Thêm cạnh vào T và tính tổng trọng số
    for(u=1;u<=G->NumberOf;u++){
        if(P[u]!=-1){
            int w = G->M[P[u]][u];
            AddEdge(T,P[u],u,w);
            SumWeight += w;
        }
    }
    // Trả về tổng trọng số
    return SumWeight;
}
int main(){
    Graph G,T;
    freopen("Prim.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    InitGraph(&G,n);
    int u,v,w;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(&G,u,v,w);
    }
    printf("Ma trận G bậc %d\n\n",G.NumberOf);
    for(int i=1;i<=G.NumberOf;i++){
        for(int j=1;j<=G.NumberOf;j++){
            printf("%2d ",G.M[i][j]);
        }
        printf("\n");
    }

    int SumWeight = Prim(&G,&T,1);

    printf("\nCây khung nhỏ nhất của G có trọng số = %d:\n\n",SumWeight);
    for(int i=1;i<=T.NumberOf;i++){
        for(int j=1;j<=T.NumberOf;j++){
            printf("%2d ",T.M[i][j]);
        }
        printf("\n");
    }
}