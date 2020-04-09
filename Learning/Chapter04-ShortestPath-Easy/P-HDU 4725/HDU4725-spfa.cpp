#include <iostream>
#include <cstring>
#include <queue>
using namespace::std;
const int maxn = 100100; // 10^5
const int INF = 0x3f3f3f3f;
// 边数较少, 用邻接表
typedef struct Node {
    Node(){next = -1;}
    int point, cost, next;
} Node;
Node Edges[6 * maxn]; // 有向边表
int edge_num; // 总边数
int head[3 * maxn]; // i点邻接的最后一条边在边表的序号
typedef struct pii {
    pii(){}
    pii(int x, int y) : point(x), cost(y) {}
    bool operator<(pii p2) const { return cost > p2.cost; }
    bool operator>(pii p2) const { return cost < p2.cost; }
    int point, cost;
} pii;

int T; // T cases
int N, M, C; // N points, M edges, C layer cost, 0<=N,M<=10000
int L[maxn]; // i点所在层, 1<=Li<=N, 入点编号从N~2*N-1, 出点编号从2*N~3*N-1
int maxLayer; // 最大层数
int least[3 * maxn]; // i点到1点的最近距离
bool visited[3 * maxn]; // 是否已获得最小值
bool bLayer[maxn]; // 第i层是否出现过

// 最开始因为数组范围开的不够大一直WA......
void addEdge(int from, int to, int cost) {
    Edges[edge_num].point = to;
    Edges[edge_num].cost = cost;
    Edges[edge_num].next = head[from];
    head[from] = edge_num++;
}
// spfa会超时, 考虑dijkstra+优先队列
// 算出来结果确实是对的, 但是会超时
int spfa(void) {
    memset(least, 0x3f, sizeof(least));
    memset(visited, 0, sizeof(visited));
    least[1] = 0;
    queue<int> qu;
    qu.push(1);
    while (!qu.empty()) {
        int pv = qu.front();
        qu.pop();
        visited[pv] = 0;
        for (int iNode = head[pv]; iNode != -1; iNode = Edges[iNode].next) {
            int px = Edges[iNode].point, cost = Edges[iNode].cost;
            if (least[px] > least[pv] + cost) {
                least[px] = least[pv] + cost;
                if (!visited[px]) {
                    qu.push(px);
                    visited[px] = 1;
                }
            }
        }
    }
    return least[N] == INF ? -1 : least[N];
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        memset(head, -1, sizeof(head));
        memset(bLayer, 0, sizeof(bLayer));
        scanf("%d%d%d", &N, &M, &C);
        edge_num = 0;
        maxLayer = -1;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &(L[i]));
            if (L[i] > maxLayer) maxLayer = L[i];
            addEdge(maxn + L[i], i, 0); // 该层入点到所有点距离为0
            addEdge(i, 2 * maxn + L[i], C); // 该层所有点到出点距离为C
            bLayer[L[i]] = 1;
        }
        for (int layer = 1; layer <= maxLayer; ++layer) {
            if (!bLayer[layer]) continue; // 没出现的层不用考虑
            if (layer > 1) addEdge(2 * maxn + layer, maxn + layer - 1, 0); // 每层出点到左边层的入点距离为0
            if (layer < maxLayer) addEdge(2 * maxn + layer, maxn + layer + 1, 0); // 每层出点到右边层入点距离为0
        }
        for (int i = 1; i <= M; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w); // 额外边, 这里要建两次边才行
            addEdge(v, u, w);
        }
        printf("Case #%d: %d\n", t, spfa());
    }
    return 0;
}