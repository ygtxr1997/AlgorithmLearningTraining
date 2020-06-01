class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> Val;
    stack<int> Min;
    MinStack() {

    }
    
    void push(int x) {
        Val.push(x);
        if (Min.empty()) Min.push(x);
        else Min.push(min(Min.top(), x));
    }
    
    void pop() {
        Val.pop();
        Min.pop();
    }
    
    int top() {
        return Val.top();
    }
    
    int getMin() {
        return Min.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */