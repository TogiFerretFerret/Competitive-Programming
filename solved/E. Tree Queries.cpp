// Problem: E. Tree Queries
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1904/E
// Memory Limit: 512 MB
// Time Limit: 4000 ms
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static const uint64_t CHRONO_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
static const uint64_t PIDRNDP = (uint64_t)(getpid())*0xbffbffbffULL;
static mt19937_64 PIDRNG(PIDRNDP);
static const uint64_t PIDRND = PIDRNG();
static const uint64_t FIXED_RANDOM = CHRONO_RANDOM ^ PIDRND;
struct CHASH {
    template <typename T> size_t operator()(const T& x) const { return hash<T>{}(x) ^ FIXED_RANDOM; }
    template <typename T1, typename T2> size_t operator()(const pair<T1, T2>& x) const { return (*this)(x.first) ^ ((*this)(x.second) + 0x9e3779b9 + (x.first << 6) + (x.first >> 2)); }
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
    if constexpr(sizeof...(args) == 0) return vector<TM>(first, Val);
    else return vector<decltype(make<TM, Val>(args...))>(first, make<TM, Val>(args...));
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
#define MULTITEST false
#define pb push_back

void solve() {
    int n, q; in(n, q);
    graph adj(n + 1);
    forn(i, n - 1) {
        int u, v; in(u, v);
        adj[u].pb(v); adj[v].pb(u);
    }
    vector<int> in_t(n + 1), out_t(n + 1), depth(n + 1);
    matrix<int> up = make<int, 0>(n + 1, 20);
    int timer = 0;
    
    function<void(int, int, int)> dfs1 = [&](int u, int p, int d) -> void {
        in_t[u] = ++timer; depth[u] = d; up[u][0] = p;
        fOrn(i, 1, 20) up[u][i] = up[up[u][i - 1]][i - 1];
        for (int v : adj[u]) if (v != p) dfs1(v, u, d + 1);
        out_t[u] = timer;
    };
    dfs1(1, 1, 0);
    
    function<bool(int, int)> is_anc = [&](int u, int v) -> bool {
        return in_t[u] <= in_t[v] && out_t[u] >= out_t[v];
    };
    function<int(int, int)> get_child_anc = [&](int a, int u) -> int {
        f0rn(i, 19, -1) if (depth[u] - (1 << i) > depth[a]) u = up[u][i];
        return u;
    };

    vector<int> tree(4 * n + 5, 0), lazy(4 * n + 5, 0);
    function<void(int)> push = [&](int v) -> void {
        if (lazy[v] != 0) {
            tree[2 * v] += lazy[v]; lazy[2 * v] += lazy[v];
            tree[2 * v + 1] += lazy[v]; lazy[2 * v + 1] += lazy[v];
            lazy[v] = 0;
        }
    };
    function<void(int, int, int, int, int, int)> update = [&](int v, int l, int r, int ql, int qr, int val) -> void {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) { tree[v] += val; lazy[v] += val; return; }
        push(v); int mid = (l + r) / 2;
        update(2 * v, l, mid, ql, qr, val); update(2 * v + 1, mid + 1, r, ql, qr, val);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    };
    function<int(int, int, int, int, int)> query = [&](int v, int l, int r, int ql, int qr) -> int {
        if (ql > r || qr < l) return -1e9;
        if (ql <= l && r <= qr) return tree[v];
        push(v); int mid = (l + r) / 2;
        return max(query(2 * v, l, mid, ql, qr), query(2 * v + 1, mid + 1, r, ql, qr));
    };
    fOrn(i, 1, n + 1) update(1, 1, n, in_t[i], in_t[i], depth[i]);

    struct Query { int id; vector<int> a; };
    vector<vector<Query>> queries(n + 1);
    forn(i, q) {
        int x, k; in(x, k);
        vector<int> a(k); in(a);
        queries[x].pb({i, a});
    }

    vector<int> ans(q);
    function<void(int, int)> dfs2 = [&](int u, int p) -> void {
        for (const Query& qry : queries[u]) {
            vector<pair<int, int>> bad;
            for (int a : qry.a) {
                if (is_anc(a, u)) {
                    int c = get_child_anc(a, u);
                    bad.pb({1, in_t[c] - 1}); bad.pb({out_t[c] + 1, n});
                } else bad.pb({in_t[a], out_t[a]});
            }
            sort(all(bad));
            int max_val = 0, last = 1;
            for (const pair<int, int>& b : bad) {
                if (b.first > last) max_val = max(max_val, query(1, 1, n, last, b.first - 1));
                last = max(last, b.second + 1);
            }
            if (last <= n) max_val = max(max_val, query(1, 1, n, last, n));
            ans[qry.id] = max_val;
        }
        for (int v : adj[u]) {
            if (v != p) {
                update(1, 1, n, 1, n, 1); update(1, 1, n, in_t[v], out_t[v], -2);
                dfs2(v, u);
                update(1, 1, n, 1, n, -1); update(1, 1, n, in_t[v], out_t[v], 2);
            }
        }
    };
    dfs2(1, 1);
    forn(i, q) out(ans[i]);
}

int main(){
    if(!INTERACTIVE) cin.tie(0)->sync_with_stdio(0);
    int t=1; if (MULTITEST) cin>>t; forn(i,t) solve();
}
