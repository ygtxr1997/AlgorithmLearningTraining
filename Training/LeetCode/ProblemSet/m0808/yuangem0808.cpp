class Solution {
public:
    unordered_map<char, int> dic;
    vector<char> letter;
    vector<int> cnt;
    int num; // 单词个数
    int len; // 字符串长度
    vector<string> ret;
    string cur;
    void dfs(int k) {
        if (k >= len) {
            ret.push_back(cur);
            return;
        }
        for (int i = 0; i < num; ++i) {
            if (cnt[i] <= 0) continue;
            cur.push_back(letter[i]);
            cnt[i]--;
            dfs(k + 1);
            cur.pop_back();
            cnt[i]++;
        }
    }
    vector<string> permutation(string S) {
        for (auto c : S) dic[c]++;
        for (auto pci : dic) {
            letter.push_back(pci.first);
            cnt.push_back(pci.second);
        }
        num = cnt.size();
        len = S.size();
        dfs(0);
        return ret;
    }
};