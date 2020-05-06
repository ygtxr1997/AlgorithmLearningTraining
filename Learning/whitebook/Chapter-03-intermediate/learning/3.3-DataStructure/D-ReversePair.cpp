// 用树状数组求逆序对
typedef long long ll;

// input
int n, a[MAX_N];

// BIT
int bit[MAX_N + 1];

// BIT-init
void init(void) {
    memset(bit, 0, sizeof(bit));
}

// BIT-sum
int sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i; // 或 i = i & (i - 1), 将最右边的 1 变成 0
    }
    return s;
}

// BIT-add
void add(int i, int x) {
    while (i <= n) {
        bit[i] += x;
        i += i & -i; // 设最右边有 d 个 0, 增加 2^d
    }
}

// 计算逆序数
void solve(void) {
    ll ans = 0;
    for (int j = 0; j < n; ++j) {
        ans += j - sum(a[j]); // a[j]前面的数字个数 - a[j]前面比它小的数 = 逆序数
        add(a[j], 1); // 出现过的值就设为1, 未出现过的依旧是0
    }
    printf("%lld\n", ans);
}
