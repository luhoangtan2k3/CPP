#include<stdio.h>

#define MaxElement 20
struct Edge{
    int u,v;
};
struct Graph{
    int n,m;
    struct Edge Edges[MaxElement];
};
void InitGraph(struct Graph *G,int n){
    G->n = n;
    G->m = 0;
}
void AddEdge(struct Graph *G,int u,int v){
    for(int i=1;i<=G->m;i++){
        if((G->Edges[i].u==u&&G->Edges[i].v==v)||(G->Edges[i].u==v&&G->Edges[i].v==u)){
            return;
        }
    }
    G->Edges[G->m].u = u;
    G->Edges[G->m].v = v;
    G->m++;
}
int Adjacent(struct Graph G,int u,int v){
    for(int i=0;i<G.m;i++){
        if((G.Edges[i].u==u&&G.Edges[i].v==v)||(G.Edges[i].u==v&&G.Edges[i].v==u)){
            return 1;
        }
    }
    return 0;
}
int Degree(struct Graph G,int u){
    int Deg = 0;
    for(int i=0;i<G.m;i++){
        if(G.Edges[i].u==u){
            Deg++;
        }
        if(G.Edges[i].v==u){
            Deg++;
        }
    }
    return Deg;
}
int main(int argc, char const *argv[]){
    struct Graph G;
    freopen("DataGraph.txt","r",stdin);
    int n,m,u,v,i,j;
    scanf("%d%d",&n,&m);
    InitGraph(&G, n);
    for(i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        AddEdge(&G,u,v);
    }
}