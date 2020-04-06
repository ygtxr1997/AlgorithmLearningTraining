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

// 考虑使用spfa优化,即bellman的队列优化版本,实际上并不会比bellman快
// SPFA非简单图貌似不能用邻接矩阵，新加入的负边会覆盖原来的边，跪了
// 多重图不要用邻接矩阵！！！
int F; // F farms
int N, M, W; // N fields, M paths, W wormholes, 1<=N<=500, 1<=M<=2500, 1<=W<=200
vector<vector<Edge>> table; // table[i]={以i节点开头的所有边}
int least[501]; // 判断负环，每次取最近
bool bellman(void) {
    int visited[501] = { 0 }; // 当前是否在队列中
    int update[501] = { 0 }; // 节点的更新次数
    memset(visited, 0, sizeof(visited));
    memset(update, 0, sizeof(update));
    queue<int> qu;
    least[1] = 0;
    qu.push(1);
    int cur_index = 1;
    while (!qu.empty()) {
        cur_index = qu.front();
        qu.pop();
        visited[cur_index] = 0;
        for (int j = 0; j < table[cur_index].size(); ++j) {
            Edge& edge = table[cur_index][j];
            int to = edge.to, cost = edge.cost;
            if (least[to] > least[cur_index] + cost) {
                least[to] = least[cur_index] + cost;
                update[to] = update[cur_index] + 1;
                if (visited[to] == 0) { qu.push(to); visited[to] = 1; }
                if (update[to] >= N) return true; // 一个节点的更新次数大于N次，存在负环
            }
        }
    }
    return false;
}

int main(void) {
    cin >> F;
    while (F--) {
        cin >> N >> M >> W;
        table.clear();
        table.resize(N + 1);
        memset(least, 0x3f, sizeof(least));
        for (int x = 1; x <= M + W; ++x) {
            int S, E, T;
            cin >> S >> E >> T;
            if (x <= M) { 
                table[S].push_back(Edge(S, E, T));
                table[E].push_back(Edge(E, S, T));
            }
            else table[S].push_back(Edge(S, E, -T));
        }
        if (bellman()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}