//Tested on: https://codeforces.com/contest/87/problem/E
//needs point.cpp

//Returns the vertices of the Minkowski sum of P and Q.
//P and Q must previously be ordered by (x, y).
//Sum is returned with the same order. Complexity: O(|P| + |Q|).
vector <pt> Minkowski(vector <pt> P, vector <pt> Q) {
    P.pb(P[0]);
    Q.pb(Q[0]);
    vector <pt> ret = {P[0] + Q[0]};
    int i = 0, j = 0;
    while(i < sz(P) - 1 || j < sz(Q) - 1) {
        pt nex;
        if(i == sz(P) - 1 || (j < sz(Q) - 1 && (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]) > 0)) {
            nex = P[i] + Q[++j];
        }
        else {
            nex = P[++i] + Q[j];
        }
        while(sz(ret) >= 2 && (nex - ret[sz(ret) - 2]).cross(ret[sz(ret) - 1] - ret[sz(ret) - 2]) == 0) {
            ret.pop_back();
        }
        ret.pb(nex);
    }
    ret.pop_back();
    return ret;
}
