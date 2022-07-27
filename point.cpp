//if T = double change == and != to handle eps.
struct pt {
    using T = long long;
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

int up(pt p) {
    if(p.x == 0 && p.y == 0) return 0;
    return (p.y > 0 || (p.y == 0 && p.x < 0)) ? 1 : -1;
}

bool polar_cmp(pt &a, pt &b) {
    return up(a) < up(b) || (up(a) == up(b) && a.cross(b) > 0);
}
