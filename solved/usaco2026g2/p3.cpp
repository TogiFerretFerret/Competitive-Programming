#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define fOrn(v,s,e) for(int v=(s);v<(e);++v)
#define pb push_back
#define ff first
#define ss second

void solve(){
    int n, f;
    vector<int> a(n+1);
    vector<vector<int>> rev(n+1);
    forn(i, n) {
        cin >> a[i+1];
        rev[a[i+1]].pb(i+1);
    }
    vector<int> start(f);
    vector<bool> has(n+1, false);
    forn(i, f) {
        cin >> start[i];
        has[start[i]] = true;
    }

    vector<int> df(n+1, 1e9);
    queue<int> q;
    for(int i=1; i<=n; ++i) if(has[i]) { df[i] = 0; q.push(i); }
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : rev[u]) if(df[v] == 1e9) { df[v] = df[u] + 1; q.push(v); }
    }

    vector<int> vis(n+1, 0), onc(n+1, -1), dtc(n+1), ent(n+1), cpos(n+1);
    vector<vector<int>> cycs;
    
    for(int i=1; i<=n; ++i){
        if(vis[i]) continue;
        int u = i;
        vector<int> p;
        while(!vis[u]){
            vis[u] = 1; p.pb(u); u = a[u];
        }
        bool curr = false;
        int sidx = -1;
        forn(k, p.size()) if(p[k] == u) { curr = true; sidx = k; break; }
        
        if(curr){
            int cid = cycs.size();
            vector<int> cn;
            for(int k=sidx; k<p.size(); ++k){
                cn.pb(p[k]); onc[p[k]] = cid; cpos[p[k]] = k - sidx;
                ent[p[k]] = p[k]; dtc[p[k]] = 0; vis[p[k]] = 2;
            }
            cycs.pb(cn);
            for(int k=sidx-1; k>=0; --k){
                int v = p[k], nxt = p[k+1];
                ent[v] = ent[nxt]; dtc[v] = dtc[nxt] + 1; vis[v] = 2; onc[v] = onc[ent[v]];
            }
        } else {
            for(int k=p.size()-1; k>=0; --k){
                int v = p[k], nxt = (k==p.size()-1)?u:p[k+1];
                ent[v] = ent[nxt]; dtc[v] = dtc[nxt] + 1; vis[v] = 2; onc[v] = onc[ent[v]];
            }
        }
    }

    vector<vector<bool>> bad(cycs.size());
    forn(i, cycs.size()) bad[i].assign(cycs[i].size(), false);
    
    forn(i, f){
        int u = start[i], cid = onc[u];
        if(cid == -1) continue;
        int ph = (dtc[u] - cpos[ent[u]]) % (int)cycs[cid].size();
        if(ph < 0) ph += cycs[cid].size();
        bad[cid][ph] = true;
    }

    for(int i=1; i<=n; ++i){
        int lim = (df[i] == 1e9) ? 1e9 : df[i] - 1;
        if(lim == 1e9) { cout << -2 << "\n"; continue; }
        if(lim < 0) { cout << -1 << "\n"; continue; }
        
        int cid = onc[i], len = cycs[cid].size();
        int bph = (dtc[i] - cpos[ent[i]]) % len;
        if(bph < 0) bph += len;
        
        int ans = -1;
        f0rn(r, lim, -1){
            int cph = (bph + r) % len;
            if(!bad[cid][cph]) { ans = r; break; }
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

/// notes: i'm retarded like legit why did i reverse array + forgot input?
