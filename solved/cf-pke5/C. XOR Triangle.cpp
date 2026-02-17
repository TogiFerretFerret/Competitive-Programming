// Problem: C. XOR Triangle
// Judge: Codeforces
// URL: https://codeforces.com/gym/672032/problem/C
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
#define MULTITEST false
#define pb push_back
void solve(){
    const int MOD = 998244353;

    struct Transition {
        int next_mask;
        int count;
    };

    // adj[digit][current_mask]
    auto adj = matrix<vector<Transition>>(2,matrix<Transition>(64));

    auto precompute = [&]() {
        forn(d, 2) {
            forn(mask, 64) {
                int tight_abc = mask >> 3; 
                int cond_curr = mask & 7;  
                
                int counts[64] = {0};
                
                forn(bits, 8) {
                    int u = (bits >> 2) & 1; 
                    int v = (bits >> 1) & 1; 
                    int w = bits & 1;        
                    
                    // --- Tightness Logic ---
                    int t_a = (tight_abc >> 2) & 1;
                    if (t_a && u > d) continue;
                    int nt_a = t_a && (u == d);

                    int t_b = (tight_abc >> 1) & 1;
                    if (t_b && v > d) continue;
                    int nt_b = t_b && (v == d);

                    int t_c = tight_abc & 1;
                    if (t_c && w > d) continue; 
                    int nt_c = t_c && (w == d);
                    
                    // --- Condition Logic ---
                    int X = u ^ v;
                    int Y = v ^ w;
                    
                    int new_cond = 0;
                    if (X == 1 && Y == 1) new_cond |= 4; // Cond 1
                    if (X == 1 && Y == 0) new_cond |= 2; // Cond 2
                    if (X == 0 && Y == 1) new_cond |= 1; // Cond 3
                    
                    int final_cond = cond_curr | new_cond;
                    
                    int next_mask = (nt_a << 5) | (nt_b << 4) | (nt_c << 3) | final_cond;
                    counts[next_mask]++;
                }
                
                forn(nm, 64) {
                    if (counts[nm] > 0) {
                        adj[d][mask].push_back({nm, counts[nm]});
                    }
                }
            }
        }
    };

    precompute();

    string s;
    in(s);

    vector<ll> dp(64, 0);
    // Initial state: Tightness 111 (56), Conditions 000 (0) -> 56
    dp[56] = 1;

    for (char c : s) {
        int d = c - '0';
        vector<ll> next_dp(64, 0);
        
        forn(mask, 64) {
            if (dp[mask] == 0) continue;
            
            ll ways = dp[mask];
            for (const auto& tr : adj[d][mask]) {
                next_dp[tr.next_mask] = (next_dp[tr.next_mask] + ways * tr.count) % MOD;
            }
        }
        
        dp = next_dp;
    }

    ll ans = 0;
    forn(mask, 64) {
        // Check if all conditions (lower 3 bits) are met
        if ((mask & 7) == 7) {
            ans = (ans + dp[mask]) % MOD;
        }
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
