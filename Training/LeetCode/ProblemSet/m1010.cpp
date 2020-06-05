class StreamRank {
    typedef struct node { // 二叉搜索树节点
        int val;
        int small; // 该点的左子树节点(包括自身)总个数
        node* left;
        node* right;
        node(){}
        node(int v) : val(v), small(1), left(nullptr), right(nullptr) {}
    } node;
    void BSTinsert(node* nd, int x) {
        if (nd->val < x) {
            if (nd->right) BSTinsert(nd->right, x);
            else {
                node* nx = new node(x);
                nd->right = nx;
            }
        } else if (nd->val > x) {
            nd->small++;
            if (nd->left) {
                BSTinsert(nd->left, x);
            } else {
                node* nx = new node(x);
                nd->left = nx;
            }
        } else nd->small++;
    }
    int BSTfind(node* nd, int x) {
        if (!nd) return 0;
        if (nd->val == x) return nd->small;
        if (nd->val > x) { // 向左寻找
            return BSTfind(nd->left, x);
        } else { // 向右寻找
            return nd->small + BSTfind(nd->right, x);
        }
    }
public:
    node* root = nullptr;
    StreamRank() {

    }
    
    void track(int x) {
        if (!root) root = new node(x);
        else BSTinsert(root, x);
    }
    
    int getRankOfNumber(int x) {
        return BSTfind(root, x);
    }
};

/**
 * Your StreamRank object will be instantiated and called as such:
 * StreamRank* obj = new StreamRank();
 * obj->track(x);
 * int param_2 = obj->getRankOfNumber(x);
 */