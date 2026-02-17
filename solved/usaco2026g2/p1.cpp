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
	int n;ll k;cin>>n>>k;
	vector<ll> a(n), b(n);forn(i,n)cin>>a[i];forn(i,n)cin>>b[i];
	function<ll(ll)> gcost=[&](ll d)->ll{
		vector<ll>p;p.reserve(2*n);
		forn(i,n){
			ll c=b[i]+d;
			if(a[i]<c)p.pb(a[i]),p.pb(c);
			else{
				ll s=a[i]+c;
				ll m1=(s>=0)?(s/2):((s-1)/2);
				ll m2=(s>=0)?((s+1)/2):(s/2);// hehe in cf this would collide w/ my macros for io
				p.pb(m1);p.pb(m2);
			}
		}
		if(p.empty())return 0LL;
		nth_element(p.begin(),p.begin()+n,p.end());//faster than nlogn sort for median
		ll x=p[n];
		ll cost=0;
		forn(i,n){
			ll c=b[i]+d;
			ll t1=0;if(a[i]-x>0)t1=a[i]-x;ll t2=0;if(x-c>0)t2=x-c;
			t1=t2>t1?t2:t1;
			cost+=t1;
		}
		return cost;
	};
	ll low=-2000000001LL,high=2000000001LL,ans=high;// low can be -2*10^9 and high 2*10^9 (off by 1 just to be safe)

	while(low<=high){
		ll mid=low+(high-low)/2;
		if(gcost(mid)<=k)ans=mid,high=mid-1;
		else low=mid+1;
	}
	cout<<ans<<"\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;
    if(cin >> t) forn(i,t) solve();
}


