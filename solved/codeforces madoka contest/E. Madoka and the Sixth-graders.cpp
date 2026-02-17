// Problem: E. Madoka and the Sixth-graders
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1647/E
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

#define MULTITEST false
#define pb push_back

void solve(){
    int n;
    in(n);

    // Madoka is basically a functional graph of bad decisions.
    vector<int> p(n + 1);
    vector<int> in_deg(n + 1, 0);
    fOrn(i, 1, n + 1) {
        in(p[i]);
        in_deg[p[i]]++;
    }

    vector<ll> a(n + 1);
    fOrn(i, 1, n + 1) in(a[i]);

    // These sources (Z) are the only things more empty than the plot of this show.
    vector<int> Z;
    fOrn(i, 1, n + 1) if (in_deg[i] == 0) Z.pb(i);

    ll max_val = 0;
    int max_idx = -1;
    fOrn(i, 1, n + 1) {
        if (a[i] > max_val) {
            max_val = a[i];
            max_idx = i;
        }
    }

    // Binary lifting to jump through timelines, which is still less confusing than the movie.
    matrix<int> up = make<int, 0>(n + 1, 32);
    fOrn(i, 1, n + 1) up[i][0] = p[i];
    fOrn(j, 1, 32) {
        fOrn(i, 1, n + 1) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    ll K = 0;
    if (max_val > n) {
        ll z_sz = (ll)Z.size();
        ll val = max_val;
        ll entry_round = (val - n - 1) / z_sz + 1;
        int z_idx = (int)((val - n - 1) % z_sz);
        int start_node = Z[z_idx];

        int dist = -1;
        int curr = start_node;
        // Looking for the target index... still faster than waiting for a likable character.
        forn(steps, 2 * n + 1) {
            if (curr == max_idx) {
                dist = steps;
                break;
            }
            curr = p[curr];
        }
        K = entry_round + (ll)dist;
    }

    function<int(int, ll)> jump = [&](int u, ll k_steps) -> int {
        forn(j, 32) {
            if ((k_steps >> j) & 1) {
                u = up[u][j];
            }
        }
        return u;
    };

    vector<int> target(n + 1);
    vector<bool> is_essential_min(n + 1, false);
    fOrn(u, 1, n + 1) {
        target[u] = jump(u, K);
        ll dest_val = a[target[u]];
        if (dest_val <= n) {
            is_essential_min[(int)dest_val] = true;
        }
    }

    // Fillers: much like Sayaka's character arc, they are just there to be used and discarded.
    set<int> fillers;
    fOrn(v, 1, n + 1) {
        if (!is_essential_min[v]) {
            fillers.insert(v);
        }
    }

    vector<int> b(n + 1);
    vector<bool> group_min_satisfied(n + 1, false);
    fOrn(u, 1, n + 1) {
        int group = target[u];
        int mandatory_val = (int)a[group];

        if (!group_min_satisfied[group]) {
            b[u] = mandatory_val;
            group_min_satisfied[group] = true;
        } else {
            // Finding a filler that fits, unlike the happy ending this show tried to have.
            set<int>::iterator it = fillers.upper_bound(mandatory_val);
            b[u] = *it;
            fillers.erase(it);
        }
    }

    vector<int> ans(n);
    forn(i, n) ans[i] = b[i + 1];
    out(ans); // Output the result and turn away, just like the audience did.
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
