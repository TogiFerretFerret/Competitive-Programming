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
    function<int(const string&, char)> find_idx = [&](const string& s, char c) -> int {
        return s.find(c);
    };
    string left, right;
    cin>>left>>right;
    string dum;
    getline(cin, dum);
    string msg;
    getline(cin, msg);
    forn(i, msg.length()) {
        char c = msg[i];
        if (!isalpha(c)) {
            cout<<c;
            continue;
        }
        int idx = find_idx(left, c);
        rotate(left.begin(), left.begin() + idx, left.end());
        rotate(right.rbegin(), right.rbegin() + idx, right.rend());
        char cipher = right[0];
        cout<<cipher;
        char l_rem = left[25];
        left.erase(25, 1);
        left.insert(left.begin() + 13, l_rem);
        rotate(right.begin(), right.begin() + 1, right.end());
        char r_rem = right[2];
        right.erase(2, 1);
        right.insert(right.begin() + 13, r_rem);
    }
    cout<<"\n";
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
