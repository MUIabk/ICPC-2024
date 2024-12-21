const int maxN = 3e5+1;
vector<int> sol;
struct DSU{
    vector<pair<int, int>> st[4*maxN];
    vector<int> p, rank, op;
    vector<pair<int&, int>> e;
    int ans = 0;
    void init(int n){
        p.resize(n+1); rank.assign(n+1 , 1);
        for(int i = 0 ; i<= n ; i++) p[i] = i;
        ans = n;
    }
    int get(int u){
        if(u == p[u]){
            return u;
        }
        return get(p[u]);
    }
    void add(int u , int v){
        u = get(u); v = get(v);
        if(u == v){
            op.pb(0);
            return;
        }
        if(rank[u] > rank[v]) swap(u , v);
        ans --;
        op.pb(-1);
        e.pb({p[u] , p[u]});
        p[u] = v;
        e.pb({rank[v] , rank[v]});
        rank[v] += rank[u];
    }
    void upd(int node , int l , int r , int lx, int rx, pll p){ // [l ,r], tot range = [0, Q]
        if(lx >= r || rx <= l){
            return;
        }
        if(lx >= l && rx <= r){
            st[node].pb(p);
        }else{
            int mid = (lx+rx)/2;
            upd(2*node+1 , l , r , lx , mid , p);
            upd(2*node+2 , l , r , mid , rx , p);
        }
    }
    void undo(){
        if(!op.back()){
            op.pop_back();
            return;
        }else{
            ans++;
            op.pop_back();
            for(int i = 0 ; i < 2 ; i ++){
                e.back().first = e.back().second;
                e.pop_back();
            }
        }
    }
    void build(int node, int l , int r){
        for(auto it: st[node]){
            add(it.first , it.second);
        }
        if(r-l == 1){
            sol.pb(ans);
        }else{
            int mid = (l+r)/2;
            build(2*node+1 , l , mid);
            build(2*node+2 , mid ,r);
        }
        for(auto it: st[node]){
            undo();
        }
    }
};
