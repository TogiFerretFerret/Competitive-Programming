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
    struct Aircraft {
        string name;
        double speed;
        double fuel_rate;
        int max_payload;
        int maintenance;
    };
    int n;
    cin>>n;
    Aircraft f22;
    f22.name = "F-22 Raptor";
    cin>>f22.speed>>f22.fuel_rate>>f22.max_payload>>f22.maintenance;
    Aircraft raider;
    raider.name = "Sikorsky Raider";
    cin>>raider.speed>>raider.fuel_rate>>raider.max_payload>>raider.maintenance;
    forn(i, n) {
        double dist;
        int load;
        cin>>dist>>load;
        bool f22_ok = (load <= f22.max_payload);
        bool raider_ok = (load <= raider.max_payload);
        double f22_fuel = dist * f22.fuel_rate;
        double f22_score = ((dist / f22.speed) * 3600.0) + f22_fuel + f22.maintenance;
        double raider_fuel = dist * raider.fuel_rate;
        double raider_score = ((dist / raider.speed) * 3600.0) + raider_fuel + raider.maintenance;
        if (!f22_ok) {
            cout<<raider.name<<"\n";
        } else if (!raider_ok) {
            cout<<f22.name<<"\n";
        } else {
            if (abs(f22_score - raider_score) < 0.01) {
                if (f22_fuel < raider_fuel) cout<<f22.name<<"\n";
                else cout<<raider.name<<"\n";
            } else {
                if (f22_score < raider_score) cout<<f22.name<<"\n";
                else cout<<raider.name<<"\n";
            }
        }
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
