#include <iostream>
#include <queue>
#include <cstring>
using namespace::std;
typedef pair<int, int> pii;

// BFS，筛选素数
int n;
int start, target;
bool visited[10000]; // 辅助数组
int bPrime[10000]; // 0:未知, 1:合数, 2:素数
bool isPrime(int num) {
    if (num % 2 == 0) return false;
    if (bPrime[num] != 0) return bPrime[num] - 1;
    bPrime[num] = 1;
    for (int x = 3; x * x <= num; ++x) { if (num % x == 0) return false; }
    bPrime[num] = 2;
    return true;
}

int solve() {
    int ans = INT_MAX;
    queue<pii> qu;
    qu.push(pii(start, 0));
    visited[start] = 1;
    while (!qu.empty()) {
        int front = qu.front().first, step = qu.front().second;
        if (front == target) { ans = step; break; }
        int next;
        for (int n0 = 1; n0 <= 9; n0 += 2) {
            next = (front / 10) * 10 + n0;
            if (!visited[next] && isPrime(next)) { visited[next] = 1; qu.push(pii(next, step + 1)); }
        }
        for (int n1 = 0; n1 <= 9; n1++) {
            next = (front / 100) * 100 + n1 * 10 + (front % 10);
            if (!visited[next] && isPrime(next)) { visited[next] = 1; qu.push(pii(next, step + 1)); }
        }
        for (int n2 = 0; n2 <= 9; n2++) {
            next = (front / 1000) * 1000 + n2 * 100 + (front % 100);
            if (!visited[next] && isPrime(next)) { visited[next] = 1; qu.push(pii(next, step + 1)); }
        }
        for (int n3 = 1; n3 <= 9; n3++) {
            next = n3 * 1000 + (front % 1000);
            if (!visited[next] && isPrime(next)) { visited[next] = 1; qu.push(pii(next, step + 1)); }
        }
        qu.pop();
    }
    return ans;
}

int main(void) {
    while (cin >> n) {
        for (int k = 0; k < n; ++k) {
            cin >> start >> target;
            memset(visited, 0, sizeof(bool) * 10000);
            memset(bPrime, 0, sizeof(bool) * 10000);
            int res = solve();
            if (res == INT_MAX) cout << "Impossible" << endl;
            else cout << res << endl;
        }
    }
    return 0;
}