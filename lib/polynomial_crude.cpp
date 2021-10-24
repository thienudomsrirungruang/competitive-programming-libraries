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

#include <mod.h>

vll divide(vll a, vll b, int sz){
    int m = b.size();
    a.resize(sz+m);
    int n = a.size();
    debug(n, m);
    vll ans;
    ll ib = inv(b[0]);
    for(int i = 0; i <= sz; i++){
        debug(i);
        // divide
        ll x = mul(ib, a[i]);
        ans.push_back(x);
        for(int j = 0; j < m; j++){
            a[i+j] = add(a[i+j], normalize(-mul(x, b[j])));
        }
    }
    return ans;
}

vll multiply(vll a, vll b){
    int n = a.size(), m = b.size();
    vll ans(n+m-1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans[i+j] = add(ans[i+j], mul(a[i], b[j]));
        }
    }
}