#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace::std;
const int maxn = 110;

int N;
int nums[maxn];

// 求最小重量
// 越先融合的就要开更多根号, 所以把最大的先融合
int main(void) {
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &nums[i]);
        sort(nums, nums + N);
        reverse(nums, nums + N);
        double res = nums[0];
        for (int i = 1; i < N; ++i) {
            res = 2 * sqrt(res * nums[i]);
        }
        printf("%.3lf\n", res);
    }
    return 0;
}