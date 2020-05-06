// 线段树的区间最小值实现
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;

const int maxn = 1 << 17;
const int INF = 0x3f3f3f3f;

// 存储线段树的全局数组
int n, dat[2 * maxn - 1];

// 初始化
void init(int n_) {
    // 把元素个数扩大为2的幂
    n = 1;
    while (n < n_) n *= 2;

    // 初值均设为无穷大
    memset(dat, 0x3f, sizeof(dat));
}

// 把第k个值更新为a
void update(int k, int a) {
    // 叶子节点
    k += n - 1;
    dat[k] = a;
    // 向上更新
    while (k > 0) {
        k = (k - 1) / 2; // 父节点
        dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]); // 子节点
    }
}

// 求[a, b)区间的最小值
// k:树节点编号, l,r:节点对应的区间是[l,r)
// 外部调用:query(a, b, 0, 0, n)
int query(int a, int b, int k, int l, int r) {
    printf("a=%d, b=%d, k=%d, l=%d, r=%d\n", a, b, k, l, r);
    // 如果[a, b)和[l, r)不相交则返回INF
    if (r <= a || b <= l) return INF;
    // 如果[a, b)完全包含[l, r), 则返回当前节点的值
    if (a <= l && r <= b) return dat[k];
    else {
        // 递归查询, 返回两个儿子中值的较小者
        int v1 = query(a, b, k * 2 + 1, l, (l + r) / 2);
        int v2 = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(v1, v2);
    }
}

void printDat(void) {
    for (int i = 0; i < 2 * n - 1; ++i) printf("%d ", dat[i]);
    printf("\n");
}

int main(void) {
    int arr[5] = {5, 3, 7, 9, 1};
    init(5);
    for (int i = 0; i < 5; ++i) {
        update(i, arr[i]);
    }
    printf("res = %d\n", query(1, 5, 0, 0, n));
    return 0;
}