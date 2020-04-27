#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 100010;

int T;
char str[maxn]; // 下标从0开始
int nxt[maxn]; // 部分匹配值偏移后得到next数组
// 根据部分匹配求循环节的长度
void getnxt(void) {
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = -1;
    int n = strlen(str);
    int j = 0, k = -1;
    while (j < n) {
        if (k == -1 || str[k] == str[j]) {
            j++, k++;
            nxt[j] = k; 
        } else k = nxt[k];
    }
}

int main(void) {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%s", str); // 下标从0开始
        int n = strlen(str);
        getnxt();
        int cyc = n - nxt[n]; // 循环节长度
        if (nxt[n] == 0) printf("%d\n", n); // 循环节为1
        else if (n % cyc == 0) printf("0\n"); // 恰好有整数个循环节
        else printf("%d\n", cyc - (n % cyc)); // 最后一个循环节需要补齐
    }
    return 0;
}