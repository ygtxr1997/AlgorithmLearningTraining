class SortedStack {
public:
    stack<int> Val;
    stack<int> Cache;
    SortedStack() {

    }
    
    void push(int val) {
        while (!Val.empty() && Val.top() < val) {
            Cache.push(Val.top());
            Val.pop();
        }
        Val.push(val);
        while (!Cache.empty()) {
            Val.push(Cache.top());
            Cache.pop();
        }
    }
    
    void pop() {
        if (!Val.empty()) Val.pop();
    }
    
    int peek() {
        if (Val.empty()) return -1;
        return Val.top();
    }
    
    bool isEmpty() {
        return Val.empty();
    }
};

/**
 * Your SortedStack object will be instantiated and called as such:
 * SortedStack* obj = new SortedStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->isEmpty();
 */