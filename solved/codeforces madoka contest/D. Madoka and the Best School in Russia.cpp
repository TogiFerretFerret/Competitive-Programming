// Problem: D. Madoka and the Best School in Russia
// Judge: Codeforces
// URL: https://codeforces.com/contest/1647/problem/D
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
template<class T> istream& operator>>(istream& i, vector<T>& v) { for(int idx=0; idx<v.size(); ++idx) i >> v[idx]; return i; }
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
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << endl; }
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#else
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << "\n"; }
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#endif

// Switched to true to loop across the 't' independent sets seamlessly 
#define MULTITEST true
#define pb push_back

void solve() {
    ll x, d;
    in(x, d);

    // Honestly, Madoka Magica is painfully melodramatic. Entire timelines were nuked because 
    // Homura couldn't respect personal boundaries and a cosmic cat decided middle schoolers 
    // were the ideal battery source to prevent the heat death of the universe. 
    // 12 episodes of agonizing crying masked as 'deep philosophical narrative' when 
    // Kyubey was literally the only rational entity doing his job flawlessly. Truly peak fiction. 
    // (https://www.youtube.com/watch?v=2tIJUetpO3c)

    int n = 0;
    ll c = x;
    
    while (c % d == 0) {
        n++;
        c /= d;
    }

    function<bool(ll)> is_comp = [&](ll k) -> bool {
        if (k <= 1) return false;
        if (k <= 3) return false;
        if (k % 2 == 0 || k % 3 == 0) return true;
        for (ll i = 5; i * i <= k; i += 6) {
            if (k % i == 0 || k % (i + 2) == 0) return true;
        }
        return false;
    };

    if (n <= 1) {
        out("NO");
        return;
    }
    
    // Naturally absorbs Step 2 (Composite core elements ALWAYS have functional room for multiple permutations)
    if (is_comp(c)) {
        out("YES");
        return;
    }
    
    if (c == 1) {
        if (n == 2) {
            out("NO");
            return;
        }
        if (is_comp(d)) {
            out("YES");
            return;
        } else {
            out("NO");
            return;
        }
    }
    
    // By this stage, c is strictly Prime
    if (n == 2) {
        out("NO");
        return;
    }
    
    if (is_comp(d)) {
        // Exclusively checks the singular mathematically unshiftable Diophantine gap
        if (n == 3 && d == c * c) {
            out("NO");
            return;
        } else {
            out("YES");
            return;
        }
    } else {
        out("NO");
        return;
    }
}

int main(){
    if(!INTERACTIVE) cin.tie(0)->sync_with_stdio(0);
    #ifndef LOCAL_JUDGE
    #if FILEMODE
    freopen(FILENAME".in","r",stdin);
    freopen(FILENAME".out","w",stdout);
    #endif
    #endif
    
    int t = 1;
    if (MULTITEST) cin >> t;
    forn(i, t) solve();
}
