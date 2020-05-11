class Solution {
public:
    typedef struct node {
        node(){}
        node(int l, int r) : left(l), right(r) {}
        bool operator<(const node& n2) {
            if (left != n2.left) return left < n2.left;
            return right > n2.right;
        }
        int left, right;
    } node;
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<node> intv(n);
        for (int i = 0; i < n; ++i) {
            intv[i] = node(intervals[i][0], intervals[i][1]);
        }
        // 排序后根据左右界判断
        sort(intv.begin(), intv.end());
        int cnt = 0;
        for (int i = 0; i < n; ) {
            cnt++;
            int j;
            for (j = i + 1; j < n && intv[j].left < intv[i].right && intv[j].right <= intv[i].right; ++j) ;
            i = j;
        }
        return cnt;
    }
};