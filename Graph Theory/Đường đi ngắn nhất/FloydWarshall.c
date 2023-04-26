#include<stdio.h>
#include<limits.h>
#define MaxElement 50
#define NOEDGE 0
struct Graph{
    int M[MaxElement][MaxElement];
    int NumberOf;
};
void InitGraph(struct Graph *G,int NumberOf){
    G->NumberOf = NumberOf;
    for(int i=1;i<=G->NumberOf;i++){
        for(int j=1;j<=G->NumberOf;j++){
            G->M[i][j] = NOEDGE;
        }
    }
}
void AddEdge(struct Graph *G,int x,int y,int w){
    G->M[x][y] = w;
}
int Adjacent(struct Graph G,int x,int y){
    return G.M[x][y] == 1;
}
int Degree(struct Graph G,int Number){
    int Count =0;
    for(int i=0;i<=G.NumberOf;i++){
        if(G.M[i][Number]==1){
            Count++;
        }
    }
    return Count;
}
int Pi[MaxElement][MaxElement];
int Next[MaxElement][MaxElement];
int FloydWarshall(struct Graph *G){
    int u,v,k;
    for(u=1;u<=G->NumberOf;u++){
        for(v=1;v<=G->NumberOf;v++){
            if(G->M[u][v]!=NOEDGE){
                Pi[u][v] = G->M[u][v];
                Next[u][v] = v;
            }
            else{
                Pi[u][v] = INT_MAX;
                Next[u][v] = -1;
            }
        }
        Pi[u][u] = 0;
    }
    for(k=1;k<=G->NumberOf;k++){
        for(u=1;u<=G->NumberOf;u++){
            for(v=1;v<=G->NumberOf;v++){
                if(Pi[u][k]!=INT_MAX && Pi[k][v]!=INT_MAX && Pi[u][k]+Pi[k][v]<Pi[u][v]){
                    Pi[u][v] = Pi[u][k]+Pi[k][v];
                    Next[u][v] = Next[u][k];
                }
            }
        }
    }
    int NegativeCycle = 0;
    for(u=1;u<=G->NumberOf;u++){
     if(Pi[u][u]<0){
            printf("Phát hiện chu trình âm\n");
            NegativeCycle = 1;
            break;
        }
    }
    if(NegativeCycle==1){
        return 1;
    }else{
        return 0;
    }
}
void PrintResult(struct Graph *G){
    int u,v;
    for(u=1;u<=G->NumberOf;u++){
        for(v=1;v<=G->NumberOf;v++){
            if(Pi[u][v]==INT_MAX){
                printf("Không có đường đi từ %d tới %d\n", u, v);
            }else{
                printf("Đường đi ngắn nhất từ %d tới %d là: %d\n", u, v, Pi[u][v]);
                printf("Các đỉnh trên đường đi là: ");
                while(u!=v){
                    printf("%d -> ", u);
                    u = Next[u][v];
                }
                printf("%d\n", v);
            }
        }
    }
}
int main(){
    struct Graph G;
    freopen("FloydWarshall.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    InitGraph(&G,n);
    int u,v,w;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(&G,u,v,w);
    }
    if(FloydWarshall(&G)==0){
        PrintResult(&G);
    }else{
        printf("Tồn tại ít nhất 1 chu trình âm\n");
    }
}