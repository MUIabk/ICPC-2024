struct Biconnected {
  int n, m;
  vector<vector<int>> g, f, gg;
  vector<vector<pair<int, int>>> ess;
  vector<int> par, rs;
  int zeit;
  vector<int> dis, fin, low;
  Biconnected() {}
  explicit Biconnected(int n_) : n(n_), m(0), g(n_) {}
  void ae(int u, int v) {
    ++m;
    assert(0 <= u); assert(u < n);
    assert(0 <= v); assert(v < n);
    g[u].push_back(v);
    if (u != v) g[v].push_back(u);
  }
  int stackVLen, stackELen;
  vector<int> stackV;
  vector<pair<int, int>> stackE;
  vector<int> cntPar;
  void dfs(int u) {
    stackV[stackVLen++] = u;
    dis[u] = low[u] = zeit++;
    for (const int v : g[u]) {
      if (par[u] == v && !cntPar[u]++) continue;
      if (~dis[v]) {
        if (dis[u] >= dis[v]) stackE[stackELen++] = std::make_pair(v, u);
        if (low[u] > dis[v]) low[u] = dis[v];
      } else {
        f[u].push_back(v);
        par[v] = u;
        rs[v] = rs[u];
        const int stackEPos = stackELen;
        stackE[stackELen++] = std::make_pair(u, v);
        dfs(v);
        if (low[u] > low[v]) low[u] = low[v];
        if (dis[u] <= low[v]) {
          const int x = gg.size();
          gg.emplace_back();
          ess.emplace_back();
          for (; ; ) {
            const int w = stackV[--stackVLen];
            gg[w].push_back(x);
            gg[x].push_back(w);
            if (w == v) break;
          }
          gg[u].push_back(x);
          gg[x].push_back(u);
          for (; stackELen > stackEPos; ) ess[x].push_back(stackE[--stackELen]);
        }
      }
    }
    fin[u] = zeit;
  }
  void build() {
    f.assign(n, {}); dis.assign(n, -1);
    gg.assign(n, {}); ess.assign(n, {});
    par.assign(n, -1); rs.assign(n, -1);
    zeit = 0;
    fin.assign(n, -1); low.assign(n, -1);
    stackV.resize(n); stackE.resize(m);
    cntPar.assign(n, 0);
    for (int u = 0; u < n; ++u) if (!~dis[u]) {
      stackVLen = stackELen = 0;
      rs[u] = u;
      dfs(u);
    }
  }
  //gg[u].size(), number of connected components when u is removed
  inline bool isArt(int u) const {
    return (gg[u].size() >= 2);
  }
  // Returns w s.t. w is a child of u and a descendant of v in the DFS forest.
  // Returns -1 instead if v is not a proper descendant of u
  //   O(log(deg(u))) time
  int dive(int u, int v) const {
    if (dis[u] < dis[v] && dis[v] < fin[u]) {
      int j0 = 0, j1 = f[u].size();
      for (; j0 + 1 < j1; ) {
        const int j = (j0 + j1) / 2;
        ((dis[f[u][j]] <= dis[v]) ? j0 : j1) = j;
      }
      return f[u][j0];
    } else {
      return -1;
    }
  }
  // Returns true iff there exists a v-w path when u is removed.
  //   O(log(deg(u))) time
  bool isStillReachable(int u, int v, int w) const {
    if (rs[v] != rs[w]) return false;
    if (rs[u] != rs[v]) return true;
    const int vv = dive(u, v);
    const int ww = dive(u, w);
    if (~vv) {
      if (~ww) {
        return (vv == ww || (dis[u] > low[vv] && dis[u] > low[ww]));
      } else {
        return (dis[u] > low[vv]);
      }
    } else {
      if (~ww) {
        return (dis[u] > low[ww]);
      } else {
        return true;
      }
    }
  }
};
