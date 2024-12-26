#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template<class T>using ind_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>using ind_mset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
typedef gp_hash_table<long long,long long> fast_map;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll uid(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
