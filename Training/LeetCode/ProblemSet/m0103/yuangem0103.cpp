class Solution {
public:
    string replaceSpaces(string S, int length) {
        int n = S.size();
        string ret;
        for (int i = 0; i < n && i < length; ++i) {
            if (S[i] != ' ') ret.push_back(S[i]);
            else ret.append("%20");
        }
        return ret;
    }
};