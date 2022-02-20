//needs some changes to be more generic
//i.e. eps for the doubles
//check point.cpp for the point structure
//-----------
pair<pt, pt> ClosestPair(vector<pt> P) {
    sort(all(P), [&](const pt &p, const pt &q) { return p.x < q.x; });
    set <pair<ll, ll>> S;
    ll best_distance = 8e18; //may need to change this manually
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
