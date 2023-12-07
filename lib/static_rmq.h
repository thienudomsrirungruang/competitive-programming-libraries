template <typename T>
struct RMQ {

    public:
    vector<T> v;
    int n;
    // sparse table
    vector<vector<T>> st;

    // assocative, idempotent
    inline T op(T x, T y);

    RMQ(vector<T> &v);

    RMQ();

    // query [l, r)
    T query(int l, int r);
};
