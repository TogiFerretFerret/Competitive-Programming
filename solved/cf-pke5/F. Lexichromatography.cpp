// Problem: F. Lexichromatography
// Judge: Codeforces
// URL: https://codeforces.com/gym/672032/problem/F
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
void solve(){
    const ll MOD = 998244353;
    int n;
    in(n);

    map<int, vector<int>> pos;
    forn(i, n) {
        int x;
        in(x);
        pos[x].pb(i + 1);
    }

    auto power = [&](ll base, ll exp) -> ll {
        ll res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    };

    auto modInverse = [&](ll n_val) -> ll {
        return power(n_val, MOD - 2);
    };

    int D = pos.size();
    ll total_configs = power(2, D);

    for (auto const& [val, vec] : pos) {
        if (vec.size() % 2 != 0) {
            out((total_configs * modInverse(2)) % MOD);
            return;
        }
    }

    struct Interval {
        int l, r, val;
        bool operator<(const Interval& other) const {
            return l < other.l;
        }
    };

    vector<Interval> intervals;
    map<int, int> val_id;
    int id_counter = 0;

    for (auto const& [val, vec] : pos) {
        val_id[val] = ++id_counter;
        for (size_t i = 0; i < vec.size(); i += 2) {
            intervals.pb({vec[i], vec[i+1], val});
        }
    }

    sort(all(intervals));

    struct DSU {
        vector<int> parent;
        int components;
        
        DSU(int n) {
            parent.resize(n + 1);
            iota(parent.begin(), parent.end(), 0);
            components = 0; 
        }
        
        void set_components(int k) {
            components = k;
        }

        int find(int i) {
            if (parent[i] == i)
                return i;
            return parent[i] = find(parent[i]);
        }

        void unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
                components--;
            }
        }
    };

    DSU dsu(D);
    dsu.set_components(D);
    
    set<pair<int, int>> active;
    
    bool possible = true;
    
    for (const auto& interv : intervals) {
        int u = interv.l;
        int v = interv.r;
        int cur_val_id = val_id[interv.val];
        
        auto it = active.lower_bound({u + 1, -1});
        
        while (it != active.end() && it->first < v) {
            dsu.unite(cur_val_id, it->second);
            it = active.erase(it);
        }
        
        if (it != active.end()) {
            int encloser_val_id = it->second;
            if (encloser_val_id != cur_val_id) {
                possible = false;
                break;
            }
        }
        
        active.insert({v, cur_val_id});
    }

    ll count_equal = 0;
    if (possible) {
        count_equal = power(2, dsu.components);
    }
    
    ll num = (total_configs - count_equal + MOD) % MOD;
    ll ans = (num * modInverse(2)) % MOD;
    
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
