// Problem: D. Table Cut
// Judge: Codeforces
// URL: https://codeforces.com/contest/2194/problem/D
// Memory Limit: 256 MB
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

    auto pref = make<int, 0>(n, m + 1);
    
    ll total_ones = 0;
    forn(i, n) {
        int row_accum = 0;
        forn(j, m) {
            int val;
            in(val);
            total_ones += val;
            row_accum += val;
            pref[i][j + 1] = row_accum; 
        }
    }

    int cols = m + 1;
    vector<int> min_dp((ll)(n + 1) * cols);
    vector<int> max_dp((ll)(n + 1) * cols);

    min_dp[0] = 0;
    max_dp[0] = 0;
    
    fOrn(j, 1, m + 1) {
        min_dp[j] = min_dp[j - 1]; 
        max_dp[j] = max_dp[j - 1];
    }
    
    fOrn(i, 1, n + 1) {
        ll row_idx = (ll)i * cols;
        ll prev_row_idx = (ll)(i - 1) * cols;
        
        min_dp[row_idx] = min_dp[prev_row_idx];
        max_dp[row_idx] = max_dp[prev_row_idx];
        
        fOrn(j, 1, m + 1) {
            ll curr = row_idx + j;
            ll up = prev_row_idx + j;
            ll left = row_idx + j - 1;

            int w_up = pref[i - 1][j];
            int min_from_up = min_dp[up] + w_up;
            int max_from_up = max_dp[up] + w_up;
            
            int min_from_left = min_dp[left];
            int max_from_left = max_dp[left];
            
            min_dp[curr] = min(min_from_up, min_from_left);
            max_dp[curr] = max(max_from_up, max_from_left);
        }
    }

    ll end_idx = (ll)n * cols + m;
    int min_k = min_dp[end_idx];
    int max_k = max_dp[end_idx];

    ll S = total_ones;
    ll best_k = -1;
    ll max_val = -1;

    function<void(ll)> check_val = [&](ll k) -> void {
        if (k < min_k || k > max_k) return;
        ll val = k * (S - k);
        if (val > max_val) {
            max_val = val;
            best_k = k;
        }
    };
    
    check_val(min_k);
    check_val(max_k);
    check_val(S / 2);
    check_val((S + 1) / 2);
    
    out(max_val);

    string path;
    path.reserve(n + m);
    int r = n;
    int c = m;
    int curr_k = best_k;
    
    while (r > 0 || c > 0) {
        bool went_up = false;
        
        if (r > 0) {
            ll prev_idx = (ll)(r - 1) * cols + c;
            int w = pref[r - 1][c];
            int needed = curr_k - w;
            
            if (needed >= min_dp[prev_idx] && needed <= max_dp[prev_idx]) {
                path += 'D';
                r--;
                curr_k = needed;
                went_up = true;
            }
        }
        
        if (!went_up) {
            path += 'R';
            c--;
        }
    }
    
    reverse(all(path));
    out(path);
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
