class StackOfPlates {
public:
    list<stack<int>> li;
    int cap;
    StackOfPlates(int cap) {
        this->cap = cap;
    }
    
    void push(int val) {
        if (cap == 0) return;
        if (li.size() == 0 || li.back().size() == cap) {
            stack<int> st;
            st.push(val);
            li.push_back(st);
        } else li.back().push(val);
    }
    
    int pop() {
        if (li.empty()) return -1;
        int val = li.back().top();
        li.back().pop();
        if (li.back().empty()) li.pop_back();
        return val;
    }
    
    int popAt(int index) {
        if (index >= li.size()) return -1;
        auto ite = li.begin();
        for (int i = 0; i < index; i++) ite++;
        int val = ite->top();
        ite->pop();
        if (ite->empty()) li.erase(ite);
        return val;
    }
};

/**
 * Your StackOfPlates object will be instantiated and called as such:
 * StackOfPlates* obj = new StackOfPlates(cap);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAt(index);
 */