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

using ull = unsigned long long;
using uint = unsigned int;
using u16 = uint16_t;

// https://codeforces.com/blog/entry/103785?#comment-922682
const int S = 16;
u16 pw[1<<S];
u16 lg[1<<S];
bool log_computed = false;

struct Nimber {
    ull val;
    
    typedef Nimber N;

    explicit Nimber(ull v=0) : val(v) {}

    N operator+(const N o) const { return N(val) += o; }
    N operator-(const N o) const { return N(val) -= o; }
    N operator*(const N o) const { return N(val) *= o; }
    N operator/(const N o) const { return N(val) /= o; }

    N& operator+=(const N o) { val ^= o.val; return *this; }
    N& operator-=(const N o) { val ^= o.val; return *this; }
    N& operator*=(const N o) { val = mul(val, o.val); return *this; }
    N& operator/=(const N o) { val = mul(val, o.inv().val); return *this; }

    N pow(ull exp) const {
        N out = N(1);
        N fac = *this;
        while(exp > 0) {
            if(exp & 1) {
                out *= fac;
            }
            fac *= fac;
            exp >>= 1;
        }
        return out;
    }

    N inv() const {
        assert(val != 0);
        return this->pow(-2ULL);
    }

    private:
    static ull mul(ull a, ull b, int half = 32) {
        if(a <= 1 || b <= 1) {
            return a * b;
        }
        if(log_computed && a < (1<<S) && b < (1<<S)) {
            int t = lg[a] + lg[b];
            if(t >= (1<<S) - 1) {
                t -= (1<<S) - 1;
            }
            return pw[t];
        }
        ull mask = (1ULL << half) - 1;
        ull a0 = a & mask;
        ull a1 = a >> half;
        ull b0 = b & mask;
        ull b1 = b >> half;
        ull A = mul(a0, b0, half / 2);
        ull C = mul(a1, b1, half / 2);
        ull B = mul(a0 ^ a1, b0 ^ b1, half / 2) ^ A ^ C;

        B <<= half;
        C = (C << half) ^ mul(C, (1ULL << (half-1)), half / 2);

        return A ^ B ^ C;
    }
};

ostream& operator<<(ostream &os, Nimber x) { return os << x.val; }
istream& operator>>(istream &is, Nimber &x) { ull p; is >> p; x = Nimber(p); return is; }

void precomp_log() {
    pw[0] = 1;
    lg[1] = 0;
    Nimber base = Nimber((1ULL<<16)-1);
    for(int i = 1; i < (1<<S)-1; i++) {
        pw[i] = (Nimber(pw[i-1]) * base).val;
        lg[pw[i]] = i;
    }
    log_computed = true;
}
