// Problem: E. Idiot First Search
// Judge: Codeforces
// URL: https://codeforces.com/contest/2195/problem/E
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

    struct Node {
        int l, r;
        ll size;
        ll w;
        ll ans;
    };

    vector<Node> tree(n + 1);
    vector<int> parent = make<int, 0>(n + 1);

    fOrn(i, 1, n + 1) {
        int l, r;
        in(l, r);
        tree[i].l = l;
        tree[i].r = r;
        if (l != 0) parent[l] = i;
        if (r != 0) parent[r] = i;
    }

    vector<int> order;
    order.reserve(n);
    vector<int> stack;
    stack.pb(1);

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        order.pb(u);
        
        if (tree[u].r != 0) stack.pb(tree[u].r);
        if (tree[u].l != 0) stack.pb(tree[u].l);
    }

    ll MOD = 1e9 + 7;

    f0rn(i, n - 1, -1) {
        int u = order[i];
        ll current_size = 1; 
        if (tree[u].l != 0) current_size += tree[tree[u].l].size;
        if (tree[u].r != 0) current_size += tree[tree[u].r].size;
        
        tree[u].size = current_size;
        
        ll val = (2 * (tree[u].size % MOD)) % MOD;
        tree[u].w = (val - 1 + MOD) % MOD;
    }

    forn(i, n) {
        int u = order[i];
        ll parent_ans = 0;
        if (u != 1) {
            parent_ans = tree[parent[u]].ans;
        }
        tree[u].ans = (tree[u].w + parent_ans) % MOD;
    }

    vector<ll> ans_vec;
    ans_vec.reserve(n);
    fOrn(i, 1, n + 1) {
        ans_vec.pb(tree[i].ans);
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
