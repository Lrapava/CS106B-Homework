class Solution {
public:
    char findTheDifference(string s, string t) {
        int f[26];
        for (int i = 0; i < 26; i++) {
            f[i] = 0;
        }
        for (char c : s) {
            f[c-'a']--;
        }
        for (char c : t) {
            f[c-'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (f[i]) {
                return char(i+'a');
            }
        }
        return '~';
    }
};
