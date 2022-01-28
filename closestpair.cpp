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


using T = ll;

struct pt {
    T x, y;
    pt(T xi = 0, T yi = 0) : x(xi), y(yi) {}

    pt operator + (pt p) const { return pt(x + p.x, y + p.y); }
    pt operator - (pt p) const { return pt(x - p.x, y - p.y); }
    pt operator * (T &c) const { return pt(x * c, y * c); }
    pt operator / (T &c) const { return pt(x / c, y / c); }
    bool operator == (pt p) const { return x == p.x && y == p.y; }
    bool operator != (pt p) const { return x != p.x || y != p.y; }

    T sq_len() { return x * x + y * y; }
    double abs() { return sqrt(sq_len()); }

    pt rot(const double &ang) const {
        return pt(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
    }
    pt perp() { return pt(-y, x); } //rot(pi/2)

    T dot(pt p)  { return x * p.x + y * p.y; }
    T cross(pt p) { return x * p.y - y * p.x; }

    friend istream& operator >> (istream &is, pt &p) {
        return is >> p.x >> p.y;
    }
    friend ostream& operator<<(ostream& os, const pt &p) {
        return os  << p.x << " " << p.y;
    }
};

/* needs some changes done to the types
if using doubles
*/

pair<pt, pt> ClosestPair(vector<pt> P) {
    sort(all(P), [&](const pt &p, const pt &q) { return p.x < q.x; });
    set <pair<ll, ll>> S;
    ll best_distance = 8e18;
    int j = 0;
    pair <pt, pt> ans;
    for(int i = 0; i < sz(P); i++) {
        ll d = ceil(sqrt(best_distance));
        while(j < i && P[i].x - P[j].x >= d) { //only care for [x - d, x]
            S.erase({P[j].y, P[j].x});
            j++;
        }
        auto it1 = S.lower_bound({P[i].y - d, P[i].x});
        auto it2 = S.upper_bound({P[i].y + d, P[i].x});
        //now we have a box of 2d x d. theres just O(1) pts here (~8)
        for(auto it = it1; it != it2; ++it) {
            int dx = P[i].x - it->s;
            int dy = P[i].y - it->f;
            ll cur_dist = 1ll * dx * dx + 1ll * dy * dy;
            if(cur_dist < best_distance) {
                ans = {P[i], pt(it->s, it->f)};
                best_distance = cur_dist;
            }
        }
        S.insert({P[i].y, P[i].x});
    }
    return ans;

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n;
    cin >> n;
    vector<pt> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i].x >> arr[i].y;
    }

    pair <pt, pt> ans = ClosestPair(arr);
    ll re = (ans.f.x - ans.s.x) *  (ans.f.x - ans.s.x) +
                (ans.f.y - ans.s.y) * (ans.f.y - ans.s.y);

    cout << re;
    return 0;
}

