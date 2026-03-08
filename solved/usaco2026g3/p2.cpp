#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define pb push_back
void solve(){
	int n,m,k,l;cin>>n>>m>>k>>l;
	vector<int> s(k),d(l),idst(n+1,0);for(int&x:s)cin>>x;
	forn(i,l)cin>>d[i],idst[d[i]]=1;
	vector<vector<int>> adj(n+1);
	forn(i,m){
		int u,v;cin>>u>>v;
		adj[u].pb(v),adj[v].pb(u);
	}
	//bfs + dag sp
	vector<int>dist(n+1,-1);
	queue<int> q;vector<vector<int>> layers(n+1);
	dist[1]=0;q.push(1);layers[0].pb(1);int md=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		md=max(md,dist[u]);
		for(int v:adj[u]){
			if(dist[v]==-1){
				dist[v]=dist[u]+1;
				layers[dist[v]].pb(v);
				q.push(v);
			}
		}
	}
	vector<pair<int,int>> ss;
	bool sp=1;
	for(int farm:s){
		sp=dist[farm]==-1?0:sp;
		ss.pb({dist[farm],farm});
	}
	if(sp){
		sort(all(ss));
		// check for dupes
		for(int i=0;i+1<ss.size();++i){// if i use a macro for this i segfault
			if(ss[i].first==ss[i+1].first){
				sp=0;break;
			}
		}
	}
	if(!sp){string ans(n-1,'0');cout<<ans<<"\n";return;}
	vector<int> fc={1};
	for(pair<int,int>&p:ss)fc.pb(p.second);
	vector<int> nci(n+1,-1),fwd=nci;forn(i,fc.size())nci[fc[i]]=i;
	fwd[1]=0;
	forn(i,md+1){ //topogoglical order
		for(int u:layers[i]){
			int cs=fwd[u];
			if(cs==-1)continue;
			if(nci[u]>0)if(cs==nci[u]-1)cs=nci[u];else cs=-1;
			if(cs==-1){fwd[u]=-1;continue;}
			fwd[u]=cs;
			//propagate
			for(int v:adj[u])if(dist[v]==dist[u]+1)fwd[v]=max(fwd[v],cs);
		}
	}
	vector<int> bwd(n+1,1e9);
	f0rn(i,md,-1){
		for(int u:layers[i]){
			if(idst[u])bwd[u]=min(bwd[u],(int)fc.size());//typecast bc .size is unsigned
			if(bwd[u]==1e9)continue;
			int pv=bwd[u];
			if(nci[u]!=-1)if(bwd[u]==nci[u]+1)pv=nci[u];else pv=1e9;
			//propagate
			if(pv!=1e9)for(int v:adj[u])if(dist[v]==dist[u]-1)bwd[v]=min(bwd[v],pv);
		}
	}
	bool cv=bwd[1]==1;
	if(fwd[fc[fc.size()-1]]!=fc.size()-1)cv=0;
	if(!cv){string ans(n-1,'0');cout<<ans<<"\n";return;}
	vector<int> sd;for(pair<int,int>&p:ss)sd.pb(p.first);
	// queries
	string ans="";ans.reserve(n-1);
	for(int f=2;f<n+1;++f){
		if(dist[f]==-1){ans+='0';continue;}else if(nci[f]!=-1){ans+='1';continue;}
		vector<int>::iterator it=lower_bound(all(sd),dist[f]);
		if(it!=sd.end()&&*it==dist[f]){ans+='0';continue;}
		ans+=(fwd[f]==(it-sd.begin())&&bwd[f]==((it-sd.begin())+1))?'1':'0';
	}
	cout<<ans<<"\n";
}
int main(){cin.tie(0)->sync_with_stdio(0);int t;cin>>t;while(t--)solve();}
