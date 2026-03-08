#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define fOrn(v,s,e) for(int v=(s);v<(e);++v)
#define pb push_back
#define MULTITEST true
void solve() {
    int n;cin>>n;
    unordered_map<int, int> parent;
    string line;
    getline(cin, line);
    forn(i, n) {
        getline(cin, line);
        if (line.empty()) { 
            i--; continue; 
        }
        stringstream ss(line);
        int p_node;
        ss>>p_node;
        int c_node;
        while(ss>>c_node) {
            parent[c_node] = p_node;
        }
    }
    getline(cin, line);
    stringstream ss(line);
    vector<int> faults;
    int f;
    while(ss>>f) {
        faults.pb(f);
    }
    unordered_map<int, int> depth;
    function<int(int)> get_depth = [&](int node) -> int {
        if (node == 1) return 0;
        if (depth.count(node)) return depth[node];
        return depth[node] = 1 + get_depth(parent[node]);
    };
    function<int(int, int)> get_lca = [&](int u, int v) -> int {
        int du = get_depth(u);
        int dv = get_depth(v);
        while (du > dv) {
            u = parent[u];
            du--;
        }
        while (dv > du) {
            v = parent[v];
            dv--;
        }
        while (u != v) {
            u = parent[u];
            v = parent[v];
        }
        return u;
    };
    if (faults.empty()) {
        cout<<1<<"\n"; 
        return;
    }
    int current_ancestor = faults[0];
    fOrn(i, 1, faults.size()) {
        current_ancestor = get_lca(current_ancestor, faults[i]);
    }
    cout<<current_ancestor<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
