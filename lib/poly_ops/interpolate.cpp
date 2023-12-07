#include <bits/stdc++.h>
#include <poly.cpp>

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

using uint = unsigned int;

// Adapted from kactl
template <typename T>
Poly<T> interpolate(vector<T> x, vector<T> y) {
    int n = x.size();
    assert(y.size() == n);
    vector<T> res(n), temp(n);
    for(int k = 0; k < n-1; k++){
        for(int i = k+1; i < n; i++){
            y[i] = (y[i] - y[k]) / (x[i] - x[k]);
        }
    }
    T last = 0; temp[0] = 1;
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++) {
            res[i] += y[k] * temp[i];
            swap(last, temp[i]);
            temp[i] -= last * x[k];
        }
    }
    return res;
}
