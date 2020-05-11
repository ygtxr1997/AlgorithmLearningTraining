class Solution {
public:
    #define INF 0x3f3f3f3f
    vector<vector<int>> table; // 邻接表
    vector<int> res; // res[i]:比i钱多且安静值最小的那个人
    void addEdge(int from, int to) {
        table[from].push_back(to);
    }
    int dfs(int node, vector<int>& quiet) {
        if (res[node] != INF) return res[node]; // 记忆化搜索
        res[node] = node; // 自己不小于自己
        for (int i = 0; i < table[node].size(); ++i) {
            int nxt = table[node][i];
            int nxt_res = dfs(nxt, quiet);
            if (quiet[nxt_res] < quiet[res[node]]) {
                res[node] = nxt_res;
            }
        }
        return res[node];
    }
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        table.resize(n); res.resize(n);
        fill(res.begin(), res.end(), INF);
        for (int i = 0; i < richer.size(); ++i) {
            addEdge(richer[i][1], richer[i][0]); // 0比1更有钱
        }
        for (int i = 0; i < n; ++i) {
            dfs(i, quiet);
        }
        return res;
    }
};