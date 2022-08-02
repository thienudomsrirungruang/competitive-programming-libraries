#include <bits/stdc++.h>
#include <modint_crude.cpp>

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

template <typename T>
struct Poly{
    vector<T> coeff;

    T & operator[] (int x) {
        return coeff[x];
    }

    Poly() { }

    Poly(int sz) { coeff.resize(sz); }
    Poly(unsigned int sz) { coeff.resize(sz); }
    Poly(ll sz) { coeff.resize(sz); }
    Poly(unsigned long long sz) { coeff.resize(sz); }

    template <typename R>
    Poly(vector<R> vec){
        coeff.resize(vec.size());
        for(int i = 0; i < vec.size(); i++){
            coeff[i] = T(vec[i]);
        }
    }

    template <typename R>
    Poly(Poly<R> poly){
        coeff.resize(poly.size());
        for(int i = 0; i < poly.size(); i++){
            coeff[i] = T(poly[i]);
        }
    }

    int size() const {
        return coeff.size();
    }

    void resize(int sz) {
        coeff.resize(sz);
    }

    Poly<T> to_size(int sz) const {
        Poly<T> res(*this);
        res.resize(sz);
        return res;
    }

    bool empty() const {
        return coeff.empty();
    }


    /* Trivial ops */
    
    Poly<T> operator+(Poly<T> other){
        Poly<T> res(max(size(), other.size()));
        for(int i = 0; i < res.size(); i++){
            res[i] = ((size() > i) ? coeff[i] : T(0)) + ((other.size() > i) ? other[i] : T(0));
        }
        return res;
    }

    void operator+=(const Poly<T> other){
        if(other.size() > size()){
            coeff.resize(other.size());
        }
        for(int i = 0; i < other.size(); i++){
            coeff += other[i];
        }
    }

    Poly<T> operator-(Poly<T> other){
        Poly<T> res(max(size(), other.size()));
        for(int i = 0; i < res.size(); i++){
            res[i] = ((size() > i) ? coeff[i] : T(0)) - ((other.size() > i) ? other[i] : T(0));
        }
        return res;
    }

    void operator-=(const Poly<T> other){
        if(other.size() > size()){
            coeff.resize(other.size());
        }
        for(int i = 0; i < other.size(); i++){
            coeff += other[i];
        }
    }
    
    Poly<T> operator*(const T scalar) const {
        Poly<T> res(size());
        for(int i = 0; i < size(); i++){
            res[i] = coeff[i] * scalar;
        }
        return res;
    }

    void operator*=(const T scalar){
        for(int i = 0; i < size(); i++){
            coeff[i] *= scalar;
        }
    }

    Poly<T> operator/(const T scalar) const {
        Poly<T> res(size());
        for(int i = 0; i < size(); i++){
            res[i] = coeff[i] / scalar;
        }
        return res;
    }

    void operator/=(const T scalar){
        for(int i = 0; i < size(); i++){
            coeff[i] /= scalar;
        }
    }

    // testing equality for zero: x == Poly<T>()
    bool operator==(Poly<T> other) {
        for(int i = 0; i < max(size(), other.size()); i++){
            if(((size() > i) ? coeff[i] : T(0)) != ((other.size() > i) ? other[i] : T(0))) return false;
        }
        return true;
    }

    bool operator!=(Poly<T> other) {
        return !(*this == other);
    }

    // Computes the polynomial evaluated at x.
    T operator()(T x){
        T res = T(0);
        for(int i = size() - 1; i >= 0; i--){
            res = res * x;
            res = res + coeff[i];
        }
        return res;
    }



    /* FFT ops */

    Poly<T> operator*(const Poly<T> other) const {
        return multiply(*this, other);
    }

    // F.inv(n) returns a polynomial R such that F * R = 1 (mod z^n).
    // This means all nonzero coefficients of exponents < n are zero under the field.
    // The length of the returned polynomial will be the smallest power of two >= n.
    // Explanation: https://codeforces.com/blog/entry/12513 (editorial for div1E)
    Poly<T> inv(int n) const {
        assert(coeff.size() > 0);
        assert(coeff[0] != T(0));
        Poly<T> res = Poly<T>(vector<T>{T(1) / coeff[0]});
        int m = 1;
        while(m < n){
            m <<= 1;
            res = (res * T(2)) - (res * res * (*this)).to_size(m);
        }
        return res;
    }

    // F.sqrt(n) returns a polynomial S such that S * S = 1 (mod z^n).
    // This means all nonzero coefficients of exponents < n are zero under the field.
    // The length of the returned polynomial will be at least n.
    // Explanation: https://codeforces.com/blog/entry/12513 (editorial for div1E)
    // If using mod-ints, please check that the square root exists before calling.
    Poly<T> sqrt(int n) const {
        int i;
        for(i = 0; i < coeff.size() && coeff[i] == 0; i++) {}
        if(i == coeff.size()) {
            return Poly<T>(n);
        }
        assert(i % 2 == 0); // if not, no solutions
        Poly<T> nz = Poly<T>(vector<T>(coeff.begin() + i, coeff.end()));
        Poly<T> res = Poly<T>(vector<T>{find_sqrt(nz[0])});
        int m = 1;
        while(m+i/2 < n){
            m <<= 1;
            res = (res + (res.inv(m) * nz).to_size(m)) / T(2);
        }
        debug(res, nz, m, i);
        vector<T> padded_coeff(m+i/2);
        copy(res.coeff.begin(), res.coeff.end(), padded_coeff.begin() + i/2);
        Poly<T> padded_res = Poly<T>(padded_coeff);
        return padded_res;
    }
    
    private:

    template<uint M>
    static ModInt<M> find_sqrt(ModInt<M> x){
        return x.sqrt();
    }
    
