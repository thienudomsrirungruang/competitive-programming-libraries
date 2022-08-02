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


const ll INF = 1e18;

// segtree beats
struct Node{
    // invariant: *if* all ancestors have madd = 0,
    //            max1 and max2 are first and second max
    //            maxc is count of max1
    //            similar for min

    int lo, hi, mid, sz;
    Node *l, *r;

    // state
    ll max1, max2, maxc, min1, min2, minc;
    ll sum, madd = 0;

    Node(vll &v, int lo, int hi) : lo(lo), hi(hi){
        mid = lo + (hi - lo) / 2;
        sz = hi - lo;
        if(sz == 1){
            sum = v[lo];
            max1 = v[lo];
            max2 = -INF;
            maxc = 1;
            min1 = v[lo];
            min2 = INF;
            minc = 1;
        }else{
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            update();
        }
    }

    // pre: you and all ancestors must have no lazy state
    void update(){
        assert(lo + 1 < hi);
        assert(madd == 0); // all ancestors must also have madd = 0, but this is not checked
        sum = l->sum + r->sum;
        if(l->max1 == r->max1){
            max1 = l->max1;
            max2 = max(l->max2, r->max2);
            maxc = l->maxc + r->maxc;
        }else if(l->max1 < r->max1){
            max1 = r->max1;
            max2 = max(l->max1, r->max2);
            maxc = r->maxc;
        }else{
            max1 = l->max1;
            max2 = max(l->max2, r->max1);
            maxc = l->maxc;
        }
        if(l->min1 == r->min1){
            min1 = l->min1;
            min2 = min(l->min2, r->min2);
            minc = l->minc + r->minc;
        }else if(l->min1 > r->min1){
            min1 = r->min1;
            min2 = min(l->min1, r->min2);
            minc = r->minc;
        }else{
            min1 = l->min1;
            min2 = min(l->min2, r->min1);
            minc = l->minc;
        }
        // debug("update", lo, hi, min1, min2, max2, max1, sum);
    }

    void upd_add(int a, int b, ll val){
        // debug("upd_add", a, b, val, lo, hi, min1, min2, max2, max1);
        if(b <= lo || hi <= a) return;
        if(a <= lo && hi <= b){
            madd += val;
            sum += (ll) sz * val;
            max1 += val;
            max2 += val;
            min1 += val;
            min2 += val;
        }else{
            push();
            l->upd_add(a, b, val);
            r->upd_add(a, b, val);
            update();
        }
    }

    // min(val, x)
    void upd_chmin(int a, int b, ll val){
        // debug("upd_chmin", a, b, val, lo, hi, min1, min2, max2, max1);
        if(b <= lo || hi <= a) return;
        if(a <= lo && hi <= b && val >= max1) return;
        if(a <= lo && hi <= b && val > max2){
            sum -= maxc * (max1 - val);
            max1 = val;
            if(val <= min1){ // only one distinct value
                min1 = val;
                min2 = INF;
            }else if(val < min2){ // now max1 = min2
                min2 = val;
            }
        }else if(sz == 1){
            max1 = min(val, sum);
            min1 = min(val, sum);
            sum = min(val, sum);
        }else{
            push();
            l->upd_chmin(a, b, val);
            r->upd_chmin(a, b, val);
            update();
        }
    }

    // max(val, x)
    void upd_chmax(int a, int b, ll val){
        // debug("upd_chmax", a, b, val, lo, hi, min1, min2, max2, max1);
        if(b <= lo || hi <= a) return;
        if(a <= lo && hi <= b && val <= min1) return;
        if(a <= lo && hi <= b && val < min2){
            sum += minc * (val - min1);
            min1 = val;
            if(val >= max1){ // only one distinct value
                max1 = val;
                max2 = -INF;
            }else if(val > max2){ // now min1 = max2
                max2 = val;
            }
        }else if(sz == 1){
            max1 = max(val, sum);
            min1 = max(val, sum);
            sum = max(val, sum);
        }else{
            push();
            l->upd_chmax(a, b, val);
            r->upd_chmax(a, b, val);
            update();
        }
    }

    // pre: no lazy state in ancestors
    // post: no lazy state in you and ancestors
    void push(){
        assert(sz > 1);
        if(madd != 0){
            l->upd_add(lo, hi, madd);
            r->upd_add(lo, hi, madd);
            madd = 0;
        }
        l->upd_chmin(lo, hi, max1);
        r->upd_chmin(lo, hi, max1);
        l->upd_chmax(lo, hi, min1);
        r->upd_chmax(lo, hi, min1);
        update();
    }

    ll get_sum(int a, int b){
        // debug("get_sum", a, b, lo, hi, min1, min2, max2, max1);
        if(b <= lo || hi <= a) return 0;
        if(a <= lo && hi <= b) return sum;
        push();
        return l->get_sum(a, b) + r->get_sum(a, b);
    }
};
ostream& operator<<(ostream &os, Node *n) {
    os << '[' << n->lo << ", " << n->hi << ") " << n->sum << ' ' << n->min1 << ' ' << n->min2 << ' ' << n->max2 << ' ' << n->max1 << " (" << n->madd << ')' << endl;
    if(n->sz > 1) os << n->l << n->r;
    return os;
}