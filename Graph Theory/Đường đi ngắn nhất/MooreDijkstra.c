#include<stdio.h>
#define MaxElement 50
#define NOEDGE -1
struct Graph{
    int M[MaxElement][MaxElement];
    int Amount;
};
void InitGraph(struct Graph *G,int Amount){
    G->Amount = Amount;
    for(int i=1;i<=G->Amount;i++){
        for(int j=1;j<=G->Amount;j++){
            G->M[i][j] = NOEDGE;
        }
    }
}
void AddEdge(struct Graph *G,int x,int y,int w){
    G->M[x][y] = w;
    G->M[y][x] = w;
}
#define OO 99999
int Mark[MaxElement];
int Pi[MaxElement];
int P[MaxElement];
void MooreDijkstra(struct Graph *G,int s){
    int v;
    for(int v=1;v<=G->Amount;v++){
        Pi[v]=OO;
        Mark[v]=0;
    }
    Pi[s]=0;
    P[s]=-1;
    for(int i=1;i<=G->Amount;i++){
        int MinPi =OO;
        for(int j=1;j<=G->Amount;j++){
            if(Mark[j]==0&&Pi[j]<MinPi){
                MinPi = Pi[j];
                v = j;
            }
        }
        Mark[v]=1;
        for(int i=1;i<=G->Amount;i++){
            if(G->M[v][i]!=NOEDGE&&Mark[i]==0){
                if(Pi[v]+G->M[v][i]<Pi[i]){
                    Pi[i]=Pi[v]+G->M[v][i];
                    P[i]=v;
                }
            }
        }
    }
}
int main(){
    struct Graph G;
    freopen("MooreDijkstra.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    InitGraph(&G,n);
    int u,v,w;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(&G,u,v,w);
    }
    MooreDijkstra(&G,1);
    for(int i=1;i<=G.Amount;i++){
        printf("\nPi[%d] = %d,P[%d] = %d\n",i,Pi[i],i,P[i]);
    }
    int Path[MaxElement];
    int Vertex = 0;
    int Current = 2;
    int Temp = Current;
    while(Current!=-1){
        Path[Vertex] = Current;
        Vertex++;
        Current = P[Current];
    }
    printf("\nĐường đi ngắn nhất đến %d: ",Temp);
    for(int i=Vertex-1;i>=1;i--){
        printf("%d --> ",Path[i]);
    }
    printf("%d ",Path[0]);
}