// Problem: F. Parabola Independence
// Judge: Codeforces
// URL: https://codeforces.com/contest/2195/problem/F
// Memory Limit: 512 MB
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
#define MULTITEST true
#define pb push_back
void solve(){
    int n;
    in(n);

    struct Func {
        ll a, b, c;
        int id;
    };

    vector<Func> funcs(n);
    forn(i, n) {
        in(funcs[i].a, funcs[i].b, funcs[i].c);
        funcs[i].id = i;
    }

    function<bool(const Func&, const Func&)> is_strictly_less = [&](const Func& f1, const Func& f2) -> bool {
        ll A = f2.a - f1.a;
        ll B = f2.b - f1.b;
        ll C = f2.c - f1.c;

        if (A > 0) {
            ll disc = B * B - 4 * A * C;
            return disc < 0;
        } else if (A == 0) {
            return (B == 0 && C > 0);
        } else {
            return false;
        }
    };

    graph adj = graph(n);
    vector<int> in_degree = make<int, 0>(n);

    forn(i, n) {
        forn(j, n) {
            if (i == j) continue;
            if (is_strictly_less(funcs[i], funcs[j])) {
                adj[i].pb(j);
                in_degree[j]++;
            }
        }
    }

    vector<int> q;
    q.reserve(n);
    forn(i, n) {
        if (in_degree[i] == 0) q.pb(i);
    }

    int head = 0;
    while(head < q.size()){
        int u = q[head++];
        for(int v : adj[u]){
            in_degree[v]--;
            if(in_degree[v] == 0) q.pb(v);
        }
    }

    vector<int> dp_L = make<int, 1>(n);
    
    for(int u : q) {
        for(int v : adj[u]) {
            dp_L[v] = max(dp_L[v], dp_L[u] + 1);
        }
    }

    vector<int> dp_R = make<int, 1>(n);
    
    f0rn(i, n - 1, -1) {
        int u = q[i];
        for(int v : adj[u]) {
            dp_R[u] = max(dp_R[u], dp_R[v] + 1);
        }
    }

    vector<int> ans(n);
    forn(i, n) {
        ans[i] = dp_L[i] + dp_R[i] - 1;
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
