class Solution {
public:
    unordered_map<string, vector<string>> hash; // <code, ind>
    string encode(const string& str) {
        string ret;
        int letter[26] = {0};
        for (int i = 0; i < str.size(); ++i) {
            letter[str[i] - 'a']++;
        }
        for (int i = 0; i < 26; ++i) {
            if (letter[i] != 0) {
                ret.append(string(1, (char)('a' + i)) + to_string(letter[i]));
            }
        }
        return ret;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        for (int i = 0; i < n; ++i) {
            hash[encode(strs[i])].push_back(strs[i]);
        }
        vector<vector<string>> ret;
        for (auto psv : hash) {
            ret.push_back(psv.second);
        }
        return ret;
    }
};