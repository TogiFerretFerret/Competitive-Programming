// Problem: E. The Turtle Strikes Back
// Judge: Codeforces
// URL: https://codeforces.com/contest/2194/problem/E
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
    int n, m;
    in(n, m);

    vector<ll> a(n * m);
    in(a);

    const ll INF = 1e18;

    vector<ll> dp_start(n * m, -INF);
    dp_start[0] = a[0];

    forn(i, n) {
        forn(j, m) {
            int curr = i * m + j;
            if (dp_start[curr] == -INF) continue;
            
            if (j + 1 < m) {
                int right = i * m + (j + 1);
                dp_start[right] = max(dp_start[right], dp_start[curr] + a[right]);
            }
            if (i + 1 < n) {
                int down = (i + 1) * m + j;
                dp_start[down] = max(dp_start[down], dp_start[curr] + a[down]);
            }
        }
    }

    vector<ll> dp_end(n * m, -INF);
    dp_end[n * m - 1] = a[n * m - 1];

    f0rn(i, n - 1, -1) {
        f0rn(j, m - 1, -1) {
            int curr = i * m + j;
            if (curr == n * m - 1) continue;
            
            ll max_next = -INF;
            
            if (j + 1 < m) {
                max_next = max(max_next, dp_end[curr + 1]);
            }
            if (i + 1 < n) {
                max_next = max(max_next, dp_end[curr + m]);
            }
            
            if (max_next != -INF) {
                dp_end[curr] = a[curr] + max_next;
            }
        }
    }

    int diag_count = n + m;
    vector<ll> diag_best1(diag_count, -INF);
    vector<ll> diag_best2(diag_count, -INF);
    vector<ll> M(n * m, -INF);

    forn(i, n) {
        forn(j, m) {
            int idx = i * m + j;
            if (dp_start[idx] != -INF && dp_end[idx] != -INF) {
                ll path_val = dp_start[idx] + dp_end[idx] - a[idx];
                M[idx] = path_val;
                
                int d = i + j;
                if (path_val > diag_best1[d]) {
                    diag_best2[d] = diag_best1[d];
                    diag_best1[d] = path_val;
                } else if (path_val > diag_best2[d]) {
                    diag_best2[d] = path_val;
                }
            }
        }
    }

    ll final_ans = INF;

    forn(i, n) {
        forn(j, m) {
            int idx = i * m + j;
            
            if (M[idx] != -INF) {
                ll val_if_flipped = M[idx] - 2 * a[idx];
                
                int d = i + j;
                ll val_avoiding;
                
                if (M[idx] == diag_best1[d]) {
                    val_avoiding = diag_best2[d];
                } else {
                    val_avoiding = diag_best1[d];
                }
                
                ll outcome = max(val_if_flipped, val_avoiding);
                
                if (outcome < final_ans) {
                    final_ans = outcome;
                }
            }
        }
    }

    out(final_ans);
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
