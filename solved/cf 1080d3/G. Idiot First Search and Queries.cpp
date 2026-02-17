// Problem: G. Idiot First Search and Queries
// Judge: Codeforces
// URL: https://codeforces.com/contest/2195/problem/G
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
    int n, q;
    in(n, q);

    auto left_child = make<int, 0>(n + 1);
    auto right_child = make<int, 0>(n + 1);
    auto parent = make<int, 0>(n + 1);

    fOrn(i, 1, n + 1) {
        int l, r;
        in(l, r);
        left_child[i] = l;
        right_child[i] = r;
        if (l != 0) parent[l] = i;
        if (r != 0) parent[r] = i;
    }
    parent[1] = 0; 

    vector<int> tour;
    tour.reserve(4 * n + 100);
    auto start_idx = make<int, 0>(n + 1);
    auto sub_size = make<int, 0>(n + 1);

    function<void(int)> dfs_build_tour = [&](int u) -> void {
        start_idx[u] = tour.size();
        
        if (left_child[u] == 0 && right_child[u] == 0) {
            tour.pb(parent[u]);
        } else {
            tour.pb(left_child[u]);
            dfs_build_tour(left_child[u]);
            
            tour.pb(right_child[u]);
            dfs_build_tour(right_child[u]);
            
            tour.pb(parent[u]);
        }
        
        sub_size[u] = (int)tour.size() - start_idx[u];
    };

    if (n > 0) {
        dfs_build_tour(1);
    }

    const int MAXLOG = 20;
    auto up = make<int, 0>(n + 1, MAXLOG);
    auto sum_up = make<ll, 0>(n + 1, MAXLOG);

    fOrn(i, 1, n + 1) {
        up[i][0] = parent[i];
        sum_up[i][0] = sub_size[i];
    }
    
    fOrn(j, 1, MAXLOG) {
        fOrn(i, 1, n + 1) {
            int ancestor = up[i][j-1];
            if (ancestor != 0) {
                up[i][j] = up[ancestor][j-1];
                sum_up[i][j] = sum_up[i][j-1] + sum_up[ancestor][j-1];
            } else {
                up[i][j] = 0;
                sum_up[i][j] = sum_up[i][j-1]; 
            }
        }
    }

    vector<int> results;
    results.reserve(q);

    forn(j, q) {
        int v;
        ll k;
        in(v, k);
        
        if (k == 0) {
            results.pb(v);
            continue;
        }

        int curr = v;
        
        f0rn(bit, MAXLOG - 1, -1) {
            if (up[curr][bit] != 0 && sum_up[curr][bit] < k) {
                k -= sum_up[curr][bit];
                curr = up[curr][bit];
            }
        }
        
        // k is 1-based index (moves).
        int idx = start_idx[curr] + (int)k - 1;
        results.pb(tour[idx]);
    }
    out(results);
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
