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

struct Vector{
    ll x;
    ll y;

    Vector(ll _x, ll _y){
        x = _x;
        y = _y;
    };

    Vector operator +(Vector other){
        return Vector(x + other.x, y + other.y);
    }

    Vector operator -(Vector other){
        return Vector(x - other.x, y - other.y);
    }

    // dot
    ll operator *(Vector other){
        return (ll) x * other.x + (ll) y * other.y;
    }

    bool operator ==(Vector other){
        return x == other.x && y == other.y;
    }

    ll sqlength(){
        return x * x + y * y;
    }
};


void __print(Vector p) {cerr << '{' << p.x << ", " << p.y << '}';}