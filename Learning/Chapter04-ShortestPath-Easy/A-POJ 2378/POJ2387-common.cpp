#include <iostream>
#include <cstring>
#include <vector>
#define INF 0x7f7f7f7f
using namespace::std;

// O(n*n)的dijkstra算法
int N, T; // 2 <= N <= 1000, 1 <= T <= 2000
int dist[1002][1002]; // i到j的边权值
int least[1002]; // 1到各边的最短距离
bool visited[1002]; // 已经得到最小值的节点
int solve() {
    visited[1] = 1;
    int last_index = 1, last_min = 0;
    for (int i = 1; i < N; ++i) { // 最多N-1次
        int cur_min = INF, cur_index; // 获得当前least[]的最小值及对应序号
        for (int j = 2; j <= N; ++j) {
            if (visited[j] == 1) continue; // 跳过已经得到最小值的节点
            least[j] = min(least[j], dist[last_index][j] + last_min);
            if (least[j] < cur_min) {
                cur_min = least[j];
                cur_index = j;
            }
        }
        if (cur_index == N) return least[N]; // 提前找到
        visited[cur_index] = 1;
        last_index = cur_index;
        last_min = cur_min;
    }
    return least[N];
}

int main(void) {
    while (cin >> T >> N) {
        memset(dist, 0x7f, sizeof(int) * 1002 * 1002);
        memset(least, 0x7f, sizeof(int) * 1002); // 0x3f3f3f3f:∞
        memset(visited, 0, sizeof(bool) * 1002);
        for (int t = 1; t <= T; ++t) {
            int p1, p2, d12;
            cin >> p1 >> p2 >> d12;
            // 不是简单图，两个节点之间可能有多条边
            dist[p1][p2] = dist[p2][p1] = min(d12, dist[p1][p2]);
        }
        cout << solve() << endl;
    }
    return 0;
}