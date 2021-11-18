#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
#define pb push_back
using namespace std;

using vi = vector<int>;

const int N = 2e5 + 3;
const int mod = 1e9 + 7;

template <class T = int>
struct Dinic {
    struct Edge { //u->v with capacity cap. no need to store u.
        int v;
        T cap;
        Edge(int v_, T cap_) : v(v_), cap(cap_) {}
    };

    int s, t, n;
    vi pt, dist; //first potential edge, distance in level graph.
    vector <Edge> edges; //edges in this graph, even indices are original edges, odd are their reverse.
    vector <vi> adj; //index of edge from me.

    Dinic(int n_, int s_, int t_)  : n(n_), s(s_), t(t_),
                        pt(n + 1), dist(n + 1), adj(n + 1) {}

    void addEdge(int u, int v, T cap) {
        edges.pb(Edge(v, cap));
        edges.pb(Edge(u, T(0)));
        adj[u].pb(sz(edges) - 2);
        adj[v].pb(sz(edges) - 1);
    }

    bool bfs() { //preparing the level graph
        fill(all(dist), n);
        queue <int> q;
        dist[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto e : adj[u]) {
                if(edges[e].cap == 0) continue;
                int v = edges[e].v;
                if(dist[v] == n) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist[t] != n;
    }

    T dfs(int u, int flow) {
        if(u == t) return flow;
        for(; pt[u] < sz(adj[u]); pt[u]++) {
            int i = adj[u][pt[u]];
            int v = edges[i].v;
            int c = edges[i].cap;
            if(!c || dist[v] != dist[u] + 1) {
                continue;
            }
            T can_push = dfs(v, min(flow, c));
            if(can_push > 0) {
                edges[i].cap -= can_push;
                edges[i ^ 1].cap += can_push;
                //instead of keeping flow, pushing flow is like decreasing capacity, and
                //increasing capacity in its reverse.
                return can_push; //note that pt doesnt increase if this returns
            }
        }
        return T(0);
    }

    T maxFlow() {
        T ans(0);
        while(bfs()) { //there are still augmenting paths
            fill(all(pt), 0); //new iteration, restart edge pointers
            while(true) { //find blocking flow one path at a time
                T flow = dfs(s, T(1e9)); //initial infinity flow
                if(flow > 0) {
                    ans += flow;
                }
                else {
                    break;
                }
            }
        }
        return ans;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Dinic <long long> G (n, 1, n);

    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d",&a, &b, &c);
        G.addEdge(a, b, c);
    }

    printf("%lld\n", G.maxFlow());
    return 0;
}


