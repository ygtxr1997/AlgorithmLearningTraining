#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000010;

int N;
char str[maxn];
int nxt[maxn];
void getNxt(int len) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || str[j] == str[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}
void solve(void) {
    int len = strlen(str);
    getNxt(len);
    for (int i = 1; i <= len; ++i) {
        if (nxt[i] == 0) continue; // 循环节为1
        int cyc = i - nxt[i]; // 1~i的前缀字符串的循环节长度
        if (i % cyc == 0) { // 恰好有整数个循环节
            printf("%d %d\n", i, i / cyc); // 总长度, 循环节个数
        }
    }
    printf("\n");
}

int main(void) {
    int t = 1;
    while (scanf("%d", &N) && N != 0) {
        scanf("%s", str);
        printf("Test case #%d\n", t++);
        solve();
    }
    return 0;
}