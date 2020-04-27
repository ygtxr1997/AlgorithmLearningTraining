#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace::std;
const int maxn = 64 * 1024;

int nxt[5] = {-1, 0, 0, 0, 0}; // 手动计算doge的next[]
char str[maxn];
char mode[5] = "doge";
void getnxt(void) {}
int kmp(void) {
    int cnt = 0;
    int l1 = strlen(str), l2 = strlen(mode);
    int i = 0, j = 0;
    int dif = 'a' - 'A'; // 大小写不敏感
    while (i < l1) {
        if (j == -1 || str[i] == mode[j] || str[i] == mode[j] - dif || str[i] == mode[j] + dif) {
            i++, j++;
        } else j = nxt[j];
        if (j >= l2) {
            j = nxt[j];
            cnt++;
        }
    }
    return cnt;
}

int main(void) {
    int cnt = 0;
    //freopen("input.txt", "r", stdin);
    while (gets(str)) {
        cnt += kmp();
    }
    printf("%d\n", cnt);
    return 0;
}