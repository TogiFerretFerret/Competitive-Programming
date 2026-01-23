// Problem: C. Complete the MST
// Judge: Codeforces
// URL: https://codeforces.com/contest/1508/problem/C
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
m1(out) { cout << forward<T>(a);  m2(cout << " " <<); cout << "\n"; }
m1(debug) { cerr << forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> forward<T>(a); m2(cin >>); }
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
#define MULTITEST false
#define pb push_back
void solve(){
	int n, m;
    in(n, m);

    struct Edge {
        int u, v;
        ll w;
    };

    ll fixed_xor_sum = 0;
    vector<Edge> fixed_edges;
    vector<vector<pair<int, ll>>> fixed_adj(n + 1);

    forn(i, m) {
        int u, v;
        ll w;
        in(u, v, w);
        fixed_xor_sum ^= w;
        fixed_edges.pb({u, v, w});
        fixed_adj[u].pb({v, w});
        fixed_adj[v].pb({u, w});
    }

    vector<int> comp(n + 1, 0);
    int K = 0;
    set<int> remaining;
    forn(i, n) remaining.insert(i + 1);

    vector<int> mark(n + 1, 0);

    forn(i, n) {
        int start_node = i + 1;
        if (remaining.count(start_node)) {
            K++;
            vector<int> q;
            q.pb(start_node);
            remaining.erase(start_node);
            comp[start_node] = K;

            int head = 0;
            while (head < q.size()) {
                int u = q[head++];

                for (auto& edge : fixed_adj[u]) {
                    mark[edge.first] = u;
                }

                auto it = remaining.begin();
                while (it != remaining.end()) {
                    int candidate = *it;
                    if (mark[candidate] != u) {
                        comp[candidate] = K;
                        q.pb(candidate);
                        it = remaining.erase(it);
                    } else {
                        it++;
                    }
                }
            }
        }
    }

    ll total_free = (ll)n * (n - 1) / 2 - m;
    ll free_edges_in_forest = n - K;
    bool has_cycle = (total_free > free_edges_in_forest);

    if (has_cycle) {
        vector<Edge> super_edges;
        for (const auto& e : fixed_edges) {
            if (comp[e.u] != comp[e.v]) {
                super_edges.pb({comp[e.u], comp[e.v], e.w});
            }
        }
        sort(all(super_edges), [&](const Edge& a, const Edge& b) -> bool {
            return a.w < b.w;
        });

        vector<int> parent(K + 1);
        iota(all(parent), 0);
        function<int(int)> find = [&](int i) -> int {
            if (parent[i] == i) return i;
            return parent[i] = find(parent[i]);
        };
        function<bool(int, int)> unite = [&](int i, int j) -> bool {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
                return true;
            }
            return false;
        };

        ll ans = 0;
        for (const auto& e : super_edges) {
            if (unite(e.u, e.v)) {
                ans += e.w;
            }
        }
        out(ans);
    } else {
        vector<vector<bool>> is_fixed(n + 1, vector<bool>(n + 1, false));
        for (const auto& e : fixed_edges) {
            is_fixed[e.u][e.v] = is_fixed[e.v][e.u] = true;
        }

        vector<Edge> all_free_edges;
        forn(i, n) {
            int u = i + 1;
            forn(j, n) {
                int v = j + 1;
                if (v > u && !is_fixed[u][v]) {
                    all_free_edges.pb({u, v, 0});
                }
            }
        }

        vector<Edge> mst_candidates = fixed_edges;
        for (auto& e : all_free_edges) mst_candidates.pb(e);

        sort(all(mst_candidates), [&](const Edge& a, const Edge& b) -> bool {
            return a.w < b.w;
        });

        ll m0 = 0;
        vector<int> parent(n + 1);
        iota(all(parent), 0);
        function<int(int)> find = [&](int i) -> int {
            if (parent[i] == i) return i;
            return parent[i] = find(parent[i]);
        };
        function<bool(int, int)> unite = [&](int i, int j) -> bool {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
                return true;
            }
            return false;
        };

        vector<vector<int>> mst_adj(n + 1);
        vector<pair<int, int>> mst_free_used;

        for (const auto& e : mst_candidates) {
            if (unite(e.u, e.v)) {
                m0 += e.w;
                mst_adj[e.u].pb(e.v);
                mst_adj[e.v].pb(e.u);
                if (e.w == 0) {
                    mst_free_used.pb({e.u, e.v});
                }
            }
        }

        vector<int> tin(n + 1, 0), tout(n + 1, 0);
        int timer = 0;

        function<void(int, int)> dfs_mst = [&](int u, int p) -> void {
            tin[u] = ++timer;
            for (int v : mst_adj[u]) {
                if (v != p) dfs_mst(v, u);
            }
            tout[u] = timer;
        };

        dfs_mst(1, 0);

        function<bool(int, int)> is_ancestor = [&](int u, int v) -> bool {
            return tin[u] <= tin[v] && tout[u] >= tout[v];
        };

        ll min_penalty = fixed_xor_sum;

        for (auto& p : mst_free_used) {
            int u = p.first;
            int v = p.second;

            int child = (tin[u] > tin[v]) ? u : v;

            ll best_f = -1;

            for (const auto& f : fixed_edges) {
                bool u_in_subtree = is_ancestor(child, f.u);
                bool v_in_subtree = is_ancestor(child, f.v);

                if (u_in_subtree != v_in_subtree) {
                    if (best_f == -1 || f.w < best_f) {
                        best_f = f.w;
                    }
                }
            }

            ll current_penalty = fixed_xor_sum;
            if (best_f != -1) {
                current_penalty = min(current_penalty, best_f);
            }
            if (current_penalty < min_penalty) min_penalty = current_penalty;
        }

        out(m0 + min_penalty);
    }
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int t=1;
	if (MULTITEST) cin>>t;
	forn(i,t)solve();
}
