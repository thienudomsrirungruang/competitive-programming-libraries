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

struct XorBasis {
    // inv: msb of basis is decreasing
    vi basis;

    XorBasis() {}

    int dim() {return basis.size();}

    // add a vector to the basis, if it's independent.
    // O(dim)
    void add(int x){
        for(int i = 0; i < basis.size(); i++){
            int b = basis[i];
            if(x == 0) return;
            if(clz(b) > clz(x)){
                basis.insert(basis.begin() + i, x);
                return;
            }
            if(clz(b) == clz(x)){
                x ^= b;
            }
        }
        if(x > 0) basis.push_back(x);
    }

    void merge_with(XorBasis* a){
        for(int i : a->basis) {
            this->add(i);
        }
    }

    friend XorBasis* merge_basis(XorBasis* a, XorBasis* b){
        if(a->dim() < b->dim()) swap(a, b);
        XorBasis* x = new XorBasis();
        x->basis = a->basis;
        for(int i : b->basis) {
            x->add(i);
        }
        return x;
    }

    // maximum element in the subspace.
    // O(dim)
    int max_element(){
        int ans = 0;
        for(int i : basis){
            ans = max(ans, ans ^ i);
        }
        return ans;
    }

    private:
    int clz(int x){
        if(x == 0) return 32;
        return __builtin_clz(x);
    }
};