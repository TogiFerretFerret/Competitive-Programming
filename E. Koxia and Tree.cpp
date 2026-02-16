// Problem: E. Koxia and Tree
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1770/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static const uint64_t CHRONO_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
static const uint64_t PIDRNDP = (uint64_t)(getpid())*0xbffbffbffULL;
static mt19937_64 PIDRNG(PIDRNDP);
static const uint64_t PIDRND = PIDRNG();
static const uint64_t FIXED_RANDOM = CHRONO_RANDOM ^ PIDRND;
struct CHASH {
    template <typename T> size_t operator()(const T& x) const {
        return hash<T>{}(x) ^ FIXED_RANDOM;
    }
    template <typename T1, typename T2> size_t operator()(const pair<T1, T2>& x) const {
        return (*this)(x.first) ^ ((*this)(x.second) + 0x9e3779b9 + (x.first << 6) + (x.first >> 2));
    }
};
template<class T, class U> istream& operator>>(istream& i, pair<T, U>& p) { return i >> p.first >> p.second; }
template<class T, class U> ostream& operator<<(ostream& o, const pair<T, U>& p) { return o << p.first << " " << p.second; }
template<class T> istream& operator>>(istream& i, vector<T>& v) { for(auto& x : v) i >> x; return i; }
template<class T> ostream& operator<<(ostream& o, const vector<T>& v) { for(int i=0; i<v.size(); ++i) o << v[i] << (i==v.size()-1?"":" "); return o; }
#define m1(x) template<class T, class... U> void x(T&& a, U&&... b)
#define m2(x) (int[]){(x std::forward<U>(b),0)...}
template<typename T1,typename T2> using hashmap=unordered_map<T1,T2,CHASH>;
template<typename TM> using matrix=vector<vector<TM>>;
using graph=matrix<int>;
template<typename TM> using tensor=vector<matrix<TM>>;
template<typename TM> using hypermatrix=vector<tensor<TM>>;
template<typename TM, TM Val = TM(), typename... Args> auto make(size_t first, Args... args){
    if constexpr(sizeof...(args) == 0){
        return vector<TM>(first, Val);
    } else {
        return vector<decltype(make<TM, Val>(args...))>(first, make<TM, Val>(args...));
    }
}
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define fOrn(v,s,e) for(int v=(s);v<(e);++v)
#define INTERACTIVE false
#ifndef LOCAL_JUDGE
#define FILEMODE false
#define FILENAME "pname"
#endif
#if INTERACTIVE
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << endl; }//softmod for interactive
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#else
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << "\n"; }//softmod for interactive
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#endif
#define MULTITEST false
#define pb push_back
void solve(){
    int n, k_bfs;
    in(n, k_bfs);
    
    vector<int> a(k_bfs);
    in(a);
    
    vector<ll> p_val = make<ll, 0>(n + 1);
    forn(i, k_bfs) {
        p_val[a[i]] = 1;
    }
    
    struct Edge {
        int u, v;
        int id;
    };
    
    vector<Edge> edges(n - 1);
    forn(i, n - 1) {
        in(edges[i].u, edges[i].v);
        edges[i].id = i;
    }
    
    vector<vector<pair<int, int>>> adj(n + 1);
    for(const Edge& e : edges) {
        adj[e.u].pb({e.v, e.id});
        adj[e.v].pb({e.u, e.id});
    }
    
    vector<int> edge_node = make<int, 0>(n - 1);
    vector<int> tin = make<int, 0>(n + 1);
    vector<int> tout = make<int, 0>(n + 1);
    int timer = 0;
    
    function<void(int, int)> dfs_order = [&](int u, int p) -> void {
        tin[u] = ++timer;
        for (const pair<int, int>& edge : adj[u]) {
            int v = edge.first;
            int id = edge.second;
            if (v != p) {
                edge_node[id] = v;
                dfs_order(v, u);
            }
        }
        tout[u] = timer;
    };
    
    dfs_order(1, 0);
    
    vector<ll> bit_sum = make<ll, 0>(n + 1);
    vector<ll> bit_var = make<ll, 0>(n + 1);
    
    function<void(vector<ll>&, int, ll)> update = [&](vector<ll>& bit, int idx, ll val) -> void {
        for (; idx <= n; idx += idx & -idx) bit[idx] = (bit[idx] + val) % 998244353;
    };
    
    function<ll(vector<ll>&, int)> query = [&](vector<ll>& bit, int idx) -> ll {
        ll sum = 0;
        for (; idx > 0; idx -= idx & -idx) sum = (sum + bit[idx]) % 998244353;
        return sum;
    };
    
    function<ll(ll, ll)> power = [&](ll base, ll exp) -> ll {
        ll res = 1;
        base %= 998244353;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % 998244353;
            base = (base * base) % 998244353;
            exp /= 2;
        }
        return res;
    };
    
    function<ll(ll)> modInverse = [&](ll n) -> ll {
        return power(n, 998244353 - 2);
    };
    
    fOrn(i, 1, n + 1) {
        ll val = p_val[i];
        ll term = (val - val * val % 998244353 + 998244353) % 998244353;
        update(bit_sum, tin[i], val);
        update(bit_var, tin[i], term);
    }
    
    ll total_score = 0;
    ll inv2 = modInverse(2);
    
    forn(i, n - 1) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        ll pu = p_val[u];
        ll pv = p_val[v];
        
        ll avg = (pu + pv) % 998244353 * inv2 % 998244353;
        
        ll var_u = (pu - pu * pu % 998244353 + 998244353) % 998244353;
        ll var_v = (pv - pv * pv % 998244353 + 998244353) % 998244353;
        
        update(bit_sum, tin[u], (998244353 - pu) % 998244353);
        update(bit_var, tin[u], (998244353 - var_u) % 998244353);
        
        update(bit_sum, tin[v], (998244353 - pv) % 998244353);
        update(bit_var, tin[v], (998244353 - var_v) % 998244353);
        
        p_val[u] = avg;
        p_val[v] = avg;
        
        ll new_var = (avg - avg * avg % 998244353 + 998244353) % 998244353;
        
        update(bit_sum, tin[u], avg);
        update(bit_var, tin[u], new_var);
        
        update(bit_sum, tin[v], avg);
        update(bit_var, tin[v], new_var);
        
        int node = edge_node[i];
        
        ll SumP = (query(bit_sum, tout[node]) - query(bit_sum, tin[node] - 1) + 998244353) % 998244353;
        ll SumVar = (query(bit_var, tout[node]) - query(bit_var, tin[node] - 1) + 998244353) % 998244353;
        
        ll E_S2 = (SumP * SumP % 998244353 + SumVar) % 998244353;
        ll k_SumP = (ll)k_bfs * SumP % 998244353;
        
        ll term = (k_SumP - E_S2 + 998244353) % 998244353;
        total_score = (total_score + term) % 998244353;
    }
    
    ll k_comb = (ll)k_bfs * (k_bfs - 1) % 998244353 * inv2 % 998244353;
    ll ans = total_score * modInverse(k_comb) % 998244353;
    
    out(ans);
}
int main(){
    if(!INTERACTIVE)cin.tie(0)->sync_with_stdio(0);
    #ifndef LOCAL_JUDGE
    #if FILEMODE
    freopen(FILENAME".in","r",stdin);
    freopen(FILENAME".out","w",stdout);
    #endif
    #endif
    int t=1;
    if (MULTITEST) cin>>t;
    forn(i,t)solve();
}
