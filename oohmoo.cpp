#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// CHASH -> Crazy Hellish Asseninely Stupid Hash 
static const uint64_t CHRONO_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
static const uint64_t PIDRNDP = (uint64_t)(getpid())*0xbffbffbffULL;
static mt19937_64 PIDRNG(PIDRNDP);
static const uint64_t PIDRND = PIDRNG();
static const uint64_t FIXED_RANDOM = CHRONO_RANDOM ^ PIDRND;
struct CHASH {
    template <typename T>
    size_t operator()(const T& x) const {
        return hash<T>{}(x) ^ FIXED_RANDOM;
    }
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& x) const {
        return (*this)(x.first) ^ ((*this)(x.second) + 0x9e3779b9 + (x.first << 6) + (x.first >> 2));
    }
};
template<typename T1,typename T2>
using hashmap=unordered_map<T1,T2,CHASH>;
template<typename TM>
using matrix=vector<vector<TM>>;
#define all(x) (x).begin(),(x).end()
void solve(){
	ll MOD=1e9+7;
	ll n,d,a,b;cin>>n>>d>>a>>b;
	vector<ll> m(n);for(ll&x:m)cin>>x;
	sort(all(m));ll l=n-a,r=n-b-1;
	ll ql=r,qr=r;while(ql>0&&m[ql-1]==m[r])--ql;
	while(qr+1<n&&m[qr+1]==m[r])++qr;ll p=0,z=m[r];
	for(ll i=0;i<d;++i){ll x=(r-ql+1)+p;z+=x/(qr-ql+1);p=x%(qr-ql+1);
	while(qr+1<n&&m[qr+1]==z)++qr;while(ql>l&&m[ql-1]+i+1==z)--ql;}
	for(ll i=l;i<ql;++i)m[i]+=d;for(ll i=ql;i<=qr;++i)m[i]=qr-1<p?z+1:z;
	ll ans=0;for(ll i=0;i<n;++i)ans=(ans+(m[i]%MOD)*(m[i]%MOD))%MOD;
	cout<<ans<<"\n";
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
