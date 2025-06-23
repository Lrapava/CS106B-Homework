class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector <pair <int, bool>> brackets;
        for (auto i : intervals) {
            brackets.push_back({i[0], false});
            brackets.push_back({i[1], true});
        }
        sort(brackets.begin(), brackets.end());
        
        int depth = 0, outer = -1;
        vector <vector <int>> res;
        
        for (auto b : brackets) {
            if (!b.second) {
                if (depth == 0) {
                    outer = b.first;
                }
                depth++;
            } else {
                depth--;
                if (depth == 0) {
                    res.push_back({outer, b.first});
                }
            }
        }
        return res;
    }
};
