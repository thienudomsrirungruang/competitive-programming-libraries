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

#include <modint_crude.cpp>
using mint = ModInt<int(1e9 + 7)>;

using cnum = mint;
const int N = 2e5 + 20;
cnum fact[N];
cnum inv_fact[N];
void precomp(){ // don't forget to call precomp()!
    fact[0] = mint(1);
    for(int i = 1; i < N; i++){
        fact[i] = fact[i-1] * i;
    }
    for(int i = 0; i < N; i++){
        inv_fact[i] = fact[i].inv();
    }
}

cnum ncr(ll n, ll r){
    assert(n >= 0);
    if(r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n-r];
}

cnum ncr_crude(ll n, ll r){
    cnum ans = mint(1);
    for(int i = 0; i < r; i++){
        ans = ans * cnum(i+1).inv();
        ans = ans * n-i;
    }
    return ans;
}
