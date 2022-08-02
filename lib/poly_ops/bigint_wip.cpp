// 64*W-bit integers
// todo: fast multiplication
using ull = unsigned long long;
using uint = unsigned int;
template <int W>
struct BigInt{
    ull val[W]; // little-endian
    BigInt(){
        memset(val, 0, 8*W);
    }

    BigInt(int x){
        ll y = x;
        memset(val, (y < 0 ? -1 : 0), 8*W);
        val[0] = x;
    }

    BigInt(ll x){
        memset(val, (x < 0 ? -1 : 0), 8*W);
        val[0] = x;
    }

    BigInt(uint x){
        memset(val, 0, 8*W);
        val[0] = x;
    }

    BigInt(ull x){
        memset(val, 0, 8*W);
        val[0] = x;
    }

    BigInt(const BigInt<W> &x){
        memcpy(val, x.val, 8 * W);
    }

    /* Comparisons */
    bool is_negative(){
        return val[W-1] >> 63;
    }

    /* Shifts */

    BigInt& operator<<=(const uint k){
        uint num_words = k / 64;
        uint offset = k % 64;
        if(offset != 0){
            for(int i = 0; i + num_words + 1 < K; i++){
                val[i] = val[i + num_words] << offset | (val[i + num_words + 1] >> (64-offset));
            }
            if(num_words > 0) val[K - num_words - 1]
        }
    }

    /* Arithmetic operations */

    // Optimise into add with carry: https://stackoverflow.com/questions/6659414/efficient-128-bit-addition-using-carry-flag
    BigInt& operator+=(const BigInt<W> rhs){
        val[0] += rhs.val[0];
        for(int b = 1; b < W; b++){
            val[b] += rhs.val[b] + (val[b-1] < rhs.val[b-1]);
        }
        return *this;
    }

    friend BigInt operator+(const BigInt& lhs, const BigInt& rhs) {
        return BigInt(lhs) += rhs;
    }

    BigInt& operator-=(const BigInt<W> rhs){
        return (*this) += (-rhs);
    }

    friend BigInt operator-(const BigInt& lhs, const BigInt& rhs) {
        return BigInt(lhs) -= rhs;
    }
    
    BigInt operator~() const {
        BigInt res;
        for(int b = 0; b < W; b++){
            res.val[b] = ~val[b];
        }
        return res;
    }

    BigInt operator-() const {
        return ~(*this) + 1;
    }


    // For printing
    friend ostream& operator<<(ostream &os, BigInt x) {
        return os;
    }

    friend istream& operator>>(istream &is, BigInt &x) {
        return is;
    }
};
