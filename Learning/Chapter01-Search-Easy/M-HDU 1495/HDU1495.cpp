#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace::std;
typedef pair<int, int> pii;
typedef pair<pii, pii> piiii;

// 读清题意，不允许在平均分配前把可乐喝掉
//  i, j, k
int S, N, M;
bool visited[101][101][101]; // 保存三个杯子的访问状态
pii pour(int i, int j, int k, int op) {
    int cur_a, cur_b, max_b, res_a, res_b; // a->b
    if (op == 1) { // 1. i->j
        cur_a = i; cur_b = j; max_b = N;
    } else if (op == 2) { // 2. i->k
        cur_a = i; cur_b = k; max_b = M;
    } else if (op == 3) { // 3. j->k
        cur_a = j; cur_b = k; max_b = M; 
    } else if (op == 4) { // 4. k->j
        cur_a = k; cur_b = j; max_b = N;
    } else if (op == 5) { // 5. j->i
        cur_a = j; cur_b = i; max_b = S;
    } else if (op == 6) { // 6. k->i
        cur_a = k; cur_b = i; max_b = S;
    }
    if (cur_a + cur_b >= max_b) { res_a = (cur_a + cur_b - max_b); res_b = max_b; }
    else { res_a = 0; res_b = cur_a + cur_b; }
    return pii(res_a, res_b);
}
int bfs(void) {
    queue<piiii> qu; // <<S, N>, <M, step>>
    qu.push(piiii(pii(S, 0), pii(0, 0)));
    visited[S][0][0] = 1;
    int full = 0;
    while (!qu.empty()) {
        int i = qu.front().first.first, j = qu.front().first.second,
            k = qu.front().second.first, step = qu.front().second.second;
        if (2 * i == S || 2 * j == S || 2 * k == S) { if (full++ == 2) return step; }
        pii res;
        int n_i, n_j, n_k;
        // 1. i->j
        res = pour(i, j, k, 1); 
        n_i = res.first, n_j = res.second, n_k = k;
        if (visited[n_i][n_j][k] == 0) { visited[n_i][n_j][k] = 1; qu.push(piiii(pii(n_i, n_j), pii(n_k, step + 1))); }
        // 2. i->k
        res = pour(i, j, k, 2);
        n_i = res.first, n_j = j, n_k = res.second;
        if (visited[n_i][n_j][k] == 0) { visited[n_i][n_j][k] = 1; qu.push(piiii(pii(n_i, n_j), pii(n_k, step + 1))); }
        // 3. j->k
        res = pour(i, j, k, 3);
        n_i = i, n_j = res.first, n_k = res.second;
        if (visited[n_i][n_j][k] == 0) { visited[n_i][n_j][k] = 1; qu.push(piiii(pii(n_i, n_j), pii(n_k, step + 1))); }
        // 4. k->j
        res = pour(i, j, k, 4);
        n_i = i, n_j = res.second, n_k = res.first;
        if (visited[n_i][n_j][k] == 0) { visited[n_i][n_j][k] = 1; qu.push(piiii(pii(n_i, n_j), pii(n_k, step + 1))); }
        // 5. j->i
        res = pour(i, j, k, 5);
        n_i = res.second, n_j = res.first, n_k = k;
        if (visited[n_i][n_j][k] == 0) { visited[n_i][n_j][k] = 1; qu.push(piiii(pii(n_i, n_j), pii(n_k, step + 1))); }
        // 6. k->i
        res = pour(i, j, k, 6);
        n_i = res.second, n_j = j, n_k = res.first;
        if (visited[n_i][n_j][k] == 0) { visited[n_i][n_j][k] = 1; qu.push(piiii(pii(n_i, n_j), pii(n_k, step + 1))); }
        qu.pop();
    }
    return -1;
}

int main(void) {
    while ((cin >> S >> N >> M) && (S + M + N) != 0) {
        memset(visited, 0, sizeof(bool) * 101 * 101 * 101);
        int ans = bfs();
        if (ans == -1) cout << "NO" << endl;
        else cout << ans << endl;
    }
    return 0;
}