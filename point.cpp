#include <bits/stdc++.h>
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
using ld = long double;

const int N = 3e5 + 3;
const int mod = 1e9 + 7;

//if T = double change == and != to handle eps.
struct pt {
    using T = double;
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
        return os << "("<< p.x << ", " << p.y << ")";
    }
};

bool ccw(pt a, pt b, pt c) {
    return (b - a).cross(c - a) > 0;
}

bool cw(pt a, pt b, pt c) {
    return (b - a).cross(c - a) < 0;
}


const double pi = acos(-1.0);
int main() {
    pt a, b;
    cin >> a;
    return 0;
}
