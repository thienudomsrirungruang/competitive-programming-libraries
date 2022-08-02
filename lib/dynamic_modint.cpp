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

template<typename C> struct rge{C l, r;};
template<typename C> rge<C> range(C i, C j) { return rge<C>{i, j}; }
template<typename C> ostream& operator<<(ostream &os, rge<C> &r) { os << '{'; for(auto it = r.l; it != r.r; it++) os << "," + (it == r.l) << *it; os << '}'; return os; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '{' << p.first << "," << p.second << '}'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ","; return os << '}'; }
void dbg_out() { cerr << ']' << endl; }
template<typename A> void dbg_out(A H) { cerr << H; dbg_out(); }
template<typename A, typename B, typename... C> void dbg_out(A H, B G, C... T) { cerr << H << ","; dbg_out(G, T...); }
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = [", dbg_out(__VA_ARGS__)
#else
#define debug(...)
#endif



// prime mods only, adapted from ACL
using uint = unsigned int;
using ull = unsigned long long;

uint MOD; // initialise this!
struct ModIntA{
    uint _v;
    ModIntA() : _v(0) {}
    ModIntA(int val) {
        int x = val % (int) MOD;
        if(x < 0) x += MOD;
        _v = (uint) x;
    }
    ModIntA(ll val){
        ll x = val % (ll) MOD;
        if(x < 0) x += MOD;
        _v = (uint) x;
    }
    ModIntA(uint val) {
        _v = val % MOD;
    }
    ModIntA(ull val) {
        _v = (uint) (val % MOD);
    }
    uint val(){ return _v; }
    ModIntA& operator++(){
        _v++;
        if(_v == MOD) _v = 0;
        return *this;
    }
    ModIntA& operator--(){
        if(_v == 0) _v = MOD;
        _v--;
        return *this;
    }
    ModIntA operator++(int){
        ModIntA result = *this;
        ++*this;
        return result;
    }
    ModIntA& operator--(int){
        ModIntA result = *this;
        --*this;
        return result;
    }
    ModIntA& operator+=(const ModIntA& rhs){
        _v += rhs._v;
        if (_v >= MOD) _v -= MOD;
        return *this;
    }
    ModIntA& operator-=(const ModIntA& rhs){
        _v -= rhs._v;
        if (_v >= MOD) _v += MOD;
        return *this;
    }
    ModIntA& operator*=(const ModIntA& rhs){
        ull z = _v;
        z *= rhs._v;
        _v = (uint)(z % MOD);
        return *this;
    }
    ModIntA& operator/=(const ModIntA& rhs){
        return *this = *this * rhs.inv();
    }
    ModIntA operator+() const { return *this; }
    ModIntA operator-() const { return ModIntA() - *this; }
    ModIntA pow(ll n) const {
        assert(0 <= n);
        ModIntA x = *this, r = 1;
        while(n){
            if(n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    ModIntA inv() const {
        assert(_v);
        return pow(MOD - 2);
    }
    friend ModIntA operator+(const ModIntA& lhs, const ModIntA& rhs) {
        return ModIntA(lhs) += rhs;
    }
    friend ModIntA operator-(const ModIntA& lhs, const ModIntA& rhs) {
        return ModIntA(lhs) -= rhs;
    }
    friend ModIntA operator*(const ModIntA& lhs, const ModIntA& rhs) {
        return ModIntA(lhs) *= rhs;
    }
    friend ModIntA operator/(const ModIntA& lhs, const ModIntA& rhs) {
        return ModIntA(lhs) /= rhs;
    }
    friend bool operator==(const ModIntA& lhs, const ModIntA& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const ModIntA& lhs, const ModIntA& rhs) {
        return lhs._v != rhs._v;
    }
};
ostream& operator<<(ostream &os, ModIntA x) { return os << x.val(); }
istream& operator>>(istream &is, ModIntA &x) { ll p; is >> p; x = ModIntA(p); return is; }

// TODO: sqrt
