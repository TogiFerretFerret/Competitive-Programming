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
	int n,m;cin>>n>>m;
	vector<vector<pair<int,char>>> adj(n+1);
	forn(i,m){
		int u,v;char c;cin>>u>>v>>c;
		adj[u].pb({v,c});
		adj[v].pb({u,c});
	}
	vector<int> ans(n+1,-1);
	vector<int> level;level.pb(1);
	ans[1]=0;int d=1;
	while(!level.empty()){
		char minc='z'+1;
		bool ed=false;
		for(int&u:level){
			for(pair<int,char>&e:adj[u]){
				if(e.ss<minc){
					minc=e.ss;
					ed=true;
				}
			}
		}
		if(!ed)break;
		vector<int> nlevel;
		for(int&u:level){
			for(pair<int,char>&e:adj[u]){
				if(e.ss==minc&&ans[e.ff]==-1){
					ans[e.ff]=d;
					nlevel.pb(e.ff);
				}
			}
		}
		level=nlevel;d++;
	}
	for(int i=1;i<=n;i++){
		// cool thing i saw in some cf editorial once
		cout<<ans[i]<<"\n "[i!=n];
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int t;cin>>t;forn(i,t)solve();
}




