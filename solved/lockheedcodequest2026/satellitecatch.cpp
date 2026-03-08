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
    constexpr double G = 6.673e-11;
    constexpr double M = 5.98e24;
    constexpr double R_EARTH = 6.37e6;
    constexpr double PI = 3.14159265358979323846;
    double h;
    cin>>h;
    double r = R_EARTH + h;
    double v_raw = sqrt((G * M) / r);
    int v_rounded = (int)round(v_raw);
    double num = 4.0 * PI * PI * pow(r, 3);
    double den = G * M;
    double t_raw = sqrt(num / den);
    ll total_seconds = (ll)round(t_raw);
    ll hours = total_seconds / 3600;
    ll remainder = total_seconds % 3600;
    ll minutes = remainder / 60;
    ll seconds = remainder % 60;
    cout<<v_rounded<<" "<<hours<<":"<<setfill('0')<<setw(2)<<minutes<<":"<<setfill('0')<<setw(2)<<seconds<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
