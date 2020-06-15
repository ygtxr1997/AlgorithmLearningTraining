class Solution {
public:
    int UnionSet[100010];
    int find(int x) {
        if (x != UnionSet[x]) {
            UnionSet[x] = find(UnionSet[x]);
        }
        return UnionSet[x];
    }
    vector<string> trulyMostPopular(vector<string>& names, vector<string>& synonyms) {
        vector<string> ind2name; // vec[ind]=name
        unordered_map<string, int> name2ind; // hash[name]=ind
        vector<int> ind2cnt; // vec[ind]=cnt
        // init
        for (int i = 0; i < 100010; ++i) UnionSet[i] = i;
        for (const string& str : names) {
            int l = str.find('(');
            string name = str.substr(0, l);
            int cnt = stoi(str.substr(l + 1, str.size() - l - 2).c_str());
            ind2name.push_back(name);
            ind2cnt.push_back(cnt);
            name2ind[name] = ind2cnt.size() - 1;
        }
        // union
        for (const string& str : synonyms) {
            int m = str.find(',');
            string name1 = str.substr(1, m - 1), name2 = str.substr(m + 1, str.size() - m - 2);
            int ind1 = name2ind[name1], ind2 = name2ind[name2];
            int r1 = find(ind1), r2 = find(ind2);
            if (r1 != r2) {
                if (ind2name[r1] < ind2name[r2]) {
                    UnionSet[r2] = r1;
                    ind2cnt[r1] += ind2cnt[r2];
                } else {
                    UnionSet[r1] = r2;
                    ind2cnt[r2] += ind2cnt[r1];
                }
            }
        }
        // out
        vector<string> ret;
        for (int i = 0; i < names.size(); ++i) {
            if (UnionSet[i] == i) { // 是根节点
                string cur(ind2name[i]);
                cur += "(" + to_string(ind2cnt[i]) + ")";
                ret.push_back(cur);
            }
        }
        return ret;
    }
};