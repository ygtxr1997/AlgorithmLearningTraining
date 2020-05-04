#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 2010;
const int INF = 0x3f3f3f3f;
int n, m;
int dist[maxn][maxn];
int vis[maxn];
int least[maxn];
int prime(void) {
    int ans = -1;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) {
        least[i] = dist[1][i];
    }
    vis[1] = 1;
    for (int i = 1; i < n; ++i) {
        int k, cur_min = INF;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && least[j] < cur_min) {
                cur_min = least[j];
                k = j;
            }
        }
        vis[k] = 1;
        ans = max(ans, cur_min); // 记录最大树枝
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && least[j] > dist[k][j]) {
                least[j] = dist[k][j];
            }
        }
    }
    return ans;
}

int main(void) {
    while (scanf("%d%d", &n, &m) != EOF) {
        int a, b, c;
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            // 输入有重边
            dist[a][b] = dist[b][a] = min(dist[b][a], c);
        }
        printf("%d\n", prime());
    }
    return 0;
}