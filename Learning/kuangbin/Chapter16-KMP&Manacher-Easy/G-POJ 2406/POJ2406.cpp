#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000010;

char str[maxn];
int nxt[maxn];
void getnxt(int len) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || str[k] == str[j]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}

int main(void) {
    while (scanf("%s", str)) {
        int len = strlen(str);
        if (len == 1 && str[0] == '.') break;
        getnxt(len);
        int cyc = len - nxt[len]; // 循环节长度
        if (len % cyc == 0)
            printf("%d\n", len / cyc); // 循环节个数
        else printf("%d\n", 1); // 不能整除
    }
    return 0;
}
