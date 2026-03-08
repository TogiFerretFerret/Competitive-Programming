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
    int area;
    cin>>area;
    vector<int> sq;
    while(area > 0) {
        int side = sqrt(area);
        int sq_area = side * side;
        sq.pb(sq_area);
        area -= sq_area;
    }
    cout<<"[";
    forn(i, sq.size()) {
        cout<<sq[i];
        if (i < (int)sq.size() - 1) cout<<", ";
    }
    cout<<"]\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
