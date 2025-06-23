// https://leetcode.com/problems/number-of-provinces/description/

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        bool* was = new bool[n];
        vector <vector <int>> neigh(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (isConnected[i][j]) {
                    neigh[i].push_back(j);
                }
            }
            was[i] = false;
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (!was[i]) {
                res++;
                queue <int> q;
                q.push(i);
                while (!q.empty()) {
                    int fr = q.front();
                    q.pop();
                    was[fr] = true;
                    for (int& x : neigh[fr]) {
                        if (!was[x]) {
                            q.push(x);
                        }
                    }
                }
            }
        }
        return res;
    }
};
