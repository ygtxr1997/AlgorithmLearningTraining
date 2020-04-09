#include <iostream>
#include <cstring>
#include <queue>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 310;
typedef struct pii {
    pii(int x, int y) : point(x), cost(y) {}
    bool operator<(pii p2) const { return cost > p2.cost; }
    bool operator>(pii p2) const { return cost < p2.cost; }
    int point, cost;
} pii;

int T; // T cases
int N; // 1<n<=300
int dist[maxn][maxn]; // 邻接矩阵
int least[maxn]; // 1到各点的最短距离
bool visited[maxn]; // 是否已经获得最小值

// 这题关键在把题意的矩阵转换为图
// 1. X12+X13+...+X1n=1 即点1的出度是1
// 2. X14+X24+...+X(n-1)n=1 即点n的入度是1
// 3.∑Xki (1<=k<=n)=∑Xij (1<=j<=n). 即其他点的入度都等于出度
// 综上, ∑Cij*Xij就是符合上述三个条件的总路径长度之和
// 符合上述条件的有:1.点1到点n的最短路径;2.以点1为起点的圈+以点n为起点的圈(非自环)
// 分别获得以节点1和N为起点的圈(非自环)
void dijkstra(int start, int& cir) {
    memset(least, 0x3f, sizeof(least));
    memset(visited, 0, sizeof(visited));
    least[start] = 0;
    priority_queue<pii> pqu;
    pqu.push(pii(start, 0));
    while (!pqu.empty()) {
        int pv = pqu.top().point, cost = pqu.top().cost;
        pqu.pop();
        if (visited[pv]) continue;
        visited[pv] = 1;
        cir = min(cir, least[pv] + dist[pv][start]); // 同时获取最小圈
        for (int px = 1; px <= N; ++px) {
            if (!visited[px] && least[px] > cost + dist[pv][px]) {
                least[px] = cost + dist[pv][px];
                pqu.push(pii(px, least[px]));
            }
        }
    }
}

int main(void) {
    while (scanf("%d", &N) != EOF) {
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                scanf("%d", &dist[i][j]);
            }
            dist[i][i] = INF; // 防止产生自环
        }
        int cir1 = INF, cirn = INF; // 以1为起点的最小圈, 以n为起点的最小圈
        dijkstra(N, cirn);
        dijkstra(1, cir1); // 先算N再算1
        printf("%d\n", min(least[N], cir1 + cirn));
    }
    return 0;
}