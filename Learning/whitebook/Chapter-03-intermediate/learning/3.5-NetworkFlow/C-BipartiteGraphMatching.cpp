// ---------------------------------------------------------------------
// 题目描述:
// 有 N 台计算机和 K 个任务.
// 我们可以给每台计算机分配一个任务, 每台计算机能够处理的任务种类各不相同.
// 请求出最多能够处理的人物的个数.
// ---------------------------------------------------------------------
// 思路:
// 定义无向二分图 G=(U∪V,E).
// U:计算机顶点集合, V:任务的顶点集合,
// 对于任意u∈U和v∈V, 计算机u能处理v任务 <=> (u,v)∈E.
// 在G中满足两两不含公共端点的边集合M⊆E的基数|M|, 边集合M又称为匹配.
// |M|最大的M又称为最大匹配, 当2|M|=|V|时又称为完美匹配.
// 可以将二分图匹配转化为最大流问题.
// 把(u,v)都转化为有向边, 添加源点s和汇点t, 添加边(s,u)和(v,t).
// 这样得到的最大s-t流就是原二分图G中最大匹配的数量.
// 或者利用所有边的容量都是1以及二分图的性质, 可以更简单地实现.
// ---------------------------------------------------------------------
int V; // 顶点数
vector<int> G[maxv]; // 邻接表
int match[maxv]; // 匹配的顶点
bool used[maxv]; // DFS使用

// 添加边
void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

// 通过DFS寻找增广路
bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); ++i) {
        int u = G[v][i], w = match[u];
        if (w < 0 || !used[w] && dfs(w)) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

// 求解二分图的最大匹配
int bipartite_matching(void) {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int v = 0; v < V; v++) {
        if (match[v] < 0) {
            memset(used, 0, sizeof(used));
            if (dfs(v)) {
                res++;
            }
        }
    }
    return res;
}