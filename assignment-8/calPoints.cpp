// https://leetcode.com/problems/baseball-game/description

class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector <int> score(operations.size());
        int i = 0;
        for (auto op : operations) {
            if (op == "C") {
                score[--i] = 0;
                continue;
            }
            if (op == "D") {
                score[i] = 2*score[i-1];
            } else if (op == "+") {
                score[i] = score[i-1] + score[i-2];
            } else {
                score[i] = stoi(op);
            }
            i++;
        }
        int res = 0;
        for (int s : score) {
            res += s;
        }
        return res;
    }
};
