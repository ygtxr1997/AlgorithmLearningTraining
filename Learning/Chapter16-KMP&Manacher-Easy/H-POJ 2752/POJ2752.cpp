#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 400010;

char str[maxn];
int nxt[maxn];
void printAns(int i) { // 升序打印
    if (i == 0) return;
    printAns(nxt[i]);
    printf("%d ", i);
}
void getnxt(int len) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == - 1 || str[k] == str[j]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
    printAns(len);
    printf("\n");
}
int main(void) {
    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        getnxt(len);
    }
    return 0;
}