class MyCalendar {
public:
    typedef pair<int, int> pii;
    map<int, int> mp; // <left, right>
    MyCalendar() {

    }
    
    bool book(int start, int end) {
        if (mp.empty()) { mp.insert(pii(start, end)); return true; }
        auto ub = mp.find(start);
        if (ub != mp.end()) return false;
        ub = mp.upper_bound(start); // 直接调用map的STL upper_bound()函数
        bool flag;
        if (ub == mp.begin()) {
            if (end <= ub->first) flag = true;
            else flag = false;
        } else if (ub == mp.end()) {
            auto lb = ub;
            lb--;
            if (start >= lb->second) flag = true;
            else flag = false;
        } else {
            auto lb = ub;
            lb--;
            if (end <= ub->first && start >= lb->second) flag = true;
            else flag = false;
        }
        if (flag) mp.insert(pii(start, end));
        return flag;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */