#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;

int N, C;
typedef struct node {
    int d, c;
} node;
bool cmp(const node& n1, const node& n2) {
    return n1.d > n2.d;
}
node vec[23];

// 贪心策略, 对于面额大于等于C的硬币, 每周刚好用一枚硬币付清;
// 对于面额小于C的硬币, 先从大到小取硬币直到不能再添加,
// 然后再从小到大取硬币直到总额>=C,
// 如果找不到总额>=C的, 说明已经不可能再凑满C, 循环结束
int main(void) {
    cin >> N >> C;
    for (int i = 0; i < N; ++i) scanf("%d%d", &vec[i].d, &vec[i].c);
    sort(vec, vec + N, cmp);
    int cnt = 0, j = 0;
    for (; j < N; ++j) if (vec[j].d < C) break;
    for (int i = 0; i < j; ++i) cnt += vec[i].c; // 面额大于C
    while (1) {
        int now = 0; // 尽量填充满每一个C
        for (int i = j; i < N; ++i) { // 先选大的
            while (vec[i].c && now + vec[i].d <= C) {
                now += vec[i].d;
                vec[i].c--;
            }
        }
        for (int i = N - 1; i >= j; --i) { // 再选小的
            while (vec[i].c && now < C) {
                now += vec[i].d;
                vec[i].c--;
            }
        }
        if (now < C) break; // 凑不到C了
        cnt++;
    }
    cout << cnt << endl;
}