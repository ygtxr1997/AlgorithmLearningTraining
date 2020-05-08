// ---------------------------------------------------------------------
// 题目描述:
// 给定 N 个方块排成一列, 用红蓝绿黄四种颜色的油漆给方块染色.
// 求染成红色的方块和染成绿色的方块的个数同时为偶数的染色方案的个数.
// 输出对 1e4+7 求模后的答案.
// 1 <= N <= 10^9
// ---------------------------------------------------------------------
// 思路:
// 从左到右染色, 染到第 i 个方块.
// 此时红绿都是偶数的方案数为 ai,
// 红绿恰有一个偶数的方案数为 bi,
// 红绿都是奇数的方案数为 ci.
// 这样, 染到第 i+1 个方块为止, 红绿都是偶数的方案数有如下两种可能:
// 1. 到第 i 个方块, 红绿都是偶数, 并且 i+1 个方块染成了蓝色或者绿色
// 2. 到第 i 个方块, 红绿恰有一个是奇数, 并且 i+1 个方块染成了奇数个对应的颜色
// 所以可得到递推式,
// a(i+1) = 2 * a(i) + b(i)
// b(i+1) = 2 * a(i) + 2 * b(i) + 2 * c(i)
// c(i+1) = b(i) + 2 * c(i)
// 矩阵表示如下,
// | a(i+1) |   | 2 1 0 |   | a(i) |
// | b(i+1) | = | 2 2 2 | * | b(i) |
// | c(i+1) |   | 0 1 2 |   | c(i) |
// 因此得到,
// | a(i) |    | 2 1 0 |      | 1 |
// | b(i) | = (| 2 2 2 |)^i * | 0 |
// | c(i) |    | 0 1 2 |      | 0 |
// 再用快速幂运算即可求得答案
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

const int M = 1e4 + 7;

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

// input
int N;

void solve() {
    mat A(3, vec(3));
    A[0][0] = 2; A[0][1] = 1; A[0][2] = 0;
    A[1][0] = 2; A[1][1] = 2; A[1][2] = 2;
    A[2][0] = 0; A[2][1] = 1; A[2][2] = 2;
    A = pow(A, N);
    printf("%d\n", A[0][0]);
}

int main(void) {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        solve();
    }
    return 0;
}