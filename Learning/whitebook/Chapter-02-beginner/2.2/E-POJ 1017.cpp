#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 7;

int nums[maxn];

// 贪心, 从大到小放并且尽量保证箱子不能再放下任何物品
int main(void) {
    //freopen("input.txt", "r", stdin);
    while (scanf("%d%d%d%d%d%d", &nums[1], &nums[2], &nums[3], &nums[4], &nums[5], &nums[6])
        && nums[1] + nums[2] + nums[3] + nums[4] + nums[5] + nums[6] != 0) {
        int cnt = nums[6];
        cnt += nums[5];
        nums[1] = max(0, nums[1] - nums[5] * 11);
        cnt += nums[4];
        if (nums[2] >= 5 * nums[4]) nums[2] -= nums[4] * 5;
        else nums[1] = max(0, nums[1] - (5 * nums[4] - nums[2]) * 4), nums[2] = 0;
        cnt += nums[3] / 4 + (nums[3] % 4 == 0 ? 0 : 1);
        nums[3] %= 4;
        if (nums[3] > 0) {
            if (nums[2] >= 7 - 2 * nums[3]) nums[2] -= 7 - 2 * nums[3], nums[1] = max(0, nums[1] - (8 - nums[3]));
            else nums[1] = max(0, nums[1] - (36 - 9 * nums[3] - 4 * nums[2])), nums[2] = 0;
        }
        cnt += nums[2] / 9 + (nums[2] % 9 == 0 ? 0 : 1);
        nums[2] %= 9;
        if (nums[2] > 0) nums[1] = max(0, nums[1] - (36 - nums[2] * 4));
        cnt += nums[1] / 36 + (nums[1] % 36 == 0 ? 0 : 1);
        printf("%d\n", cnt);
    }
    return 0;
}