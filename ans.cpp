// Problem: E. Remove at the lowest cost
// Judge: Codeforces
// URL: https://codeforces.com/contest/2176/problem/E
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
#define m2(x) (int[]){(x forward<U>(b),0)...}
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
m1(out) { cout << forward<T>(a);  m2(cout << " " <<); cout << endl; }//softmod for interactive
m1(debug) { cerr << forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> forward<T>(a); m2(cin >>); }
#else
m1(out) { cout << forward<T>(a);  m2(cout << " " <<); cout << "\n"; }//softmod for interactive
m1(debug) { cerr << forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> forward<T>(a); m2(cin >>); }
#endif
#define MULTITEST true
#define pb push_back
void solve(){
    int n;
    in(n);
    vector<int> a(n), init_c(n), p_ops(n);
    in(a, init_c, p_ops);
    forn(i, n) p_ops[i]--;

    struct SuperGroup {
        int id;
        int size = 0;
        multiset<int> costs;
        vector<int> parents;
        int min_c = 0;
        ll term_valley = 0;
        int rep_val = 0;
        bool is_peak = false;
        int get_min() {
            return costs.empty() ? 2000000007 : *costs.begin();
        }
        void refresh() {
            min_c = get_min();
        }
    };

    vector<int> bg_id(n), bg_vals;
    int bg_cnt = 0;
    if (n > 0) {
        int l = 0;
        fOrn(i, 1, n) {
            if (a[i] != a[i - 1]) {
                bg_vals.pb(a[l]);
                fOrn(k, l, i) bg_id[k] = bg_cnt;
                bg_cnt++;
                l = i;
            }
        }
        bg_vals.pb(a[l]);
        fOrn(k, l, n) bg_id[k] = bg_cnt;
        bg_cnt++;
    }

    vector<int> ngl(bg_cnt, -1), ngr(bg_cnt, -1);
    stack<int> s;
    forn(i, bg_cnt) {
        while (!s.empty() && bg_vals[s.top()] <= bg_vals[i]) s.pop();
        if (!s.empty()) ngl[i] = s.top();
        s.push(i);
    }
    while (!s.empty()) s.pop();
    f0rn(i, bg_cnt - 1, -1) {
        while (!s.empty() && bg_vals[s.top()] <= bg_vals[i]) s.pop();
        if (!s.empty()) ngr[i] = s.top();
        s.push(i);
    }

    vector<int> p_dsu(bg_cnt);
    iota(all(p_dsu), 0);
    function<int(int)> find = [&](int x) -> int {
        return p_dsu[x] == x ? x : p_dsu[x] = find(p_dsu[x]);
    };

    forn(i, bg_cnt) {
        if (ngl[i] != -1 && ngr[i] != -1 && bg_vals[ngl[i]] == bg_vals[ngr[i]]) {
            int u = find(ngl[i]), v = find(ngr[i]);
            if (u != v) p_dsu[v] = u;
        }
    }

    vector<int> map_sg(bg_cnt, -1);
    int sg_sz = 0;
    forn(i, bg_cnt) {
        int r = find(i);
        if (map_sg[r] == -1) map_sg[r] = sg_sz++;
    }

    vector<SuperGroup> sgs(sg_sz);
    vector<int> elem_sg(n);
    forn(i, n) {
        int r = find(bg_id[i]);
        int u = map_sg[r];
        elem_sg[i] = u;
        sgs[u].id = u;
        sgs[u].costs.insert(init_c[i]);
        sgs[u].size++;
        sgs[u].rep_val = a[i];
    }

    graph children(sg_sz);
    forn(i, bg_cnt) {
        int u = map_sg[find(i)];
        if (ngl[i] != -1) {
            int p = map_sg[find(ngl[i])];
            if (u != p) sgs[u].parents.pb(p);
        }
        if (ngr[i] != -1) {
            int p = map_sg[find(ngr[i])];
            if (u != p) sgs[u].parents.pb(p);
        }
    }

    ll total_valley = 0, total_peak_elems = 0;
    multiset<int> peak_mins;
    vector<int> sg_eff_offer(sg_sz, 2000000007);

    forn(i, sg_sz) {
        sort(all(sgs[i].parents));
        sgs[i].parents.erase(unique(all(sgs[i].parents)), sgs[i].parents.end());
        if (sgs[i].parents.empty()) {
            sgs[i].is_peak = true;
            total_peak_elems += sgs[i].size;
        } else {
            for (int p : sgs[i].parents) children[p].pb(i);
        }
        sgs[i].refresh();
        if (sgs[i].is_peak) peak_mins.insert(sgs[i].min_c);
    }

    function<ll()> get_peak_part = [&]() -> ll {
        if (total_peak_elems == 0) return 0;
        int m = peak_mins.empty() ? 0 : *peak_mins.begin();
        return (total_peak_elems - 1) * (ll)m;
    };

    function<bool(int)> relax = [&](int u) -> bool {
        SuperGroup &g = sgs[u];
        if (g.is_peak) {
            int new_offer = g.min_c;
            if (new_offer != sg_eff_offer[u]) {
                sg_eff_offer[u] = new_offer;
                return true;
            }
            return false;
        }
        int bound = 2000000007;
        for (int p : g.parents) bound = min(bound, sg_eff_offer[p]);
        int E = min(g.min_c, bound);
        ll new_cost = (ll)g.size * E;
        bool changed = false;
        if (new_cost != g.term_valley) {
            total_valley -= g.term_valley;
            g.term_valley = new_cost;
            total_valley += g.term_valley;
        }
        if (E != sg_eff_offer[u]) {
            sg_eff_offer[u] = E;
            changed = true;
        }
        return changed;
    };

    vector<int> ord(sg_sz);
    iota(all(ord), 0);
    sort(all(ord), [&](int x, int y) { return sgs[x].rep_val > sgs[y].rep_val; });
    for (int u : ord) relax(u);

    vector<ll> results;
    results.pb(total_valley + get_peak_part());

    vector<int> q;
    q.reserve(sg_sz);
    forn(k, n) {
        int idx = p_ops[k];
        int u = elem_sg[idx];
        if (sgs[u].is_peak) peak_mins.erase(peak_mins.find(sgs[u].min_c));
        sgs[u].costs.erase(sgs[u].costs.find(init_c[idx]));
        init_c[idx] = 0;
        sgs[u].costs.insert(0);
        sgs[u].refresh();
        if (sgs[u].is_peak) peak_mins.insert(sgs[u].min_c);

        if (relax(u)) {
            q.clear();
            for (int v : children[u]) q.pb(v);
            int h = 0;
            while (h < (int)q.size()) {
                int cur = q[h++];
                if (relax(cur)) {
                    for (int nxt : children[cur]) q.pb(nxt);
                }
            }
        }
        results.pb(total_valley + get_peak_part());
    }
    out(results);
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
