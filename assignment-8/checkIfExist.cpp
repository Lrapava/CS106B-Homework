class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        std::unordered_set <int> twox;
        int zeroc = 0;
        for (int x : arr) {
            twox.insert(2*x);
            if (x == 0) {
                zeroc++;
            }
        }
        if (zeroc > 1) {
            return true;
        }
        for (int x : arr) {
            if (x != 0 && twox.find(x) != twox.end()) {
                return true;
            }
        }
        return false;
    }
};
