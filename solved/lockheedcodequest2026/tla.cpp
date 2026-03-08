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
    string line;
    getline(cin, line);
    string ans = "";
    bool in_word = false;
    forn(i, line.length()) {
        char c = line[i];
        if (c == ' ' || c == '-') {
            in_word = false;
        } else if (isalpha(c)) {
            if (!in_word) {
                ans += toupper(c);
                in_word = true;
            }
        }
    }
    cout<<ans<<"\n";
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
