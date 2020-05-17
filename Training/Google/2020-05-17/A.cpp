#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 2 * 1e5 + 10;

int N, K;
int A[maxn];
void solve() {
    int ans = 0;
    for (int i = 0; i < N;) {
        if (A[i] != K) i++;
        else {
            int cur = K;
            i++;
            while (i < N && A[i] == cur - 1) {
                i++;
                cur--;
            }
            if (i > 1 && A[i - 1] == 1) ans++;
        }
    }
    printf("%d\n", ans);
}
int main(void) {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d", &N, &K);
        for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
        printf("Case #%d: ", t);
        solve();
    }
}