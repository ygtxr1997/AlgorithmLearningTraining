class MyQueue {
public:
    /** Initialize your data structure here. */
    stack<int> In;
    stack<int> Out;
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        In.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        while (!In.empty()) {
            Out.push(In.top());
            In.pop();
        }
        int val = Out.top();
        Out.pop();
        while (!Out.empty()) {
            In.push(Out.top());
            Out.pop();
        }
        return val;
    }
    
    /** Get the front element. */
    int peek() {
        while (!In.empty()) {
            Out.push(In.top());
            In.pop();
        }
        int val = Out.top();
        while (!Out.empty()) {
            In.push(Out.top());
            Out.pop();
        }
        return val;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return In.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */