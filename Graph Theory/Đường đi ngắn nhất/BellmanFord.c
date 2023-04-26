#include<stdio.h>
#define MaxElement 20
struct Edge{
    int u,v,w;
};
struct Graph{
    int n,m;
    struct Edge Edges[MaxElement];
};
void InitGraph(struct Graph *G,int n){
    G->n = n;
    G->m = 0;
}
void AddEdge(struct Graph *G,int u,int v,int w){
    G->Edges[G->m].u = u;
    G->Edges[G->m].v = v;
    G->Edges[G->m].w = w;
    G->m++;
}
#define OO 99999
int Pi[MaxElement];
int P[MaxElement];
int BellmanFord(struct Graph *G,int s){
    int u,v,w;
    for(u=1;u<=G->n;u++){
        Pi[u]=OO;
    }
    Pi[s]=0;
    P[s]=-1;
    for(int i=1;i<G->n;i++){
        for(int j=0;j<G->m;j++){
            u = G->Edges[j].u;
            v = G->Edges[j].v;
            w = G->Edges[j].w;
            if(Pi[u]==OO) continue;
            if(Pi[u]+w<Pi[v]){
                Pi[v]=Pi[u]+w;
                P[v]=u;
            }
        }
    }
    int NegativeCycle =0;
    for(int i=0;i<G->m;i++){
        int u = G->Edges[i].u;
        int v = G->Edges[i].v;
        int w = G->Edges[i].w;
        if((Pi[u]+w<Pi[v])){
            NegativeCycle =1;
            break;
        }
    }
    if(NegativeCycle==1){
        printf("Chứa chu trình âm(không hoạt động)");
    }else{
        printf("Có thể in ra đường đi ngắn nhất");
    }
}
int main(){
    struct Graph G;
    freopen("BellmanFord.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    InitGraph(&G,n);
    int u,v,w;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(&G,u,v,w);
    }
    BellmanFord(&G,1);
}