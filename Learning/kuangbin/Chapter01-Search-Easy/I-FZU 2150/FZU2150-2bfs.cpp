#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
using namespace::std;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> piii;

// 两次搜索：第一次把连在一起的草地划分为一个part；根据part的数量决定第二次的搜索方式；
//          如果part为0个或者3个以上，则不用搜索；
//          如果part为1个，则在该连通草坪内进行两个端点的bfs，保存最小步数；
//          如果part为2个，则在两个连通草坪内分别bfs，取最小步数。
int T, n, m;
vector<string> grid(11, string(11, '0')); // 草坪情况
vector<vector<pii>> part(100, vector<pii>(0)); // 同一个连通块的草坪放在一个数组内
int visited[101][101] = { 0 }; // 辅助数组，保存已经燃烧过的草坪
// BFS
int bfs(queue<piii>& qu, int p) {
    int step = 0;
    while (!qu.empty()) {
        int x = qu.front().first.first, y = qu.front().first.second;
        step = qu.front().second;
        if (x + 1 < n && grid[x + 1][y] == p && visited[x + 1][y] == 0) { 
            visited[x + 1][y] = 1; qu.push(piii(pii(x + 1, y), step + 1));
        } 
        if (x - 1 >= 0 && grid[x - 1][y] == p && visited[x - 1][y] == 0) {
            visited[x - 1][y] = 1; qu.push(piii(pii(x - 1, y), step + 1));
        } 
        if (y + 1 < m && grid[x][y + 1] == p && visited[x][y + 1] == 0) {
            visited[x][y + 1] = 1; qu.push(piii(pii(x, y + 1), step + 1));
        } 
        if (y - 1 >= 0 && grid[x][y - 1] == p && visited[x][y - 1] == 0) {
            visited[x][y - 1] = 1; qu.push(piii(pii(x, y - 1), step + 1));
        }
        qu.pop();
    }
    return step;
}
// 恰好有2个连通块
int twoPart(int p) {
    int count = part[p].size(), least = INT_MAX;
    queue<piii> qu; // <<x,y>,step>
    for (int s = 0; s < count; ++s) {
        qu.push(piii(part[p][s], 0));
        visited[part[p][s].first][part[p][s].second] = 1;
        least = min(least, bfs(qu, p));
        memset(visited, 0, sizeof(int) * 101 * 101);
    }
    return least;
}
// 只有1个连通块
int onePart() {
    int count = part[1].size(), least = INT_MAX;
    queue<piii> qu; // <<x,y>,step>
    for (int s1 = 0; s1 < count; ++s1) {
        for (int s2 = s1; s2 < count; ++s2) {
            qu.push(piii(part[1][s1], 0)); qu.push(piii(part[1][s2], 0));
            visited[part[1][s1].first][part[1][s1].second] = visited[part[1][s2].first][part[1][s2].second] = 1;
            if (s1 == s2) qu.pop();
            least = min(least, bfs(qu, 1));
            memset(visited, 0, sizeof(int) * 101 * 101);
        }
    }
    return least;
}
// 把草坪按照连通块分割
int divide() {
    queue<pii> qu;
    int Di = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') {
                qu.push(pii(i, j)); grid[i][j] = Di;
                while (!qu.empty()) {
                    int x = qu.front().first, y = qu.front().second;
                    part[Di].push_back(pii(x, y));
                    if (x + 1 < n && grid[x + 1][y] == '#') { grid[x + 1][y] = Di; qu.push(pii(x + 1, y)); }
                    if (x - 1 >= 0 && grid[x - 1][y] == '#') { grid[x - 1][y] = Di; qu.push(pii(x - 1, y)); }
                    if (y + 1 < m && grid[x][y + 1] == '#') { grid[x][y + 1] = Di; qu.push(pii(x, y + 1)); }
                    if (y - 1 >= 0 && grid[x][y - 1] == '#') { grid[x][y - 1] = Di; qu.push(pii(x, y - 1)); }
                    qu.pop();
                }
                Di++;
            }
        }
    }
    return Di - 1;
}

int main(void) {
     cin >> T;
     {
        for (int t = 1; t <= T; ++t) {
            part = vector<vector<pii>>(100, vector<pii>(0));
            cin >> n >> m;
            for (int i = 0; i < n; ++i)
                cin >> grid[i];
            int d = divide(), ans;
            if (d == 0) ans = 0;
            else if (d == 1) ans = onePart();
            else if (d == 2) ans = max(twoPart(1), twoPart(2));
            else ans = -1;
            cout << "Case " << t << ": " << ans << endl;
        }
    }
    return 0;
}