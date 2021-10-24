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

template <int N>
struct Vec{
    vi v;

    Vec(){
        v.resize(N);
    }

    Vec(vi _v){
        v = _v;
    }

    Vec<N> operator+(Vec<N> other){
        Vec<N> nv;
        for(int i = 0; i < N; i++){
            nv.v[i] = v[i] + other.v[i];
        }
        return nv;
    }
    Vec<N> operator-(Vec<N> other){
        Vec<N> nv;
        for(int i = 0; i < N; i++){
            nv.v[i] = v[i] - other.v[i];
        }
        return nv;
    }
    Vec<N> operator*(int s){
        Vec<N> nv;
        for(int i = 0; i < N; i++){
            nv.v[i] = v[i] * s;
        }
        return nv;
    }

    int sum(){
        return accumulate(v.begin(), v.end(), 0);
    }

    vi nonzero(){
        vi ans;
        for(int i = 0; i < N; i++){
            if(v[i] != 0){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
template <int N>
void __print(Vec<N> x) {_print(x.v);}