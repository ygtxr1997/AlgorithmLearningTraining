class TripleInOne {
public:
    int sSize;
    vector<int> st;
    int top[3];
    TripleInOne(int stackSize) {
        sSize = stackSize;
        st.resize(3 * stackSize);
        top[0] = 0;
        top[1] = 0;
        top[2] = 0;
    }
    
    void push(int stackNum, int value) {
        if (top[stackNum] == sSize) return; // 栈满
        st[stackNum * sSize + top[stackNum]] = value;
        top[stackNum]++;
    }
    
    int pop(int stackNum) {
        if (isEmpty(stackNum)) return -1;
        top[stackNum]--;
        return st[stackNum * sSize + top[stackNum]];
    }
    
    int peek(int stackNum) {
        if (isEmpty(stackNum)) return -1;
        return st[stackNum * sSize + top[stackNum] - 1];
    }
    
    bool isEmpty(int stackNum) {
        return top[stackNum] == 0;
    }
};

/**
 * Your TripleInOne object will be instantiated and called as such:
 * TripleInOne* obj = new TripleInOne(stackSize);
 * obj->push(stackNum,value);
 * int param_2 = obj->pop(stackNum);
 * int param_3 = obj->peek(stackNum);
 * bool param_4 = obj->isEmpty(stackNum);
 */