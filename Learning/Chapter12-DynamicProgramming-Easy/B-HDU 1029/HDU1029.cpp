#include <iostream>
#include <cstring>
#define TEST
using namespace::std;
const int maxn = 1000010;

int N;
int vec[maxn];

int solve(void) {
    int ans = vec[1], cnt = 1; // 前i个数中出现次数最多的那个数以及它的出现次数
    for (int i = 2; i < N; ++i) {
        if (vec[i] == ans) cnt++;
        else {
            cnt--;
            if (cnt == 0) ans = vec[i + 1];
        }
    }
    return ans;
}

int main(void) {
    #ifdef TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    while (scanf("%d", &N) != EOF) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &vec[i]);
        }
        printf("%d\n", solve());
    }
    return 0;
}