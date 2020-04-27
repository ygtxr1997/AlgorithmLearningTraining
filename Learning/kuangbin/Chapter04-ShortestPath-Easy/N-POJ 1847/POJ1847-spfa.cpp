#include <iostream>
#include <cstring>
#include <queue>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 102;

int N, A, B;
int K;
int dist[maxn][maxn];
int least[maxn];
bool visited[maxn]; // 是否在队列中

// 尝试用spfa算法, 已经0ms了, 不需要slf优化
int spfa(int start, int end) {
    queue<int> dq;
    dq.push(start);
    least[start] = 0;
    while (!dq.empty()) {
        int pv = dq.front();
        dq.pop();
        visited[pv] = 0;
        if (visited[pv]) continue;
        for (int px = 1; px <= N; ++px) {
            if (least[px] > least[pv] + dist[pv][px]) {
                least[px] = least[pv] + dist[pv][px];
                if (!visited[px]) {
                    dq.push(px);
                    visited[px] = 1;
                }
            }
        }
    }
    return least[end] == INF ? -1 : least[end]; // 这里不要漏
}

int main(void) {
    memset(dist, 0x3f, sizeof(dist));
    memset(least, 0x3f, sizeof(least));
    memset(visited, 0, sizeof(visited));
    scanf("%d%d%d", &N, &A, &B);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &K);
        for (int j = 1; j <= K; ++j) {
            int next;
            scanf("%d", &next);
            if (j == 1) dist[i][next] = 0;
            else dist[i][next] = 1;
        }
    }
    printf("%d\n", spfa(A, B));
    return 0;
}