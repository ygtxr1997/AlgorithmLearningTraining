class Solution {
public:
    int key[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
    vector<string> getValidT9Words(string num, vector<string>& words) {
        vector<string> ret;
        for (string word : words) {
            string dec; // 单词转换为数字按键
            for (char c : word) dec.push_back('0' + key[c - 'a']);
            if (dec == num) ret.push_back(word);
        }
        return ret;
    }
};