#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000100;

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
    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        getnxt(len);
        int cyc = len - nxt[len]; // 循环节长度
        printf("%d\n", cyc);
    }
    return 0;
}