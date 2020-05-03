#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace::std;
const int maxn = 2511;

// 本质是贪心, 借用优先队列辅助
// 对比区间覆盖问题, 按照牛的minSPF升序排序, 按照瓶子的SPF升序排序
// 对于每个瓶子, 尽可能把它分配给maxSPF较小的牛, 直到再也没有符合条件的牛或者瓶子消耗完毕
int C, L; // 牛数, 瓶子数
typedef pair<int, int> pii;
pii cow[maxn], bot[maxn]; // 牛的信息<minSPF, maxSPF>, 瓶子的信息<SPF, cnt>
int solve(void) {
    int ans = 0;
    sort(cow, cow + C); // 先处理minSPF较小的牛
    sort(bot, bot + L); // 先处理SPF较小的瓶子
    priority_queue<int, vector<int>, greater<int>> pqu; // 小根堆, 先考虑maxSPF较小的牛
    int j = 0; // 牛j
    for (int i = 0; i < L; ++i) { // 遍历瓶子i
        int curSPF = bot[i].first, curCnt = bot[i].second;
        while (j < C && cow[j].first <= curSPF) { // minSPF小于该瓶子的, 将其maxSPF放入优先队列准备下一步处理
            pqu.push(cow[j].second);
            j++;
        }
        while (!pqu.empty() && curCnt) { // 待处理牛为空或者瓶子消耗完后, 该瓶子考虑完毕
            int maxSPF = pqu.top();
            pqu.pop();
            if (maxSPF < curSPF) continue; // 最大值比该瓶子SPF小, 不能分配给该牛, 后面肯定也没有瓶子可以给该牛
            ans++; // 可以分配给这头牛
            curCnt--;
        }
    }
    return ans;
}
int main(void) {
    while (scanf("%d%d", &C, &L) != EOF) {
        for (int i = 0; i < C; ++i) scanf("%d%d", &cow[i].first, &cow[i].second);
        for (int i = 0; i < L; ++i) scanf("%d%d", &bot[i].first, &bot[i].second);
        printf("%d\n", solve());
    }
    return 0;
}