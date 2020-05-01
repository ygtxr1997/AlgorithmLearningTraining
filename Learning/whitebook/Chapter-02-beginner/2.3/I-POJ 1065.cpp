#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 5010;
const int INF = 0x3f3f3f3f;

int T;
int n;
typedef struct node {
    bool operator<(const node& n2) const {
        if (l != n2.l) return l < n2.l;
        return w <= n2.w;
    }
    int l, w;
} node;
node sticks[maxn];
int que[maxn]; // que[i]:长度为i的最长递增子序列的最大值
int tot; // 队列长度

// 先把l按照从小到大排序, 再根据w计算最长递减子序列, 该长度就是最终答案
// 可以用队列二分优化版, 还可以转化为负数然后求最长递增子序列
int solve(void) {
    sort(sticks, sticks + n);
    tot = 0;
    for (int i = 0; i < n; ++i) {
        int val = -sticks[i].w; // 转化为负数处理
        if (tot == 0) {
            que[tot++] = val;
        } else {
            int pos = lower_bound(que, que + tot, val) - que;
            if (pos >= tot) tot++;
            que[pos] = val;
        }
    }
    return tot;
}
int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &sticks[i].l, &sticks[i].w);
        }
        printf("%d\n", solve());
    }
    return 0;
}