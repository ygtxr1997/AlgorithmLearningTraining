// ---------------------------------------------------------------------
// 题目描述:
// 桌子上有 n 根木棍, 木棍 i 的两端坐标分别是(pix, piy)和(qix, qiy).
// 给定 m 对木棍(ai, bi), 判断每对木棍是否相连.
// 当木棍有公共点或者通过相连的木棍连在一起, 则视为木棍相连.
// 2 <= n <= 12
// 0 <= pix, piy, qix, qiy <= 100
// 0 <= m <= 10000, 1 <= ai, bi <= n
// ---------------------------------------------------------------------
// 思路:
// 对于向量P1=(x1, y1), P2(x2, y2),
// 定义内积 p1 · p2 = x1x2 + y1y2, 外积 p1 × p2 = x1y2 - x2y1
// 外积为0说明向量共线, 内积<=0说明夹角不为锐角
// 更具体地, 设点q, (p1-q)×(p2-q)=0则说明q在线段p1-p2上,
// (p1-q) · (p2-q)<=0则说明q在p1-p2之间.
// 求直线交点时, 直线p1-p2上的点可以表示为p1+t(p2-p1), 而该点也在q1-q2上, 所以有
// (q2-q1)×(p1+t(p2-p1)-q1)=0.
// 求得 t 的值为:
// p1 + ((q2-q1)×(q1-p1)/(q2-q1)×(p2-p1))(p2-p1)
// 这里还要考虑边界情况, 平行的线段可能也有公共点, 这里通过检查端点是否在另一条线段上来判断.
// ---------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace::std;
const int maxn = 25;

double EPS = 1e-10; // 精度

// 考虑误差的加法运算
double add(double a, double b) {
    if (abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
    return a + b;
}

// 二维向量
struct P {
    double x, y;
    P() {}
    P(double x, double y) : x(x), y(y) {}
    P operator+(P p) { return P(add(x, p.x), add(y, p.y)); }
    P operator-(P p) { return P(add(x, -p.x), add(y, -p.y)); }
    P operator*(double d) { return P(x * d, y * d); } // 数乘
    double dot(P p) { return add(x * p.x, y * p.y); } // 内积
    double det(P p) { return add(x * p.y, -y * p.x); } // 外积
};

// 判断点q是否在线段p1-p2上
bool on_seg(P p1, P p2, P q) {
    // 外积为0, 内积为非正
    return (p1 - q).det(p2 - q) == 0 && (p1 - q).dot(p2 - q) <= 0;
}

// 计算直线p1-p2与直线q1-q2的交点
P intersection(P p1, P p2, P q1, P q2) {
    return p1 + (p2 - p1) * ((q2 - q1).det(q1 - p1) / (q2 - q1).det(p2 - p1));
}

// input
int n;
P p[maxn], q[maxn];

bool g[maxn][maxn]; // 相连关系图

void solve() {
    for (int i = 0; i < n; ++i) {
        g[i][i] = 1;
        for (int j = 0; j < i; ++j) {
            // 判断木棍是否有公共点
            if ((p[i] - q[i]).det(p[j] - q[j]) == 0) {
                // 平行
                g[i][j] = g[j][i] = on_seg(p[i], q[i], p[j])
                                    || on_seg(p[i], q[i], q[j])
                                    || on_seg(p[j], q[j], p[i])
                                    || on_seg(p[j], q[j], q[i]);
            } else {
                // 不平行
                P r = intersection(p[i], q[i], p[j], q[j]);
                g[i][j] = g[j][i] = on_seg(p[i], q[i], r) && on_seg(p[j], q[j], r);
            }
        }
    }
    // Floyd
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                g[i][j] |= g[i][k] && g[k][j];
            }
        }
    }
}

int main(void) {
    while (scanf("%d", &n) && n != 0) {
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            p[i] = P(x1, y1);
            q[i] = P(x2, y2);
        }
        solve();
        int a, b;
        while (scanf("%d%d", &a, &b) && a + b) {
            if (g[a - 1][b - 1]) printf("CONNECTED\n");
            else printf("NOT CONNECTED\n");
        }
    }
}