#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 30;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;

int T;
char tmp[maxn];
int vec[maxn];
int tot;
// 枚举全排列即可, 两个数的长度尽可能接近
// 10! = 3,628,800‬
int getnum(int i , int j) {
    if (j != i && vec[i] == 0) return INF; // 不能以0开头
    int k = j;
    int res = 0, base = 1;
    while (k >= i) {
        res += vec[k] * base;
        base *= 10;
        k--;
    }
    return res;
}
int solve(void) {
    int res = INF;
    int mid = tot / 2;
    do {
        int n1 = getnum(0, mid - 1), n2 = getnum(mid, tot - 1);
        res = min(res, abs(n1 - n2));
    } while (next_permutation(vec, vec + tot));
    return res;
}

int main(void) {
    scanf("%d", &T);
    getchar(); // 换行
    while (T--) {
        gets(tmp);
        int len = strlen(tmp);
        tot = 0;
        for (int i = 0; i < len; ++i) {
            if (tmp[i] != ' ') vec[tot++] = tmp[i] - '0';
        }
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}