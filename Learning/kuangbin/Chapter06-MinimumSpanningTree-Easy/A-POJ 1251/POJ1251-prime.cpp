#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 28;
const int INF = 0x3f3f3f3f;

// Prime求最小生成树
int n; // 1<n<27
int dist[maxn][maxn];
int least[maxn]; // 已加入集合中的各点到未加入集合中个点的最小距离
int visited[maxn];

int prime(void) {
    int sum = 0;
    for (int j = 1; j <= n; ++j) {
        least[j] = dist[1][j];
    }
    least[1] = 0;
    memset(visited, 0, sizeof(visited));
    visited[1] = 1;
    for (int i = 1; i < n; i++) {
        int cur_index, cur_min = INF;
        for (int j = 1; j <= n; ++j) { // 找到权值最小的边
            if (!visited[j] && least[j] < cur_min) {
                cur_min = least[j];
                cur_index = j;
            }
        }
        visited[cur_index] = 1;
        sum += cur_min; // 新的树枝
        for (int j = 1; j <= n; ++j) { // 加入了新的点后, 需要更新least[]
            if (!visited[j] && least[j] > dist[cur_index][j]) {
                least[j] = dist[cur_index][j];
            }
        }
    }
    return sum;
}

int main(void) {
    while ((cin >> n) && n != 0) {
        memset(dist, 0x3f, sizeof(dist));
        int k;
        for (int i = 1; i < n; ++i) { // 建立邻接矩阵
            char ci;
            cin >> ci >> k;
            for (int m = 1; m <= k; ++m) {
                int j, dij;
                char cj;
                cin >> cj >> dij;
                j = cj - 'A' + 1;
                dist[i][j] = dist[j][i] = dij;
            }
        }
        printf("%d\n", prime());
    }
    return 0;
}