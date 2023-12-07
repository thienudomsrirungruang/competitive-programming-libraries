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

#include <static_rmq.h>

// O(n log n) / O(1) static LCA.
struct LCA {
    public:
    vvi adj;
    int n;
    RMQ<pii> tour_rmq;

    private:
    vpii tour;
    vi enter;
    vi exit;
    vi depth;
    int time = 0;

    void dfs1(int u, int d, int last) {
        depth[u] = d;
        enter[u] = time;
        for(int v : adj[u]){
            if(v == last) continue;
            tour.push_back({d, u}); time++;
            dfs1(v, d + 1, u);
        }
        tour.push_back({d, u}); time++;
        exit[u] = time;
    }

    public:
    LCA(vvi &adj, int root = 0): adj(adj) {
        n = adj.size();
        enter.resize(n);
        exit.resize(n);
        depth.resize(n);
        dfs1(root, 0, -1);
        tour_rmq = RMQ<pii>(tour);
    }

    int lca(int u, int v){
        pii res = tour_rmq.query(min(enter[u], enter[v]), max(exit[u], exit[v]));
        return res.second;
    }

    inline int dist(int u, int v){
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