    static double find_sqrt(double x){
        return ::sqrt(x);
    }


    /* FFT corner */

    /* Multiplication pattern matching */
    template <uint _MOD>
    static Poly<ModInt<_MOD>> multiply(Poly<ModInt<_MOD>> a, Poly<ModInt<_MOD>> b){
        int root = primitive_root_constexpr(_MOD);
        if(root == -1){
            #ifdef DEBUG
            cerr << "[WARN] *** Using arbitrary-mod FFT, comment to ignore" << endl;
            #endif
            return conv_mod(a.coeff, b.coeff);
        }else{
            return conv_ntt(a, b, ModInt<_MOD>(root));
        }
    }

    // See util/generate_primitive_root.cpp to generate more
    static constexpr int primitive_root_constexpr(uint m) {
        switch(m){
            case 2:          return 1;
            case 167772161:  return 3;
            case 469762049:  return 3;
            case 754974721:  return 11;
            case 998244353:  return 3;
            case 1004535809: return 3;
            case 1012924417: return 5;

            default:         return -1;
        }
    }

    static Poly<double> multiply(Poly<double> a, Poly<double> b){
        return conv(a, b);
    }
    
    /* For mods of FFT-able form */
    template <uint _MOD>
    static void ntt(vector<ModInt<_MOD>> &a, ModInt<_MOD> _root) {
        using _mint = ModInt<_MOD>;
        int n = a.size(), L = 31 - __builtin_clz(n);
        vector<_mint> rt(2, 1);
        for (int k = 2, s = 2; k < n; k *= 2, s++) {
            rt.resize(n);
            _mint z[] = {1, _root.pow(_MOD >> s)};
            for(int i = k; i < 2*k; i++) rt[i] = rt[i / 2] * z[i & 1];
        }
        vi rev(n);
        for(int i = 0; i < n; i++){
            rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        }
        for(int i = 0; i < n; i++){
            if (i < rev[i]){
                swap(a[i], a[rev[i]]);
            }
        }
        for (int k = 1; k < n; k *= 2){
            for (int i = 0; i < n; i += 2 * k){
                for(int j = 0; j < k; j++) {
                    _mint z = rt[j + k] * a[i + j + k], &ai = a[i + j];
                    a[i + j + k] = ai - z;
                    ai += z;
                }
            }
        }
    }

    template <uint _MOD>
    static Poly<ModInt<_MOD>> conv_ntt(const Poly<ModInt<_MOD>> &a, const Poly<ModInt<_MOD>> &b, ModInt<_MOD> _root) {
        using _mint = ModInt<_MOD>;
        if (a.empty() || b.empty()) return Poly<_mint>();
        int s = a.size() + b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
        _mint inv = _mint(n).inv();
        vector<_mint> L(a.coeff), R(b.coeff), out(n);
        L.resize(n), R.resize(n);
        ntt(L, _root);
        ntt(R, _root);
        for(int i = 0; i < n; i++){
            out[-i & (n - 1)] = L[i] * R[i] * inv;
        }
        ntt(out, _root);
        return Poly<_mint>(vector<_mint>(out.begin(), out.begin() + s));
    }

    /* Doubles and arbitrary-mod */
    // Arbitrary-mod works when n*log n*mod < 8.6*10^14 (source: kactl)

    using C = complex<double>;

    static void fft(vector<C>& a) {
        int n = a.size(), L = 31 - __builtin_clz(n);
        static vector<complex<long double>> R(2, 1);
        static vector<C> rt(2, 1);  // (^ 10% faster if double)
        for (static int k = 2; k < n; k *= 2) {
            R.resize(n); rt.resize(n);
            auto x = polar(1.0L, acos(-1.0L) / k);
            for(int i = k; i < 2*k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
        }
        vi rev(n);
        for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        for(int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2){
            for (int i = 0; i < n; i += 2 * k) {
                for(int j = 0; j < k; j++) {
                    auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];
                    C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
            }
        }
    }
    static Poly<double> conv(const Poly<double> a, const Poly<double> b) {
        if (a.empty() || b.empty()) return Poly<double>();
        vd res(a.size() + b.size() - 1);
        int L = 32 - __builtin_clz(res.size()), n = 1 << L;
        vector<C> in(n), out(n);
        copy(a.coeff.begin(), a.coeff.end(), begin(in));
        for(int i = 0; i < b.size(); i++) in[i].imag(b.coeff[i]);
        fft(in);
        for (C& x : in) x *= x;
        for(int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
        fft(out);
        for(int i = 0; i < res.size(); i++) res[i] = imag(out[i]) / (4 * n);
        return Poly<double>(res);
    }

    template <uint M>
    static Poly<ModInt<M>> conv_mod(vector<ModInt<M>> &a, vector<ModInt<M>> &b) {
        if (a.empty() || b.empty()) return {};
        Poly<ModInt<M>> res((int) (a.size() + b.size() - 1));
        int B=32-__builtin_clz(res.size()), n=1<<B, cut=int(::sqrt(M));
        vector<C> L(n), R(n), outs(n), outl(n);
        for(int i = 0; i < a.size(); i++) L[i] = C((int)(a[i].val()) / cut, (int)(a[i].val()) % cut);
        for(int i = 0; i < b.size(); i++) R[i] = C((int)(b[i].val()) / cut, (int)(b[i].val()) % cut);
        fft(L), fft(R);
        for(int i = 0; i < n; i++) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
        fft(outl), fft(outs);
        for(int i = 0; i < res.size(); i++) {
            ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
            ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
            res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        }
        return res;
    }
};

template<typename T> ostream& operator<<(ostream &os, Poly<T> x) { return os << "<Poly " << x.coeff << ">"; }

/* TODO: Runtime arbitrary mod */
