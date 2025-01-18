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
template<typename C> ostream& operator<<(ostream &os, rge<C> &r) { os << '{'; for(auto it = r.l; it != r.r; it++) os << "," + (it == r.l) << *it; os << '}'; return os; }
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

struct Node {
    Node *l, *r;
    int lo, hi;

    void refresh() {
        // ...
    }

    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 == hi) {
            // ...
        } else {
            int mid = (lo + hi) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
            refresh();
        }
    }

    int query(int L, int R) {
        if(hi <= L || R <= lo) {
            // ...
            return 0;
        }
        if(L <= lo && hi <= R) {
            // ...
            return val;
        }
        // ...
    }

    void set(int L, int R, int x) {
        if(hi <= L || R <= lo) {
            return;
        }
        if(L <= lo && hi <= R) {
            // ...
            return;
        }
        // ...
        l->set(L, R, x);
        r->set(L, R, x);
        refresh();
    }
};

ostream& operator<<(ostream& os, Node *n) {
    os << n->lo << ' ' << n->hi << endl;
    if(n->lo + 1 < n->hi) {
        os << n->l;
        os << n->r;
    }
    return os;
}
