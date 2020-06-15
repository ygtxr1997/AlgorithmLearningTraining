class Solution {
public:
    int getKthMagicNumber(int k) {
        typedef long long ll;
        if (k == 1) return 1;
        priority_queue<ll> pqu;
        unordered_set<ll> vis;
        pqu.push(-1);
        vis.insert(-1);
        while (--k) {
            ll top = -pqu.top();
            pqu.pop();
            if (!vis.count(-top * 3)) { pqu.push(-top * 3); vis.insert(-top * 3); }
            if (!vis.count(-top * 5)) { pqu.push(-top * 5); vis.insert(-top * 5); }
            if (!vis.count(-top * 7)) { pqu.push(-top * 7); vis.insert(-top * 7); }
        }
        return -pqu.top();
    }
};