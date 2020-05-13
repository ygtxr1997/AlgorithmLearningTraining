class Solution {
public:
    typedef struct node {
        node(){}
        node(string str, int cnt) : word(str), time(cnt) {}
        bool operator<(const node& n2) const { 
            if (time != n2.time) return time < n2.time;
            return word > n2.word;
        }
        string word;
        int time;
    } node;
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> ret;
        unordered_map<string, int> hash; // <word, time>
        vector<node> vec;
        for (int i = 0; i < words.size(); ++i) hash[words[i]]++;
        for (auto pii : hash) vec.push_back(node(pii.first, pii.second));
        sort(vec.begin(), vec.end());
        int n = vec.size();
        for (int i = n - 1; i >= n - k; --i) {
            ret.push_back(vec[i].word);
        }
        return ret;
    }
};