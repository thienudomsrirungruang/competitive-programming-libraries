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

struct Line{
    ll m, c;
    int idx;
    Line(ll _m, ll _c, int _idx) : m(_m), c(_c), idx(_idx) {}

    ll eval(ll x){
        return m * x + c;
    }
};
// void __print(Line x) {cerr << "{m=" << x.m << ", c=" << x.c << '}';}
ostream& operator<<(ostream &os, Line x) { return os << "{m=" << x.m << ", c=" << x.c << '}'; }

// floored division, source: kactl
ll divide(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}

// returns floor(x), x is where lines intercept
ll line_intersection(Line l1, Line l2){
    assert(l1.m != l2.m);
    return divide(l2.c-l1.c, l1.m-l2.m);
}

// queries and slopes both in nondecreasing order
struct CHT{
    deque<Line> q;

    Line eval(ll x){
        assert(!q.empty());
        while(q.size() > 1 && q.front().eval(x) <= next(q.begin())->eval(x)){
            q.pop_front();
        }
        return q.front();
    }

    void add(Line l){
        if(!q.empty() && l.m == q.back().m){
            if(l.c < q.back().c){
                return;
            }else{
                q.pop_back();
            }
        }
        while(q.size() > 1 && line_intersection(q.back(), *prev(prev(q.end()))) >= line_intersection(q.back(), l)){
            q.pop_back();
        }
        q.push_back(l);
    }
};
