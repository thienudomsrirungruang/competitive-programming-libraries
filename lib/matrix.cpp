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

template <typename T>
vector<vector<T>> matmul(vector<vector<T>> a, vector<vector<T>> b){
    int x = a.size();
    int y = b.size();
    int z = b[0].size();
    assert(y == a[0].size());
    vector<vector<T>> ans(x, vector<T>(z));
    for(int i = 0; i < x; i++){
        for(int j = 0; j < z; j++){
            for(int k = 0; k < y; k++){
                ans[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return ans;
}

template <typename T>
vector<T> matmul(vector<vector<T>> a, vector<T> b){
    int x = a.size();
    int y = b.size();
    assert(y == a[0].size());
    vector<T> ans(x);
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            ans[i] += a[i][j] * b[j];
        }
    }
    return ans;
}
