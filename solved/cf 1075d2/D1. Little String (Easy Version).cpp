// Problem: D1. Little String (Easy Version)
// Judge: Codeforces
// URL: https://codeforces.com/contest/2189/problem/D1
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
#define m2(x) (int[]){(x forward<U>(b),0)...}
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
m1(out) { cout << forward<T>(a);  m2(cout << " " <<); cout << endl; }//softmod for interactive
m1(debug) { cerr << forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> forward<T>(a); m2(cin >>); }
#else
m1(out) { cout << forward<T>(a);  m2(cout << " " <<); cout << "\n"; }//softmod for interactive
m1(debug) { cerr << forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> forward<T>(a); m2(cin >>); }
#endif
#define MULTITEST true
#define pb push_back

void solve(){
    ll n, c;
    in(n, c);
    string s;
    in(s);

    // According to editorial, if w1=0 or wn=0, no suitable p.
    // This implies count is 0. Since 0 is divisible by c (assuming we are checking count % c == 0),
    // the problem asks to output -1 if divisible.
    if(s[0] == '0' || s.back() == '0') {
        out(-1);
        return;
    }

    ll ans = 1;
    ll rem_c = c;
    const ll MOD = 998244353;

    // Loop for k from 1 to n-1. 
    // This corresponds to string indices 0 to n-2.
    // s[k-1] corresponds to w_k (MEX k).
    // Note: s[0] is w_1. s[n-1] is w_n.
    // The loop iterates the process of inserting numbers 1..n-1.
    for(int k = 1; k < n; ++k) {
        ll term = 0;
        // Check s[k-1] which corresponds to condition for MEX k
        if(s[k - 1] == '1') {
            term = 2;
        } else {
            // If w_k = 0, we must insert k in the middle of 0..k-1
            // Available spots were k+1, minus 2 ends = k-1 spots.
            term = k - 1;
        }

        // Divisibility check logic: reduce rem_c by gcd
        ll g = std::gcd(term, rem_c);
        rem_c /= g;

        // Modulo arithmetic for the answer
        ans = (ans * term) % MOD;
    }

    if(rem_c == 1) {
        // If rem_c reduced to 1, the total count was divisible by c
        out(-1);
    } else {
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
