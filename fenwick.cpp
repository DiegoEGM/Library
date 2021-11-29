#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+3;

//1-indexed!!!
template <class T>
struct FenwickTree {
    vector <T> tree;
    int n_;

    FenwickTree(int n) : n_(n), tree(n + 1) {}

    T get(int i) {
        if(i <= 0 || i > n_) return T(0);
        T sum = T(0);
        for(; i; i -= (i & -i))
            sum += tree[i];
        return sum;
    }

    void upd(int i, T val) {
        for(; i <= n_; i += (i & -i))
            tree[i] += val;
    }
    //first index i with get(i) >= v (a prefix sum 'lower_bound') (needs to be all non negative ofc)
    int first_index(T val) {
        int i = 0, p = 0; //index, log2(sz)
        T sum = T(0);

        while(1 << (p + 1) <= n_)
            p++;

        for(; p >= 0; p--) {
            int new_idx = i + (1 << p);
            if(new_idx <= n_ && sum + tree[new_idx] < val) {
                sum += tree[new_idx];
                i = new_idx;
            }
        }
        //+1 since we stayed at last i with get(i) < v.
        return i + 1; //returns n_ + 1 if total sum is < v.
    }
};

//source for 'first_index': https://codeforces.com/blog/entry/61364

//------------------------------------------------------------------
long long v[N];

int main()
{
    int n;
    scanf("%d",&n);
    FenwickTree <long long> BIT(n);

    for(int i = 1; i <= n; i++) {
        scanf("%lld",&v[i]);
    }

     for(int i = 1; i <= n; i++) {
        BIT.upd(i, v[i]);
     }

    for(int i = 1; i <= n; i++) {
        long long hold = BIT.get(i) - BIT.get(i - 1);
        printf("%lld\n", hold);
    }

    printf("[%d]", BIT.first_index(10));
    return 0;
}
