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

struct TwoSat {
    private:
    vvi adj;
    vvi radj;

    void add_edge(int x, int y){
        adj[x].push_back(y);
        radj[y].push_back(x);
    }

    public:
    TwoSat(int n) {
        adj.resize(2*n);
        radj.resize(2*n);
    }

    void resize(int n){
        adj.resize(2*n);
        radj.resize(2*n);
    }

    using Var = int;

    Var var(int x, bool is_negated){
        return (x << 1) | is_negated;
    }

    Var neg(Var x){
        return x ^ 1;
    }

    // x || y
    void c_or(Var x, Var y){
        add_edge(neg(x), y);
        add_edge(neg(y), x);
    }

    // x => y
    void c_implies(Var x, Var y){
        c_or(neg(x), y);
    }

    // x xor y
    void c_xor(Var x, Var y){
        c_implies(x, neg(y));
        c_implies(neg(x), y);
    }

    // x
    void c_true(Var x){
        c_or(x, x);
    }

    // returns true if it is satisfiable. If satisfiable, also returns a satisfying arrangement.
    bool solve(vector<bool> &result){
        int n = adj.size();
        vi vis(n);
        vi order;
        vi fin(n);
        int time = 0;
        for(int i = 0; i < n; i++){
            if(vis[i]) continue;
            dfs1(i, vis, order, fin, time);
        }
        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), 0);
        vi cc(n);
        int comp = 0;
        for(int i : order){
            if(vis[i]) continue;
            dfs2(i, comp, vis, cc);
            comp++;
        }
        for(int i = 0; i < n; i+=2){
            if(cc[i] == cc[i^1]){
                return false;
            }
        }
        for(int i = 0; i < n; i+=2){
            result[i>>1] = cc[i] > cc[i^1];
        }
        return true;
    }

    private:
    void dfs1(int u, vi &vis, vi &order, vi &fin, int &time){
        vis[u] = 1;
        for(int v : adj[u]){
            if(!vis[v]){
                dfs1(v, vis, order, fin, time);
            }
        }
        order.push_back(u);
        fin[u] = time++;
    }

    void dfs2(int u, int id, vi &vis, vi &cc){
        vis[u] = 1;
        cc[u] = id;
        for(int v : radj[u]){
            if(!vis[v]){
                dfs2(v, id, vis, cc);
            }
        }
    }
};
