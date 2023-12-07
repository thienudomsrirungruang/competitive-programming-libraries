#include <bits/stdc++.h>

using namespace std;

#define u_map unordered_map
#define u_set unordered_set
#define u_multiset unordered_multiset

using ll = long long;
using vvi = vector<vector<int>>;
using vi = vector<int>;
using vvll = vector<vector<long long>>;
using vll = vector<long long>;
using vd = vector<double>;
using vvd = vector<vector<double>>;
using pii = pair<int, int>;
using vpii = vector<pair<int, int>>;

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

/*
(Dynamic) Li Chao Tree.

Supports range line add, point min

Initially there is one line y = 0x + INF.
*/
namespace lichao {
    const ll INF = 4'234'567'890'123'456'789;

    struct Line{
        ll m, c;
        Line(ll _m, ll _c) : m(_m), c(_c) {}

        ll eval(ll x){
            return m * x + c;
        }
    };
    // void __print(Line x) {cerr << "{m=" << x.m << ", c=" << x.c << '}';}
    ostream& operator<<(ostream &os, Line x) { return os << "{m=" << x.m << ", c=" << x.c << '}'; }

    struct Node {
        Node *l = 0, *r = 0;
        int lo, hi; // [lo, hi)
        Line line = Line(0, INF);

        Node(int lo, int hi): lo(lo), hi(hi) {}

        void push() {
            assert(lo + 1 < hi);
            if(!l) {
                int mid = lo + (hi - lo) / 2;
                l = new Node(lo, mid);
                r = new Node(mid, hi);
            }
        }

        // Insert new_line on [left, right). O(log^2 n) / O(log n) if left=0, right=n.
        void insert_line(int left, int right, Line new_line) {
            if(right <= lo || hi <= left) return;
            if(left <= lo && hi <= right) {
                bool ldiff = line.eval(lo) <= new_line.eval(lo);
                bool rdiff = line.eval(hi - 1) <= new_line.eval(hi - 1);
                if(ldiff && rdiff) return;
                if(!ldiff && !rdiff){
                    line = new_line;
                    return;
                }
                int mid = lo + (hi - lo) / 2;
                bool mdiff = line.eval(mid) <= new_line.eval(mid);
                if(!mdiff){
                    swap(line, new_line);
                }
                push();
                if(ldiff != mdiff){
                    l->insert_line(left, right, new_line);
                } else {
                    r->insert_line(left, right, new_line);
                }
                return;
            }
            push();
            l->insert_line(left, right, new_line);
            r->insert_line(left, right, new_line);
        }

        // Get min at x. O(log n).
        ll query(int x){
            assert(lo <= x && x < hi);
            if(!l){
                return line.eval(x);
            }
            ll rec;
            int mid = lo + (hi - lo) / 2;
            if(x >= mid) {
                rec = r->query(x);
            } else {
                rec = l->query(x);
            }
            return min(line.eval(x), rec);
        }
    };
}
