#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define pb push_back
const ll mod=1e9+7;
void solve(){
	function<ll(ll,ll)> powmod=[&](ll b,ll e)->ll{
		ll r=1;b%=mod;
		while(e>0){
			if(e&1)r=(r*b)%mod;
			b=(b*b)%mod;e>>=1;
		}
		return r;
	};
	function<ll(ll)> inv=[&](ll x)->ll{
		return powmod(x,mod-2);
	};
	int n;cin>>n;
	vector<vector<int>> adj(n+1);vector<int> sub(n+1,0);
	forn(i,n-1){
		int u,v;cin>>u>>v;
		adj[u].pb(v),adj[v].pb(u);
	}
	function<void(int,int)> gsz=[&](int u,int p)->void{
		sub[u]=1;
		for(int v:adj[u]){if(v!=p){gsz(v,u);sub[u]+=sub[v];}}
	};
	gsz(1,0);
	ll dpr=1,tot=0,f=1;forn(i,n)dpr=(dpr*sub[i+1])%mod;
	function<void(int,int,ll)> dfs=[&](int u,int p,ll val)->void{
		tot=(tot+val)%mod;
		for(int v:adj[u]){if(v!=p){
			ll nv=(val*sub[v])%mod;nv=(nv*inv(n-sub[v]))%mod;
			dfs(v,u,nv);
		}}
	};
	dfs(1,0,inv(dpr));
	forn(i,n-1)f=(f*(i+1))%mod;
	cout<<(tot*inv(f))%mod<<"\n";
}
int main(){cin.tie(0)->sync_with_stdio(0);int t;cin>>t;while(t--)solve();}
