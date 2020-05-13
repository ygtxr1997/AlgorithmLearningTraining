// 循环删除当前的叶子节点, 直到只剩0条边或者1条边
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<int> dim(n, 0); // 节点度数
        vector<bool> del(n, 0); // 删除的节点
        while (!edges.empty() && edges.size() != 1) {
            for (int i = 0; i < edges.size(); ++i) { // 根据边表计算每个节点的度
                int v1 = edges[i][0], v2 = edges[i][1];
                if (del[v1] || del[v2]) continue;
                dim[v1]++;
                dim[v2]++;
            }
            int nxt_size = edges.size();
            for (int i = 0; i < nxt_size; ++i) {
                int v1 = edges[i][0], v2 = edges[i][1];
                if (del[v1] || del[v2]) continue;
                if (dim[v1] == 1 || dim[v2] == 1) { // 只添加度不为1的节点对应的边
                    if (dim[v1] == 1) { del[v1] = 1; swap(edges[i--], edges[--nxt_size]); }
                    if (dim[v2] == 1) { del[v2] = 1; swap(edges[i--], edges[--nxt_size]); }
                    continue;
                }
            }
            fill(dim.begin(), dim.end(), 0);
            edges.resize(nxt_size);
        }
        vector<int> ret;
        for (int i = 0; i < n; ++i) if (!del[i]) ret.push_back(i);
        return ret;
    }
};