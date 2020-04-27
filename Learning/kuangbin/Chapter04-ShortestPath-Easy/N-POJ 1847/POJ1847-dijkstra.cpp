#include <iostream>
#include <cstring>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 102;

int N, A, B;
int K;
int dist[maxn][maxn];
int least[maxn];
bool visited[maxn];

int dijkstra(int start, int end) {
    least[start] = 0;
    for (int i = 1; i <= N; ++i) least[i] = dist[start][i];
    int last_index = start;
    for (int time = 1; time < N; ++time) {
        int cur_min = INF;
        for (int j = 1; j <= N; ++j) {
            if (visited[j]) continue;
            if (cur_min > least[j]) {
                cur_min = least[j];
                last_index = j;
            }
        }
        if (end == last_index) break;
        visited[last_index] = 1;
        for (int j = 1; j <= N; ++j) {
            if (!visited[j] && least[j] > least[last_index] + dist[last_index][j]) {
                least[j] = least[last_index] + dist[last_index][j];
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
    printf("%d\n", dijkstra(A, B));
    return 0;
}