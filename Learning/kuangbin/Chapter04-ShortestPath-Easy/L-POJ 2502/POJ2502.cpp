#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace::std;
const double INF = 100000000.0;
const int maxn = 310;
typedef struct pos {
    pos(){}
    pos(int x1, double y1) : x(x1), y(y1) {}
    pos& operator=(const pos& p2) { x = p2.x; y = p2.y; return *this; }
    int x, y;
} pos;

pos coord[maxn]; // 坐标, coord[0]=home, coord[1]=school
double dist[maxn][maxn]; // 邻接矩阵
double least[maxn]; // 最短时间
bool visited[maxn]; // 已得到最小值的
int N; // 总节点数
inline double getDist(int p1, int p2) {
    return sqrt(((double)coord[p1].x - coord[p2].x) * ((double)coord[p1].x - coord[p2].x)
                + ((double)coord[p1].y - coord[p2].y) * ((double)coord[p1].y - coord[p2].y));
}
// 朴素dijkstra, 还是用标准写法吧。。。。
double dijkstra(void) {
    int last_index = 0;
    least[0] = 0; visited[0] = 1;
    for (int i = 1; i < N; ++i) {
        least[i] = dist[0][i]; // 初始化
    }
    for (int time = 1; time < N; ++time) {
        double cur_min = INF; // 找到最小值节点
        for (int i = 1; i < N; ++i) {
            if (!visited[i] && least[i] < cur_min) {
                cur_min = least[i];
                last_index = i;
            }
        }
        visited[last_index] = 1;
        for (int x = 1; x < N; ++x) {
            if (visited[x]) continue; // 更新与最小值节点相连的所有边
            if (least[x] > least[last_index] + dist[last_index][x]) {
                least[x] = least[last_index] + dist[last_index][x];
            }
        }
    }
    return least[1]; // 四舍五入
}
int main(void) {
    memset(coord, 0, sizeof(coord));
    // 这里memset 0x3f 的话会WA, 0x3f:double=0.0, -1:double=nan
    // 又是个新坑啊，double类型就老实for循环初始化吧
    for (int k = 0; k < maxn; ++k) {
        for (int j = 0; j < maxn; ++j) dist[k][j] = INF;
        least[k] = INF;
    }
    memset(visited, 0, sizeof(visited));
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    scanf("%d%d%d%d", &(coord[0].x), &(coord[0].y), &(coord[1].x), &(coord[1].y));
    int i = 2, line = 1;
    while (scanf("%d%d", &(coord[i].x), &(coord[i].y)) != EOF) {
        if (coord[i].x == -1 && coord[i].y == -1) {
            line = 1;
            continue;
        }
        if (line == 1) { line++; }
        else { dist[i][i - 1] = dist[i - 1][i] = min(dist[i][i - 1], getDist(i, i - 1) * 3.0 / 2000); } // 地铁分钟
        i++;
    }
    N = i;
    for (int j = 0; j < N; ++j) {
        for (int k = j + 1; k < N; ++k) {
            dist[j][k] = dist[k][j] = min(dist[j][k], getDist(j, k) * 3.0 / 500); // 走路分钟
        }
    }
    printf("%0.0lf\n", dijkstra());
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}