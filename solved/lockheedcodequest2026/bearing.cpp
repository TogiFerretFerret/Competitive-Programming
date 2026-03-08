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
    constexpr double PI = 3.14159265358979323846;
    double deg1, dist1, deg2, dist2;
    cin>>deg1>>dist1>>deg2>>dist2;
    double rad1 = deg1 * PI / 180.0;
    double x1 = dist1 * sin(rad1);
    double y1 = dist1 * cos(rad1);
    double rad2 = deg2 * PI / 180.0;
    double x2 = dist2 * sin(rad2);
    double y2 = dist2 * cos(rad2);
    double dx = x2 - x1;
    double dy = y2 - y1;
    double distTraveled = sqrt(dx * dx + dy * dy);
    double speedKmh = distTraveled / 0.1;
    double headingRad = atan2(dy, dx);
    double headingDegMath = headingRad * 180.0 / PI;
    double headingBearing = 90.0 - headingDegMath;
    if (headingBearing < 0) {
        headingBearing += 360.0;
    }
    if (headingBearing >= 360.0) {
        headingBearing -= 360.0;
    }
    cout<<(ll)round(speedKmh)<<" "<<(ll)round(headingBearing)<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
