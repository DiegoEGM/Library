/*
Convex Hull Trick to maximize linear function.
This works when you are adding two-pointers-like
both in increasing slopes and in increasing points for the queries.
to-do:
-check if it handles parallel lines (delete many and keep highest intercept? or does it do that already?)
-declutter the checks in the whiles (some things cancel out => transforms to some cross product?)
verified at: https://cses.fi/problemset/task/2086/
-make a binary search version? (so no need for queries to be increasing)
*/
struct cht {
    struct line {
        ll m, b;
        line(ll m = 0, ll b = -linf) : m(m), b(b) {}
        ll eval(ll x) const {
            return m * x + b;
        }
    };
    deque <line> dq;
    cht() : dq(1) {}
    ll query(ll x) {
        while(dq.size() >= 2 && (dq[sz(dq) - 1].b - dq[sz(dq) - 2].b) <= x * (dq[sz(dq) - 2].m - dq[sz(dq) - 1].m))
            dq.pop_back();
        return dq.back().eval(x);
    }
    void add_line(ll m, ll b) {
        line L(m, b);
        while(dq.size() >= 2 && (dq[1].b - dq[0].b) * (L.m - dq[0].m) >= (dq[0].m - dq[1].m) * (dq[0].b - L.b))
            dq.pop_front();
        dq.push_front(L);
    }
};
