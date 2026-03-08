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
    struct Point {
        int r, c;
        int dist;
    };
    struct Radar {
        int r, c;
        int radius;
    };
    int x, y;
	cin>>x>>y;
    vector<string> grid(y);
    vector<Radar> radars;
    int startR, startC, endR, endC;
    forn(r, y) {
        cin>>grid[r];
        forn(c, x) {
            char cell = grid[r][c];
            if (cell == 'P') {
                startR = r;
                startC = c;
            } else if (cell == 'D') {
                endR = r;
                endC = c;
            } else if (isdigit(cell)) {
                radars.pb({r, c, cell - '0'});
            }
        }
    }
    vector<vector<bool>> blocked(y, vector<bool>(x, false));
    for (const Radar& radar : radars) {
        int rad = radar.radius;
        int limit = rad + 1;
        int rMin = max(0, radar.r - limit);
        int rMax = min(y - 1, radar.r + limit);
        int cMin = max(0, radar.c - limit);
        int cMax = min(x - 1, radar.c + limit);
        int limitSq = rad * rad + rad;
        fOrn(r, rMin, rMax + 1) {
            fOrn(c, cMin, cMax + 1) {
                int dr = r - radar.r;
                int dc = c - radar.c;
                if (dr * dr + dc * dc <= limitSq) {
                    blocked[r][c] = true;
                }
            }
        }
    }
    queue<Point> q;
    q.push({startR, startC, 0});
    vector<vector<bool>> visited(y, vector<bool>(x, false));
    visited[startR][startC] = true;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        if (curr.r == endR && curr.c == endC) {
            cout<<curr.dist<<"\n";
            return;
        }
        forn(i, 4) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            if (nr >= 0 && nr < y && nc >= 0 && nc < x) {
                if (!visited[nr][nc] && !blocked[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc, curr.dist + 1});
                }
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
