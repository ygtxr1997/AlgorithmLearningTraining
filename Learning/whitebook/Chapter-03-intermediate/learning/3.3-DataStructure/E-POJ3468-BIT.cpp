// ---------------------------------------------------------------------
// 题目描述:
// 给定一个数列 A1, A2, ..., AN, 以及 Q 个操作, 按顺序执行这些操作.
// 操作分为两种, 
// 1. 给出 l, r, x, 对 A[l], A[l+1], ..., A[r] 同时加上 x
// 2. 给出 l, r, 求 A[l], A[l+1], ..., A[r] 的和
// ---------------------------------------------------------------------
// 思路二:
// 树状数组也可以像线段树那样每个节点维护两个数据.
// 如果给区间[l, r)同时加上 x 的话, 每个节点的值会如何变化呢?
// 不妨设 
//          s(i) =  加上 x 之前的前缀和 Σ(j=1, i)aj
//         s'(i) =  加上 x 之后的前缀和 Σ(j=1, i)aj
// 那么就有
//           i<l => s'(i)=s(i)
//       l<=i<=r => s'(i)=s(i)+x*(i-l+1)
//                       =s(i)+x*i-x*(l-1)
//           r<i => s'(i)=s(i)+x*(r-l+1)
// 下面记 sum(bit, i) 为树状数组 bit 的前 i 项和.
// 构建两个树状数组 bit0(不包含公共和), bit1(包含公共和), 并且设
//      前缀和 Σ(j=1, i)aj = sum(bit1, i)*i + sum(bit0, i)
// 那么在[l,r]区间同时加上x可以看成:
// 1. 在 bit0 的 l 位置加上 -x(l-1)
// 2. 在 bit1 的 l 位置加上 x
// 3. 在 bit0 的 r+1 位置加上 xr
// 4. 在 bit1 的 r+1 位置加上 -x
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
typedef long long ll;
const int maxn = 100010; // 100010

// input
int N, Q; // 数字个数, 操作次数
int A[maxn]; // 数组
char T[maxn]; // opt
int L[maxn], R[maxn], X[maxn]; // a, b, c

// BIT
// 下标从1开始
ll bit0[maxn], bit1[maxn];

// bitx 的前 i 项和
ll sum(ll *b, int i) {
    ll s = 0;
    while (i > 0) {
        s += b[i];
        i -= i & -i;
    }
    return s;
}

// bitx 的第 i 项加 v
void add(ll *b, int i, int v) {
    while (i <= N) {
        b[i] += v;
        i += i & -i;
    }
}

void solve(void) {
    for (int i = 1; i <= N; ++i) {
        add(bit0, i, A[i]);
    }

    for (int i = 0; i < Q; ++i) {
        if (T[i] == 'C') {
            add(bit0, L[i], -X[i] * (L[i] - 1));
            add(bit1, L[i], X[i]);
            add(bit0, R[i] + 1, X[i] * R[i]);
            add(bit1, R[i] + 1, -X[i]);
        } else if (T[i] == 'Q') {
            ll res = 0;
            res += sum(bit0, R[i]) + sum(bit1, R[i]) * R[i];
            res -= sum(bit0, L[i] - 1) + sum(bit1, L[i] - 1) * (L[i] - 1);
            printf("%lld\n", res);
        }
    }
}

int main(void) {
    while (scanf("%d%d", &N, &Q) != EOF) {
        // BIT 要求下标都从 1 开始
        for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
        for (int i = 0; i < Q; ++i) {
            getchar();
            scanf("%c ", &T[i]);
            if (T[i] == 'Q') {
                scanf("%d%d", &L[i], &R[i]);
            } else if (T[i] == 'C') {
                scanf("%d%d%d", &L[i], &R[i], &X[i]);
            }
        }
        solve();
    }
    return 0;
}