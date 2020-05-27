class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
        map<int, int> cnt;
        for (int i = 0; i < hand.size(); ++i) cnt[hand[i]]++;
        auto ite = cnt.begin();
        while (ite != cnt.end()) {
            int num = ite->first, c = ite->second;
            if (c == 0) {
                ite++;
                continue; // 该牌已经消耗完
            }
            for (int i = 1; i < W; ++i) {
                if (cnt.count(num + i) == 0) return false; // 不够用
                if (cnt[num + i] < c) return false;
                cnt[num + i] -= c;
            }
            ite++;
        }
        return true;
    }
};