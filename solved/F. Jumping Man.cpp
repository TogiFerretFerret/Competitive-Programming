// Problem: F. Jumping Man
// Judge: Codeforces
// URL: https://codeforces.com/contest/2183/problem/F
// Memory Limit: 1024 MB
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
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << endl; }
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#else
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << "\n"; }
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#endif
#define MULTITEST true
#define pb push_back

void solve() {
    int n;
    in(n);
    string s;
    in(s);
    
    vector<vector<int>> adj(n);
    forn(i, n - 1) {
        int u, v;
        in(u, v);
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    vector<vector<int>> children(n);
    vector<int> post_order;
    post_order.reserve(n);
    
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        for (int v : adj[u]) {
            if (v != p) {
                children[u].pb(v);
                dfs(v, u);
            }
        }
        post_order.pb(u);
    };
    dfs(0, -1);
    
    ll MOD = 998244353;
    vector<int> Sub(n * n, 0);
    vector<int> SumV(n * n, 0);
    
    for (int u : post_order) {
        int un = u * n;
        for (int v : post_order) {
            long long sum_v_u = 0;
            for (int cu : children[u]) {
                sum_v_u += Sub[cu * n + v];
            }
            if (sum_v_u >= MOD) sum_v_u %= MOD;
            SumV[un + v] = sum_v_u;
            
            long long sum_v_v = 0, sum_strict = 0;
            for (int cv : children[v]) {
                sum_v_v += Sub[un + cv];
                sum_strict += SumV[un + cv];
            }
            if (sum_v_v >= MOD) sum_v_v %= MOD;
            if (sum_strict >= MOD) sum_strict %= MOD;
            
            long long sub_val = 0;
            // The mathematical overlap pairings universally equate via Inclusion-Exclusion
            if (s[u] == s[v]) {
                sub_val = 1 + sum_v_u + sum_v_v;
            } else {
                sub_val = sum_v_u + sum_v_v - sum_strict;
            }
            
            sub_val %= MOD;
            if (sub_val < 0) sub_val += MOD;
            
            Sub[un + v] = sub_val;
        }
    }
    
    vector<int> ans(n);
    forn(i, n) {
        ans[i] = Sub[i * n + i];
    }
    
    out(ans);
}

int main(){
    if(!INTERACTIVE) cin.tie(0)->sync_with_stdio(0);
    #ifndef LOCAL_JUDGE
    #if FILEMODE
    freopen(FILENAME".in","r",stdin);
    freopen(FILENAME".out","w",stdout);
    #endif
    #endif
    int t = 1;
    if (MULTITEST) cin >> t;
    forn(i, t) solve();
}
