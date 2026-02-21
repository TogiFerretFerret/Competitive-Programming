// Problem: E. Infinite Card Game
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1895/E
// Memory Limit: 512 MB
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

struct Card { int a, b, id; };

void solve() {
    int n; in(n);
    vector<Card> M(n);
    forn(i, n) in(M[i].a);
    forn(i, n) { in(M[i].b); M[i].id = i; }
    int m; in(m);
    vector<Card> B(m);
    forn(i, m) in(B[i].a);
    forn(i, m) { in(B[i].b); B[i].id = i; }
    
    function<bool(const Card&, const Card&)> comp = [&](const Card& x, const Card& y) -> bool { return x.a > y.a; };
    sort(all(M), comp); sort(all(B), comp);
    
    vector<int> m_max_def(n), b_max_def(m);
    int mx = -1;
    forn(i, n) { mx = max(mx, M[i].b); m_max_def[i] = mx; }
    mx = -1;
    forn(i, m) { mx = max(mx, B[i].b); b_max_def[i] = mx; }
    
    function<int(int, const vector<Card>&, const vector<int>&)> get_resp = [&](int def, const vector<Card>& cards, const vector<int>& max_d) -> int {
        int l = 0, r = (int)cards.size() - 1, idx = cards.size();
        while (l <= r) {
            int mid = (l + r) / 2;
            if (cards[mid].a > def) { idx = mid; r = mid - 1; }
            else l = mid + 1;
        }
        return (idx == cards.size()) ? -1 : max_d[idx];
    };
    
    vector<int> nxt(1000005, 0), state(1000005, 0), res(1000005, 0);
    forn(i, 1000005) {
        int b_resp = get_resp(i, B, b_max_def);
        if (b_resp == -1) nxt[i] = -1;
        else {
            int m_resp = get_resp(b_resp, M, m_max_def);
            nxt[i] = (m_resp == -1) ? -2 : m_resp;
        }
    }
    
    function<void(int)> dfs = [&](int u) -> void {
        state[u] = 1;
        int v = nxt[u];
        if (v == -1) res[u] = 1;
        else if (v == -2) res[u] = -1;
        else {
            if (state[v] == 0) dfs(v);
            res[u] = (state[v] == 1) ? 0 : res[v];
        }
        state[u] = 2;
    };
    forn(i, 1000005) if (state[i] == 0) dfs(i);
    
    int w = 0, d = 0, l = 0;
    forn(i, n) {
        if (res[M[i].b] == 1) w++;
        else if (res[M[i].b] == 0) d++;
        else l++;
    }
    out(w, d, l);
}

int main(){
    if(!INTERACTIVE) cin.tie(0)->sync_with_stdio(0);
    int t=1; if (MULTITEST) cin>>t; forn(i,t) solve();
}
