#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxp = 40010;

// 实际上是个最长递增子序列问题
int t;
int p;
int vec[maxp];
int que[maxp];
int tot;
int solve(void) {
    tot = 0;
    for (int i = 0; i < p; ++i) {
        int val = vec[i];
        if (tot == 0) que[tot++] = val;
        else {
            int pos = lower_bound(que, que + tot, val) - que;
            if (pos >= tot) tot++;
            que[pos] = val;
        }
    }
    return tot;
}
int main(void) {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &p);
        for (int i = 0; i < p; ++i) scanf("%d", &vec[i]);
        printf("%d\n", solve());
    }
    return 0;
}