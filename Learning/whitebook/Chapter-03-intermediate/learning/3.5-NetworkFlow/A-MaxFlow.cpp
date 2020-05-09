// 用于表示边的结构体
struct edge {
    int to, cap, rev; // 终点, 容量, 反向边
};

vector<edge> G[maxv]; // 图的邻接矩阵
bool used[maxv];      // DFS使用

// 添加边时同时添加反向边
// 正向边容量为 cap
// 反向边容量为 0
void add_edge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, G[to].size()});
    G[to].push_back((edge){from, 0, G[from].size() - 1});
}

// 通过DFS寻找增广路
// v:当前节点, t:目标终点, f:当前节点可发送的最大流
int dfs(int v, int t, int f) {
    if (v == t) return f; // 递归终点
    used[v] = true;
    for (int i = 0; i < G[v].size(); ++i) { // 遍历i的所有出边
        edge &e = G[v][i];
        if (!used[e.to] && e.cap > 0) { // 只能走cap大于0且节点未访问过的边
            int d = dfs(e.to, t, min(f, e.cap)); // 正向边可发送最大流
            if (d > 0) {
                e.cap -= d; // 正向边发送相应的流, 容量减少
                G[e.to][e.rev].cap += d; // 反向边可退回的流
                return d;
            }
        }
    }
    return 0; // 无其他路径, 流的增量为0
}

// 求解从s到t的最大流
int max_flow(int s, int t) {
    int flow = 0;
    for (;;) {
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, INF);
        if (f == 0) return flow;
        flow += f;
    }
}