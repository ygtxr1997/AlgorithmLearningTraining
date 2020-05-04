#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 103;
const int INF = 0x3f3f3f3f;

int N;
int dist[maxn][maxn];
int least[maxn]; // 已加入集合的点到未加入集合的点的最小距离
bool vis[maxn];
int prime(void) {
    int ans = 0;
    memset(vis, 0, sizeof(vis));
    memset(least, 0x3f, sizeof(least));
    least[1] = 0; // 从任意节点开始
    vis[1] = 1;
    for (int j = 1; j <= N; ++j) least[j] = dist[1][j]; // 初始化
    for (int i = 1; i <= N - 1; ++i) {
        int cur_index, cur_min = INF;
        for (int j = 1; j <= N; ++j) {
            if (!vis[j] && least[j] < cur_min) {
                cur_min = least[j];
                cur_index = j;
            }
        }
        ans += cur_min; // 新的树枝
        vis[cur_index] = 1;
        for (int j = 1; j <= N; ++j) { // 更新least
            if (!vis[j] && least[j] > dist[cur_index][j]) {
                least[j] = dist[cur_index][j];
            }
        }
    }
    return ans;
}

int main(void) {
    while (scanf("%d", &N) != EOF) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                scanf("%d", &dist[i][j]);
            }
        }
        printf("%d\n", prime());
    }
    return 0;
}