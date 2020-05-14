class Solution {
public:
    static const int INF = 0x3f3f3f3f;
    typedef struct node {
        node(){}
        node(int a, int c) : val(a), ind(c) {}
        bool operator<(const node& n2) const { 
            if (ind == n2.ind) return val < n2.val;
            return ind < n2.ind;
        }
        int val, ind;
    } node;
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> ind; // <num, ind>
        for (int i = 0; i < arr2.size(); ++i) ind[arr2[i]] = i;
        map<node, int> mp; // <node, cnt>
        for (int i = 0; i < arr1.size(); ++i) {
            int val = arr1[i], index;
            if (ind.count(val) == 0) { // 未出现, ind为INF
                index = INF;
            } else index = ind[val];
            mp[node(val, index)]++;
        }
        vector<int> ret;
        for (auto pni : mp) {
            int val = pni.first.val, cnt = pni.second;
            for (int i = 0; i < cnt; i++) {
                ret.push_back(val);
            }
        }
        return ret;
    }
};