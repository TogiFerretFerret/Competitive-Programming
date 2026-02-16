// Problem: E1. Distance Tree (easy version)
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1632/E1
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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
#define MULTITEST true
#define pb push_back
void solve(){
    int n;
    in(n);
    
    graph adj = graph(n + 1);
    forn(i, n - 1) {
        int u, v;
        in(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    int LOGN = 0;
    while((1 << LOGN) <= n) LOGN++;
    LOGN++; 
    
    vector<vector<int>> up = make<int, 0>(n + 1, LOGN);
    vector<int> depth = make<int, 0>(n + 1);
    matrix<int> nodes_by_depth = matrix<int>(n + 1);
    vector<int> suff_diam = make<int, 0>(n + 1);
    
    function<void(int, int, int)> dfs = [&](int u, int p, int d) -> void {
        depth[u] = d;
        up[u][0] = p;
        nodes_by_depth[d].pb(u);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
    };
    
    dfs(1, 0, 0);
    
    // Precompute binary lifting
    forn(j, LOGN) {
        if(j == 0) continue;
        fOrn(i, 1, n + 1) {
            if (up[i][j-1] != 0)
                up[i][j] = up[up[i][j-1]][j-1];
            else
                up[i][j] = 0;
        }
    }
    
    function<int(int, int)> get_lca = [&](int u, int v) -> int {
        if (depth[u] < depth[v]) swap(u, v);
        f0rn(j, LOGN - 1, -1) {
            if (depth[u] - (1 << j) >= depth[v]) {
                u = up[u][j];
            }
        }
        if (u == v) return u;
        f0rn(j, LOGN - 1, -1) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    };
    
    function<int(int, int)> get_dist = [&](int u, int v) -> int {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    };
    
    int max_depth = 0;
    fOrn(i, 1, n + 1) max_depth = max(max_depth, depth[i]);
    
    int u_end = -1, v_end = -1;
    int current_diam = 0;
    
    f0rn(k, max_depth - 1, -1) {
        for (int node : nodes_by_depth[k+1]) {
            if (u_end == -1) {
                u_end = node;
                v_end = node;
                current_diam = 0;
            } else {
                int d1 = get_dist(u_end, node);
                int d2 = get_dist(v_end, node);
                if (max(d1, d2) > current_diam) {
                    current_diam = max(d1, d2);
                    if (d1 > d2) v_end = node;
                    else u_end = node;
                }
            }
        }
        suff_diam[k] = current_diam;
    }
    
    vector<int> arr = make<int, 0>(max_depth + 2);
    forn(k, max_depth + 1) {
        arr[k] = suff_diam[k] - 2 * k;
    }
    
    vector<int> ans_vec;
    fOrn(x, 1, n + 1) {
        int ans = max_depth;
        
        if (x <= max_depth) {
            int k = x;
            int bound = -2 * x;
            
            // Optimization: The smallest valid K is likely near previous answers or we can just iterate.
            // Since N is small (3000), O(N^2) total across queries is fine, but loop is actually O(N) per x
            // However, logic says find *minimal* K >= x.
            for (; k <= max_depth; ++k) {
                if (arr[k] <= bound) {
                    ans = k;
                    break;
                }
            }
        }
        ans_vec.pb(ans);
    }
    out(ans_vec);
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
