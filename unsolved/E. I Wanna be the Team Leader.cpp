// Problem: E. I Wanna be the Team Leader
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1886/E
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
#define MULTITEST false
#define pb push_back
void solve() {
    int n, m; in(n, m);
    vector<pair<ll, int>> a(n + 1);
    fOrn(i, 1, n + 1) { in(a[i].first); a[i].second = i; }
    
    function<bool(const pair<ll, int>&, const pair<ll, int>&)> comp = [&](const pair<ll, int>& x, const pair<ll, int>& y) -> bool { return x.first > y.first; };
    sort(a.begin() + 1, a.end(), comp);
    vector<ll> b(m); in(b);
    
    matrix<int> nxt = make<int, 1000000000>(m, n + 2);
    forn(p, m) {
        int cur_i = 1;
        fOrn(j, 1, n + 1) {
            ll req = (b[p] + a[j].first - 1) / a[j].first;
            int max_idx = j - req + 1;
            while (cur_i <= max_idx) nxt[p][cur_i++] = j;
        }
    }
    
    vector<int> dp(1 << m, 1000000000);
    vector<pair<int, int>> parent(1 << m, {-1, -1});
    dp[0] = 0;
    
    forn(mask, 1 << m) {
        if (dp[mask] > n) continue;
        forn(p, m) {
            if (!(mask & (1 << p))) {
                int next_mask = mask | (1 << p);
                int end = nxt[p][dp[mask] + 1];
                if (end <= n && end < dp[next_mask]) {
                    dp[next_mask] = end;
                    parent[next_mask] = {p, dp[mask] + 1};
                }
            }
        }
    }
    
    if (dp[(1 << m) - 1] > n) { out("NO"); return; }
    out("YES");
    
    int mask = (1 << m) - 1;
    matrix<int> ans(m);
    while (mask > 0) {
        int p = parent[mask].first;
        int start = parent[mask].second;
        int end = dp[mask];
        fOrn(i, start, end + 1) ans[p].pb(a[i].second);
        mask ^= (1 << p);
    }
    forn(i, m) {
        cout << ans[i].size();
        for (int x : ans[i]) cout << " " << x;
        cout << "\n";
    }
}

int main(){
    if(!INTERACTIVE) cin.tie(0)->sync_with_stdio(0);
    int t=1; if (MULTITEST) cin>>t; forn(i,t) solve();
}
