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

// prime mods only, source: ACL
using uint = unsigned int;
using ull = unsigned long long;
struct ModInt{
    uint _v, MOD;
    ModInt(uint MOD) : _v(0), MOD(MOD) {}
    ModInt(int val, uint MOD) : MOD(MOD) {
        int x = val % MOD;
        if(x < 0) x += MOD;
        _v = (uint) x;
    }
    ModInt(ll val, uint MOD) : MOD(MOD) {
        ll x = val % (ll) MOD;
        if(x < 0) x += MOD;
        _v = (uint) x;
    }
    ModInt(uint val, uint MOD) : MOD(MOD) {
        _v = val % MOD;
    }
    ModInt(ull val, uint MOD) : MOD(MOD) {
        _v = (uint) (val % MOD);
    }
    uint val(){ return _v; }
    ModInt& operator++(){
        _v++;
        if(_v == MOD) _v = 0;
        return *this;
    }
    ModInt& operator--(){
        if(_v == 0) _v = MOD;
        _v--;
        return *this;
    }
    ModInt operator++(int){
        ModInt result = *this;
        ++*this;
        return result;
    }
    ModInt& operator--(int){
        ModInt result = *this;
        --*this;
        return result;
    }
    ModInt& operator+=(const ModInt& rhs){
        _v += rhs._v;
        if (_v >= MOD) _v -= MOD;
        return *this;
    }
    ModInt& operator-=(const ModInt& rhs){
        _v -= rhs._v;
        if (_v >= MOD) _v += MOD;
        return *this;
    }
    ModInt& operator*=(const ModInt& rhs){
        ull z = _v;
        z *= rhs._v;
        _v = (uint)(z % MOD);
        return *this;
    }
    ModInt& operator/=(const ModInt& rhs){
        return *this = *this * rhs.inv();
    }
    ModInt operator+() const { return *this; }
    ModInt operator-() const { return ModInt(MOD) - *this; }
    ModInt pow(ll n) const {
        assert(0 <= n);
        ModInt x = *this, r = ModInt(1, MOD);
        while(n){
            if(n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    ModInt inv() const {
        assert(_v);
        return pow(MOD - 2);
    }
    friend ModInt operator+(const ModInt& lhs, const ModInt& rhs) {
        return ModInt(lhs) += rhs;
    }
    friend ModInt operator-(const ModInt& lhs, const ModInt& rhs) {
        return ModInt(lhs) -= rhs;
    }
    friend ModInt operator*(const ModInt& lhs, const ModInt& rhs) {
        return ModInt(lhs) *= rhs;
    }
    friend ModInt operator/(const ModInt& lhs, const ModInt& rhs) {
        return ModInt(lhs) /= rhs;
    }
    friend bool operator==(const ModInt& lhs, const ModInt& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const ModInt& lhs, const ModInt& rhs) {
        return lhs._v != rhs._v;
    }
};
ostream& operator<<(ostream &os, ModInt x) { return os << x.val(); }
istream& operator>>(istream &is, ModInt &x) { ll p; is >> p; x = ModInt(p); return is; }

 
const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
 
static ull splitmix64(ull x) {
    x += FIXED_RANDOM;
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}
 
const int NMODS = 2;
uint MODS[NMODS];

struct CombinedMint{
    vector<ModInt> vals;
 
    CombinedMint() {
        for(int i = 0; i < NMODS; i++){
            vals.push_back(ModInt(0, MODS[i]));
        }
    }
 
    CombinedMint(ll x) {
        for(int i = 0; i < NMODS; i++){
            vals.push_back(ModInt(x, MODS[i]));
        }
    }
 
    CombinedMint& operator++(){
        for(int i = 0; i < NMODS; i++) vals[i]++;
        return *this;
    }
    CombinedMint& operator--(){
        for(int i = 0; i < NMODS; i++) vals[i]--;
        return *this;
    }
    CombinedMint operator++(int){
        CombinedMint result = *this;
        for(int i = 0; i < NMODS; i++) vals[i]++;
        return result;
    }
    CombinedMint& operator--(int){
        CombinedMint result = *this;
        for(int i = 0; i < NMODS; i++) vals[i]--;
        return result;
    }
    CombinedMint& operator+=(const CombinedMint& rhs){
        for(int i = 0; i < NMODS; i++) vals[i] += rhs.vals[i];
        return *this;
    }
    CombinedMint& operator-=(const CombinedMint& rhs){
        for(int i = 0; i < NMODS; i++) vals[i] -= rhs.vals[i];
        return *this;
    }
    CombinedMint& operator*=(const CombinedMint& rhs){
        for(int i = 0; i < NMODS; i++) vals[i] *= rhs.vals[i];
        return *this;
    }
    CombinedMint& operator/=(const CombinedMint& rhs){
        for(int i = 0; i < NMODS; i++) vals[i] /= rhs.vals[i];
        return *this;
    }
    CombinedMint operator+() const { return *this; }
    CombinedMint operator-() const { return CombinedMint(0) - *this; }
    CombinedMint pow(ll n) const {
        CombinedMint x;
        for(int i = 0; i < NMODS; i++) x.vals[i] = vals[i].pow(n);
        return x;
    }
    CombinedMint inv() const {
        CombinedMint x;
        for(int i = 0; i < NMODS; i++) x.vals[i] = vals[i].inv();
        return x;
    }
    friend CombinedMint operator+(const CombinedMint& lhs, const CombinedMint& rhs) {
        return CombinedMint(lhs) += rhs;
    }
    friend CombinedMint operator-(const CombinedMint& lhs, const CombinedMint& rhs) {
        return CombinedMint(lhs) -= rhs;
    }
    friend CombinedMint operator*(const CombinedMint& lhs, const CombinedMint& rhs) {
        return CombinedMint(lhs) *= rhs;
    }
    friend CombinedMint operator/(const CombinedMint& lhs, const CombinedMint& rhs) {
        return CombinedMint(lhs) /= rhs;
    }
 
    ull hsh() const {
        ull ou = 0;
        for(ModInt mi : vals){
            ou = splitmix64(ou * 0x2938a4f184103fab ^ mi.val());
        }
        return ou;
    }
    friend bool operator==(const CombinedMint& lhs, const CombinedMint& rhs) {
        return lhs.hsh() == rhs.hsh();
    }
    friend bool operator!=(const CombinedMint& lhs, const CombinedMint& rhs) {
        return lhs.hsh() != rhs.hsh();
    }
};
ostream& operator<<(ostream &os, CombinedMint x) { return os << x.vals[0].val(); }