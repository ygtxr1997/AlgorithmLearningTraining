#include <iostream>
#include <cstring>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 102;

int M, N; // M 等级限制, N 物品总数
int P[maxn]; // 价格, 0:起点, 1:终点
int L[maxn]; // 地位
int X, T, V; // X 替代品总个数, T 替代品编号, V 优惠后价格
int dist[maxn][maxn]; // 邻接表
bool visited[maxn]; // 是否已获得最小值
int least[maxn]; // 起点0到各个点的最小值

// 有最大等级限制的dijkstra
int dijkstra(int maxLevel) {
    for (int i = 1; i <= N; ++i) least[i] = P[i]; // 初始最小值就是原价
    int last_index = 0;
    for (int time = 1; time <= N; ++time) {
        int cur_min = INF;
        for (int j = 0; j <= N; ++j) {
            if (!visited[j] && least[j] < cur_min) {
                cur_min = least[j];
                last_index = j;
            }
        }
        if (last_index == 1) break;
        visited[last_index] = 1;
        for (int j = 0; j <= N; ++j) {
            if (!visited[j] && least[last_index] + dist[last_index][j] < least[j]) {
                least[j] = least[last_index] + dist[last_index][j];
            }
        }
    }
    return least[1];
}

int main(void) {
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d", &M, &N);
    for (int i = 1; i <= N; ++i) { // 第i件物品
        scanf("%d%d%d", &P[i], &L[i], &X);
        for (int x = 1; x <= X; ++x) {
            scanf("%d%d", &T, &V);
            dist[T][i] = V;
        }
    }
    int ans = INF;
    for (int i = 1; i <= N; ++i) { // 枚举所有最大等级
        int maxLevel = L[i];
        for (int j = 1; j <= N; ++j) {
            if (L[j] > maxLevel || maxLevel - L[j] > M) visited[j] = 1; // 超出等级限制的原价即最小
            else visited[j] = 0;
        }
        ans = min(ans, dijkstra(maxLevel));
    }
    printf("%d\n", ans);
    return 0;
}