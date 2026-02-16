// Problem: F1. Again Trees... (Easy Version)
// Judge: Codeforces
// URL: https://codeforces.com/contest/2194/problem/F1
// Memory Limit: 1024 MB
// Time Limit: 1000 ms
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
    int n, k;
    in(n, k);

    graph adj = graph(n + 1);
    forn(i, n - 1) {
        int u, v;
        in(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vector<int> a(n);
    in(a);

    vector<int> b(k);
    in(b);

    const ll MOD = 1e9 + 7;
    vector<int> relevant_vals;
    map<int, int> val_to_idx;
    vector<int> sub_xor = make<int, 0>(n + 1);

    function<void()> prepare_relevant_vals = [&]() -> void {
        int subsets = 1 << k;
        forn(mask, subsets) {
            int val = 0;
            forn(i, k) {
                if ((mask >> i) & 1) {
                    val ^= b[i];
                }
            }
            relevant_vals.pb(val);
        }
        sort(all(relevant_vals));
        relevant_vals.erase(unique(all(relevant_vals)), relevant_vals.end());
        forn(i, relevant_vals.size()) {
            val_to_idx[relevant_vals[i]] = i;
        }
    };

    prepare_relevant_vals();

    function<void(int, int)> dfs_xor = [&](int u, int p) -> void {
        sub_xor[u] = a[u - 1]; 
        for (int v : adj[u]) {
            if (v != p) {
                dfs_xor(v, u);
                sub_xor[u] ^= sub_xor[v];
            }
        }
    };

    dfs_xor(1, 0);

    function<bool(int)> is_in_b = [&](int val) -> bool {
        for (int x : b) {
            if (x == val) return true;
        }
        return false;
    };

    function<vector<ll>(int, int)> dp_dfs = [&](int u, int p) -> vector<ll> {
        int sz = relevant_vals.size();
        vector<ll> current_dp(sz, 0);
        
        if (val_to_idx.count(0)) {
            current_dp[val_to_idx[0]] = 1;
        }

        for (int v : adj[u]) {
            if (v == p) continue;

            vector<ll> child_dp = dp_dfs(v, u);
            vector<ll> next_dp(sz, 0);

            ll ways_to_cut_this_child = 0;
            
            forn(j, sz) {
                if (child_dp[j] == 0) continue;
                
                int removed_val_in_child = relevant_vals[j];
                int current_comp_val = sub_xor[v] ^ removed_val_in_child;
                
                if (is_in_b(current_comp_val)) {
                    ways_to_cut_this_child = (ways_to_cut_this_child + child_dp[j]) % MOD;
                }
            }

            forn(i, sz) {
                if (current_dp[i] == 0) continue;
                ll ways_u = current_dp[i];

                // Keep edge
                forn(j, sz) {
                    if (child_dp[j] == 0) continue;
                    
                    int combined_xor = relevant_vals[i] ^ relevant_vals[j];
                    int idx = val_to_idx[combined_xor];
                    
                    ll ways = (ways_u * child_dp[j]) % MOD;
                    next_dp[idx] = (next_dp[idx] + ways) % MOD;
                }

                // Cut edge
                if (ways_to_cut_this_child > 0) {
                    int combined_xor_cut = relevant_vals[i] ^ sub_xor[v];
                    int idx = val_to_idx[combined_xor_cut];
                    
                    ll ways = (ways_u * ways_to_cut_this_child) % MOD;
                    next_dp[idx] = (next_dp[idx] + ways) % MOD;
                }
            }
            current_dp = next_dp;
        }
        return current_dp;
    };

    vector<ll> root_results = dp_dfs(1, 0);
    ll ans = 0;

    forn(i, relevant_vals.size()) {
        if (root_results[i] == 0) continue;
        
        int removed_xor = relevant_vals[i];
        int final_root_comp_val = sub_xor[1] ^ removed_xor;
        
        if (is_in_b(final_root_comp_val)) {
            ans = (ans + root_results[i]) % MOD;
        }
    }

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
