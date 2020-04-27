#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#define INF 0x3f3f3f3f
using namespace::std;
typedef pair<int, int> pii;

// 时间复杂度O(n*n*n)，dijkstra算法的变形，设一条通路的"青蛙距离"为最长的那条边，要求从起点到终点的最短青蛙距离
// 遍历已得到结果v和未得到结果x的石头，把每次遍历时"青蛙距离"最小的那个节点加入v，总共n-1次即可
int n; // 2 <= n <= 200, 一共n个石头
pii stones[201]; // [<xi, yi>]
float least[201]; // 第i个点到第1个点的最短青蛙距离
bool visited[201]; // 已经得到最短青蛙距离的点
// 计算欧氏距离
inline float getODist(pii& p1, pii& p2) {
    return sqrt((float)(p1.first - p2.first) * (p1.first - p2.first)
            + (p1.second - p2.second) * (p1.second - p2.second));
}
float dijkstra(void) {
    visited[1] = 1; least[1] = 0;
    for (int time = 1; time < n; ++time) { // 一共要运行n-1次
        int cur_index, cur_min = INF; 
        for (int v = 1; v <= n; ++v) { // 遍历已经得到最小距离的点
            if (visited[v] == 0) continue;
            for (int x = 2; x <= n; x++) { // 还未得到最小距离的点
                if (visited[x] == 1) continue;
                float Odist = getODist(stones[v], stones[x]);
                least[x] = min(least[x], max(least[v], Odist));
                if (least[x] < cur_min) {
                    cur_min = least[x];
                    cur_index = x;
                }
            }
        }
        visited[cur_index] = 1;
        if (cur_index == 2) return least[2];
    }
    return least[2];
}

int main(void) {
    int t = 1;
    while ((cin >> n) && n != 0) {
        memset(stones, 0, sizeof(pii) * 201);
        for (int i = 0; i < 201; ++i) least[i] = INF;
        memset(visited, 0, sizeof(bool) * 201);
        for (int i = 1; i <= n; ++i) {
            cin >> stones[i].first >> stones[i].second;
        }
        getchar();
        float ans = dijkstra();
        printf("Scenario #%d\n", t++);
        printf("Frog Distance = %.3f\n\n", ans);
    }
    return 0;
}