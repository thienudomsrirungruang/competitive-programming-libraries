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

void init_random(){
    // 32-bit
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // 64-bit
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
}
