// ---------------------------------------------------------------------
// 题目描述:
// 一本书共有 P 页, 第 i 页恰好有一个知识点 ai, 同一个知识点可能重复出现,
// Jessica 希望通过阅读其中连续的一些页来把所有的知识点都覆盖到.
// 给定每页的知识点, 求出要阅读的最少页数
// ---------------------------------------------------------------------
// 思路:
// 滑动窗口
// [s, t] -> [s+1, t'] (t' >= t)
// 利用二叉树存储区间内每个知识点的出现次数, 窗口左边界移动就让该点出现的次数减一,
// 减至0时, 就删除该节点;(或者令设一个变量num记录当前出现次数>=0的节点个数)
// 同时, 窗口右边界每次移动就让该知识点出现的次数加一
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
using namespace::std;
const int maxp = 1000010;

int P;
int arr[maxp];
int solve(void) {
    // 统计知识点个数
    set<int> all;
    for (int i = 0; i < P; ++i) all.insert(arr[i]);
    int n = all.size();

    // 滑动窗口
    int s = 0, t = 0, num = 0;
    map<int, int> cnt;
    int res = P;
    while (1) {
        while (t < P && num < n) {
            if (cnt[arr[t++]]++ == 0) { // 先判断是否为0, 再++
                num++; // 出现新的知识点
            }
        }
        if (num < n) break; // 无法覆盖所有知识点
        res = min(res, t - s);
        if (--cnt[arr[s++]] == 0) { // 知识点出现次数减至0
            num--;
        }
    }
    return res;
}
int main(void) {
    while (scanf("%d", &P) != EOF) {
        for (int i = 0; i < P; ++i) scanf("%d", &arr[i]);
        printf("%d\n", solve());
    }
    return 0;
}