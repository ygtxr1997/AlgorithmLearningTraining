#include <iostream>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace::std;

// dijkstra优化版，O(n^2)，做吐了，还是1600ms
int T;
int n, m; // 1 <= n <= 1000, n个点, m条边
int dist[1001][1001];
inline int dijkstra(void) {
    int most[1001] = { 0 }; // 从1出发到x的最大负重
    int visited[1001] = { 0 };
    most[1] = INF;
    visited[1] = 1;
    int v = 1;
    for (int time = 1; time < n; ++time) { // 重复n-1次可得结果
        int cur_index, cur_max = 0; 
        for (int x = 2; x <= n; ++x) { // 未得到最大负重的x
            if (!visited[x]) {
                most[x] = max(most[x], min(most[v], dist[v][x]));
                if (most[x] > cur_max) {
                    cur_max = most[x];
                    cur_index = x;
                }
            }
        }
        if (cur_index == n) return most[cur_index];
        visited[cur_index] = 1;
        v = cur_index;
    }
    return most[n];
}

int main(void) {
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        memset(dist, -1, sizeof(dist));
        cin >> n >> m;
        int x, y, dxy;
        for (int i = 1; i <= m; ++i) {
            cin >> x >> y >> dxy;
            dist[x][y] = dist[y][x] = dxy;
        }
        int ans = dijkstra();
        printf("Scenario #%d:\n", t);
        printf("%d\n\n", ans);
    }
    return 0;
}