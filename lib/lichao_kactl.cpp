#include <bits/stdc++.h>

using namespace std;

using ll = long long;

/*
(Dynamic) Li Chao Tree.
Supports range line add, point min.
Inserting a line is O(log^2 n) (O(log n) over entire range).
Querying is O(log n).
Initially there is one line y = 0x + INF.
*/
const ll INF = 1e18;

struct Line {
    ll m, c;
    Line(ll _m, ll _c) : m(_m), c(_c) {}
    ll eval(ll x){ return m * x + c; }
};
struct Node {
    Node *l = 0, *r = 0;
    int lo, hi; // [lo, hi)
    Line line = Line(0, INF);
    Node(int lo, int hi): lo(lo), hi(hi) {}
    void push() {
        if(!l) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
    }
    void ins(int L, int R, Line new_line) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            bool ldiff = line.eval(lo) <= new_line.eval(lo);
            bool rdiff = line.eval(hi - 1) <= new_line.eval(hi - 1);
            if(!ldiff && !rdiff) line = new_line;
            if(ldiff == rdiff) return;
            int mid = lo + (hi - lo) / 2;
            bool mdiff = line.eval(mid) <= new_line.eval(mid);
            if(!mdiff) swap(line, new_line);
            push();
            if(ldiff != mdiff) l->ins(L, R, new_line);
            else r->ins(L, R, new_line);
            return;
        }
        push();
        l->ins(L, R, new_line);
        r->ins(L, R, new_line);
    }
    ll query(int x){
        if(!l) return line.eval(x);
        return min(line.eval(x), (x<l->hi?l:r)->query(x));
    }
};
