// ---------------------------------------------------------------------
// 题目描述:
// 网络中有计算机s和t, 现在每秒钟要从s传输大小为F的数据到t.
// 该网络中一共有N台计算机, 由单向通信电缆相连, 每条通信电缆都有每秒最大传输量.
// 此外, 每条通信电缆还有对应的传输费用, 单位传输费用为d.
// 求传输数据所需的最小费用.
// ---------------------------------------------------------------------
// 思路:
// 类似求解最大流问题, 残存网络的反向边的费用应该是原边费用的相反数.
// 因为有负权边, 所以不能用Dijkstra算法了, 需要用Bellman-Ford算法.
// ---------------------------------------------------------------------

// 边结构体
struct edge { 
    int to, cap, cost, rev; // 终点, 容量, 费用, 反向边
};

int V;
vector<edge> G[maxv]; // 邻接表
int dist[maxv]; // 最短距离
int prevv[maxv], preve[maxv]; // 最短路的前驱节点和对应的边

// 添加边
void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back((edge){to, cap, cost, G[to].size()});
    G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
}

// 求解s到t流量为f的最小费用流
// 如果不能再增广则返回-1
int min_cost_flow(int s, int t, int f) {
    int res = 0;
    while (f > 0) {
        // Bellman-Ford
        fill(dist, dist + V, INF);
        dist[s] = 0;
        bool update = 1;
        while (update) {
            update = 0;
            for (int v = 0; v < V; ++v) {
                if (dist[v] == INF) continue;
                for (int i = 0; i < G[v].size(); ++i) {
                    edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                        dist[e.to] = dist[v] + e.cost;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        update = 1;
                    }
                }
            }
        }

        if (dist[t] == INF) return -1; // 不能再增广
        int d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * dist[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
        return res;
    }
}