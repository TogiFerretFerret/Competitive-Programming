#include <bits/stdc++.h>
using namespace std;
// using hashmap with two template types as unordered_map (don't force int:int but use template types)
typedef long long ll;
// CHASH -> less hackable mtg-rng based custom hash function (plus using current time)
struct CHASH {
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
};
template<typename T1,typename T2>
using hashmap=unordered_map<T1,T2,CHASH>;
template<typename TM>
using matrix=vector<vector<TM>>;

void solve(){
	const int MOD = 1e9+7;ll l;
	function<int(int,int)> mod_mul=[&](int a,int b)->int{return (1LL*a*b)%MOD;};
	function<int(int,ll)> mod_pow=[&](int a,ll e)->int{if(e==0)return 1;int an=mod_pow(a,e/2);an=mod_mul(an,an);if(e%2)an=mod_mul(an,a);return an;};
	int n,k;cin>>n>>k>>l;
	vector<int> fct(n);fct[0]=1;
	for(int i=1;i<n;++i)fct[i]=mod_mul(fct[i-1],i);
	string s;cin>>s;
	int rq=0;int ans=1;
	for(int i=0;i<n;++i){
		if(s[i]=='M'){
			ans=mod_mul(mod_mul(fct[rq+k], mod_pow(fct[k],MOD-2)), mod_pow(fct[rq],MOD-2));
			rq+=k;
		} else --rq;
	}
	cout<<mod_pow(ans,l)<<'\n';
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	solve();
}


