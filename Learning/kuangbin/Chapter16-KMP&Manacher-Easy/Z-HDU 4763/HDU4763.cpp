#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1e6 + 10;

int N;
char str[maxn];
int nxt[maxn];
void getnxt(int len) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || str[j] == str[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}
bool kmp(char* S, int l1, char* mode, int l2) {
    int i = 0, j = 0;
    while (i < l1) {
        if (j == -1 || S[i] == mode[j]) {
            i++, j++;
        } else j = nxt[j];
        if (j >= l2) return 1;
    }
    return 0;
}

int main(void) {
    scanf("%d", &N);
    while (N--) {
        scanf("%s", str);
        int len = strlen(str);
        getnxt(len);
        int j = nxt[len];
        int ans = 0;
        while (j > 0 && ans == 0) {
            // 前段和后段已经找到, 再去中段寻找, 取最长的即可退出
            if (kmp(str + j, len - 2 * j, str, j)) ans = j;
            j = nxt[j];
        } 
        printf("%d\n", ans);
    }
    return 0;
}