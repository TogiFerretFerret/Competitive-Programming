// Problem: E. Minecraft
// Judge: Codeforces
// URL: https://codeforces.com/gym/672032/problem/E
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
#define MULTITEST true
#define pb push_back
void solve(){
    int n, k;
    in(n, k);

    string s;
    in(s);

    vector<int> col_cnt(k, 0);
    forn(i, n) {
        string t;
        in(t);
        forn(j, k) {
            if (t[j] == '1') {
                col_cnt[j]++;
            }
        }
    }

    struct Entry {
        int prev_carry;
        int bit;
    };

    // history[step][carry]
    vector<vector<Entry>> history(k, vector<Entry>(n + 1));
    
    vector<int> reachable;
    reachable.pb(0);
    
    vector<int> seen(n + 1, -1);

    forn(step, k) {
        int col = k - 1 - step;
        int s_bit = s[col] - '0';
        int ones = col_cnt[col];
        int zeros = n - ones;

        vector<int> next_reachable;
        if (!reachable.empty()) next_reachable.reserve(reachable.size());

        for (int c : reachable) {
            // Option 0: x_j = 0
            int val0 = ones + c;
            if (val0 % 2 == s_bit) {
                int next_c = val0 / 2;
                if (next_c <= n) {
                    if (seen[next_c] != step) {
                        seen[next_c] = step;
                        next_reachable.pb(next_c);
                        history[step][next_c] = {c, 0};
                    }
                }
            }
            
            // Option 1: x_j = 1
            int val1 = zeros + c;
            if (val1 % 2 == s_bit) {
                int next_c = val1 / 2;
                if (next_c <= n) {
                    if (seen[next_c] != step) {
                        seen[next_c] = step;
                        next_reachable.pb(next_c);
                        history[step][next_c] = {c, 1};
                    }
                }
            }
        }
        reachable = move(next_reachable);
        if (reachable.empty()) break;
    }

    bool found = false;
    for (int c : reachable) {
        if (c == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        out("-1");
    } else {
        string res = "";
        res.reserve(k);
        int curr = 0;
        f0rn(step, k - 1, -1) {
            Entry e = history[step][curr];
            res += (char)('0' + e.bit);
            curr = e.prev_carry;
        }
        out(res);
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
