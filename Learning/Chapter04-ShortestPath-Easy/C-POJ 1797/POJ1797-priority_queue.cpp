#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
const long long INF =  0x3f3f3f3f;
using namespace::std;
typedef pair<int, int> pii;
typedef long long ll;

// O(n^3)会超时，考虑用优先队列优化，配合longlong位操作保存pair，最快还是1600ms
int T;
int n, m; // 1 <= n <= 1000, n个点, m条边
pii table[1001][1001]; // [point][index]=point|weight
bool visited[1001]; // 已经得到最大容量的点
int most[1001]; // 从1出发到x的最大负重
int dijkstra(void) {
    priority_queue<long long> pqu; // weight|point 
    pqu.push((INF << 32) + 1);
    while (!pqu.empty()) {
        long long weightv = pqu.top() >> 32, pointv = (pqu.top() << 32) >> 32;
        pqu.pop();
        if (visited[pointv]) continue;
        visited[pointv] = 1;
        most[pointv] = weightv;
        if (pointv == n) return weightv;
        for (int x = table[pointv][0].first; x >= 1; --x) {
            long long weightvx = table[pointv][x].second, pointx = table[pointv][x].first;
            long long newweight = most[pointv] < weightvx ? most[pointv] : weightvx;
            pqu.push((newweight << 32) + pointx);
        }
    }
    return most[n];
}

int main(void) {
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        memset(table, 0, sizeof(ll) * 1001 * 1001);
        memset(visited, 0, sizeof(visited));
        memset(most, 0, sizeof(most));
        cin >> n >> m;
        for (int i = 1; i <= m; ++i) {
            ll x, y, dxy;
            cin >> x >> y >> dxy;
            table[x][0].first++; table[x][table[x][0].first] = pii(y, dxy);
            table[y][0].first++; table[y][table[y][0].first] = pii(x, dxy);
        }
        int ans = dijkstra();
        printf("Scenario #%d:\n", t);
        printf("%d\n\n", ans);
    }
    return 0;
}