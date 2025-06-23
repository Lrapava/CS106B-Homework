// https://leetcode.com/problems/remove-all-occurrences-of-a-substring/description/

class Solution {
public:
    string removeOccurrences(string s, string part) {
        const int ps = (int)part.size();
        string res;
        int rs = 0;
        for (char c : s) {
            res.push_back(c);
            rs ++;
            if (rs >= ps && res.compare(res.size()-ps, ps, part) == 0) {
                res.erase(res.end() - ps, res.end());
                rs -= ps;
            }
        }
        return res;
    }
};
