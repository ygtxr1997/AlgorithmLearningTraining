// ---------------------------------------------------------------------
// 题目描述:
// 用 N 个半径为 R 厘米的球进行如下实验.
// 在 H 米高的位置设置一个圆筒, 将球垂直放入圆筒, 最底下的球底部高度也为 H.
// 实验开始时, 最下面的球开始下落, 此后, 每一秒又有一个球开始掉落.
// 不计空气阻力, 并假设所有碰撞均是弹性碰撞.
// 请求出实验开始后 T 秒钟时每个球底端的高度, 设重力加速度为 g=10m/s^2.
// ---------------------------------------------------------------------
// 思路:
// 类似之前的题目"Ants", 多个球的弹性碰撞可以转化成球互相穿过运动, 避免物理模拟.
// 每个球的可运动最大高度都是H.
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace::std;
const double g = 10.0; // 重力加速度
const int maxn = 103;

int C; // test cases
int N, H, R, T; // 球数, 初始高度, 球半径, 时间

double y[maxn]; // 球的最终位置

// 求出T时刻球的位置
double calc(int T) {
    if (T < 0) return H;
    double t = sqrt(2 * H / g);
    int k = (int)(T / t);
    if (k % 2 == 0) { // 上升周期
        double d = T - k * t;
        return H - g * d * d / 2;
    } else { // 下降周期
        double d = k * t + t - T;
        return H - g * d * d / 2;
    }
}

void solve(void) {
    for (int i = 0; i < N; i++) {
        y[i] = calc(T - i);
    }
    sort(y, y + N);
    for (int i = 0; i < N; ++i) {
        // 注意厘米与米的单位换算
        printf("%.2lf%c", y[i] + 2 * R * i / 100.0, i + 1 == N ? '\n' : ' ');
    }
}

int main(void) {
    scanf("%d", &C);
    while (C--) {
        scanf("%d%d%d%d", &N, &H, &R, &T);
        solve();
    }
    return 0;
}