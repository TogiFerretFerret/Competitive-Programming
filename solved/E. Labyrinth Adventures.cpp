// Problem: E. Labyrinth Adventures
// Judge: Codeforces
// URL: https://codeforces.com/contest/1681/problem/E
// Memory Limit: 512 MB
// Time Limit: 6000 ms
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
const ll INF64 = 1e18;
typedef pair<int, int> pt;
#define x first
#define y second

void solve(){
    int n;
    in(n);
    vector<vector<pt>> d(n - 1, vector<pt>(2));
    forn(i, n - 1) forn(j, 2){
        in(d[i][j]);
        --d[i][j].x, --d[i][j].y;
    }
    
    int lg = 1;
    while ((1 << lg) < n - 1) ++lg;
    
    auto dp = make<ll, INF64>(n - 1, lg, 2, 2);
    
    forn(i, n - 2) forn(k, 2){
        dp[i][0][0][k] = (ll)abs(d[i][0].x + 1 - d[i + 1][k].x) + abs(d[i][0].y - d[i + 1][k].y) + 1;
        dp[i][0][1][k] = (ll)abs(d[i][1].x - d[i + 1][k].x) + abs(d[i][1].y + 1 - d[i + 1][k].y) + 1;
    }
    
    for (int l = 1; l < lg; ++l) {
        forn(i, n - 2) {
            if (i + (1 << (l - 1)) < n - 1) {
                forn(j, 2) forn(k, 2) forn(t, 2) {
                    dp[i][l][j][k] = min(dp[i][l][j][k], 
                        dp[i][l - 1][j][t] + dp[i + (1 << (l - 1))][l - 1][t][k]);
                }
            }
        }
    }
    
    int m;
    in(m);
    forn(_, m){
        int x1, y1, x2, y2;
        in(x1, y1, x2, y2);
        --x1, --y1, --x2, --y2;
        
        int l1 = max(x1, y1);
        int l2 = max(x2, y2);
        
        if (l1 > l2){
            swap(l1, l2);
            swap(x1, x2);
            swap(y1, y2);
        }
        
        if (l1 == l2){
            out(abs(x1 - x2) + abs(y1 - y2));
            continue;
        }
        
        vector<ll> ndp(2);
        ndp[0] = (ll)abs(x1 - d[l1][0].x) + abs(y1 - d[l1][0].y);
        ndp[1] = (ll)abs(x1 - d[l1][1].x) + abs(y1 - d[l1][1].y);
        
        for (int i = lg - 1; i >= 0; --i) {
            if (l1 + (1 << i) < l2){
                vector<ll> tmp(2, INF64);
                forn(j, 2) forn(k, 2) {
                    tmp[k] = min(tmp[k], ndp[j] + dp[l1][i][j][k]);
                }
                ndp = tmp;
                l1 += (1 << i);
            }
        }
        
        ll ans = INF64;
        ans = min(ans, ndp[0] + (ll)abs(d[l1][0].x + 1 - x2) + abs(d[l1][0].y - y2) + 1);
        ans = min(ans, ndp[1] + (ll)abs(d[l1][1].x - x2) + abs(d[l1][1].y + 1 - y2) + 1);
        
        out(ans);
    }
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
