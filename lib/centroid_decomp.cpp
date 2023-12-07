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

#include <lca.h>

struct CentroidDecomp {
    private:
    
    vi vis;
    int n;
    vi sz;

    vvi adj;

    void dfs_sz(int u, int last) {
        sz[u] = 1;
        for(int v : adj[u]){
            if(v == last || vis[v]) continue;
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }

    int dfs_cen(int u, int last, int total_sz) {
        for(int v : adj[u]){
            if(v == last || vis[v]) continue;
            if(sz[v] * 2 > total_sz){
                return dfs_cen(v, u, total_sz);
            }
        }
        return u;
    }

    inline int find_centroid(int u) {
        dfs_sz(u, -1);
        return dfs_cen(u, -1, sz[u]);
    }

    public:
    // input: tree in adj
    // output: par[i] is the parent of node i, -1 if no parent
    vi decomp(vvi &_adj) {
        adj = _adj;
        n = adj.size();
        vis.clear();
        vis.resize(n);
        sz.clear();
        sz.resize(n);

        vi par(n);
        queue<pii> nodes;
        nodes.push({0, -1});

        while(!nodes.empty()) {
            int u, p;
            tie(u, p) = nodes.front();
            nodes.pop();
            int c = find_centroid(u);
            vis[c] = 1;
            par[c] = p;
            for(int v : adj[c]){
                if(vis[v]) continue;
                nodes.push({v, c});
            }
        }
        return par;
    }
};


void dfs1(int u, int last, vvi &adj, vi &depth){
    for(int v : adj[u]){
        if(v == last) continue;
        depth[v] = depth[u] + 1;
        dfs1(v, u, adj, depth);
    }
}

inline int dist(int u, int v, vi &depth, LCA &lca){
    return depth[u] + depth[v] - 2 * depth[lca.lca(u, v)];
}

void solve(){
    int n, q;
    cin >> n >> q;
    vvi adj(n);
    for(int i = 0; i < n-1; i++){
        int x, y;
        cin >> x >> y;
        x--;y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    vi centroid_par = CentroidDecomp().decomp(adj);

    vi depth(n);
    dfs1(0, -1, adj, depth);

    LCA lca(adj);

    vi dp = depth; // hacky but works?

    while(q--){
        int t, v;
        cin >> t >> v;
        v--;
        if(t == 1){ // update node v to red
            int cur = v;
            while(cur != -1){
                dp[cur] = min(dp[cur], dist(v, cur, depth, lca));
                cur = centroid_par[cur];
            }
        } else { // query closest to v
            int ans = 1e9;
            int cur = v;
            int lft = 0;
            while(cur != -1){
                ans = min(ans, dist(v, cur, depth, lca) + dp[cur]);
                cur = centroid_par[cur];
            }
            cout << ans << endl;
        }
    }
};
