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
    string kw_line, pt_line;
    getline(cin, kw_line);
    getline(cin, pt_line);
    vector<int> p_idx, k_idx;
    forn(i, pt_line.length()) {
        char c = pt_line[i];
        if (isalpha(c)) p_idx.pb(tolower(c) - 'a');
    }
    forn(i, kw_line.length()) {
        char c = kw_line[i];
        if (isalpha(c)) k_idx.pb(tolower(c) - 'a');
    }
    string res = "";
    int k_len = k_idx.size();
    forn(i, p_idx.size()) {
        int p_val = p_idx[i];
        int k_val;
        if (i < k_len) k_val = k_idx[i];
        else k_val = p_idx[i - k_len];
        int c_val = (p_val + k_val) % 26;
        res += (char)('A' + c_val);
    }
    cout<<res<<"\n";
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
