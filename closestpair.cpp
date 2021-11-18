#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...) 0
#endif

//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
#define x first
#define y second
#define f first
#define s second
#define pb push_back
#define inf INT_MAX
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int N = 1e6+5;
const int mod = 1e9 + 7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int x, int y) {
    return uniform_int_distribution<>(x, y)(rng);
}

/*
verified: https://www.spoj.com/problems/CLOPPAIR/
much better constant than recursive (runs in ~1.2s for 1e6)
source : https://codeforces.com/blog/entry/58747.
not much changes needed for double, maybe consider an eps.
*/

using point = pii;

pair<point, point> closest_point_solver(vector<point> P) {
    sort(all(P), [&](const point &p, const point &q) { return p.x < q.x; });
    set <point> S; //sorted by Y.
    ll best_distance = LLONG_MAX;
    int j = 0;
    pair <point, point> ans;
    for(int i = 0; i < sz(P); i++) {
        ll d = ceil(sqrt(best_distance));
        while(j < i && P[i].x - P[j].x >= d) { //only care for [x - d, x]
            S.erase({P[j].y, P[j].x});
            j++;
        }
        auto it1 = S.lower_bound({P[i].y - d, P[i].x});
        auto it2 = S.upper_bound({P[i].y + d, P[i].x});
        //now we have a box of 2d x d. theres just O(1) points here (~8)
        for(auto it = it1; it != it2; ++it) {
            int dx = P[i].x - it->s;
            int dy = P[i].y - it->f;
            ll cur_dist = 1ll * dx * dx + 1ll * dy * dy;
            if(cur_dist < best_distance) {
                ans = {P[i], {it->s, it->f}};
                best_distance = cur_dist;
            }
        }
        S.insert({P[i].y, P[i].x});
    }
    return ans;

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n = 100;
    //cin >> n;
    vector<pii> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i].x = uid(-1e9, 1e9); arr[i].y = uid(-1e9, 1e9);
       // cin >> arr[i].x >> arr[i].y;
    }

    pair <point, point> ans = closest_point_solver(arr);

    //recover positions in the original array.
    int idx_a = -1, idx_b = -1;
    for(int i = 0; i < n; i++) {
        if(arr[i] == ans.f) idx_a = i;
        else if(arr[i] == ans.s) idx_b = i;
    }
    cout << min(idx_a, idx_b) << " " << max(idx_a, idx_b) << " ";
    //take square root (we used distance squared for precision)
    double re = 1.0 * (ans.f.x - ans.s.x) * 1.0 * (ans.f.x - ans.s.x) +
                1.0 * (ans.f.y - ans.s.y) * 1.0 * (ans.f.y - ans.s.y);
    re = sqrt(re);

    cout << fixed << setprecision(6) << re;
    return 0;
}
