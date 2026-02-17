// Problem: E. Middle Duplication
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1623/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
    int n, k_limit;
    in(n, k_limit);

    string s;
    in(s);

    struct Node {
        int id;
        int left = 0;
        int right = 0;
        int parent = 0;
        char val;
        bool good = false;
    };

    vector<Node> tree(n + 1);
    fOrn(i, 1, n + 1) {
        tree[i].id = i;
        tree[i].val = s[i-1];
    }

    fOrn(i, 1, n + 1) {
        int l, r;
        in(l, r);
        tree[i].left = l;
        tree[i].right = r;
        if(l) tree[l].parent = i;
        if(r) tree[r].parent = i;
    }

    vector<bool> dup_mark(n + 1, false);
    vector<int> depth(n + 1);
    vector<int> top_chain(n + 1);
    vector<int> in_order_nodes;

    char last_char = 0;
    bool run_status = false;

    function<void(int)> calc_good_bad = [&](int u) -> void {
        if (!u) return;
        
        calc_good_bad(tree[u].right);
        
        if (tree[u].val != last_char) {
            if (last_char > tree[u].val) run_status = true;
            else run_status = false;
            last_char = tree[u].val;
        }
        tree[u].good = run_status;
        
        calc_good_bad(tree[u].left);
    };

    function<void(int, int, int)> calc_structure = [&](int u, int d, int t) -> void {
        if (!u) return;
        depth[u] = d;
        top_chain[u] = t;
        
        if (tree[u].left) calc_structure(tree[u].left, d + 1, t);
        
        if (tree[u].right) calc_structure(tree[u].right, d + 1, tree[u].right);
    };

    function<void(int)> get_in_order = [&](int u) -> void {
        if (!u) return;
        get_in_order(tree[u].left);
        in_order_nodes.pb(u);
        get_in_order(tree[u].right);
    };

    calc_good_bad(1);
    calc_structure(1, 1, 1);
    get_in_order(1);

    depth[0] = 0;
    dup_mark[0] = true;

    for (int u : in_order_nodes) {
        if (dup_mark[u]) continue;
        if (!tree[u].good) continue;
        
        int t = top_chain[u];
        int anc = tree[t].parent;
        
        if (!dup_mark[anc]) continue;
        
        int cost = depth[u] - depth[anc];
        
        if (k_limit >= cost) {
            int curr = u;
            while (curr != anc) {
                if (!dup_mark[curr]) {
                    dup_mark[curr] = true;
                    k_limit--;
                }
                curr = tree[curr].parent;
            }
        }
    }

    string result = "";
    function<void(int)> build_output = [&](int u) -> void {
        if (!u) return;
        build_output(tree[u].left);
        result += tree[u].val;
        if (dup_mark[u]) result += tree[u].val;
        build_output(tree[u].right);
    };

    build_output(1);
    out(result);
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
