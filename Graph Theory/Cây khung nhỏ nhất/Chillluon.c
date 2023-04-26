#include<stdio.h>
#define MAXN 100
#define MAXM 500
#define OO 9999999
struct Edge{
    int u, v;
    int w;
    int Link;
};
struct Graph{
    int n, m;
    struct Edge Edges[MAXM];
} Graph;
struct Tree {
    int n;
    int Parent[MAXN];
    int Weight[MAXN];
    int Link[MAXN];
};
void InitGraph(struct Graph *G, int n){
    G->n = n;
    G->m = 0;
}
void InitTree(struct Tree *T, int n){
    T->n = n;
    for(int i=1;i<=n;i++){
        T->Parent[i] = -1;
        T->Weight[i] = OO;
        T->Link[i] = -1;
    }
}
void AddEdge(struct Graph *G, int u, int v, int w, int Link){
    G->Edges[G->m].u = u;
    G->Edges[G->m].v = v;
    G->Edges[G->m].w = w;
    G->Edges[G->m].Link = Link;
    G->m++;
}
void BuildH(struct Graph *G, int Root, struct Tree *H){
    // Khởi tạo một cây H với n đỉnh
    InitTree(H,G->n);
    // Duyệt qua tất cả các cạnh trong G
    for(int e=0;e<G->m;e++){
        int u = G->Edges[e].u;
        int v = G->Edges[e].v;
        int w = G->Edges[e].w;
        int Link = G->Edges[e].Link;
        // Nếu trọng số của cạnh nhỏ hơn trọng số của cha hiện tại của v trong H
        if(w<H->Weight[v]){
            // Đặt u làm cha mới của v trong H
            H->Parent[v] = u;
            // Đặt trọng số của v trong H là w
            H->Weight[v] = w;
            // Đặt liên kết của v trong H là e
            H->Link[v] = Link;
        }
    }
    // Đặt Root là gốc của H
    H->Parent[Root] = -1;
    // Đặt trọng số của Root trong H là 0
    H->Weight[Root] = 0;
}

// Khởi tạo một mảng ID với kích thước MAXN
int ID[MAXN];

int FindCycles(struct Tree *H, int Root){
    // Khởi tạo một mảng Color với kích thước MAXN
    int Color[MAXN];
    int u,No=0;
    // Khởi tạo tất cả các phần tử của ID và Color thành -1
    for(int i=1;i<=H->n;i++){
        ID[i] = -1;
        Color[i] = -1;
    }
    // Duyệt qua tất cả các đỉnh trong H
    for(int i=1;i<=H->n;i++){
        u=i;
        // Trong khi u không phải là gốc và ID[u] chưa được đặt và Color[u] khác i
        while(u!=Root&&ID[u]==-1&&Color[u]!=i){
            // Đặt Color[u] thành i
            Color[u] = i;
            // Đặt u làm cha của nó trong H
            u = H->Parent[u];
        }
        // Nếu Color[u] bằng i, thì đã tìm thấy chu trình
        if(Color[u]==i){
            No++;
            int v = H->Parent[u];
            while(v!=u){
                // Đặt ID[v] thành No
                ID[v] = No;
                v = H->Parent[v];
            }
            // Đặt ID[u] thành No
            ID[u] = No;
        }
    }
    return No;
}

void Contract(struct Graph *G, struct Tree *H, int No,struct Graph *G1){
    // Khởi tạo một đồ thị G1 với No đỉnh
    InitGraph(G1,No);
    // Duyệt qua tất cả các cạnh trong G
    for(int e=0;e<G->m;e++){
        int u = G->Edges[e].u;
        int v = G->Edges[e].v;
        int w = G->Edges[e].w;
        // Nếu ID[u] khác ID[v]
        if (ID[u] != ID[v]){
            // Thêm một cạnh từ đỉnh ID[u] đến đỉnh ID[v] với trọng số w-H->Weight[v]
            AddEdge(G1, ID[u], ID[v], w - H->Weight[v], e);
        }
    }
}
void Expand(struct Tree *H,struct Graph *G1, struct Tree * H1){
    for(int i=1;i<=H->n;i++){
        if(H->Parent[i]!=-1){
            struct Edge Pe = G1->Edges[H->Link[i]];
            // Đặt Pe.u là cha của Pe.v trong H1
            H1->Parent[Pe.v] = Pe.u;
            // Thêm trọng số của i trong H vào Pe.v trong H1
            H1->Weight[Pe.v] += H->Weight[i];
            // Đặt Pe.Link là liên kết của Pe.v trong H1
            H1->Link[Pe.v] = Pe.Link;
        }
    }
}
#define MAXIT 10
void Chuliu(struct Graph *G0, int s, struct Tree *T){
    struct Graph G[MAXIT];
    struct Tree H[MAXIT];
    int Temp = 0;
    int Root = s;
    G[0] = *G0;
    while(1){
        // Xây dựng cây H từ đồ thị G
        BuildH(&G[Temp],Root,&H[Temp]);
        // Tìm chu trình trong cây H
        int No = FindCycles(&H[Temp],Root);
        // Nếu không tìm thấy chu trình nào, thoát khỏi vòng lặp
        if(No==0) break;
        // Đánh số lại các đỉnh trong chu trình
        for(int i=1;i<=H[Temp].n;i++){
            if(ID[i]==-1){
                ID[i] = ++No;
            }
        }
        // Thu gọn đồ thị G và lưu vào G1
        Contract(&G[Temp],&H[Temp],No,&G[Temp+1]);
        // Đặt lại gốc của cây bao trùm nhỏ nhất
        Root = ID[Root];
        Temp++;
    }
    // Mở rộng cây bao trùm nhỏ nhất và lưu vào T
    for(int k = Temp;k>0;k--){
        Expand(&H[k],&G[k-1],&H[k-1]);
    }
    *T = H[0];
}
int main(int argc, char const *argv[]){
    struct Graph G;
    int n,m,i,e,u,v,w;
    freopen("Chillluon.txt","r",stdin);
    scanf("%d%d",&n,&m);
    InitGraph(&G,n);
    for(e=0;e<m;e++){
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(&G,u,v,w,-1);
    }
    struct Tree T;
    Chuliu(&G,1,&T);
    for(i=1;i<=T.n;i++){
        if(T.Parent[i]!=-1){
            printf("(%d , %d) %d\n",T.Parent[i],i,T.Weight[i]);
        }
    }
    return 0;
}