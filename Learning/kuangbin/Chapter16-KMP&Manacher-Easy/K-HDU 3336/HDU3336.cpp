#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 200010;
const int mod = 10007;

int T;
int n;
char str[maxn];
int nxt[maxn];
void getnxt(void) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < n) {
        if (k == -1 || str[j] == str[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        scanf("%s", str);
        getnxt();
        int ans = n % mod;
        for (int i = 1; i <= n; ++i) {
            ans = (ans + (nxt[i] > 0 ? 1 : 0)) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}