// ---------------------------------------------------------------------
// 题目描述:
// 给定一个数列 a1, a2, ..., an 和 m 个三元组表示的查询.
// 对于每个查询(i, j, k), 输出ai, ai+1, ..., aj 的升序排列中第 k 个数.
// n<=100000, m<=5000
// |ai|<=1e9
// ---------------------------------------------------------------------
// 思路二:
// 线段树
// 线段树的每个节点都保存对应区间排序后的结果, 每个节点保存一个数列.
// 建树的过程和归并排序类似, 复杂度是O(nlog(n)).
// 要计算某个区间内不超过 x 的数的个数, 只需要递归地进行如下操作:
// 1. 如果所给区间与节点对应区间没有交集, 则返回 0 个
// 2. 如果所给区间完全包含节点对应区间, 那么使用二分搜索对该节点保存的数组进行查找
// 3. 否则两个区间有交集, 那么对两个儿子递归地进行计算之后求和即可
// 总时间复杂度是O(nlog(n) + mlog^3(n))
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace::std;
const int maxn = 100010;
const int maxm = 5010;
const int ST_SIZE = (1 << 18) - 1;

// input
int N, M;
int A[maxn];
int I[maxm], J[maxm], K[maxm];

int nums[maxn]; // 对 A 排序后的数组
vector<int> dat[ST_SIZE]; // 线段树的数据

// 构建线段树
void init(int k , int l, int r) {
    if (r - l == 1) {
        dat[k].push_back(A[l]);
    } else {
        int lch = k * 2 + 1, rch = k * 2 + 2;
        init(lch, l, (l + r) / 2);
        init(rch, (l + r) / 2, r);
        dat[k].resize(r - l);
        // STL merge
        merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(),
            dat[k].begin());
    }
}

// 计算[i, j)中不超过 x 的元素个数
int query(int i, int j , int x, int k, int l, int r) {
    if (j <= l || r <= i) { // 不相交
        return 0;
    } else if (i <= l && r <= j) { // 完全包含
        return upper_bound(dat[k].begin(), dat[k].end(), x) - dat[k].begin();
    } else { // 相交
        int lc = query(i, j, x, k * 2 + 1, l, (l + r) / 2);
        int rc = query(i, j, x, k * 2 + 2, (l + r) / 2, r);
        return lc + rc;
    }
}

void solve(void) {
    for (int i = 0; i < N; ++i) nums[i] = A[i];
    sort(nums, nums + N);
    init(0, 0, N);
    for (int i = 0; i < M; ++i) {
        // 查找[l, r)中第k个数
        int l = I[i], r = J[i] + 1, k = K[i];

        int lb = -1, ub = N - 1;
        while (ub - lb > 1) {
            int md = (ub + lb) / 2;
            int c = query(l, r, nums[md], 0, 0, N);
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
