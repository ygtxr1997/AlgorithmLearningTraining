class Solution {
public:
    typedef struct node {
        int h, w;
        node(){}
        node(int x, int y) : h(x), w(y) {}
    } node;
    static bool cmp(const node& n1, const node& n2) {
        if (n1.h != n2.h) return n1.h < n2.h;
        return n1.w > n2.w;
    }
    int bestSeqAtIndex(vector<int>& height, vector<int>& weight) {
        vector<node> vec;
        for (int i = 0; i < height.size(); ++i) vec.push_back(node(height[i], weight[i]));
        sort(vec.begin(), vec.end(), cmp);
        vector<int> que(1, -1); // 放入一个最小值
        for (int i = 0; i < vec.size(); ++i) {
            // 按高度降序升序排序后, 只需考虑重量关系
            int pos = lower_bound(que.begin(), que.end(), vec[i].w) - que.begin();
            if (pos >= que.size()) que.push_back(vec[i].w);
            else que[pos] = min(que[pos], vec[i].w);
        }
        return que.size() - 1;
    }
};