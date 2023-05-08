#include<stdio.h>
#define MAXLENGHT 100
struct Edge{
	int u,v,w;
};
struct Graph{
	struct Edge Edges[MAXLENGHT];
	int n,m;
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
int Parent[MAXLENGHT];
int FindRoot(int u){
	if(Parent[u]==u){
		return u;
	}
	return FindRoot(Parent[u]);
}
int Kruskal(struct Graph *G,struct Graph *T){
	int i,j;
	for(i=0;i<G->m-1;i++){
		for(j=i+1;j<G->m;j++){
			if(G->Edges[i].w>G->Edges[j].w){
				struct Edge Temp = G->Edges[i];
				G->Edges[i] = G->Edges[j];
				G->Edges[j] = Temp;
			}
		}
	}
	InitGraph(T,G->n);
	for(i=1;i<=G->n;i++){
		Parent[i] = i;
	}
	int SumWeight = 0;
	for(i=0;i<G->m;i++){
		int u = G->Edges[i].u;
		int v = G->Edges[i].v;
		int w = G->Edges[i].w;
		int RootU = FindRoot(u);
		int RootV = FindRoot(v);
		if(RootU!=RootV){
			AddEdge(T,u,v,w);
			Parent[RootV] = RootU;
			SumWeight += w;
		}
	}
	return SumWeight;
}
int main(){
	struct Graph G,T;
	int n,m,u,v,w,e;
	freopen("Kruskal.txt","r",stdin);
	scanf("%d%d",&n,&m);
	InitGraph(&G,n);
	for(e=1;e<=m;e++){
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(&G,u,v,w);
	}
	int SumWeight = Kruskal(&G,&T);
	printf("Cây khung nhỏ nhất của G có trọng số = %d\n",SumWeight);
	for(e=0;e<T.m;e++){
		printf("(%d,%d): %d\n",T.Edges[e].u,T.Edges[e].v,T.Edges[e].w);
	}
}