#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
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
int least[maxn]; // i点到1点的最近距离
bool visited[maxn]; // 是否已获得最小值
bool bLayer[maxn]; // 第i层是否出现过

void addEdge(int from, int to, int cost) {
    Edges[edge_num].point = to;
    Edges[edge_num].cost = cost;
    Edges[edge_num].next = head[from];
    head[from] = edge_num++;
}
// spfa会超时, 考虑dijkstra+优先队列
int dijkstra(void) {
    memset(least, 0x3f, sizeof(least));
    memset(visited, 0, sizeof(visited));
    least[1] = 0;
    priority_queue<pii> qu;
    qu.push(pii(1, 0));
    while (!qu.empty()) {
        int pv = qu.top().point, cost = qu.top().cost;
        qu.pop();
        if (visited[pv] == 1) continue;
        visited[pv] = 1;
        least[pv] = cost;
        for (int iNode = head[pv]; iNode != -1; iNode = Edges[iNode].next) {
            int px = Edges[iNode].point, cost = Edges[iNode].cost;
            if (!visited[px] && least[px] > least[pv] + cost) {
                least[px] = least[pv] + cost;
                qu.push(pii(px, least[px]));
            }
        }
    }
    return least[N] == INF ? -1 : least[N];
}

int main(void) {
    freopen("input.txt", "w", stdout);
    srand((unsigned)time(NULL));
    T = 20; printf("%d\n", T);
    for (int t = 1; t <= T; ++t) {
        N = 1 + (rand() % maxn);
        M = 1 + (rand() % maxn);
        C = 1 + (rand() % 1000);
        printf("%d %d %d\n", N, M, C);
        for (int i = 1; i <= N; ++i) {
            int Li = 1 + (rand() % N);
            printf("%d ", Li);
        }
        printf("\n");
        for (int i = 1; i <= M; ++i) {
            int u, v, w;
            u = 1 + (rand() % N);
            v = 1 + (rand() % N);
            w = 1 + (rand() % 10000);
            printf("%d %d %d\n", u, v, w);
        }
        printf("\n");
    }
    return 0;
}