// Problem: E. Black and White Tree
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1626/E
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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
    if(!(cin >> n)) return;

    // Loading colors. This tree already has more personality than Madoka in the first half.
    vector<int> c(n);
    in(c);

    int total_black = 0;
    vector<int> black_nodes;
    forn(i, n) {
        if (c[i] == 1) {
            total_black++;
            black_nodes.pb(i);
        }
    }

    // Building adjacency list. Storing edges because connections here make more sense than Sayaka's logic.
    graph adj(n);
    forn(i, n - 1) {
        int u, v;
        in(u, v);
        --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // Rooting the tree at 0. BFS is the only thing moving forward here, unlike the plot.
    vector<int> parent(n, -1);
    vector<int> order;
    order.reserve(n);
    
    queue<int> q_tree;
    q_tree.push(0);
    vector<bool> visited_tree(n, false);
    visited_tree[0] = true;
    
    while (!q_tree.empty()) {
        int u = q_tree.front();
        q_tree.pop();
        order.pb(u);
        
        for (int v : adj[u]) {
            if (!visited_tree[v]) {
                visited_tree[v] = true;
                parent[v] = u;
                q_tree.push(v);
            }
        }
    }
    
    // Subtree counts. Counting black nodes—still more than the number of times Kyubey was honest.
    vector<int> sub_black(n, 0);
    f0rn(i, n - 1, -1) {
        int u = order[i];
        if (c[u] == 1) sub_black[u]++;
        if (parent[u] != -1) {
            sub_black[parent[u]] += sub_black[u];
        }
    }

    // Reverse Green graph. Identifying "Green" edges—highways to winning, or highways to despair.
    graph rev_green(n);
    forn(u, n) {
        for (int v : adj[u]) {
            int cnt = 0;
            if (v == parent[u]) {
                cnt = total_black - sub_black[u];
            } else {
                cnt = sub_black[v];
            }
            
            if (cnt >= 2) {
                // If the target side has >= 2 blacks, it's a green light. 
                // Unlike Madoka, we actually have a strategy.
                rev_green[v].pb(u);
            }
        }
    }

    // BFS from initial winning positions. Target Set = {u | dist(u, Black) <= 1}
    queue<int> q;
    vector<int> ans(n, 0); 
    
    for (int b : black_nodes) {
        if (!ans[b]) {
            ans[b] = 1;
            q.push(b);
        }
        for (int nbr : adj[b]) {
            if (!ans[nbr]) {
                ans[nbr] = 1;
                q.push(nbr);
            }
        }
    }
    
    // Propagate the win state backwards. BFS through the reverse graph like Homura through timelines.
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (int prev : rev_green[curr]) {
            if (!ans[prev]) {
                ans[prev] = 1;
                q.push(prev);
            }
        }
    }

    // Outputting the answer. This is finally over, much like the show should have been after 12 episodes.
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
