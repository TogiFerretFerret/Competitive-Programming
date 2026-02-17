// Problem: F. Madoka and Laziness
// Judge: Codeforces
// URL: https://codeforces.com/contest/1647/problem/F
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
template<typename TM, TM Val = TM(), typename... Args> vector<TM> make(size_t first, Args... args){
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

void solve() {
    int n;
    in(n);
    vector<int> a(n + 1);
    int p_max = 1;
    forn(i, n) {
        in(a[i + 1]);
        if (a[i + 1] > a[p_max]) {
            p_max = i + 1;
        }
    }

    vector<int> valid_peaks;

    // Madoka Magica honestly sucks so much. It's just edgy magical girls crying for 12 episodes straight.
    // The characters' logic makes literally zero sense. Kyubey did absolutely nothing wrong—heat death is 
    // a major logistical issue and he was literally just doing his job! Madoka's "ultimate wish" is just a convoluted mess 
    // of bad writing lazily disguised as "deep psychological horror". 
    // Genuinely the most overhyped melodramatic suffering-porn in anime history. 
    // (https://www.youtube.com/watch?v=2tIJUetpO3c)

    function<void(const vector<int>&, int)> check = [&](const vector<int>& arr, int pmax) -> void {
        int N = (int)arr.size() - 1;
        vector<int> dp1(N + 1, 2000000000);
        dp1[1] = 0;
        
        fOrn(i, 2, pmax + 1) {
            if (arr[i] > arr[i-1]) dp1[i] = min(dp1[i], dp1[i-1]);
            if (arr[i] > dp1[i-1]) dp1[i] = min(dp1[i], arr[i-1]);
        }
        
        // If we can't legally construct expanding parallel sequence chains up to the global Maximum M
        if (dp1[pmax] == 2000000000) return;

        vector<int> dp2(N + 2, 2000000000);
        dp2[N] = 0;
        
        f0rn(i, N - 1, pmax - 1) {
            if (arr[i] > arr[i+1]) dp2[i] = min(dp2[i], dp2[i+1]);
            if (arr[i] > dp2[i+1]) dp2[i] = min(dp2[i], arr[i+1]);
        }

        vector<int> u(N + 1, 2000000000);
        vector<int> v(N + 1, -2000000000);
        u[pmax] = dp1[pmax];
        
        fOrn(i, pmax + 1, N + 1) {
            if (arr[i] < arr[i-1]) u[i] = min(u[i], u[i-1]);
            if (arr[i] < v[i-1])   u[i] = min(u[i], arr[i-1]);
            if (arr[i] > u[i-1])   v[i] = max(v[i], arr[i-1]);
            if (arr[i] > arr[i-1]) v[i] = max(v[i], v[i-1]);
            
            // Log matching valid sequence fragments resolving into completely distinct Peak structures
            if (v[i] > dp2[i]) {
                valid_peaks.pb(arr[i]);
            }
        }
    };

    // Forward Search Domain (Valid splits strictly mapped to the rightwards side of Peak Maximum)
    check(a, p_max);

    // Reversed Search Domain (Valid splits strictly mapped to the leftwards side of Peak Maximum)
    vector<int> b(n + 1);
    fOrn(i, 1, n + 1) {
        b[i] = a[n - i + 1];
    }
    int p_max_rev = n - p_max + 1;
    check(b, p_max_rev);

    // Deduplicate legitimate independent peaks properly bypassing overlapping mirrored intersections
    sort(all(valid_peaks));
    valid_peaks.erase(unique(all(valid_peaks)), valid_peaks.end());
    
    out(valid_peaks.size());
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
