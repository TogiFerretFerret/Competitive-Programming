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
    constexpr double PI = 3.14159265358979323846; // thanks python
    constexpr double EPS_ANG = 1e-9;
    struct interval {
        int id;
        double l, r;
        bool wraps;
        double len;
        bool contains(double theta) const {
            if (!wraps) {
                return theta > l + EPS_ANG && theta < r - EPS_ANG;
            } else {
                return theta > l + EPS_ANG || theta < r - EPS_ANG;
            }
        }
    };
    struct LinSeg {
        double start, end;
    };
    function<double(double)> norm = [&](double a) -> double {
        a = fmod(a, 2 * PI);
        if (a < 0) a += 2 * PI;
        return a;
    };
    int n;
    cin>>n;
    vector<interval> intervals;
    intervals.reserve(n);
    forn(i, n) {
        double x1, y1, x2, y2;
        char c;
        cin>>x1>>c>>y1>>c>>x2>>c>>y2;
        vector<pair<double, double>> pts = {
            {x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}
        };
        vector<double> angs;
        for (pair<double, double>& p : pts) angs.pb(atan2(p.second, p.first));
        sort(all(angs));
        double max_gap = 0;
        int gap_idx = -1;
        forn(j, 3) {
            double d = angs[j+1] - angs[j];
            if (d > max_gap) { max_gap = d; gap_idx = j; }
        }
        double wrap_gap = 2 * PI - (angs[3] - angs[0]);
        if (wrap_gap > max_gap) { max_gap = wrap_gap; gap_idx = 3; }
        double l, r;
        if (gap_idx == 3) {
            l = angs[0];
            r = angs[3];
        } else {
            l = angs[gap_idx + 1];
            r = angs[gap_idx];
        }

        // Store
        interval in;
        in.id = i;
        in.l = norm(l);
        in.r = norm(r);
        
        // Determine properties
        if (in.l > in.r) in.wraps = true;
        else in.wraps = false;

        if (in.wraps) in.len = (2 * PI - in.l) + in.r;
        else in.len = in.r - in.l;

        intervals.pb(in);
    }
    int btidx = 0;
    double mlv = 1e18;
    forn(i, n) {
        if (intervals[i].len < mlv) {
            mlv = intervals[i].len;
            btidx = i;
        }
    }
    const interval& target = intervals[btidx];
    int global_min = n + 1; // max possible shots is n
    forn(i, n) {
        double shot = norm(intervals[i].r - 1e-7);
        if (!target.contains(shot)) continue;
        vector<bool> covered(n, false);
        int sc = 1;
        
        forn(j, n) {
            if (intervals[j].contains(shot)) covered[j] = true;
        }
        vector<LinSeg> rmndrs;
        rmndrs.reserve(n);
        forn(j, n) {
            if (!covered[j]) {
                double s_rel = norm(intervals[j].l - shot);
                double e_rel = norm(intervals[j].r - shot);
                if (e_rel < s_rel) {
                    e_rel = 2 * PI; 
                }
                rmndrs.pb({s_rel, e_rel});
            }
        }
        sort(all(rmndrs), [&](const LinSeg& a, const LinSeg& b) -> bool {
            return a.end < b.end;
        });
        double llp = -1.0; 
        for (const LinSeg& seg : rmndrs) {
            if (llp < 0 || llp <= seg.start + 1e-9) {
                sc++;
                llp = seg.end - 1e-7;
            }
        }
        if (sc<global_min) global_min = sc;
    }
    cout<<global_min<<"\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin >> t;
    forn(i, t) solve();
}
