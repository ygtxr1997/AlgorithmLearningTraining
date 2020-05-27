class TopVotedCandidate {
public:
    map<int, int> win; // <time, people>
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        vector<int> tickets(persons.size());
        int n = persons.size(), mx = 0;
        for (int i = 0; i < n; ++i) {
            win[times[i]] = mx = (++tickets[persons[i]]
                >= tickets[mx] ? persons[i] : mx);
        }
    }
    
    int q(int t) {
        return (--win.upper_bound(t))->second;
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */