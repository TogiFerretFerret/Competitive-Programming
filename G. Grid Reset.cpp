// Problem: G. Grid Reset
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1991/G
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
    struct Node {
        uint32_t parent_node;
        uint32_t state_and_choice;
        
        int state() const { return state_and_choice & 0x7FFFFFFF; }
        int choice() const { return state_and_choice >> 31; }
    };

    // Statically sized caches to sidestep deep recursion and TLE bounds between independent cases
    static int state_to_node[3200000];
    static bool initialized = false;
    if (!initialized) {
        memset(state_to_node, -1, sizeof(state_to_node));
        initialized = true;
    }
    
    static vector<Node> all_nodes;
    if (all_nodes.capacity() < 4000000) {
        all_nodes.reserve(4000000);
    }
    all_nodes.clear();

    int n, m, k, q;
    in(n, m, k, q);
    string seq;
    in(seq);
    
    // Explicit resolutions to instantly-resetting edge geometries
    if (n == k) {
        int curr_h = 1;
        for (char op : seq) {
            if (op == 'H') {
                out(curr_h, 1);
                curr_h++;
                if (curr_h > n) curr_h = 1;
            } else {
                out(1, m);
            }
        }
        return;
    }
    
    if (m == k) {
        int curr_v = 1;
        for (char op : seq) {
            if (op == 'H') {
                out(n, 1);
            } else {
                out(1, curr_v);
                curr_v++;
                if (curr_v > m) curr_v = 1;
            }
        }
        return;
    }
    
    all_nodes.pb({(uint32_t)-1, 0});
    vector<int> curr = {0}; 
    
    forn(i, q) {
        vector<int> next_curr;
        char op = seq[i];
        
        for(int u : curr) {
            int state = all_nodes[u].state();
            int c = state % 101;
            int b = (state / 101) % 101;
            int a = (state / 10201) % 101;
            int mode = state / 1030301;
            
            if (op == 'H') {
                if (a < k && (mode == 0 || mode == 1)) {
                    int n_mode = 1, n_a = a + 1, n_b = b, n_c = c;
                    bool g1 = (n_a == k && n_b == m - k);
                    bool g2 = (n_a == k && n_c == n - k);
                    if (g1 && g2) { n_mode = 0; n_a = 0; n_b = 0; n_c = 0; }
                    else if (g1) { n_mode = 0; n_a = 0; n_b = 0; }
                    else if (g2) { n_mode = 0; n_a = 0; n_c = 0; }
                    
                    int n_state = n_mode * 1030301 + n_a * 10201 + n_b * 101 + n_c;
                    if (state_to_node[n_state] == -1) {
                        state_to_node[n_state] = all_nodes.size();
                        all_nodes.pb({(uint32_t)u, (uint32_t)n_state});
                        next_curr.pb(all_nodes.size() - 1);
                    }
                }
                if (c < n - k) {
                    int n_mode = mode, n_a = a, n_b = b, n_c = c + 1;
                    bool g1 = (n_a == k && n_b == m - k);
                    bool g2 = (n_a == k && n_c == n - k);
                    if (g1 && g2) { n_mode = 0; n_a = 0; n_b = 0; n_c = 0; }
                    else if (g1) { n_mode = 0; n_a = 0; n_b = 0; }
                    else if (g2) { n_mode = 0; n_a = 0; n_c = 0; }
                    
                    int n_state = n_mode * 1030301 + n_a * 10201 + n_b * 101 + n_c;
                    if (state_to_node[n_state] == -1) {
                        state_to_node[n_state] = all_nodes.size();
                        all_nodes.pb({(uint32_t)u, (uint32_t)(n_state | (1u << 31))});
                        next_curr.pb(all_nodes.size() - 1);
                    }
                }
            } else {
                if (a < k && (mode == 0 || mode == 2)) {
                    int n_mode = 2, n_a = a + 1, n_b = b, n_c = c;
                    bool g1 = (n_a == k && n_b == m - k);
                    bool g2 = (n_a == k && n_c == n - k);
                    if (g1 && g2) { n_mode = 0; n_a = 0; n_b = 0; n_c = 0; }
                    else if (g1) { n_mode = 0; n_a = 0; n_b = 0; }
                    else if (g2) { n_mode = 0; n_a = 0; n_c = 0; }
                    
                    int n_state = n_mode * 1030301 + n_a * 10201 + n_b * 101 + n_c;
                    if (state_to_node[n_state] == -1) {
                        state_to_node[n_state] = all_nodes.size();
                        all_nodes.pb({(uint32_t)u, (uint32_t)n_state});
                        next_curr.pb(all_nodes.size() - 1);
                    }
                }
                if (b < m - k) {
                    int n_mode = mode, n_a = a, n_b = b + 1, n_c = c;
                    bool g1 = (n_a == k && n_b == m - k);
                    bool g2 = (n_a == k && n_c == n - k);
                    if (g1 && g2) { n_mode = 0; n_a = 0; n_b = 0; n_c = 0; }
                    else if (g1) { n_mode = 0; n_a = 0; n_b = 0; }
                    else if (g2) { n_mode = 0; n_a = 0; n_c = 0; }
                    
                    int n_state = n_mode * 1030301 + n_a * 10201 + n_b * 101 + n_c;
                    if (state_to_node[n_state] == -1) {
                        state_to_node[n_state] = all_nodes.size();
                        all_nodes.pb({(uint32_t)u, (uint32_t)(n_state | (1u << 31))});
                        next_curr.pb(all_nodes.size() - 1);
                    }
                }
            }
        }
        
        // Wipe off efficiently to strictly deduplicate within current layer expansions natively 
        for (int u : next_curr) state_to_node[all_nodes[u].state()] = -1;
        
        curr = std::move(next_curr);
        if (curr.empty()) {
            out(-1);
            return;
        }
    }
    
    // Path Recreation Sequence
    vector<pair<int, int>> res;
    int curr_node = curr[0];
    f0rn(i, q - 1, -1) {
        int choice = all_nodes[curr_node].choice();
        int parent_idx = all_nodes[curr_node].parent_node;
        int p_state = all_nodes[parent_idx].state();
        
        int p_c = p_state % 101;
        int p_b = (p_state / 101) % 101;
        int p_a = (p_state / 10201) % 101;
        
        if (seq[i] == 'H') {
            if (choice == 0) res.pb({p_a + 1, 1});
            else res.pb({k + p_c + 1, 1});
        } else {
            if (choice == 0) res.pb({1, p_a + 1});
            else res.pb({1, k + p_b + 1});
        }
        curr_node = parent_idx;
    }
    
    reverse(all(res));
    for (auto& coord : res) out(coord.first, coord.second);
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
    forn(i,t) solve();
}
