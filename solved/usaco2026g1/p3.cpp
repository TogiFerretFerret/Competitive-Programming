#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9+7;
void solve(){
	int n,d;cin>>n>>d;
	vector<int> p(n),o(n);
	vector<int> ps(n+1);
	for(int i=0;i<n;++i)cin>>p[i]>>o[i];
	ps[0]=0;
	for(int i=1;i<n+1;++i)ps[i]=ps[i-1]+(1-o[i-1]);
	auto bmpow = [&](ll b, ll e){//binary exponentiation + modular power function
		ll r=1;b%=MOD;
		while(e>0){
			if(e%2==1)r=(r*b)%MOD;b=b*b%MOD;e/=2;
		}
		return r;
	};
	// powers of 2 and inverse precomp
	vector<ll> pow2(n+1);
	vector<ll> ipow2(n+1);
	pow2[0]=1;
	ipow2[0]=1;
	ll i2=bmpow(2,MOD-2);
	for(int i=1;i<n+1;++i){
		pow2[i]=(pow2[i-1]*2)%MOD;
		ipow2[i] = (ipow2[i-1]*i2)%MOD;
	}
	int rp=1;
	vector<int> rei(n+1);//range end index for coaches
	for(int i=1;i<n+1;++i){
		if(o[i-1]==1){
			ll lim=(ll)p[i-1]+d;
			while(rp<n&&(ll)p[rp]<=lim)++rp;
			if(rp<i)rp=i;
			rei[i]=rp;
		} else rei[i]=0; // not used for campers (free in perm)
	}
	vector<int> head(n+1,0); // head[i] -> first coach ind expiring at step i 
	vector<int> nxt(n+1); // next coach ind in list
	vector<ll> dp(n+1);
	ll sa=0,sb=0,ans=0;
	for(int i=1;i<=n;++i){
		int ei=i-1;int curr=head[ei];
		while(curr!=0){
			int j=curr;curr=nxt[curr];
			// remove from sa
			ll ta=(dp[j]*ipow2[ps[j]])%MOD;
			sa=(sa-ta+MOD)%MOD;// +MOD bc subt
			// add to sb
			ll cnt=ps[rei[j]]-ps[j]; // const count for j in B
			ll tb=(dp[j]*pow2[cnt])%MOD;
			sb=(sb+tb)%MOD;
		}
		if(o[i-1]==1){
			// cow i is a coach
			// transition: dp[i]=1+sa*2^(ps[i-1])+sb
			ll tas=(sa*pow2[ps[i-1]])%MOD;
			dp[i]=(1+tas+sb)%MOD;
			// add new coach to sa (starts in set a because rei[i]>=i)
			ll tn=(dp[i]*ipow2[ps[i]])%MOD;
			sa=(sa+tn)%MOD;
			nxt[i] = head[rei[i]];
			head[rei[i]] = i;
			/// add contrib to ans
			int vc=ps[rei[i]]-ps[i];
			ll ways=(dp[i]*pow2[vc])%MOD;
			ans=(ans+ways)%MOD;
		}
	}
	cout<<ans<<'\n';
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	solve();
}



