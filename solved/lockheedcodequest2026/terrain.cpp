#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define fOrn(v,s,e) for(int v=(s);v<(e);++v)
#define pb push_back
#define MULTITEST true
template<typename TM> using matrix=vector<vector<TM>>;
void solve() {
    struct State {
        int r, c;
        int dist;
    };
    int w, h;
    cin>>w>>h;
    matrix<int> terrain(h, vector<int>(w));
    forn(r, h) {
        forn(c, w) {
            cin>>terrain[r][c];
        }
    }
    function<bool(int, int)> isCellValid = [&](int r, int c) -> bool {
        if (c < 1 || c >= w - 1) return false;
        if (r < 0 || r >= h) return false;
        int currentAlt = terrain[r][c];
        int flightAlt = currentAlt + 100;
        int leftAlt = terrain[r][c - 1];
        if (leftAlt >= flightAlt) return true;
        int rightAlt = terrain[r][c + 1];
        if (rightAlt >= flightAlt) return true;
        return false;
    };
    if (w < 3) {
        cout<<"NO ROUTE AVAILABLE\n";
        return;
    }
    matrix<int> visitedDist(h, vector<int>(w, -1));
    queue<State> q;
    fOrn(c, 1, w - 1) {
        if (isCellValid(0, c)) {
            visitedDist[0][c] = 1;
            q.push({0, c, 1});
        }
    }
    int minPathLength = -1;
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        if (cur.r == h - 1) {
            minPathLength = cur.dist;
            break;
        }
        fOrn(dr, -1, 2) {
            fOrn(dc, -1, 2) {
                if (dr == 0 && dc == 0) continue;
                int nr = cur.r + dr;
                int nc = cur.c + dc;
                if (nr >= 0 && nr < h && nc >= 0 && nc < w) {
                    if (visitedDist[nr][nc] == -1) {
                        if (isCellValid(nr, nc)) {
                            visitedDist[nr][nc] = cur.dist + 1;
                            q.push({nr, nc, cur.dist + 1});
                        }
                    }
                }
            }
        }
    }
    if (minPathLength != -1) {
        cout<<minPathLength<<"\n";
    } else {
        cout<<"NO ROUTE AVAILABLE\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
