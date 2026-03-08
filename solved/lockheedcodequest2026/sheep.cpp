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
    function<double(string)> parsePace = [&](string s) -> double {
        int m, sec;
        sscanf(s.c_str(), "%d:%d", &m, &sec);
        return m + (sec / 60.0);
    };
    double trailLen;
    string paceStr;
    cin>>trailLen>>paceStr;
    double avgPace = parsePace(paceStr);
    double fastPace = avgPace - 1.0;
    double slowPace = avgPace + 1.0;
    double distFast = 5.0 / fastPace;
    double distSlow = 5.0 / slowPace;
    double distInterval = distFast + distSlow;
    double avail = trailLen - 2.0;
    if (avail < 0) {
        cout<<0<<"\n";
    } else {
        int intervals = (int)(avail / distInterval);
        if(intervals < 1) intervals = 1;
        cout<<intervals<<"\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
