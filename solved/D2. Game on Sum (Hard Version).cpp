// Problem: D2. Game on Sum (Hard Version)
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1628/D2
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
#define MULTITEST true
#define pb push_back
void solve(){
    ll n, m, k;
    in(n, m, k);

    static const int MOD = 1000000007;
    static const int MAXN = 1000005;
    static vector<ll> fact, invFact, invPow2;

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

    auto modInverse = [&](ll n) -> ll {
        return power(n, MOD - 2);
    };

    if (fact.empty()) {
        fact.resize(MAXN);
        invFact.resize(MAXN);
        invPow2.resize(MAXN);

        fact[0] = 1;
        invFact[0] = 1;
        invPow2[0] = 1; 
        ll i2 = modInverse(2);

        fOrn(i, 1, MAXN) {
            fact[i] = (fact[i - 1] * i) % MOD;
            invPow2[i] = (invPow2[i-1] * i2) % MOD;
        }
        invFact[MAXN - 1] = modInverse(fact[MAXN - 1]);
        f0rn(i, MAXN - 2, -1) {
            invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
        }
    }

    auto nCr = [&](int n, int r) -> ll {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    };

    if (m == 0) {
        out(0);
        return;
    }
    if (m == n) {
        out((n * k) % MOD);
        return;
    }

    ll ans = 0;
    fOrn(j, 1, m + 1) {
        ll combinations = nCr(n - j - 1, m - j);
        ll term = (ll)j * combinations % MOD;
        term = term * invPow2[n - j] % MOD;
        ans = (ans + term) % MOD;
    }

    ans = (ans * k) % MOD;
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
