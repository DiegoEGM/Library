//needs point.cpp

//assuming A, B, C are clockwise
bool inside_triangle(pt a, pt A, pt B, pt C) {
    return !ccw(a, B, C) && !ccw(a, C, A) && !ccw(a, A, B);
}

bool in_segment(pt a, pt A, pt B) {
    return (a - A).cross(a - B) == 0 &&
            min(A.x, B.x) <= a.x && a.x <= max(A.x, B.x)
         && min(A.y, B.y) <= a.y && a.y <= max(A.y, B.y);
}

//assuming P is sorted by (x, y). O(log |P|).
bool inside_convex_polygon(pt a, vector <pt> &P) {
    int l = 1;
    int r = sz(P) - 1;

    while(l != r) {
        int m = (l + r) / 2;
        if(!cw(a, P[0], P[m]))
            r = m;
        else
            l = m + 1;
    }

    if(l == 1) return in_segment(a, P[0], P[1]);
    return inside_triangle(a, P[0], P[l - 1], P[l]);
}
