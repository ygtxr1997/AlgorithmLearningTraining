#include <iostream>
#include <cstring>
using namespace::std;
#define INF 0x3f3f3f3f
const int maxn = 1002;

// 有向图的单源点最短路径，先求从该节点出发的，再求以该节点为终点的
int N, M, X; // 1 <= N <= 1000, 1 <= X <= N, 1 <= M <= 100000
int dist[maxn][maxn]; // 有向图
int goX[maxn]; // 去X的最短路
int leaveX[maxn]; // 离开X的最短路
bool visited[maxn];
int dijkstra(void) {
    memset(visited, 0, sizeof(visited));
    goX[X] = leaveX[X] = 0; visited[X] = 1;
    int last_index = X; // 从X开始
    // 先算go
    for (int time = 1; time < N; ++time) {
        int cur_index, cur_min = INF;
        for (int k = 1; k <= N; ++k) {
            if (visited[k]) continue;
            goX[k] = min(goX[k], goX[last_index] + dist[k][last_index]);
            if (goX[k] < cur_min) {
                cur_min = goX[k];
                cur_index = k;
            }
        }
        last_index = cur_index;
        visited[cur_index] = 1;
    }

    // 再算leave
    memset(visited, 0, sizeof(visited));
    visited[X] = 1; last_index = X;
    for (int time = 1; time < N; ++time) {
        int cur_index, cur_min = INF;
        for (int k = 1; k <= N; ++k) {
            if (visited[k]) continue;
            leaveX[k] = min(leaveX[k], leaveX[last_index] + dist[last_index][k]);
            if (leaveX[k] < cur_min) {
                cur_min = leaveX[k];
                cur_index = k;
            }
        }
        last_index = cur_index;
        visited[cur_index] = 1;
    }

    int ans = 0;
    for (int k = 1; k <= N; ++k) ans = max(ans, goX[k] + leaveX[k]);
    return ans;
}
int main(void) {
    while (cin >> N >> M >> X) {
        memset(dist, 0x3f, sizeof(dist));
        memset(goX, 0x3f, sizeof(goX));
        memset(leaveX, 0x3f, sizeof(leaveX));
        for (int m = 1; m <= M; ++m) {
            int x, y, dxy;
            cin >> x >> y >> dxy;
            dist[x][y] = dxy;
        }
        cout << dijkstra() << endl;
    }
    return 0;    
}