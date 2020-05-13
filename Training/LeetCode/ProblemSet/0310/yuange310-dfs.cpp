// 第二种方法, 任取度为1的叶子节点O,
// 从O出发找到离O最远的A,
// 再从A出发找到离A最远的点B, 并保存路径A-B, 路径上中间的1个或2个点即根节点.
class Solution {
public:
    int start;
    vector<int> dim; // 度数
    vector<vector<int>> table; // 邻接表
    vector<bool> vis;
    vector<int> far_path; // 最远路径
    void addEdge(int from, int to) {
        table[from].push_back(to);
        table[to].push_back(from);
    }
    void dfs(int v0, int node, vector<int>& path) {
        if (node != v0 && dim[node] == 1) {
            if (path.size() > far_path.size()) {
                far_path.resize(path.size());
                copy(path.begin(), path.end(), far_path.begin());
            }
            return;
        }
        for (int i = 0; i < table[node].size(); ++i) {
            int nxt = table[node][i];
            if (!vis[nxt]) {
                vis[nxt] = 1;
                path.push_back(nxt);
                dfs(v0, nxt, path);
                path.pop_back();
            }
        }
    }
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (edges.empty()) return vector<int>({0});
        if (edges.size() == 1) return vector<int>({0, 1});
        dim.resize(n); table.resize(n); vis.resize(n);
        for (int i = 0; i < edges.size(); ++i) {
            dim[edges[i][0]]++;
            dim[edges[i][1]]++;
            addEdge(edges[i][0], edges[i][1]);
        }
        int pointO;
        for (int i = 0; i < n; ++i) if (dim[i] == 1) { pointO = i; break; }
        // 从点O出发找到A
        vis[pointO] = 1;
        vector<int> path1(1, pointO);
        dfs(pointO, pointO, path1);
        start = far_path.back();
        // 从A出发找到B
        fill(vis.begin(), vis.end(), 0);
        vis[start] = 1;
        vector<int> path2(1, start);
        dfs(start, start, path2);
        if (far_path.size() % 2) return vector<int>({far_path[far_path.size() / 2]});
        else return vector<int>({far_path[far_path.size() / 2], far_path[far_path.size() / 2 - 1]});
    }
};