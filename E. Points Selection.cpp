#include <bits/stdc++.h>
using namespace std; 
typedef long long ll;
void solve(){
	int n;cin>>n;
	vector<vector<ll>> coords(3,vector<ll>(n));
	for(ll&x:coords[0])cin>>x;for(ll&x:coords[1])cin>>x;for(ll&x:coords[2])cin>>x;
	vector<vector<ll>> w(n,vector<ll>(1<<4,0));
	for(int i=0;i<n;++i)for(int m=0;m<(1<<4);++m)for(int k=0;k<4;++k)if((m>>k)&1)w[i][m]+=coords[k&1][i]*(k<2?-1:1);
	vector<vector<ll>> d(n+1,vector<ll>(1<<4,LONG_LONG_MIN));
	d[0][0]=0;for(int i=0;i<n;++i)for(int m=0;m<(1<<4);++m){
		if(d[i][m]<LONG_LONG_MIN/2ll)continue;
		d[i+1][m]=max(d[i+1][m],d[i][m]+coords[2][i]);
		int f=((1<<4)-1)^m;for(int c=f;c>0;c=(c-1)&f)
			d[i+1][m|c]=max(d[i+1][m|c],d[i][m]+2ll*w[i][c]);
	}
	cout<<d[n][(1<<4)-1]<<"\n";
}
int main(){cin.tie(0)->sync_with_stdio(0);int t;cin>>t;while(t--)solve();}
