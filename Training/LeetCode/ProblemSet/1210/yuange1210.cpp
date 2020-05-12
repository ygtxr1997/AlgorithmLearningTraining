class Solution {
public:
    typedef struct node {
        node(){}
        node(int a, int b, int c, int d) : x1(a), y1(b), x2(c), y2(d) {}
        int x1, y1;
        int x2, y2;
        int step;
    } node;
    int dir[4][4] = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 0, 1, -1}, {0, 0, -1, 1}};
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<bool>> vis(n, vector<bool>(n, 0)); // 0:未访问, 1:水平访问过
        vector<vector<bool>> vis2(n, vector<bool>(n, 0)); // 0:未访问, 1:竖直访问过
        vis[0][0] = 1;
        queue<node> qu;
        node start(0, 0, 0, 1);
        start.step = 0;
        qu.push(start);
        while (!qu.empty()) {
            int x1 = qu.front().x1, y1 = qu.front().y1, x2 = qu.front().x2, y2 = qu.front().y2, step = qu.front().step;
            qu.pop();
            if (x1 == n - 1 && y1 == n - 2 && x2 == n - 1 && y2 == n - 1) return step;
            node nxNode(x1, y1, x2, y2);
            nxNode.step = step + 1;
            int &nx1 = nxNode.x1, &ny1 = nxNode.y1, &nx2 = nxNode.x2, &ny2 = nxNode.y2;
            for (int op = 0; op < 4; ++op) {
                if (op == 2 && x1 != x2) continue; // 当前是竖直, 不能顺时针
                if (op == 3 && x1 == x2) continue; // 当前是水平, 不能逆时针
                if (op >= 2 && x1 < n - 1 && y1 < n - 1 && grid[x1 + 1][y1 + 1] != 0) continue; // 四格全空才能甩头
                nx1 = x1 + dir[op][0], ny1 = y1 + dir[op][1], nx2 = x2 + dir[op][2], ny2 = y2 + dir[op][3];
                if (nx1 >= n || ny1 >= n || nx2 >= n || ny2 >= n) continue;
                bool bvis = (nx1 == nx2) ? vis[nx1][ny1] : vis2[nx1][ny1];
                if (bvis == 0 && grid[nx1][ny1] == 0 && grid[nx2][ny2] == 0) {
                    if (nx1 == nx2) vis[nx1][ny1] = 1; // 水平访问
                    else vis2[nx1][ny1] = 1; // 竖直访问
                    qu.push(nxNode); 
                }
            }
        }
        return -1;
    }
};