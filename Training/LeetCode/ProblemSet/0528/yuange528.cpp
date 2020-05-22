class Solution {
public:
    int mx = 0;
    vector<int> hash;
    Solution(vector<int>& w) {
        for (int num : w) { 
            mx += num;
            hash.push_back(mx - 1);
        }
        srand((unsigned)time(NULL));
    }
    
    int pickIndex() {
        int r = rand() % mx;
        int pos = lower_bound(hash.begin(), hash.end(), r) - hash.begin();
        return pos;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */