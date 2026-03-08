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
    int cyl;
    double cur_fuel, max_fuel;
    int r;
    cin>>cyl>>cur_fuel>>max_fuel>>r;
    bool ok = true;
    forn(i, r) {
        char type;
        double dist;
        cin>>type>>dist;
        if (!ok) continue;
        if (cur_fuel <= 0) {
            ok = false;
            continue;
        }
        double base = 0;
        if (cyl == 4) {
            if (type == 'C') base = 28;
            else if (type == 'H') base = 35;
            else if (type == 'O') base = 20;
        } else if (cyl == 6) {
            if (type == 'C') base = 22;
            else if (type == 'H') base = 28;
            else if (type == 'O') base = 15;
        } else if (cyl == 8) {
            if (type == 'C') base = 18;
            else if (type == 'H') base = 22;
            else if (type == 'O') base = 12;
        }
        double eff_mpg = base - (0.25 * (max_fuel - cur_fuel));
        cur_fuel -= (dist / eff_mpg);
    }
    if (cur_fuel < 0) ok = false;
    if (ok) cout<<"YES\n";
    else cout<<"NO\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
