// Problem: E. Text Editor
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1701/E
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
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << endl; }
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#else
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << "\n"; }
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#endif
#define MULTITEST true
#define pb push_back

void solve() {
    int n, m;
    in(n, m);
    string s, t;
    in(s, t);

    vector<int> pref(m + 1, n + 1);
    pref[0] = 0;
    int p_idx = 0;
    forn(i, n) {
        if (p_idx < m && s[i] == t[p_idx]) {
            p_idx++;
            pref[p_idx] = i + 1;
        }
    }

    if (pref[m] > n) {
        out(-1);
        return;
    }

    vector<int> posR(m + 1, -1);
    posR[m] = n;
    p_idx = m - 1;
    f0rn(i, n - 1, -1) {
        if (p_idx >= 0 && s[i] == t[p_idx]) {
            posR[p_idx] = i;
            p_idx--;
        }
    }

    vector<int> lcp((n + 2) * (m + 2), 0);
    auto get_lcp = [&](int i, int j) -> int& {
        return lcp[i * (m + 2) + j];
    };

    f0rn(i, n - 1, -1) {
        f0rn(j, m - 1, -1) {
            if (s[i] == t[j]) get_lcp(i, j) = 1 + get_lcp(i + 1, j + 1);
            else get_lcp(i, j) = 0;
        }
    }

    int ans = n - get_lcp(0, 0);

    forn(p, m + 1) {
        int start_L = pref[p];
        int end_L = posR[p];
        fOrn(L, start_L, end_L + 1) {
            ans = min(ans, n + 1 + L - p - get_lcp(L, p));
        }
    }

    out(ans);
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
