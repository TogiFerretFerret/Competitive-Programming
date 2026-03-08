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
    function<string(const string&)> expand = [&](const string& s) -> string {
        string result = "";
        int i = 0;
        while (i < (int)s.length()) {
            char c = s[i];
            if (isdigit(c)) {
                int count = 0;
                while (i < (int)s.length() && isdigit(s[i])) {
                    count = count * 10 + (s[i] - '0');
                    i++;
                }
                i++;
                int balance = 1;
                int start = i;
                while (i < (int)s.length() && balance > 0) {
                    if (s[i] == '(') balance++;
                    else if (s[i] == ')') balance--;
                    i++;
                }
                string inner = s.substr(start, (i - 1) - start);
                string expandedInner = expand(inner);
                forn(k, count) {
                    result += expandedInner;
                }
            } else {
                result += c;
                i++;
            }
        }
        return result;
    };
    string s;
    cin>>s;
    cout<<expand(s)<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
