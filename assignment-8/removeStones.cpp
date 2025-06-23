// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {

        for (int i = 0; i < N; ++i) {
            origin[i] = i;
            weight[i] = 1;
        }

        for (const auto& s : stones) {
            unite(s[0], s[1] + OFFSET);
        }

        set<int> uniqueRoots;
        for (const auto& s : stones) {
            uniqueRoots.insert(root(s[0]));
        }

        return stones.size() - uniqueRoots.size();
    }

private:
    const int MAX = 10001;
    const int OFFSET = MAX;
    const int N = 2 * MAX;

    int origin[20002];
    int weight[20002];

    int root(int x) {
        if (origin[x] != x) {
            origin[x] = root(origin[x]);
        }
        return origin[x];
    }

    void unite(int x, int y) {
        int rx = root(x);
        int ry = root(y);
        if (rx == ry) return;

        if (weight[rx] < weight[ry]) {
            origin[rx] = ry;
            weight[ry] += weight[rx];
        } else {
            origin[ry] = rx;
            weight[rx] += weight[ry];
        }
    }
};
