//remember this is 1-indexed!
template <class T>
struct FenwickTree {
    int n; 
    vector <T> tree;
    FenwickTree(int n_) : n(n_), tree(n + 1) {}
    T get(int i) {
        if(i <= 0 || i > n) return T(0);
        T sum = T(0);
        for(; i; i -= (i & -i))
            sum += tree[i];
        return sum;
    }
    void upd(int i, T val) {
        for(; i <= n; i += (i & -i))
            tree[i] += val;
    }
    //first index i with get(i) >= v (a prefix sum "lower_bound")
    int first_index(T val) {
        int i = 0, p = 0; //index, log2(n)
        T sum = T(0);
        while((1 << (p + 1)) <= n)
            p++;
        for(; p >= 0; p--) {
            int new_idx = i + (1 << p);
            if(new_idx <= n && sum + tree[new_idx] < val) {
                sum += tree[new_idx];
                i = new_idx;
            }
        }
        //+1 since we stayed at last i with get(i) < v.
        return i + 1; //returns n + 1 if total sum is < v.
    }
};
