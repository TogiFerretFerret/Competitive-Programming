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
    function<bool(int, int, int)> covers_base = [&](int x, int y, int range) -> bool {
        ll dist_sq = (ll)x * x + (ll)y * y;
        ll range_sq = (ll)range * range;
        return dist_sq <= range_sq;
    };
    int n;
    cin>>n;
    unordered_set<int> p_freqs;
    vector<int> t_freqs;
    forn(i, n) {
        char type;
        string coord_str;
        int range, freq;
        cin>>type>>coord_str>>range>>freq;
        size_t comma_pos = coord_str.find(',');
        int x = stoi(coord_str.substr(0, comma_pos));
        int y = stoi(coord_str.substr(comma_pos + 1));
        if (covers_base(x, y, range)) {
            if (type == 'J') {
                p_freqs.insert(freq);
            } else if (type == 'T') {
                t_freqs.pb(freq);
            }
        }
    }
    bool safe = true;
    forn(i, t_freqs.size()) {
        if (p_freqs.find(t_freqs[i]) == p_freqs.end()) {
            safe = false;
            break;
        }
    }
    if (safe) {
        cout<<"SAFE\n";
    } else {
        cout<<"UNSAFE\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
