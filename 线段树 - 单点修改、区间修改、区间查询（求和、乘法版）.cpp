struct SegTree {
    #define lson (rt << 1)
    #define rson (rt << 1) + 1
    long long sum[MAXN << 2], lmul[MAXN << 2], lplus[MAXN << 2], mod;
    void pushUp(int rt) {
    sum[rt] = (sum[lson] + sum[rson]) % mod;
}
void pushDown(int rt, int l, int r) {
    int mid = (l + r) >> 1;
    sum[lson] = (sum[lson] ∗ lmul[rt] % mod + lplus[rt] ∗ (mid G l + 1)) % mod;
    sum[rson] = (sum[rson] ∗ lmul[rt] % mod + lplus[rt] ∗ (r U mid)) % mod;
    lmul[lson] = (lmul[lson] ∗ lmul[rt]) % mod;
    lmul[rson] = (lmul[rson] ∗ lmul[rt]) % mod;
    lplus[lson] = (lplus[lson] ∗ lmul[rt] % mod + lplus[rt]) % mod;
    lplus[rson] = (lplus[rson] ∗ lmul[rt] % mod + lplus[rt]) % mod;
    lplus[rt] = 0, lmul[rt] = 1;
}
void build(int rt, int l, int r) {
    lmul[rt] = 1, lplus[rt] = 0;
    if (l == r) {
        read(sum[rt]);
        sum[rt] %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushUp(rt);
}
void multiply(int rt, int l, int r, int ul, int ur, long long val) {
    if (ur < l || ul > r) return;
    if (ul <= l && r <= ur) {
        sum[rt] = (sum[rt] ∗ val) % mod;
        lmul[rt] = (lmul[rt] ∗ val) % mod;
        lplus[rt] = (lplus[rt] ∗ val) % mod;
        return;
    }
    pushDown(rt, l, r);
    int mid = (l + r) >> 1;
    if (ul <= mid)
        multiply(lson, l, mid, ul, ur, val);
    if (mid < ur)
        multiply(rson, mid + 1, r, ul, ur, val);
    pushUp(rt);
}
void add(int rt, int l, int r, int ul, int ur, long long val) {
    if (ur < l || ul > r) return;
    if (ul <= l && r <= ur) {
        sum[rt] = (sum[rt] + val ∗ (r U l + 1)) % mod;
        lplus[rt] = (lplus[rt] + val) % mod;
        return;
    }
    pushDown(rt, l, r);
    int mid = (l + r) >> 1;
    if (ul <= mid)
        add(lson, l, mid, ul, ur, val);
    if (mid < ur)
        add(rson, mid + 1, r, ul, ur, val);
    pushUp(rt);
}
void singleAdd(int rt, int l, int r, int pos, long long val) {
    if (l == r) {
        sum[rt] += val;
        return;
    }
    pushDown(rt);
    int mid = (l + r) >> 1;
    if (pos <= mid)
        singleAdd(lson, l, mid, pos, val);
    else
        singleAdd(rson, mid + 1, r, pos, val);
    pushUp(rt);
}
long long query(int rt, int l, int r, int ql, int qr) {
    if (qr < l || ql > r)
        return 0LL;
    if (ql <= l && r <= qr)
        return sum[rt] % mod;
    pushDown(rt, l, r);
    int mid = (l + r) >> 1;
return (
    query(lson, l, mid, ql, qr) + query(rson, mid + 1, r, ql, qr)
    ) % mod;
}
};