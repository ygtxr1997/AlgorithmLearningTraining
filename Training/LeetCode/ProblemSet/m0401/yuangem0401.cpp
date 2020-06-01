class Solution {
public:
    static const int maxn = 1e5 + 30;
    // 链式向前星
    int head[maxn];
    typedef struct node {
        int to, nxt;
    } node;
    vector<node> Nodes;
    void addEdge(int from, int to) {
        node Node;
        Node.to = to;
        Node.nxt = head[from];
        Nodes.push_back(Node);
        head[from] = Nodes.size() - 1;
    }
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        // init
        memset(head, -1, sizeof(head));
        for (auto vec : graph) addEdge(vec[0], vec[1]);
        // bfs
        vector<bool> vis(n, 0);
        queue<int> qu;
        qu.push(start);
        vis[start] = 1;
        while (!qu.empty()) {
            int v = qu.front();
            qu.pop();
            if (v == target) return true;
            for (int iNode = head[v]; iNode != -1; iNode = Nodes[iNode].nxt) {
                int x = Nodes[iNode].to;
                if (!vis[x]) {
                    vis[x] = 1;
                    qu.push(x);
                }
            }
        }
        return false;
    }
};