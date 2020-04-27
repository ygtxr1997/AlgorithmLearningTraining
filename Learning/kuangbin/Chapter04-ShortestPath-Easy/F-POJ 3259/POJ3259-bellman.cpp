#include <iostream>
#include <cstring>
#include <queue>
using namespace::std;
#define INF 0x3f3f3f3f
typedef struct Edge {
    Edge(){}
    Edge(int x1, int x2, int x3) : from(x1), to(x2), cost(x3) {}
    Edge(const Edge& e2) {from = e2.from; to = e2.to; cost = e2.cost;}
    Edge& operator=(const Edge& e2) {from = e2.from; to = e2.to; cost = e2.cost; return *this; }
    int from, to, cost;
} Edge;

// 朴素bellman判断是否存在负环,300+ms
int F; // F farms
int N, M, W; // N fields, M paths, W wormholes, 1<=N<=500, 1<=M<=2500, 1<=W<=200
Edge edges[6000];
int least[501]; // 判断负环，每次取最近
bool bellman(void) {
    for (int t = 1; t < N; ++t) {
        for (int e = 1; e <= 2 * M + W; ++e) {
            int from = edges[e].from, to = edges[e].to, cost = edges[e].cost;
            least[to] = min(least[to], least[from] + cost);
        }
    }
    for (int e = 1; e <= 2 * M + W; ++e) {
        int from = edges[e].from, to = edges[e].to, cost = edges[e].cost;
        if (least[from] + cost < least[to]) return true;
    }
    return false;
}

int main(void) {
    cin >> F;
    while (F--) {
        cin >> N >> M >> W;
        memset(edges, 0, sizeof(edges));
        memset(least, 0x3f, sizeof(least));
        for (int x = 1; x <= M + W; ++x) {
            int S, E, T;
            cin >> S >> E >> T;
            if (x <= M) { edges[2 * x - 1] = Edge(S, E, T); edges[2 * x] = Edge(E, S, T); }
            else edges[M + x] = Edge(S, E, -T);
        }
        if (bellman()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}