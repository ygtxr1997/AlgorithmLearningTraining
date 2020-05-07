// ---------------------------------------------------------------------
// 题目描述:
// 给定一个数列 a1, a2, ..., an 和 m 个三元组表示的查询.
// 对于每个查询(i, j, k), 输出ai, ai+1, ..., aj 的升序排列中第 k 个数.
// n<=100000, m<=5000
// |ai|<=1e9
// ---------------------------------------------------------------------
// 思路一:
// 平方分割
// 把数列排序后每 b 个一组放到各个桶里.
// 如果要求某个区间中不超过 x 的元素个数, 可以这样求得:
// 1. 对于完全包含在区间内的桶, 用二分搜索(O((n/b)log(b)))
// 2. 和区间相交但不被包含的桶, 逐个检查桶内元素(O(b))
// 设 b=sqrt(n), 则总复杂度为 O(sqrt(n)*log(n))
// 设 b=sqrt(nlog(n)), 则总复杂度为 O(sqrt(n*log(n)))
// 再加上预处理数组排序的时间O(nlog(n)), 整个算法的复杂度是O(nlog(n)+m√(n)log^(1.5)(n))
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace::std;
const int maxn = 100010;
const int maxm = 5010;
const int B = 1000; // 桶的大小

// input
int N, M;
int A[maxn];
int I[maxm], J[maxm], K[maxm];

int nums[maxn]; // 对 A 排序后的数组
vector<int> bucket[maxn / B]; // 每个桶排序后的结果

// 数据貌似变强了, 平方分割会 TLE
void solve(void) {
    for (int i = 0; i < N; ++i) {
        bucket[i / B].push_back(A[i]);
        nums[i] = A[i];
    }
    sort(nums, nums + N); // 对所有数进行排序
    for (int i = 0; i < N / B; ++i) {
        // 对每个桶分别排序
        sort(bucket[i].begin(), bucket[i].end());
    }

    for (int i = 0; i < M; ++i) {
        // 求 [l, r) 区间的第 k 个数
        int l = I[i], r = J[i] + 1, k = K[i];

        int lb = -1, ub = N - 1;
        while (ub - lb > 1) {
            int md = (lb + ub) / 2;
            int x = nums[md];
            int tl = l, tr = r, c = 0;

            // 两端多余部分
            while (tl < tr && tl % B != 0) if (A[tl++] <= x) c++;
            while (tl < tr && tr % B != 0) if (A[--tr] <= x) c++;

            // 计算每一个桶
            while (tl < tr) {
                int b = tl / B;
                c += upper_bound(bucket[b].begin(), bucket[b].end(), x)
                    - bucket[b].begin();
                tl += B;
            }

            if (c >= k) ub = md;
            else lb = md;
        }

        printf("%d\n", nums[ub]);
    }
}

int main(void) {
    while (scanf("%d%d", &N, &M) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &I[i], &J[i], &K[i]);
            I[i]--; // 转为下标从 0 开始
            J[i]--;
        }
        solve();
    }
    return 0;
}
