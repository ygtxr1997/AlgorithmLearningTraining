// ---------------------------------------------------------------------
// 题目描述:
// 给定一个数列 A1, A2, ..., AN, 以及 Q 个操作, 按顺序执行这些操作.
// 操作分为两种, 
// 1. 给出 l, r, x, 对 A[l], A[l+1], ..., A[r] 同时加上 x
// 2. 给出 l, r, 求 A[l], A[l+1], ..., A[r] 的和
// ---------------------------------------------------------------------
// 思路一:
// 树状数组(节点维护一段区间的和): 
//          一个元素的值加上x --- O(logN)
//          一段区间求和      --- O(logN)
// 线段树(节点维护一段区间的和):
//          一段区间的元素加上x --- O(NlogN)
//          一段区间求和      --- O(logN)
// 普通的线段树无法在有效时间内解决问题, 所以要修改线段树, 每个节点维护两个值:
// a. 节点对应区间内所有元素共同加上的值
// b. 节点对应区间内所有元素不包括 a 的和
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
typedef long long ll;
const int maxn = 100010; // 100010
const int dat_size = (1 << 18) - 1;

// input
int N, Q; // 数字个数, 操作次数
int A[maxn]; // 数组
char T[maxn]; // opt
int L[maxn], R[maxn], X[maxn]; // a, b, c

// ST
// a. 节点对应区间内所有元素共同加上的值
// b. 节点对应区间内所有元素不包括 a 的和
ll Data[dat_size], Datb[dat_size]; // 维护a值, 维护b值

// 对区间[a, b)加上x
// k:节点编号, l, r:节点对应区间[l, r)
void add(int a, int b, int x, int k, int l, int r) {
    if (a <= l && r <= b) { // [a, b)包含[l, r)
        Data[k] += x;
    } else if (l < b && a < r) { // [a, b)和[l, r)有交集
        Datb[k] += (min(b, r) - max(a, l)) * x;
        add(a, b, x, k * 2 + 1, l, (l + r) / 2);
        add(a, b, x, k * 2 + 2, (l + r) / 2, r);
    }
}

// 计算[a, b)的和
// k:节点编号, l, r:节点对应区间[l, r)
ll sum(int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) { // 无交集
        return 0;
    } else if (a <= l && r <= b) { // [a, b)包含[l, r)
        return Data[k] * (r - l) + Datb[k];
    } else { // 有交集
        ll res = (min(b, r) - max(a, l)) * Data[k]; // 重叠元素个数 * 公共相加值
        res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
        res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
        return res;
    }
}

void solve(void) {
    for (int i = 0; i < N; ++i) {
        add(i, i + 1, A[i], 0, 0, N);
    }

    for (int i = 0; i < Q; ++i) {
        if (T[i] == 'C') {
            add(L[i], R[i] + 1, X[i], 0, 0, N);
        } else if (T[i] == 'Q') {
            printf("%lld\n", sum(L[i], R[i] + 1, 0, 0, N));
        }
    }
}

int main(void) {
    while (scanf("%d%d", &N, &Q) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
        for (int i = 0; i < Q; ++i) {
            getchar();
            scanf("%c ", &T[i]);
            if (T[i] == 'Q') {
                scanf("%d%d", &L[i], &R[i]);
            } else if (T[i] == 'C') {
                scanf("%d%d%d", &L[i], &R[i], &X[i]);
            }
            L[i]--; // 转化为0开始的下标
            R[i]--;
        }
        solve();
    }
    return 0;
}