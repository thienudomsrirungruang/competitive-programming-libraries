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

// recommended : use KACTL, much faster!!

const ll MOD = 998244353; // 2^23 * 119 + 1
const ll base = 1 << 20;
const ll root = 565042129; // primitive root of MOD = 3, root(2^23) = 3^119, root(2^20) = root(2^23)^(2^3)

ll binexp(ll a, ll b, ll mod = MOD){
    ll ans = 1;
    while(b){
        if(b & 1){
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

int inverse(int x){
    return binexp(x, MOD - 2);
}

void fft(vi &a, bool invert){
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        ll cur_root = root;
        ll cur_base = base;
        while(cur_base > len){
            cur_base >>= 1;
            cur_root = cur_root * cur_root % MOD;
        }
        if(invert){
            cur_root = inverse(cur_root);
        }
        for(int i = 0; i < n; i += len){
            ll cur_exp = 1;
            for(int j = 0; j < len / 2; j++){
                int u = a[i+j], v = (int) (1ll * a[i+j+len/2] * cur_exp % MOD);
                a[i+j] = u + v < MOD ? u + v : u + v - MOD;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + MOD;
                cur_exp = cur_exp * cur_root % MOD;
            }
        }
    }

    if(invert){
        int n_inv = inverse(n);
        for(int i = 0; i < n; i++){
            a[i] = (int) (1ll * a[i] * n_inv % MOD);
        }
    }
}
