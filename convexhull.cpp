//needs point.cpp for cw and ccw
//this includes collinear. change ccw to !cw to delete those. O(|v|).
vector <pt> ConvexHull (vector <pt> v) {
    int n = sz(v);
    sort(all(v), [&](const pt &p, const pt &q) {
            return p.x < q.x || (p.x == q.x && p.y < q.y);
         });
    vector <pt> hull;
    vector <pt> upper(n), lower(n);
    int j = 0;
    for(int i = 0; i < n; i++) {
        while(j >= 2 && ccw(upper[j - 2], upper[j - 1], v[i])) j--;
        upper[j++] = v[i];
    }
    for(int i = 0; i < j; i++) hull.pb(upper[i]);
    j = 0;
    for(int i = n - 1; i >= 0; i--) {
        while(j >= 2 && ccw(lower[j - 2], lower[j - 1], v[i])) j--;
        lower[j++] = v[i];
    }
    for(int i = 1; i < j - 1; i++) hull.pb(lower[i]);
    return hull;
}
