#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxn = 305;
const int INF = 0x3f3f3f3f;

// 要求出每个点到其他点的距离, Floyd
int N, M; // 牛数, 电影数
int dist[maxn][maxn]; // 图距离
int team[maxn]; // 演出同一部电影的人
void Floyd(void) {
    for (int k = 1; k <= N; k++) { // K循环要写在最外面
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
int main(void) {
    while (scanf("%d%d", &N, &M) != EOF) {
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 1; i <= N; ++i) dist[i][i] = 0;
        for (int m = 0; m < M; ++m) {
            int C;
            scanf("%d", &C);
            for (int i = 0; i < C; ++i) {
                scanf("%d", &team[i]);
            }
            for (int i = 0; i < C; ++i) {
                int A = team[i];
                for (int j = i + 1; j < C; ++j) {
                    int B = team[j];
                    dist[A][B] = dist[B][A] = 1;
                }
            }
        }
        Floyd();
        int ans = INF;
        for (int i = 1; i <= N; ++i) {
            int sum = 0;
            for (int j = 1; j <= N; ++j) {
                sum += dist[i][j];
            }
            ans = min(ans, 100 * sum / (N - 1)); // 不包括自己
        }
        printf("%d\n", ans);
    }
    return 0;
}