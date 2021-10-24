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

ll isqrt(ll n){
    ll x = n;
    ll y = (x + 1) >> 1;
    while(y < x){
        x = y;
        y = (x + n / x) >> 1;
    }
    return x;
}

// floored division, source: kactl
ll divide(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}