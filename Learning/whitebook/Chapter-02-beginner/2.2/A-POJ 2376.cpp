#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 25010;
const int maxt = 1000010;
typedef struct node {
    node(){}
    node(int x, int y) : left(x), right(y) {}
    bool operator<(const node& n2) const { 
        if (left != n2.left) return left < n2.left; 
        return right > n2.right;
    }
    int left, right;
} node;
node times[maxn];

int N, T;

int solve(void) {
    sort(times, times + N); // 按照开始时间排序
    // 贪心
    if (times[0].left != 1) return -1;
    int cnt = 1;
    int id = 0, mx = times[0].right;
    while (mx < T) {
        int last_mx = mx;
        // 找到范围内结束时间最晚的
        for (int i = id + 1; times[i].left <= last_mx + 1; i++) {
            if (mx < times[i].right) {
                mx = times[i].right;
                id = i;
            }
        }
        if (mx == last_mx) return -1; // 没有找到更大的
        cnt++;
    }
    return cnt;
}

int main(void) {
    scanf("%d%d", &N, &T);
    for (int i = 0; i < N; ++i) scanf("%d%d", &times[i].left, &times[i].right);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}