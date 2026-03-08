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
    struct Printer {
        double density;
        double materialMass;
    };
    int n, p;
    cin>>n>>p;
    map<char, Printer> printers;
    forn(i, n) {
        char id;
        double density, mass;
        cin>>id>>density>>mass;
        printers[id] = {density, mass};
    }
    forn(i, p) {
        char printerID;
        int volume;
        double infill;
        cin>>printerID>>volume>>infill;
        Printer pr = printers[printerID];
        double massPerItem = volume * infill * pr.density;
        int count = 0;
        if (massPerItem > 0) {
            count = (int)(pr.materialMass / massPerItem);
        }
        cout<<count<<"\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
