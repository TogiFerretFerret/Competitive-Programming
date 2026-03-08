#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define fOrn(v,s,e) for(int v=(s);v<(e);++v)
#define pb push_back
#define MULTITEST true
void solve() {
    int val;
    string from, to;
    cin>>val>>from>>to;
    map<string, ll> multipliers;
    multipliers["SECONDS"] = 1;
    multipliers["MINUTES"] = 60;
    multipliers["HOURS"] = 3600;
    multipliers["DAYS"] = 86400;
    ll total_seconds = (ll)val * multipliers[from];
    ll result = total_seconds / multipliers[to];
    cout<<val<<" "<<from<<"->"<<result<<" "<<to<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
