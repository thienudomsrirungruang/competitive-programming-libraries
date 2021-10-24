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

vvll multiply(vvll a, vvll b){
    int x = a.size();
    int y = b.size();
    int z = b[0].size();
    assert(y == a[0].size());
    vvll ans(x, vll(z));
    for(int i = 0; i < x; i++){
        for(int j = 0; j < z; j++){
            for(int k = 0; k < y; k++){
                ans[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ans;
}