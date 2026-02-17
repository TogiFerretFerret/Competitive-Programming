#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
	int n;cin>>n;
	vector<int> a(n),b(n);
	for(int i=0;i<n;++i){
		int x;cin>>x;
		a[i]=x;
		b[n-1-i]=x;
	}
	int bs=0;
	int as=0;
	for(int i=0;i<n;++i){
		for(int j=0;j<n-1;++j){
			if(a[j]<a[j+1]){swap(a[j],a[j+1]);++as;}
			if(b[j]<b[j+1]){swap(b[j],b[j+1]);++bs;}
		}
	}
	cout<<min(bs,as)<<'\n';
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int t;cin>>t;while(t--)solve();
}



