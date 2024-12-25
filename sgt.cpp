template<typename Node, typename Update>
struct SGT {
    vector<Node> tree;
    vector<bool> lazy;
    vector<Update> updates;
    vector<ll> a; 
    int n;
    int s;
    SGT(){}
    SGT(int _n, vector<ll> &_a) { 
        a = _a;
        n = _n;
        s = 1;
        while(s < 2 * n) {
            s = s << 1;
        }
        tree.resize(s); fill(all(tree), Node());
        lazy.resize(s); fill(all(lazy), false);
        updates.resize(s); fill(all(updates), Update());
        build(0, n - 1, 1);
    }
    void build(int tl, int tr, int i) { 
        if (tl == tr)   {
            tree[i] = Node(a[tl]);
            return;
        }
        int mid = (tl + tr) / 2;
        build(tl, mid, i << 1);
        build(mid + 1, tr, i << 1 | 1);
        tree[i].merge(tree[i << 1], tree[i << 1 | 1]);
    }
    void push(int i, int tl, int tr){
        if(lazy[i]){
            int mid = (tl + tr) / 2;
            apply(i << 1, tl, mid, updates[i]);
            apply(i << 1 | 1, mid + 1, tr, updates[i]);
            updates[i] = Update();
            lazy[i] = 0;
        }
    }
    void apply(int i, int tl, int tr, Update& u){
        if(tl != tr){
            lazy[i] = 1;
            updates[i].combine(u, tl, tr);
        }
        u.apply(tree[i], tl, tr);
    }
    void update(int tl, int tr, int i, int ql, int qr, Update& u) { 
        if(tl > qr or tr < ql)
            return;
        if(tl >= ql && tr <= qr){
            apply(i, tl, tr, u);
            return;
        }
        push(i, tl, tr);
        int mid = (tl + tr) / 2;
        update(tl, mid, i << 1, ql, qr, u);
        update(mid + 1, tr, i << 1 | 1, ql, qr, u);
        tree[i].merge(tree[i << 1], tree[i << 1 | 1]);
    }
    Node query(int tl, int tr, int i, int ql, int qr) { 
        if (tl > qr or tr < ql)
            return Node();
        push(i, tl, tr);
        if (tl >= ql && tr <= qr){
            return tree[i];
        }
        int mid = (tl + tr) / 2;
        Node l, r, ans;
        l = query(tl, mid, i << 1, ql, qr);
        r = query(mid + 1, tr, i << 1 | 1, ql, qr);
        ans.merge(l, r);
        return ans;
    }
    void update(int ql, int qr, ll val) {
        Update new_update = Update(val); 
        update(0, n - 1, 1, ql, qr, new_update);
    }
    void update(int idx, ll val) {  
        Update new_update = Update(val); 
        update(0, n - 1, 1, idx, idx, new_update);
    }
    Node query(int ql, int qr) {
        return query(0, n - 1, 1, ql, qr);
    }
    Node query(int idx) {
        return query(0, n - 1, 1, idx, idx);
    }
};
struct Node {
    ll val; 
    Node() { 
        val = 0;    
    }
    Node(ll p1) {
        val = p1; 
    }
    void merge(Node &l, Node &r) { 
        val = l.val + r.val;
    }
};
struct Update {
    ll val; 
    Update(){ 
        val = 0;
    }
    Update(ll _val) { 
        val = _val;
    }
    void apply(Node &a, int tl, int tr) { 
        a.val = val;
    }
    void combine(Update& new_update, int tl, int tr){
        val = new_update.val;
    }
};
