#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+3;

/*
Bridge and Articulation Points finding.
complexity O(|V|+|E|) (that is O(n + m)),
actually we use set so it looks smthing like
O((|V| + |E|)log |V|). Consider changing the sets
to a bool array.  actually the bridge one can
just be a vector, the trouble comes with the artic
points.

note that you can reduce memory by n by making
Tarjan of 'int' type and make it return min_time,
which can be just a local variable.
For Undirected graphs!

verify articulation at: https://www.spoj.com/status/SUBMERGE,diegogarciam/
verify bridges at:
*/


struct BridgeAndArticulation {
    int t = 1, sz;
    vector <int> min_time, disc_time;
    vector <bool> in_stack;
    stack <int> stk;
    vector <int> *adj;

    set <pair<int, int>> bridges;
    set <int> artic_points;

    BridgeAndArticulation(vector<int> *adj_list, int n) {
        adj = adj_list;
        sz = n;
        min_time.resize(sz + 1, 0);
        disc_time.resize(sz + 1, 0);
        in_stack.resize(sz + 1, false);
        artic_points.clear(); bridges.clear();
    }


    void Tarjan(int node, int par) {
        if(disc_time[node]) return;

        int child_cnt = 0;
        disc_time[node] = min_time[node] = t++;
        stk.push(node);
        in_stack[node] = true;

        for(auto u : adj[node]) {
            //edge to parent isnt backedge
            //(consider changing that if it actually allows double edges)
            if(u == par) continue;

            if(!disc_time[u]) {
                Tarjan(u, node);
                child_cnt++;
                min_time[node] = min(min_time[node], min_time[u]);

                if(min_time[u] >= disc_time[node] && par != -1) {
                    artic_points.insert(node);
                }

                if(min_time[u] > disc_time[node]) {
                    bridges.insert({min(node, u), max(node, u)});
                }
                else {
                    //can connect (node, u) with a dsu here, for a bridge tree.
                }

            }
            else if(in_stack[u]) {
                min_time[node] = min(min_time[node], disc_time[u]);
            }
        }
        if(par == -1 && child_cnt > 1)
            artic_points.insert(node);

    }
};

//-----------------------------------------------------------
int n, m, a, b;
vector <int> adj[N];

int main()
{
    scanf("%d %d",&n,&m);

    for(int i = 0; i < m; i++)
    {
        scanf("%d %d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

   BridgeAndArticulation G(adj, n);

    for(int i = 1; i <= n; i++)
        G.Tarjan(i, -1);

    printf("articulation points:\n");
    for(auto u : G.artic_points) {
        printf("%d ", u);
    }

    printf("\nbridges:\n");
    for(auto e : G.bridges) {
        printf("(%d, %d)\n", e.first, e.second);
    }
    return 0;
}
