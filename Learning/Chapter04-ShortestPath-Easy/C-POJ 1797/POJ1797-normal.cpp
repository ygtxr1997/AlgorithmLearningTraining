#include <iostream>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace::std;

// 普通dijkstra，O(n^3)，会超时
int T;
int n, m; // 1 <= n <= 1000, n个点, m条边
int dist[1001][1001];
bool visited[1001]; // 已经得到最大容量的点
int most[1001]; // 从1出发到x的最大负重
int dijkstra(void) {
    most[1] = INF;
    visited[1] = 1;
    for (int time = 1; time < n; ++time) { // 重复n-1次可得结果
        int cur_index, cur_max = 0;
        for (int v = 1; v <= n; ++v) { // 已得到最大负重的v
            if (visited[v] == 0) continue;
            for (int x = 2; x <= n; ++x) { // 未得到最大负重的x
                if (visited[x] == 1) continue;
                most[x] = max(most[x], min(most[v], dist[v][x]));
                if (most[x] > cur_max) {
                    cur_max = most[x];
                    cur_index = x;
                }
            }
        }
        if (cur_index == n) return most[n];
        visited[cur_index] = 1;
    }
    return most[n];
}

int main(void) {
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        memset(visited, 0, sizeof(bool) * 1001);
        memset(most, 0, sizeof(int) * 1001);
        cin >> n >> m;
        for (int i = 1; i <= m; ++i) {
            int x, y, dxy;
            cin >> x >> y >> dxy;
            dist[x][y] = dist[y][x] = dxy;
        }
        int ans = dijkstra();
        printf("Scenario #%d:\n", t);
        cout << ans << endl;
    }
    return 0;
}