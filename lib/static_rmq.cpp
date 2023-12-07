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

// O(n log n) / O(1) static RMQ, using sparse tables.
template <typename T>
struct RMQ {
    private:
    // floor(log2(x))
    inline int log2(int x){
        assert(x > 0);
        return 31 - __builtin_clz(x);
    }

    public:
    vector<T> v;
    int n;
    // sparse table
    vector<vector<T>> st;

    // assocative, idempotent
    inline T op(T x, T y) {
        return min(x, y);
    }

    RMQ(vector<T> &v): v(v) {
        n = v.size();
        int log = log2(n) + 1;
        st = vector<vector<T>>(log, vector<T>(n));
        st[0] = v;
        int step = 1;
        for(int i = 1; i < log; i++){
            for(int j = 0; j + step < n; j++){
                st[i][j] = op(st[i-1][j], st[i-1][j+step]);
            }
            step <<= 1;
        }
    }

    RMQ() {
        n = 0;
    }

    // query [l, r)
    T query(int l, int r){
        assert(0 <= l && l < r && r <= n);
        int log = log2(r-l);
        return op(st[log][l], st[log][r-(1 << log)]);
    }
};
