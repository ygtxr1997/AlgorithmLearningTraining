class Solution {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        int Min = shorter * k, dif = longer - shorter;
        vector<int> ret;
        if (k == 0) return ret;
        while (Min <= longer * k) {
            ret.push_back(Min);
            Min += dif;
            if (dif == 0) break;
        }
        return ret;
    }
};