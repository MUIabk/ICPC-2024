struct manacher {
    vector<int> lengths;
    manacher(string s) { combined_manacher(s); }
    template<typename T_string>
    static vector<int> odd_manacher(const T_string &pattern) {
        int n = int(pattern.size());
        vector<int> radius(n, 0);
        int loc = 0;
        for (int i = 1; i < n; i++) {
            if (i <= loc + radius[loc]) radius[i] = min(radius[loc - (i - loc)], loc + radius[loc] - i);
            while (i - radius[i] > 0 && i + radius[i] < n - 1 && pattern[i - radius[i] - 1] == pattern[i + radius[i] + 1]) radius[i]++;
            if (i + radius[i] > loc + radius[loc]) loc = i;
        }
        return radius;
    }
    template<typename T_string>
    void combined_manacher(const T_string &pattern) {
        int n = int(pattern.size());
        T_string extended(2 * n + 1, 0);
        for (int i = 0; i < n; i++) extended[2 * i + 1] = pattern[i];
        lengths = odd_manacher(extended);
    }
    // whether s[start, end] is a palindrome 
    inline bool is_palindrome(int start, int end) {
        return lengths[start + end + 1] >= end - start + 1;
    }
};
