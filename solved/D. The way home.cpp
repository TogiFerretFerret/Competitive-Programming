// Problem: D. The way home
// Judge: Codeforces
// URL: https://codeforces.com/contest/1801/problem/D
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

struct Edge {
    int to;
    ll cost;
};

struct State {
    ll days;
    ll money;
    int u;      
    int w_idx;  

    bool operator>(const State& other) const {
        if (days != other.days) return days > other.days; 
        return money < other.money; 
    }
};

void solve(){
    int n, m;
    ll p;
    in(n, m, p);

    vector<ll> w(n + 1);
    vector<ll> distinct_w; 
    
    fOrn(i, 1, n + 1) {
        in(w[i]);
        distinct_w.pb(w[i]);
    }

    sort(all(distinct_w));
    distinct_w.erase(unique(all(distinct_w)), distinct_w.end());

    auto get_w_idx = [&](ll val) {
        return lower_bound(all(distinct_w), val) - distinct_w.begin();
    };

    vector<vector<Edge>> adj(n + 1);
    forn(i, m) {
        int u, v;
        ll s;
        in(u, v, s);
        adj[u].pb({v, s});
    }

    int K = distinct_w.size();
    ll INF = 1e18;
    matrix<pair<ll, ll>> dp = make<pair<ll, ll>>(n + 1, K);
    for(auto& v : dp) fill(all(v), make_pair(INF, -1LL));

    priority_queue<State, vector<State>, greater<State>> pq;

    int start_w_idx = get_w_idx(w[1]);
    dp[1][start_w_idx] = {0, p};
    pq.push({0, p, 1, start_w_idx});

    ll ans = INF;

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        ll d = cur.days;
        ll mon = cur.money;
        int u = cur.u;
        int idx = cur.w_idx;

        if (d > dp[u][idx].first) continue;
        if (d == dp[u][idx].first && mon < dp[u][idx].second) continue;

        ll current_rate = distinct_w[idx];

        for (auto& edge : adj[u]) {
            int v = edge.to;
            ll cost = edge.cost;

            ll needed_days = 0;
            ll next_mon = mon;

            if (next_mon < cost) {
                ll diff = cost - next_mon;
                needed_days = (diff + current_rate - 1) / current_rate;
                next_mon += needed_days * current_rate;
            }
            
            next_mon -= cost;
            ll next_days = d + needed_days;

            int next_idx = max(idx, (int)get_w_idx(w[v]));

            if (next_days < dp[v][next_idx].first || 
               (next_days == dp[v][next_idx].first && next_mon > dp[v][next_idx].second)) {
                
                dp[v][next_idx] = {next_days, next_mon};
                pq.push({next_days, next_mon, v, next_idx});
            }
        }
    }

    forn(i, K) {
        if (dp[n][i].first != INF) {
            ans = min(ans, dp[n][i].first);
        }
    }

    if (ans == INF) out("-1");
    else out(ans);
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
