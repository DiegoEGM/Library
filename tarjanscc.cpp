#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+3;

/*
complexity O(|V|+|E|) (that is O(n + m)).
note that you can reduce memory by n by making
Tarjan of 'int' type and make it return min_time,
which can be just a local variable. (that is,
no longer using the min_time vector).
For directed graphs!
*/


struct SCC {
    int t = 1, sz;
    vector <int> min_time, disc_time;
    vector <bool> in_stack;
    stack <int> stk;
    vector <int> *adj;

   SCC(vector<int> *adj_list, int n) {
        adj = adj_list, sz = n;
        min_time.resize(sz + 1, 0);
        disc_time.resize(sz + 1, 0);
        in_stack.resize(sz + 1, false);
    }

    //process the scc with node as its root/head.
    void processSCC(int node) {
        int top;
        do {
            top = stk.top();
            stk.pop();
            in_stack[top] = false;
        } while(top != node);
    }

    void Tarjan(int node) {
        if(disc_time[node]) return;

        disc_time[node] = min_time[node] = t++;
        stk.push(node);
        in_stack[node] = true;

        for(auto u : adj[node]) {
            if(!disc_time[u]) {
                Tarjan(u);
                min_time[node] = min(min_time[node], min_time[u]);
            }
            else if(in_stack[u]) {
                min_time[node] = min(min_time[node], disc_time[u]);
            }
        }

        if(min_time[node] == disc_time[node]) { //its the 'head' of a component
            processSCC(node);
        }
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
    }

   SCC G(adj, n);

    for(int i = 1; i <= n; i++)
        G.Tarjan(i);

    return 0;
}

/* Sample
8 10
1 2
2 3
3 4
4 3
2 5
5 6
6 7
7 8
7 5
8 5
should be {{1}, {2}, {3, 4}, {5, 6, 7, 8}}
*/
