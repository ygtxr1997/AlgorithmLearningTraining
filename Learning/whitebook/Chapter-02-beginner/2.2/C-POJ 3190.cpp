#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace::std;
const int maxn = 50100;
const int INF = 0x3f3f3f3f;
typedef struct node {
    node(){}
    bool operator<(const node& n2) const { // 优先队列使用, 按结束时间排序, 结束时间早的优先
        if (right != n2.right) return right > n2.right;
        return left < n2.left;
    }
    int left, right;
    int ind; // 原始下标
} node;
bool cmp(const node& n1, const node& n2) { // sort使用, 按开始时间排序
    if (n1.left != n2.left) return n1.left < n2.left;
    return n1.right > n2.right;
}
node intervals[maxn];

// 维护优先队列, 结束时间最早的机器在最顶端, 对于牛i, 判断牛i的开始时间是否小于最早结束时间
// 如果小于, 则不需要新的机器, 并且要更新这台机器的结束时间为牛i的结束时间,
// 如果不小于, 则需要新的机器, 并把牛i的结束时间也加入优先队列
int N;
int ans[maxn];
int tot; // 总共需要的机器数
void printans(void) {
    printf("%d\n", tot);
    for (int i = 0; i < N; ++i) {
        printf("%d\n", ans[i]);
    }
}
void solve(void) {
    sort(intervals, intervals + N, cmp);
    priority_queue<node> pqu;
    pqu.push(intervals[0]);
    ans[intervals[0].ind] = pqu.size();
    for (int i = 1; i < N; ++i) {
        if (!pqu.empty() && pqu.top().right < intervals[i].left) { // 不需要增加新的机器
            ans[intervals[i].ind] = ans[pqu.top().ind]; // 使用结束时间最早的那台机器
            pqu.pop();
        } else { // 需要增加新的机器
            ans[intervals[i].ind] = pqu.size() + 1;
        }
        pqu.push(intervals[i]);
    }
    tot = pqu.size();
}

int main(void) {
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &intervals[i].left, &intervals[i].right);
            intervals[i].ind = i;
        }
        solve();
        printans();
    }
    return 0;
}