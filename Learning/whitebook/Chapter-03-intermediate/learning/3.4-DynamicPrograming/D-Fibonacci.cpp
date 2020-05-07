// ---------------------------------------------------------------------
// 题目描述:
// 斐波那契数列
// F0 = 0
// F1 = 1
// F(n+1) = F(n+1) + F(n)
// 求这个数列第 n 项对 10000 取模的结果
// 0 <= n <= 10^16
// ---------------------------------------------------------------------
// 思路:
// 普通的按定义求得方法时间复杂度为O(n), 肯定会超时.
// 设 a = (1+sqrt(5))/2, b = (1-sqrt(5))/2,
// 则 F(n) = 1/sqrt(5) * (a^n - b^n)
// 通项公式的精度不够, 也无法求解.
// 这里用矩阵高效地求出第 n 项的值.
// | F(n+2) |   | 1 1 |   | F(n+1) |
// | F(n+1) | = | 1 0 | * | F(n)   |
// 记这个常数矩阵为 A, 则有
// | F(n+1) |         | F(1) |         | 1 |
// | F(n)   | = A^n * | F(0) | = A^n * | 0 |
// 因此只要求出 A^n 就可以求出 F(n)了, 而 A^n 的求法可以用快速幂运算.
// 时间复杂度为O(log(n)).
// ---------------------------------------------------------------------

// 二维vector表示矩阵
typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;

const int M = 1e4;

// 计算 A*B
mat mul(mat &A, mat &B) {
    mat C(A.size(), vec(B[0].size());
    for (int i = 0; i < A.size(); ++i) {
        for (int k = 0; k < B.size(); k++) {
            for (int j = 0; j < B[0].size(); j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
            }
        }
    }
    return C;
}

// 计算 A^n, 快速幂
mat pow(mat A, ll n) {
    mat B(A.size(), vec(A.size()));
    for (int i = 0; i < A.size(); ++i) {
        B[i][i] = 1;
    }
    while (n > 0) {
        if (n & 1) B = mul(B, A);
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}

// input
ll n;

void solve(void) {
    // 常数矩阵 A
    mat A(2, vec(2));
    A[0][0] = 1, A[0][1] = 1;
    A[1][0] = 1, A[1][1] = 0;
    A = pow(A, n);
    printf("%d\n", A[1][0]);
}