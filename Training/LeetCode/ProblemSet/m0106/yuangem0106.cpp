class Solution {
public:
    string compressString(string S) {
        string ret;
        for (int i = 0; i < S.size(); ) {
            int j = i + 1, cnt = 1;
            while (j < S.size() && S[j] == S[i]) {
                j++, cnt++;
            }
            ret.push_back(S[i]);
            ret.append(to_string(cnt));
            i = j;
        }
        if (ret.size() < S.size()) return ret;
        else return S;
    }
};