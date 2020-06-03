class Solution {
public:
    vector<string> permutation(string S) {
        unordered_set<string> ret;
        bool bSame = 0;
        do {
            if (ret.count(S)) {
                bSame = 1;
                break;
            }
            ret.insert(S);
        } while (next_permutation(S.begin(), S.end()) || !bSame);
        return vector<string>(ret.begin(), ret.end());
    }
};