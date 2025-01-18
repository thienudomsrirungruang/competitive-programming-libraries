#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;
using vb = vector<bool>;
using vvb = vector<vector<bool>>;
using vd = vector<double>;
using vvd = vector<vector<double>>;
using pii = pair<int, int>;
using vpii = vector<pair<int, int>>;

using uint = unsigned int;
using ull = unsigned long long;

template<typename C> struct rge{C l, r;};
template<typename C> rge<C> range(C i, C j) { return rge<C>{i, j}; }
template<typename C> ostream& operator<<(ostream &os, rge<C> r) { os << '{'; for(auto it = r.l; it != r.r; it++) os << "," + (it == r.l) << *it; os << '}'; return os; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '{' << p.first << "," << p.second << '}'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ","; return os << '}'; }
void dbg_out() { cerr << ']' << endl; }
template<typename A> void dbg_out(A H) { cerr << H; dbg_out(); }
template<typename A, typename B, typename... C> void dbg_out(A H, B G, C... T) { cerr << H << ","; dbg_out(G, T...); }
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = [", dbg_out(__VA_ARGS__)
#else
#define debug(...)
#endif

/*
Suffix automaton.
- last is the node corresponding to the entire string
- Node::terminal encodes acceptance
- follow Node::link from nodes[last] to get suffix tree of reverse

Remember to call gen_terminal() if building incrementally (with add_char)!
*/

const int S = 26;
const char C = 'a';
struct SuffixAutomaton {
    struct Node {
        int len;
        int link;
        bool terminal = false;
        int next[S];
        Node(int len) : len(len) {
            link = -1;
            memset(next, -1, sizeof(next));
        }
    };
    friend ostream& operator<<(ostream& os, Node node) {
        os << '{' << node.len << ',' << node.link << ',' << node.terminal << ',';
        os << range(node.next, node.next + S);
        os << '}';
        return os;
    }

    int n;
    int last;
    vector<Node> nodes;
    
    void init() {
        nodes.push_back(Node(0));
        n = 1;
        last = 0;
    }

    SuffixAutomaton() {
        init();
    }

    SuffixAutomaton(string &s) {
        init();
        for(char c : s) {
            add_char(c);
        }
        gen_terminal();
    }

    void add_char(char c) {
        int idx = c - C;
        int cur = n++;
        nodes.push_back(Node(nodes[last].len + 1));
        int p = last;
        while(p != -1 && nodes[p].next[idx] == -1) {
            nodes[p].next[idx] = cur;
            p = nodes[p].link;
        }
        if(p == -1) {
            nodes[cur].link = 0;
        } else {
            int q = nodes[p].next[idx];
            if(nodes[q].len == nodes[p].len + 1) {
                nodes[cur].link = q;
            } else {
                int q2 = n++;
                nodes.push_back(Node(nodes[p].len + 1));
                nodes[q2].link = nodes[q].link;
                memcpy(nodes[q2].next, nodes[q].next, sizeof(nodes[q2].next));
                while(p != -1 && nodes[p].next[idx] == q) {
                    nodes[p].next[idx] = q2;
                    p = nodes[p].link;
                }
                nodes[q].link = nodes[cur].link = q2;
            }
        }
        last = cur;
    }

    void gen_terminal() {
        int cur = last;
        while(cur != -1) {
            nodes[cur].terminal = true;
            cur = nodes[cur].link;
        }
    }

    friend ostream& operator<<(ostream& os, SuffixAutomaton &sa) {
        for(int i = 0; i < sa.n; i++) {
            for(int c = 0; c < S; c++) {
                if(sa.nodes[i].next[c] != -1) {
                    os << i << ' ' << sa.nodes[i].next[c] << ' ' << char(C+c) << endl;
                }
            }
        }
        return os;
    }
};
