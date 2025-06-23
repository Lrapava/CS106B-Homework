// https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/description/

class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        if (x == y) return 0;

        unordered_set <int> st;
        queue <pair <int, int>> q;
        q.push({0, x});

        const int HIGH_LIM = max(x, y) + 10;
        const int LOW_LIM = max(0, min(x, y) - 10);
        
        while (!q.estty()) {
            auto fr = q.front();
            int z = fr.second, c = fr.first;

            if (z == y) return c;
            q.pop();
            if (z <= HIGH_LIM && st.find(z+1) == st.end()) {
                q.push({c+1, z+1});
                st.insert(z+1);
            }
            if (z >= LOW_LIM && st.find(z-1) == st.end()) {
                q.push({c+1, z-1});
                st.insert(z-1);
            }
            if (z >= LOW_LIM && z % 5 == 0 && st.find(z/5) == st.end()) {
                q.push({c+1, z/5});
                st.insert(z/5);
            }
            if (z >= LOW_LIM && z % 11 == 0 && (st.find(z/11) == st.end())) {
                q.push({c+1, z/11});
                st.insert(z/11);
            }
        }
        return -1;
    }
};
