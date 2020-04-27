#include <iostream>
#include <vector>
#include <cstring>
using namespace::std;

int N, M; // 1<=N<=100, 1<=M<=4500
int dist[101][101];
int floyd(void) {
    // floyd算法求出所有点之间的到达关系
    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (dist[i][j] == 1) continue;
                dist[i][j] = (dist[i][k] && dist[k][j]) ? 1 : 0;
            }
        }
    }
    int ans = 0;
    // 能到达该点的点个数+该点能到达的点个数=N-1时，可确定
    for (int i = 1; i <= N; ++i) {
        int tmp = 0;
        for (int k = 1; k <= N; ++k) tmp += dist[i][k] + dist[k][i];
        if (tmp == N - 1) ans++;
    }
    return ans;
}

int main(void) {
    while (cin >> N >> M) {
        memset(dist, 0, sizeof(dist));
        for (int x = 1; x <= M; ++x) {
            int i, j;
            cin >> i >> j;
            dist[i][j] = 1;
        }
        cout << floyd() << endl;
    }
    return 0;
}