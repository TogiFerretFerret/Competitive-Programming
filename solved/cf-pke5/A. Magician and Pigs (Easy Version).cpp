// Problem: A. Magician and Pigs (Easy Version)
// Judge: Codeforces
// URL: https://codeforces.com/gym/672032/problem/A
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
#define MULTITEST false
#define pb push_back
void solve(){
    const int MOD = 998244353;
    const int MAX_VAL = 200000;
    const int MAX_ARR = 200005;

    int n;
    in(n);

    struct Op {
        int type;
        int x;
    };

    vector<Op> ops(n + 1);
    fOrn(i, 1, n + 1) {
        in(ops[i].type);
        if (ops[i].type != 3) {
            in(ops[i].x);
        }
    }

    // Precompute Total Damage (TD)
    vector<ll> TD(n + 1);
    TD[0] = 0;
    
    fOrn(i, 1, n + 1) {
        if (ops[i].type == 1) {
            TD[i] = TD[i - 1];
        } else if (ops[i].type == 2) {
            TD[i] = TD[i - 1] + ops[i].x;
        } else {
            TD[i] = TD[i - 1] * 2;
        }
        if (TD[i] > MAX_VAL) TD[i] = MAX_VAL + 1;
    }

    // Fenwick Tree Logic
    vector<int> bit(MAX_ARR + 1, 0);

    function<void(int, int)> bit_add = [&](int idx, int delta) {
        for (++idx; idx <= MAX_ARR; idx += idx & -idx) {
            bit[idx] = (bit[idx] + delta) % MOD;
        }
    };

    function<int(int)> bit_query = [&](int idx) -> int {
        int sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            sum = (sum + bit[idx]) % MOD;
        }
        return sum;
    };

    vector<int> freq(MAX_ARR, 0);

    // Initial State
    freq[0] = 1;
    bit_add(0, 1);

    ll offset = 0;
    ll mul = 1;
    ll ans = 0;

    // Backward Processing
    f0rn(i, n, 0) {
        int t = ops[i].type;

        if (t == 1) {
            ll limit = (ll)ops[i].x - offset;
            if (limit > 0) {
                if (limit > MAX_VAL + 1) limit = MAX_VAL + 1;
                int raw_count = bit_query((int)limit - 1);
                ll real_count = (1LL * raw_count * mul) % MOD;
                ans = (ans + real_count) % MOD;
            }
        } else if (t == 2) {
            offset += ops[i].x;
        } else {
            ll shift = TD[i - 1];
            if (shift == 0) {
                mul = (mul * 2) % MOD;
            } else {
                if (shift < MAX_ARR) {
                    int s_int = (int)shift;
                    f0rn(p, MAX_VAL - s_int, -1) {
                        if (freq[p] == 0) continue;
                        int target = p + s_int;
                        if (target <= MAX_VAL) {
                            int val = freq[p];
                            freq[target] = (freq[target] + val) % MOD;
                            bit_add(target, val);
                        }
                    }
                }
            }
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
