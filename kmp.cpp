//O(|s|).
//note that f[i + 1] <= f[i] + 1.
//f[i] is the length of the maximum proper preffix of s[0..i]
//that is also a suffix of s[0..i].
vector <int> kmp(string s) {
    int n = s.size();
    vector <int> f(n);
    for(int i = 1; i < n; i++) {
        int j = f[i - 1];
        while(j > 0 && s[i] != s[j])
            j = f[j - 1];
        if(s[i] == s[j])
            j++;
        f[i] = j;
    }
    return f;
}

//returns the positions of t where s is located.
vector <int> get_ocurrences(string s, string t) {
    vector <int> f = kmp(s + "#" + t); //'#' must not be in s or t.
    vector <int> oc;
    int n = s.size(), m = t.size();
    for(int i = n + n; i <= n + m; i++) {
        if(f[i] == n)
            oc.push_back(i - 2*n);
    }
    return oc;
}

//see https://cp-algorithms.com/string/prefix-function.html for cool applications

