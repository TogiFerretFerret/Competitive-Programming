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
    constexpr double G = -9.8;
    constexpr double PI = 3.14159265358979323846;
    constexpr double EPS_T = 1e-4;
    constexpr double EPS_S = 1e-5;
    struct Missile {
        double x0, y0, v0, theta;
        double vx, vy;
        double A, B, C;
    };
    function<Missile(double, double, double, double, bool)> setup_missile = [&](double x0, double y0, double v0, double theta, bool moving_right) -> Missile {
        Missile m;
        m.x0 = x0; m.y0 = y0; m.v0 = v0; m.theta = theta;
        double rad = theta * PI / 180.0;
        double v_mag_x = v0 * cos(rad);
        m.vx = moving_right ? abs(v_mag_x) : -abs(v_mag_x);
        m.vy = v0 * sin(rad);
        double vx2 = m.vx * m.vx;
        m.A = G / (2.0 * vx2);
        m.B = (m.vy / m.vx) - (G * m.x0 / vx2);
        m.C = m.y0 - (m.vy * m.x0 / m.vx) + (G * m.x0 * m.x0 / (2.0 * vx2));
        return m;
    };
    double dx, dy, dv, dth, tx, ty, tv, tth;
    cin>>dx>>dy>>dv>>dth>>tx>>ty>>tv>>tth;
    bool dmr = (tx > dx);
    bool tmr = (dx > tx);
    Missile D = setup_missile(dx, dy, dv, dth, dmr);
    Missile T = setup_missile(tx, ty, tv, tth, tmr);
    double a_val = D.A - T.A;
    double b_val = D.B - T.B;
    double c_val = D.C - T.C;
    vector<double> x_cands;
    if (abs(a_val) < 1e-10) {
        if (abs(b_val) > 1e-10) {
            x_cands.pb(-c_val / b_val);
        }
    } else {
        double delta = b_val * b_val - 4.0 * a_val * c_val;
        if (delta >= 0.0) {
            double sqrt_d = sqrt(delta);
            x_cands.pb((-b_val - sqrt_d) / (2.0 * a_val));
            x_cands.pb((-b_val + sqrt_d) / (2.0 * a_val));
        }
    }
    vector<double> vlt;
    double min_b = min(dx, tx);
    double max_b = max(dx, tx);
    for (double x : x_cands) {
        if (x < min_b - EPS_S || x > max_b + EPS_S) continue;
        double y_at = T.A * x * x + T.B * x + T.C;
        if (y_at < 0) continue;
        double t_def = (x - D.x0) / D.vx;
        double t_thr = (x - T.x0) / T.vx;
        if (t_def < 0 || t_thr < 0) continue;
        double t_launch = t_thr - t_def;
        if (t_launch >= -EPS_T) {
            if (t_launch < 0) t_launch = 0.0;
            vlt.pb(t_launch);
        }
    }
    if (vlt.empty()) {
        cout<<"TAKE COVER\n";
    } else {
        sort(all(vlt));
        cout<<fixed<<setprecision(1)<<vlt[0]<<"\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
