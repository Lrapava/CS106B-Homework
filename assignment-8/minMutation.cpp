// https://leetcode.com/problems/minimum-genetic-mutation/description/

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {

        const int shifts[8] = {
            14, 12, 10, 8, 6, 4, 2, 0
        };
        const int masks[8] = {
            3 << 14, 3 << 12, 3 << 10, 3 << 8,
            3 << 6, 3 << 4, 3 << 2, 3 << 0
        };

        auto encode = [](const string& gene) {
            int val = 0;
            for (char c : gene) {
                val <<= 2;
                switch (c) {
                    case 'A': val |= 0; break;
                    case 'C': val |= 1; break;
                    case 'G': val |= 2; break;
                    case 'T': val |= 3; break;
                }
            }
            return val;
        };

        int start = encode(startGene);
        int end = encode(endGene);

        unordered_set<int> bankSet;
        for (auto& g : bank) bankSet.insert(encode(g));
        if (!bankSet.count(end)) return -1;

        unordered_set<int> was;
        queue<pair<int, int>> q;
        q.push({start, 0});
        was.insert(start);

        while (!q.empty()) {
            auto [cur, dist] = q.front();
            q.pop();
            if (cur == end) return dist;

            for (int i = 0; i < 8; i++) {
                int curr = (cur >> shifts[i]) & 3;
                for (int j = 0; j < 4; j++) {
                    if (j == curr) continue;
                    int mut = (cur & ~masks[i]) | (j << shifts[i]);
                    if (!was.count(mut) && bankSet.count(mut)) {
                        was.insert(mut);
                        q.push({mut, dist + 1});
                    }
                }
            }
        }

        return -1;
    }
};
