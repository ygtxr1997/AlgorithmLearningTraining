#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000050;

// 增加递增限定条件的最长回文子串
int T;
int n;
int h[2 * maxn]; // 身高
int p[2 * maxn]; // 回文子串长度的一半
int manacher(void) {
    int ans = -1;
    for (int i = n; i >= 0; --i) { // 预处理
        h[2 * i + 2] = h[i];
        h[2 * i + 1] = -1;
    }
    h[0] = -2;
    int id, mx = 0;
    for (int i = 1; i < 2 * n + 1; ++i) {
        if (mx > 1) p[i] = min(mx - i, p[2 * id - i]);
        else p[i] = 1;
        if (p[i] == 0) p[i] = 1;
        while ((h[i - p[i]] == h[i + p[i]]) // 只需在这里加一个条件
            && (h[i - p[i]] <= h[i - p[i] + 2])) p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
        ans = max(ans, p[i]);
    }
    return ans - 1;
}
int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &h[i]);
        int ans = manacher();
        printf("%d\n", ans);
    }
    return 0;
}