#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;

char Big[maxn];
char Small[maxn];
int nxt[maxn];
void getNxt(void) {
    memset(nxt, 0, sizeof(nxt));
    int m = strlen(Small);
    int j = 0, k = -1;
    nxt[0] = -1;
    while (j < m) {
        if (k == -1 || Small[k] == Small[j]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}

int kmp(void) {
    getNxt();
    int n = strlen(Big), m = strlen(Small);
    int i = 0, j = 0;
    int cnt = 0;
    while (i < n) {
        if (j == -1 || Big[i] == Small[j]) i++, j++;
        else j = nxt[j];
        if (j >= m) cnt++, j = 0;
    }
    return cnt;
}

int main(void) {
    while (scanf("%s", Big) && (Big[0] != '#' && strlen(Big) != 1)) {
        scanf("%s", Small);
        printf("%d\n", kmp());
    }
    return 0;
}