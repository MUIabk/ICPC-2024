struct wavelet{
    struct Info{
        int st, lc, rc;
        Info():Info(0,-1,-1){}
        Info(int st, int lc, int rc){
            this->st = st;
            this->lc = lc;
            this->rc = rc;
        }
    };
    int mn = inf, mx = 0, n;
    vector<int> p, a;
    vector<Info> wt;
    // to reduce log(mxe(a)) to log(n) perform coordinate compression 
    wavelet(vector<int>&a){
        n = sz(a);
        for(auto &x : a){
            mx = max(mx, x);
            mn = min(mn, x);
        }
        this->a = a;
        build(this->a.begin(), this->a.end(), mn, mx);
    }
    template<typename IT>
    void build(IT from, IT to, int lo, int hi){
        int m = hi + lo >> 1;
        auto f = [&](int x){ return x <= m; };
        p.pb(0);
        int i = sz(wt);
        wt.push_back(Info());
        wt[i].st = sz(p);
        for(auto it = from; it != to; ++it) {
            p.push_back(p.back() + f(*it));
        }
        if(lo == hi or from == to)return;
        auto it = stable_partition(from, to, f);
        wt[i].lc = sz(wt);
        build(from, it, lo, m);
        wt[i].rc = sz(wt);
        build(it, to, m + 1, hi);
    }
    int equals(int i, int l, int r, int val, int lo, int hi){
        if(l > r)return 0;
        if(lo == hi){
            if(lo == val)return p[wt[i].st + r] - p[wt[i].st + l - 1];
            return 0;
        }
        int m = hi + lo >> 1;
        int lp = p[wt[i].st + l - 1], rp = p[wt[i].st + r];
        if(val <= m)return equals(wt[i].lc, lp, rp - 1, val, lo, m); 
        return equals(wt[i].rc, l - lp, r - rp , val, m + 1, hi);
    }
    int less_equals(int i, int l, int r, int val, int lo, int hi){
        if(l > r or lo > val)return 0;
        if(hi <= val)return r - l + 1;
        int m = hi + lo >> 1;
        int lp = p[wt[i].st + l - 1], rp = p[wt[i].st + r];
        return less_equals(wt[i].lc, lp, rp - 1, val, lo, m) + less_equals(wt[i].rc, l - lp, r - rp , val, m + 1, hi);
    }
    int kth(int i, int l, int r, int val, int lo, int hi){    // 1 - based
        if(lo == hi)return lo;
        int m = hi + lo >> 1;
        int lp = p[wt[i].st + l - 1], rp = p[wt[i].st + r];
        int left = rp - lp;
        if(left >= val)return kth(wt[i].lc, lp, rp - 1, val, lo, m);
        return kth(wt[i].rc, l - lp, r - rp , val - left, m + 1, hi);
    }
};
