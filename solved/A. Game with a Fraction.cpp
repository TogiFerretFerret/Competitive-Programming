#include <bits/stdc++.h>
using namespace std;
void solve(){
long long p,q;cin>>p>>q;
if (p<q && (q-p)<=min(p/2,q/3) ) {
	cout<<"Bob\n";
} else cout<<"Alice\n";
}
int main(){cin.tie(0)->sync_with_stdio(0);int t;cin>>t;while(t--)solve();}
