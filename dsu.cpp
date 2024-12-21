struct DSU{
  #define int long long
  int n,comps;
  vector<int> p,wt;
  DSU(int nn){
    n = nn, comps = nn;
    p.assign(n, -1);
    wt.resize(n, 0);
  }
  int root(int x){
    if(p[x] < 0) return x;
    int par = root(p[x]);
    wt[x] += wt[p[x]];
    return p[x] = par;
  }
  int wunite(int u,int v,int w){ //u->v==w
    if(check(u,v) and wdiff(u,v) != w) return -1;
    int p1 = root(u), p2 = root(v);
    w -= weight(v) - weight(u);
    if(p1 != p2){
      if(size(p1) < size(p2)) swap(p1,p2), w =- w;
      p[p1] += p[p2];
      p[p2] = p1;
      wt[p2] = w;
      comps --;
    } return p1!=p2;
  }
  bool unite(int u,int v){
    if(check(u,v)) return false;
    int p1 = root(u), p2 = root(v);
    assert(p1 != p2);
    if(size(p1) < size(p2)) swap(p1, p2);
    p[p1] += p[p2];
    p[p2] = p1;
    comps --;
    return true;
  }
  int weight(int x){
    root(x);
    return wt[x];
  }
  int size(int x){
    return -p[root(x)];
  }
  bool check(int u,int v){
    return root(u) == root(v);
  }
  int wdiff(int u,int v){
    return weight(v) - weight(u);
  }
  #undef int
};
