// ---------------------------------------------------------------------
// 题目描述:
// 给定 n*n 的矩阵 A 和正整数 k 和 m. 求矩阵 A 的幂的和.
// S = A + A^2 + ... + A^k
// 输出 S 的各元素对 M 取模后的答案.
// 1 <= n <= 30
// 1 <= k <= 1e9
// 1 <= M <= 1e4
// ---------------------------------------------------------------------
// 思路:
// n*n 的矩阵的 k 次幂通过快速幂可以在 O(n^3 * log(k)) 的时间内求出.
// 但是本题求的不是 k 次幂而是累乘和.如果按顺序逐个加起来, 复杂度为O(n^3*k).
// 设 I 为 n*n 的单位矩阵, S(k) = I + A + ... + A^(k-1),
// 则有
//     | A^k  |   | A 0 |   | A^(k-1) |    | A 0 |      | I |
//     | S(k) | = | I I | * | S(k-1)  | = (| I I |)^k * | 0 |
// 这样就可以在O(n^3 * log(k))时间内求出了.
// ---------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace::std;

// 二维vector表示矩阵
typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;

// input
int n, k, M;
mat A;

// 计算 A*B
mat mul(mat &A, mat &B) {
    mat C(A.size(), vec(B[0].size()));
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

void solve(void) {
    mat B(n * 2, vec(n * 2));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B[i][j] = A[i][j];
        }
        B[n + i][i] = B[n + i][n + i] = 1;
    }
    B = pow(B, k + 1);
    // 只取左下角
    for (int i = 0; i < n; ++i) {
        for (int j = 0;j < n; ++j) {
            int a = B[n + i][j] % M;
            // 减去 I
            if (i == j) a = (a + M - 1) % M;
            printf("%d%c", a, j + 1 == n ? '\n' : ' ');
        }
    }
}

int main(void) {
    scanf("%d%d%d", &n, &k, &M);
    A.resize(n);
    for (int i = 0; i < n; ++i) {
        A[i].resize(n);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &A[i][j]);
        }
    }
    solve();
    return 0;
}