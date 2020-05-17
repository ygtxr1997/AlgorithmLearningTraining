#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
using namespace::std;
const int maxn = 1e5 + 20;

// TLE
int N;
int A[maxn];
vector<int> dic;
void init() {
    const int mx = maxn * 100;
    for (int i = 0; i * i < mx; ++i) {
        dic.push_back(i * i);
    }
}
void solve(void) {
    int ans = 0;
    unordered_map<int, int> hash;
    hash[0] = 1;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += A[i];
        for (int t = 0; t < dic.size(); t++) {
            if (hash.count(sum - dic[t]) != 0) ans += hash[sum - dic[t]];
        }
        hash[sum]++;
    }
    printf("%d\n", ans);
}
int main(void) {
    int T;
    scanf("%d", &T);
    init();
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
        printf("Case #%d: ", t);
        solve();
    }
    return 0;
}