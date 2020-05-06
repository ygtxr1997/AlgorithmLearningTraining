// 树状数组 BIT 的实现
// 树状数组相当于去掉了线段树的所有右子节点

// [1, n]
int bit[MAX_N + 1], n;

// 计算 [1, i] 的和
int sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i; // 或 i = i & (i - 1), 将最右边的 1 变成 0
    }
    return s;
}

// 将第 i 个元素(1 <= i <= n)的值增加 x
void add(int i , int x) {
    while (i <= n) {
        bit[i] += x;
        i += i & -1; // 设最右边有 d 个 0, 增加 2^d
    }
}
