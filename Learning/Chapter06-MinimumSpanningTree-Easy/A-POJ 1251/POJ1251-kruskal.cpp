#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 28;
const int INF = 0x3f3f3f3f;
typedef struct Edge {
    Edge(){}
    bool operator<(const Edge& e2) const { return cost < e2.cost; }
    int from, to, cost;
} Edge;
Edge edges[maxn * maxn];
int tot;
void addEdge(int x, int y, int dxy) {
    edges[++tot].from = x;
    edges[tot].to = y;
    edges[tot].cost = dxy;
}

// Kruskal求最小生成树, 需要对边排序, 并结合并查集
int n; // 1<n<27
int UnionSet[maxn];
int Find(int i) {
    if (i != UnionSet[i]) {
        UnionSet[i] = Find(UnionSet[i]);
    }
    return UnionSet[i];
}
int Join(int a, int b) {
    int r1 = Find(a), r2 = Find(b);
    if (r1 == r2) return 1; // 已经在并查集中, 再次加入会产生环
    else {
        UnionSet[r1] = r2;
    }
    return 0; // 未产生环, 加入新的树枝
}

int kruskal(void) {
    int sum = 0;
    sort(edges + 1, edges + tot + 1);
    for (int i = 1; i <= n; ++i) { // 初始化并查集
        UnionSet[i] = i;
    }
    int edge_cnt = 0; // 最小生成树的边数为n-1
    for (int e = 1; e <= tot && edge_cnt <= n - 1; ++e) {
        int x = edges[e].from, y = edges[e].to, dxy = edges[e].cost;
        if (!Join(x, y)) {
            sum += dxy;
            edge_cnt++;
        }
    }
    return sum;
}

int main(void) {
    while ((cin >> n) && n != 0) {
        memset(edges, 0, sizeof(edges));
        tot = 0;
        int k;
        for (int i = 1; i < n; ++i) { // 建立边表
            char ci;
            cin >> ci >> k;
            for (int m = 1; m <= k; ++m) {
                int j, dij;
                char cj;
                cin >> cj >> dij;
                j = cj - 'A' + 1;
                addEdge(i, j, dij);
            }
        }
        printf("%d\n", kruskal());
    }
    return 0;
}