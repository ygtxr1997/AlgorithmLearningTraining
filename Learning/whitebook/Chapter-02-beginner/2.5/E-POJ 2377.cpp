#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;
const int INF = 0x3f3f3f3f;

// 转化为负数再用最小生成树prime
// 或者直接改写为最大生成树
// 注意判断连通性和重边
int N, M;
int dist[maxn][maxn];
int least[maxn];
bool vis[maxn];
int prime(void) {
    int ans = 0;
    memset(vis, 0, sizeof(vis));
    memset(least, 0x3f, sizeof(least));
    least[1] = 0; // 从任意节点开始
    vis[1] = 1;
    for (int j = 1; j <= N; ++j) least[j] = dist[1][j]; // 初始化
    for (int i = 1; i <= N - 1; ++i) {
        int cur_index = -1, cur_min = 2 * INF; // 这里要足够大才行
        for (int j = 1; j <= N; ++j) {
            if (!vis[j] && least[j] < cur_min) {
                cur_min = least[j];
                cur_index = j;
            }
        }
        if (cur_index == -1) break; // 不连通
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
    while (scanf("%d%d", &N, &M) != EOF) {
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 0; i < M; ++i) {
            int A, B, D;
            scanf("%d%d%d", &A, &B, &D);
            // 图中有重边, 只保留最大的那个, 在这里去掉
            dist[A][B] = dist[B][A] = min(dist[A][B], -D);
        }
        int res = prime();
        if (res > 0) printf("-1\n");
        else printf("%d\n", -res);
    }
    return 0;
}