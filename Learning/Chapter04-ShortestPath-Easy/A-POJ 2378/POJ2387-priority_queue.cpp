#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#define INF 0x7f7f7f7f
using namespace::std;
typedef pair<int, int> pii;

// 使用优先队列优化dijkstra算法
int N, T; // 2 <= N <= 1000, 1 <= T <= 2000
vector<vector<pii>> table(1002, vector<pii>(0)); // [point][<dist, point>]
int least[1002]; // 1到各边的最短距离
bool visited[1002] = { 0 }; // 已经得到最小值的节点
int solve() {
    priority_queue<pii> pqu; // <dist, point>,存dist的相反数，最小的dist会在顶部
    pqu.push(pii(0, 1));
    while (!pqu.empty()) {
        // 每次最小的dist会自动浮上来
        int dist = pqu.top().first, point = pqu.top().second;
        pqu.pop();
        if (visited[point] == 1) continue;
        visited[point] = 1;
        least[point] = -dist;
        if (point == N) return least[point];
        for (int k = 0; k < table[point].size(); ++k) {
            pqu.push(pii(table[point][k].first + dist, table[point][k].second));
        }
    }
    return least[N];
}

int main(void) {
    while (cin >> T >> N) {
        memset(least, 0x7f, sizeof(int) * 1002); // 0x3f3f3f3f:∞
        for (int t = 1; t <= T; ++t) {
            int p1, p2, d12;
            cin >> p1 >> p2 >> d12;
            // 不是简单图，两个节点之间可能有多条边
            table[p1].push_back(pii(-d12, p2));
            table[p2].push_back(pii(-d12, p1));
        }
        cout << solve() << endl;
        vector<vector<pii>>(1002, vector<pii>(0)).swap(table);
        memset(visited, 0, sizeof(bool) * 1002);
    }
    return 0;
}