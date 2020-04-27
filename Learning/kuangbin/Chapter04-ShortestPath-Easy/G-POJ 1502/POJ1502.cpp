#include <iostream>
#include <vector>
#include <cstring>
using namespace::std;
#define INF 0x7f7f7f7f
const int maxn = 102;

// 这题就恶心在输入上面
int n; // 1 <= n <= 100
int A[maxn][maxn];
bool visited[maxn]; // 已得到结果的
int least[maxn]; // 1到k的最短距离
int dijkstra(void) {
    int ans = 0;
    int last_index = 1; // 上一轮最小的
    least[1] = 0; visited[1] = 1;
    for (int time = 1; time < n; ++time) {
        int cur_index, cur_min = INF; // 当前最小的
        for (int k = 2; k <= n; ++k) {
            if (visited[k] == 0 && A[last_index][k] != INF) {
                least[k] = min(least[k], A[last_index][k] + least[last_index]);
                if (least[k] < cur_min) {
                    cur_min = least[k];
                    cur_index = k;
                }
            }
        }
        visited[cur_index] = 1;
        last_index = cur_index;
        if (least[cur_index] > ans) ans = least[cur_index];
    }
    return ans;
}

int main(void) {
    while (cin >> n) {
        memset(visited, 0, sizeof(visited));
        memset(least, 0x7f, sizeof(least));
        memset(A, 0, sizeof(A));
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                char tmp[maxn];
                scanf("%s", tmp);
                if (tmp[0] == 'x') A[i][j] = A[j][i] = INF;
                else A[i][j] = A[j][i] = atoi(tmp);
            }
        }
        cout << dijkstra() << endl;
    }
    return 0;
}
