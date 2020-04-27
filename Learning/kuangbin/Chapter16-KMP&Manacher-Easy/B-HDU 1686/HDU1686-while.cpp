#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000010;
const int maxm = 10010;

int c;
char W[maxm];
char T[maxn];
int Next[maxm];
void getNext(void) {
    memset(Next, 0, sizeof(Next));
    Next[0] = -1;
    int m = strlen(W);
    int i = 0, k = -1;
    while (i < m) {
        if (k == -1 || W[k] == W[i]) {
            k++, i++;
            Next[i] = k;
        } else k = Next[k];
    }
}
int kmp(void) {
    int cnt = 0;
    int m = strlen(W), n = strlen(T);
    getNext();
    int i = 0, j = 0;
    while (i < n) {
        if (j == -1 || T[i] == W[j]) i++, j++;
        else j = Next[j];
        if (j >= m) j = Next[j], cnt++;
    }
    return cnt;
}

int main(void) {
    scanf("%d",&c);
    while (c--) {
        scanf("%s", W);
        scanf("%s", T);
        printf("%d\n", kmp());
    }
    return 0;
}