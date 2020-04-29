#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace::std;
const int maxn = 1010;
const int INF = 0x3f3f3f3f;
typedef struct node {
    node(){}
    node(double x, double y) : left(x), right(y) {}
    bool operator<(const node& n2) const {
        if (left != n2.left) return left < n2.left;
        return right > n2.right;
    }
    double left, right;
} node;
node lines[maxn];

int n, d;
double max_right;

// 以海岛为对象, 求出可覆盖该岛的灯塔所在线段范围, 根据重叠区间判断灯塔数量
// 每次尽量把雷达放在最右边的位置
int solve(void) {
    sort(lines, lines + n);
    int cnt = 1;
    double mx = lines[0].right;
    for (int i = 1; i < n; ++i) {
        if (lines[i].left > mx) { // 之前的雷达不可能覆盖到i, 需要添加新的雷达
            cnt++;
            mx = lines[i].right;
        } else if (lines[i].right < mx) { // 之前的雷达位置太靠右, 需要往左移动才能覆盖i
            mx = lines[i].right;
        }
    }
    return cnt;
}

int main(void) {
    int t = 1;
    //freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &d) && !(n == 0 && d == 0)) {
        bool bDetect = 1;
        max_right = -INF;
        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (bDetect) {
                if (y > d || y < 0 || d < 0) bDetect = 0;
                lines[i].left = x - sqrt((double)d * d - y * y);
                lines[i].right = x + sqrt((double)d * d - y * y);
                max_right = max(max_right, lines[i].right);
            }
        }
        printf("Case %d: ", t++);
        if (!bDetect) printf("-1\n");
        else printf("%d\n", solve());
    }
    return 0;
}