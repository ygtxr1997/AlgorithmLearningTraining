#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 12;

int N, final;
int nums[maxn];
// 数据量小, 枚举全排列即可
int getsum(void) {
    int tmp[maxn];
    int size = N;
    memcpy(tmp, nums, sizeof(tmp));
    while (size >= 2) {
        for (int i = 1; i < size; ++i) {
            tmp[i] = tmp[i] + tmp[i + 1];
        }
        size--;
    }
    return tmp[1];
}
void solve(void) {
    do {
        if (getsum() == final) break;
    } while (next_permutation(nums + 1, nums + N + 1));
}

int main(void) {
    while (scanf("%d%d", &N, &final) != EOF) {
        for (int i = 1; i <= N; ++i) nums[i] = i;
        solve();
        for (int i = 1; i <= N; ++i) {
            printf("%d", nums[i]);
            if (i < N) printf(" ");
            else printf("\n");
        }
    }
    return 0;
}