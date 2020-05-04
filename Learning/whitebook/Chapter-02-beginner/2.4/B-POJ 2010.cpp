#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace::std;
const int maxn = 100010;
priority_queue<int> Q1, Q2;
typedef struct COW {
    bool operator<(const COW& c2) {
        if (s != c2.s) return s < c2.s; // 按分数从小到大排序
        return f < c2.f; // 分数相同, 花钱少的放前面
    }
    int s, f; // 分数, 花钱
} COW;
COW cow[maxn];
int dpl[maxn], dpr[maxn];
int N, C, F; // 录取人数, 总人数, 总钱数

// 先按照牛的得分从小到大排序,
// 不妨设 k=N/2,
// dpl[i]:i左边k头牛的最小花钱数
// dpr[i]:i右边k头牛的最小花钱数
// 借助优先队列在从左到右的遍历过程中求出dpl[]和dpr[]
int solve(void) {
    memset(dpl, 0, sizeof(dpl));
    memset(dpr, 0, sizeof(dpr));
    sort(cow, cow + C);
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < C; ++i) {
        if (i < N / 2) {
            Q1.push(cow[i].f);
            sum1 += cow[i].f;
            continue;
        }
        dpl[i] = sum1;
        if (cow[i].f < Q1.top()) {
            sum1 -= Q1.top(); // 每次取出最大花钱数, 并将该牛的花钱数加入大根堆
            Q1.pop();
            sum1 += cow[i].f;
            Q1.push(cow[i].f);
        }
    }
    for (int i = C - 1; i >= 0; --i) {
        if (i >= C - N / 2) {
            Q2.push(cow[i].f);
            sum2 += cow[i].f;
            continue;
        }
        dpr[i] = sum2;
        if (cow[i].f < Q2.top()) {
            sum2 -= Q2.top();
            Q2.pop();
            sum2 += cow[i].f;
            Q2.push(cow[i].f);
        }
    }
    int ans = -1;
    // 从右到左遍历找到第一符合dpl[i]+dpr[i]+fi<=F的牛, 该牛的得分即最大中位数
    for (int i = C; i >= 0; i--) {
        if (dpl[i] && dpr[i] && dpl[i] + dpr[i] + cow[i].f <= F) {
            ans = cow[i].s;
            break;
        }
    }
    return ans;
}
int main(void) {
    while (scanf("%d%d%d", &N, &C, &F) != EOF) {
        for (int i = 0; i < C; ++i) scanf("%d%d", &cow[i].s, &cow[i].f);
        
        printf("%d\n", solve());
    }
    return 0;
}