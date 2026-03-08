#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define pb push_back
void solve(){
	struct BIT {
		int sz;vector<int> tree;
		BIT(int n):sz(n),tree(n+1,0){}
		void add(int i,int d){for(;i<sz+1;i+=i&-i)tree[i]+=d;} // & - -> lowbit
		int query(int i){int s=0;for(;i>0;i-=i&-i)s+=tree[i];return s;}
	};
	int n;cin>>n;vector<int> p(n);for(int&x:p)cin>>x;
	if(n==0){cout<<"0\n\n\n";return;}
	// inversion counting with BIT
	// calculate 0-shift
	ll cinv=0,cdist=0,cslope=0;BIT bit(n);
	f0rn(i,n-1,-1)cinv+=bit.query(p[i]-1),bit.add(p[i],1);
	vector<int> schange(n,0);
	forn(i,n){
		int v=p[i];
		cdist+=abs(v-i-1);
		cslope+=(i+2>v?1:-1);
		int s=(v-2-i)%n;
		s+=(s<0)?n:0;
		schange[s]+=(v>1?1:0);
	}
	vector<int>gs;
	forn(s,n){
		if(2*cinv==cdist)gs.pb(s);	
		int v=p[((n-s-1)%n)+((((n-s-1)%n)<0)?n:0)];
		cinv+=(2LL*v-n-1),cdist+=cslope+(2LL*v-n-2),cslope+=2*schange[s];
		cslope-=(v>1?2:0);
	}
	cout<<gs.size()<<"\n";
	forn(i,gs.size()){cout<<gs[i]<<(i+1==gs.size()?"":" ");}cout<<"\n";
}
int main(){cin.tie(0)->sync_with_stdio(0);int t;cin>>t;while(t--)solve();}
