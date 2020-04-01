#include <iostream>
#include <vector>
#include <queue>
using namespace::std;
typedef pair<int, int> pii;

// BFS，并用dp[]辅助保存已经得到最短步数的节点
int N, K;
int bfs(void) {
    if (N >= K) return N - K;
    int ans = INT_MAX;
    vector<int> dp(100001, INT_MAX);
    queue<pii> qu; // <pos, step>
    qu.push(pii(N, 0));
    dp[N] = 0;
    while (!qu.empty()) {
        int pos = qu.front().first, step = qu.front().second;
        if (pos == K) { ans = step; break; }
        if (pos + 1 <= 100000 && dp[pos + 1] == INT_MAX) { qu.push(pii(pos + 1, step + 1)); dp[pos + 1] = step + 1; }
        if (pos - 1 >= 0 && dp[pos - 1] == INT_MAX) { qu.push(pii(pos - 1, step + 1)); dp[pos - 1] = step + 1; }
        if (pos * 2 <= 100000 && dp[pos * 2] == INT_MAX) { qu.push(pii(pos * 2, step + 1)); dp[pos * 2] = step + 1; }
        qu.pop();
    }
    return ans;
}

int main(void) {
    while (cin >> N >> K) {
        int ans = bfs();
        cout << ans << endl;
    }
}