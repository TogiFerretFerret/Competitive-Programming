// Problem: F2. Again Trees... (hard version)
// Judge: Codeforces
// URL: https://codeforces.com/contest/2194/problem/F2
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

    vector<int> a(n + 1);
    fOrn(i, 1, n + 1) in(a[i]);

    vector<int> b(k);
    in(b);

    const int MOD = 1e9 + 7;
    const int INV2 = (MOD + 1) / 2;

    vector<int> basis;
    for (int x : b) {
        int temp = x;
        for (int b_val : basis) {
            temp = min(temp, temp ^ b_val);
        }
        if (temp > 0) {
            basis.pb(temp);
            sort(basis.rbegin(), basis.rend());
        }
    }

    int dim = basis.size();
    int size = 1 << dim;

    auto get_coord = [&](int val) -> int {
        int mask = 0;
        forn(i, dim) {
            if ((val ^ basis[i]) < val) {
                val ^= basis[i];
                mask |= (1 << i);
            }
        }
        return (val == 0) ? mask : -1;
    };

    vector<int> s(n + 1);
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.reserve(n);
    vector<int> stack = {1};

    while (!stack.empty()) {
        int u = stack.back(); stack.pop_back();
        order.pb(u);
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                stack.pb(v);
            }
        }
    }

    f0rn(i, n - 1, -1) {
        int u = order[i];
        s[u] = a[u];
        for (int v : adj[u]) {
            if (v != parent[u]) s[u] ^= s[v];
        }
    }

    int root_mask = get_coord(s[1]);
    if (root_mask == -1) {
        out(0);
        return;
    }

    vector<int> b_coords;
    for (int x : b) {
        int m = get_coord(x);
        if (m != -1) b_coords.pb(m);
    }

    vector<int> G(size);
    forn(m, size) {
        ll val = 0;
        for (int bc : b_coords) {
            if (__builtin_parity(bc & m)) val--; else val++;
        }
        val %= MOD;
        if (val < 0) val += MOD;
        G[m] = val;
    }

    ll inv_size = 1;
    forn(i, dim) inv_size = (inv_size * INV2) % MOD;

    vector<vector<int>> dp(n + 1);

    f0rn(i, n - 1, -1) {
        int u = order[i];
        bool is_first_child = true;

        for (int v : adj[u]) {
            if (v == parent[u]) continue;

            int sv_mask = get_coord(s[v]);
            const vector<int>& dp_v = dp[v];

            if (sv_mask == -1) {
                if (is_first_child) {
                    dp[u] = dp_v;
                    is_first_child = false;
                } else {
                    forn(m, size) {
                        dp[u][m] = (1LL * dp[u][m] * dp_v[m]) % MOD;
                    }
                }
            } else {
                ll raw_dot = 0;
                forn(m, size) {
                    ll term = (1LL * dp_v[m] * G[m]) % MOD;
                    if (__builtin_parity(sv_mask & m)) raw_dot -= term;
                    else raw_dot += term;
                }
                raw_dot %= MOD;
                if (raw_dot < 0) raw_dot += MOD;

                int ways_cut = (raw_dot * inv_size) % MOD;

                if (is_first_child) {
                    dp[u].resize(size);
                    forn(m, size) {
                        int term_cut = (__builtin_parity(sv_mask & m) ? -ways_cut : ways_cut);
                        int res = dp_v[m] + term_cut;
                        if (res >= MOD) res -= MOD;
                        else if (res < 0) res += MOD;
                        dp[u][m] = res;
                    }
                    is_first_child = false;
                } else {
                    forn(m, size) {
                        int term_cut = (__builtin_parity(sv_mask & m) ? -ways_cut : ways_cut);
                        int val_v = dp_v[m] + term_cut;
                        if (val_v >= MOD) val_v -= MOD;
                        else if (val_v < 0) val_v += MOD;
                        dp[u][m] = (1LL * dp[u][m] * val_v) % MOD;
                    }
                }
            }
            vector<int>().swap(dp[v]);
        }

        if (is_first_child) {
            dp[u].assign(size, 1);
        }
    }

    ll ans = 0;
    const vector<int>& root_dp = dp[1];

    forn(m, size) {
        ll term = (1LL * root_dp[m] * G[m]) % MOD;
        if (__builtin_parity(root_mask & m)) ans -= term;
        else ans += term;
    }
    ans %= MOD;
    if (ans < 0) ans += MOD;
    ans = (ans * inv_size) % MOD;

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
