// Problem: C. Rubik's Cube Coloring (hard version)
// Judge: Codeforces
// URL: https://codeforces.com/gym/667910/problem/C
// Memory Limit: 256 MB
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
#define MULTITEST false
#define pb push_back
void solve(){
    ll K, N;
    in(K, N);
    
    hashmap<ll, int> fixed_colors;
    hashmap<ll, int> important_nodes;
    ll MOD = 1e9 + 7;

    function<int(string)> getColorID = [&](string s) -> int {
        if (s == "white") return 0;
        if (s == "yellow") return 1;
        if (s == "green") return 2;
        if (s == "blue") return 3;
        if (s == "red") return 4;
        if (s == "orange") return 5;
        return -1;
    };

    forn(i, N) {
        ll v;
        string s;
        in(v, s);
        fixed_colors[v] = getColorID(s);
        ll temp = v;
        while (temp >= 1) {
            important_nodes[temp] = 1;
            temp /= 2;
        }
    }

    function<ll(ll, ll)> power = [&](ll base, ll exp) -> ll {
        ll res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    };

    function<ll(int)> get_free_ways = [&](int h) -> ll {
        if (h == 0) return 1;
        ll exp_mod = MOD - 1;
        ll p2 = 1;
        ll b = 2;
        int e = h;
        while(e > 0) {
            if(e % 2) p2 = (p2 * b) % exp_mod;
            b = (b * b) % exp_mod;
            e /= 2;
        }
        ll exponent = (p2 - 1 + exp_mod) % exp_mod;
        return power(4, exponent);
    };

    function<vector<int>(int)> get_neighbors = [&](int c) -> vector<int> {
        vector<int> v;
        int opp = c ^ 1;
        forn(i, 6) {
            if (i != c && i != opp) v.pb(i);
        }
        return v;
    };

    function<ll(ll, int, int)> dfs;
    dfs = [&](ll u, int p_color, int height) -> ll {
        ll ways = 0;
        vector<int> candidates;
        
        if (fixed_colors.count(u)) {
            int fc = fixed_colors[u];
            if (p_color != -1) {
                int opp = p_color ^ 1;
                if (fc == p_color || fc == opp) return 0;
            }
            candidates.pb(fc);
        } else {
            if (p_color == -1) {
                forn(i, 6) candidates.pb(i);
            } else {
                candidates = get_neighbors(p_color);
            }
        }
        
        for (int c : candidates) {
            ll current_ways = 1;
            if (height > 1) {
                ll left_child = u << 1;
                ll right_child = (u << 1) + 1;
                int child_height = height - 1;
                
                if (important_nodes.count(left_child)) {
                    current_ways = (current_ways * dfs(left_child, c, child_height)) % MOD;
                } else {
                    current_ways = (current_ways * get_free_ways(child_height)) % MOD;
                }
                
                if (important_nodes.count(right_child)) {
                    current_ways = (current_ways * dfs(right_child, c, child_height)) % MOD;
                } else {
                    current_ways = (current_ways * get_free_ways(child_height)) % MOD;
                }
            }
            ways = (ways + current_ways) % MOD;
        }
        return ways;
    };

    out(dfs(1, -1, K));
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
