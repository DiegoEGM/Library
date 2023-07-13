//to-do: make this more general
const int S = 26;
const char off = 'a';

struct Aho {
    struct Node {
        int go[S];
        int p, link;
        bool terminal;
        char p_ch;
        Node(int p = -1, char p_ch = '$') : p(p), link(-1), terminal(false), p_ch(p_ch)  {
            fill(go, go + S, -1);
        }
    };
    vector <Node> t;
    Aho() : t(1) {}
    int add_string(string &s) { //returns the end of the string
        int u = 0;
        for(char c : s) {
            if(t[u].go[c - off] == -1) {
                t[u].go[c - off] = sz(t);
                t.pb(Node(u, c));
            }
            u = t[u].go[c - off];
        }
        t[u].terminal = true;
        return u;
    }
    int go(int u, char c) {
        if(t[u].go[c - off] != -1) return t[u].go[c - off];
        return t[u].go[c - off] = u ? go(get_link(u), c) : 0;
    }
    int get_link(int u) {
        if(t[u].link != -1) return t[u].link;
        if(!u || !t[u].p) return t[u].link = 0;
        return t[u].link = go(get_link(t[u].p), t[u].p_ch);
    }
};
