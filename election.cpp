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
	int n,q;cin>>n>>q;
	vector<int> a(n);for(int&x:a)cin>>x;
	vector<int> cnt(n+1);
	map<int,int> frm;vector<set<int>>frq(n+1);
	for(int x:a)++cnt[x];
	for(int i=1;i<=n;++i){++frm[cnt[i]];frq[cnt[i]].insert(i);}

	function<void(int, int)> chg=[&](int x, int c)->void{
		--frm[cnt[x]];if(!frm[cnt[x]])frm.erase(cnt[x]);
		frq[cnt[x]].erase(x);cnt[x]+=c;++frm[cnt[x]];
		frq[cnt[x]].insert(x);
	};
	while(q--){int idx,x;cin>>idx>>x;--idx;
	chg(a[idx],-1);a[idx]=x;chg(a[idx],1);
	vector<int> df;for(pair<int,int> p:frm)if(p.first)df.push_back(p.first);
	int m=df.size();int mf=df.back();
	vector<int> mif(m),maf(m);
	for(int i=0;i<m;++i){
		mif[i]=*frq[df[i]].begin();
		maf[i]=*frq[df[i]].rbegin();
	}
	for(int i=m-2;i>-1;--i)maf[i]=max(maf[i],maf[i+1]);
	int ans=0;for(int l=0,r=m-1;l<m;++l){
		while(r>0&&df[l]+df[r-1]>mf-1)--r;
		ans=max(ans,abs(maf[r]-mif[l]));
	}
	cout<<ans<<"\n";
	}
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	solve();
}

