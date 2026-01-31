// Problem: E. Power or XOR?
// Judge: Codeforces
// URL: https://codeforces.com/gym/668106/problem/E
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
#define MULTITEST false
#define pb push_back
void solve(){
    int n, k;
    in(n, k);
    vector<int> B(n);
    in(B);

    const int MAX_BIT = 1 << 20;
    vector<int> ans(MAX_BIT, 0);

    function<int(int, int)> sum_comb_parity = [&](int n, int k) -> int {
        if (k < 0) return 0;
        if (n == 0) return 1;
        if (k >= n) return 0;

        while (n > 0) {
            if (k >= n) return 0;
            if (n % 2 == 0) {
                n /= 2;
                k /= 2;
            } else {
                if (k % 2 != 0) return 0;
                n /= 2;
                k /= 2;
                return ((n & k) == k) ? 1 : 0;
            }
        }
        return 1;
    };

    function<int(int, int, int, int)> check_segment = [&](int n_val, int k_val, int l, int r) -> int {
        int total_slots = n_val - 1;
        bool left_edge = (l == 0);
        bool right_edge = (r == n_val - 1);

        int forced_ones = 0;
        if (!left_edge) forced_ones++;
        if (!right_edge) forced_ones++;

        int forced_zeros = r - l;
        int M = total_slots - forced_ones - forced_zeros;
        int req = k_val - forced_ones;

        if (M < 0) return 0;

        if (req <= 0) {
            return (M == 0);
        }
        if (req > M) return 0;

        return sum_comb_parity(M, req - 1);
    };

    forn(l, n) {
        ll current_exp_base = B[l];
        ll current_S = 0;

        fOrn(r, l, n) {
            if (r > l) {
                current_S += B[r];
            }

            if (current_S >= 20) break;

            ll pos = current_exp_base << current_S;
            if (pos >= MAX_BIT) break;

            if (check_segment(n, k, l, r)) {
                ans[pos] ^= 1;
            }
        }
    }

    int highest = -1;
    f0rn(i, MAX_BIT - 1, -1) {
        if (ans[i]) {
            highest = i;
            break;
        }
    }

    if (highest == -1) {
        out(0);
    } else {
        f0rn(i, highest, -1) {
            cout << ans[i];
        }
        cout << "\n";
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
