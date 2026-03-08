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
    const string EXPECTED_COLOR = "#526988";
    function<string(const string&)> extractQuotedContent = [&](const string& line) -> string {
        uint firstQ = line.find('"');
        if (firstQ == string::npos) return "";
        uint secondQ = line.find('"', firstQ + 1);
        if (secondQ == string::npos) return "";
        return line.substr(firstQ + 1, secondQ - firstQ - 1);
    };
    string line;
    getline(cin, line);
    getline(cin, line);
    getline(cin, line);
    string dimsRaw = extractQuotedContent(line);
    stringstream ss(dimsRaw);
    int w, h, c, p;
    ss>>w>>h>>c>>p;
    unordered_map<char, bool> defectMap;
    forn(i, c) {
        getline(cin, line);
        string content = extractQuotedContent(line);
        if (content.empty()) continue;
        char pixelChar = content[0];
        bool isDefect = false;
        if (content.find("None") != string::npos) {
            isDefect = false;
        } else {
            uint hashPos = content.find('#');
            if (hashPos != string::npos) {
                string hex = content.substr(hashPos, 7);
                if (hex != EXPECTED_COLOR) {
                    isDefect = true;
                } else {
                    isDefect = false;
                }
            } else {
                isDefect = true;
            }
        }
        defectMap[pixelChar] = isDefect;
    }
    matrix<bool> grid(h, vector<bool>(w, false));
    forn(r, h) {
        getline(cin, line);
        string rowContent = extractQuotedContent(line);
        forn(col, min(w, (int)rowContent.length())) {
            char ch = rowContent[col];
            if (defectMap.count(ch)) {
                grid[r][col] = defectMap[ch];
            } else {
                grid[r][col] = false;
            }
        }
    }
    bool failed = false;
    forn(r, h - 1) {
        forn(col, w - 1) {
            if (grid[r][col] && grid[r][col+1] && grid[r+1][col] && grid[r+1][col+1]) {
                failed = true;
                break;
            }
        }
        if (failed) break;
    }
    if (failed) cout<<"FAIL\n";
    else cout<<"PASS\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) {
        cin>>t;
        string dum;
        getline(cin, dum);
    }
    forn(i, t) solve();
}
