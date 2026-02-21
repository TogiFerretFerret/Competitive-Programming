// Problem: C. Minimum Array
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1887/C
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

void solve() {
    int n; in(n);
    vector<ll> a(n + 1);
    fOrn(i, 1, n + 1) in(a[i]);
    int q; in(q);
    
    vector<ll> E(n + 2, 0);
    set<int> nz;
    
    function<void(int, ll)> add_E = [&](int idx, ll val) -> void {
        if (idx > n) return;
        if (E[idx] != 0) nz.erase(idx);
        E[idx] += val;
        if (E[idx] != 0) nz.insert(idx);
    };
    
    int best = 0;
    vector<tuple<int, int, ll>> ops(q + 1);
    fOrn(j, 1, q + 1) {
        int l, r; ll x; in(l, r, x);
        ops[j] = {l, r, x};
        add_E(l, x); add_E(r + 1, -x);
        
        if (!nz.empty()) {
            int first_diff = *nz.begin();
            if (E[first_diff] < 0) {
                best = j;
                vector<int> to_clear(nz.begin(), nz.end());
                for (int idx : to_clear) { E[idx] = 0; nz.erase(idx); }
            }
        }
    }
    
    vector<ll> diff(n + 2, 0);
    fOrn(j, 1, best + 1) {
        auto [l, r, x] = ops[j];
        diff[l] += x; diff[r + 1] -= x;
    }
    
    ll cur = 0;
    fOrn(i, 1, n + 1) {
        cur += diff[i];
        a[i] += cur;
    }
    vector<ll> res(a.begin() + 1, a.end());
    out(res);
}

int main(){
    if(!INTERACTIVE) cin.tie(0)->sync_with_stdio(0);
    int t=1; if (MULTITEST) cin>>t; forn(i,t) solve();
}
