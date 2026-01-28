// Problem: D. Learning to Paint
// Judge: Codeforces
// URL: https://codeforces.com/contest/1942/problem/D
// Memory Limit: 512 MB
// Time Limit: 4500 ms
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

    auto a = make<int>(n + 1, n + 1);
    fOrn(i, 1, n + 1) {
        fOrn(j, i, n + 1) {
            in(a[i][j]);
        }
    }

    matrix<ll> dp(n + 1);
    dp[0] = {0};

    struct Element {
        ll val;
        int source_idx;
        int val_idx;

        bool operator<(const Element& other) const {
            return val < other.val;
        }
    };

    fOrn(i, 1, n + 1) {
        priority_queue<Element> pq;

        if (!dp[i-1].empty()) {
            pq.push({dp[i-1][0], 0, 0});
        }

        fOrn(j, 1, i + 1) {
            int prev_idx = j - 2;
            ll current_interval_val = a[j][i];

            if (prev_idx < 0) {
                pq.push({current_interval_val, j, 0});
            } else {
                if (!dp[prev_idx].empty()) {
                    pq.push({dp[prev_idx][0] + current_interval_val, j, 0});
                }
            }
        }

        while (dp[i].size() < k && !pq.empty()) {
            Element top = pq.top();
            pq.pop();

            dp[i].pb(top.val);

            int src = top.source_idx;
            int next_idx = top.val_idx + 1;

            if (src == 0) {
                if (next_idx < dp[i-1].size()) {
                    pq.push({dp[i-1][next_idx], src, next_idx});
                }
            } else {
                int j = src;
                ll add_val = a[j][i];
                int prev_dp_idx = j - 2;

                if (prev_dp_idx >= 0) {
                    if (next_idx < dp[prev_dp_idx].size()) {
                        pq.push({dp[prev_dp_idx][next_idx] + add_val, src, next_idx});
                    }
                }
            }
        }
    }

    out(dp[n]);
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
