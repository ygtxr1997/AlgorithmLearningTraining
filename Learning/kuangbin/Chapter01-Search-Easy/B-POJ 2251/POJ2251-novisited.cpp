#include <iostream>
#include <vector>
#include <queue>

using namespace::std;
typedef struct Pos {
    Pos(int i1, int i2, int i3, int i4) : x(i1), y(i2), z(i3), m(i4){}
    bool operator==(const Pos& P2) {return x == P2.x && y == P2.y && z == P2.z;}
    int x;
    int y;
    int z;
    int m;
} Pos;
int L, R, C;

// 用bfs可以避免多次递归取最小值，借助队列通过层序遍历可以更快地找到最短路径
// 不用visited保存，而是直接在原始矩阵上修改
int bfs(vector<vector<vector<char>>>& matrix, Pos& start, Pos& end) {
    int ans = INT_MAX;
    vector<vector<vector<bool>>> visited(L, vector<vector<bool>>(R, vector<bool>(C, 0)));
    queue<Pos> qu;
    qu.push(Pos(start.x, start.y, start.z, start.m));
    matrix[start.x][start.y][start.z] = '#';
    while (!qu.empty()) {
        int a = qu.front().x, b = qu.front().y, c = qu.front().z, d = qu.front().m;
        if (qu.front() == end) { ans = d; break; }
        // 这里容易出错!每次向队列插入节点之后，都要更新该插入节点的状态，表示该节点已经访问过(虽然还没有从队列中遍历到)
        if (a + 1 < L && matrix[a + 1][b][c] != '#') { qu.push(Pos(a + 1, b, c, d + 1)); matrix[a + 1][b][c] = '#'; }
        if (a > 0 && matrix[a - 1][b][c] != '#') { qu.push(Pos(a - 1, b, c, d + 1)); matrix[a - 1][b][c] = '#';}
        if (b + 1 < R && matrix[a][b + 1][c] != '#') { qu.push(Pos(a, b + 1, c, d + 1)); matrix[a][b + 1][c] = '#'; } 
        if (b > 0 && matrix[a][b - 1][c] != '#') { qu.push(Pos(a, b - 1, c, d + 1)); matrix[a][b - 1][c] = '#'; }
        if (c + 1 < C && matrix[a][b][c + 1] != '#') { qu.push(Pos(a, b, c + 1, d + 1)); matrix[a][b][c + 1] = '#'; } 
        if (c > 0 && matrix[a][b][c - 1] != '#') { qu.push(Pos(a, b, c - 1, d + 1)); matrix[a][b][c - 1] = '#'; }
        qu.pop();
    }
    return ans;
}

int main(void) {
    while ((cin >> L >> R >> C) && (L + R + C) != 0) {
        vector<vector<vector<char>>> matrix(L, vector<vector<char>>(R, vector<char>(C)));
        Pos start(-1, -1, -1, 0), end(-1, -1, -1, -1);
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < R; ++j) {
                for (int k = 0; k < C; ++k) {
                    cin >> matrix[i][j][k];
                    if (matrix[i][j][k] == 'S') start = Pos(i, j, k, 0);
                    else if (matrix[i][j][k] == 'E') end = Pos(i, j, k, INT_MAX);
                }
            }
            getchar();
        }
        int ans = bfs(matrix, start, end);
        if (ans == INT_MAX) cout << "Trapped!" << endl;
        else cout << "Escaped in " << ans << " minute(s)." << endl;
    }
    return 0;
}