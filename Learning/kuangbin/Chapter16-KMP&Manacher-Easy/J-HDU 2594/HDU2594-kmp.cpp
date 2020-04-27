#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 50010;

char s1[2 * maxn];
char s2[maxn];
int nxt[2 * maxn];
void getnxt(int len) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || s1[j] == s1[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}
void solve(void) {
    int l1 = strlen(s1), l2 = strlen(s2);
    strcat(s1, s2); // 合并s1和s2再求该合并串的next[]数组即可
    int l12 = strlen(s1);
    getnxt(l12);
    int k = nxt[l12];
    if (k == 0) {
        printf("0\n");
        return;
    }
    while (k > l1 || k > l2) k = nxt[k]; // 长度不能超过l1和l2
    s1[k] = '\0';
    printf("%s %d\n", s1, k);
}

int main(void) {
    while (scanf("%s", s1) != EOF) {
        scanf("%s", s2);
        solve();
    }
    return 0;
}