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
    map<string, vector<string>> recipes = {
        {"strawberry swirl", {"strawberry", "blueberry"}},
        {"banana burst", {"banana", "kiwi", "orange"}},
        {"tropical tango", {"kiwi", "orange", "mango", "blueberry"}},
        {"mango medley", {"mango", "strawberry", "blueberry", "banana"}}
    };
    string ingredient_line;
    string name_line;
    getline(cin, ingredient_line);
    if (ingredient_line.empty()) getline(cin, ingredient_line);
    getline(cin, name_line);
    set<string> stock;
    stringstream ss(ingredient_line);
    string item;
    while(getline(ss, item, '|')) {
        stock.insert(item);
    }
    if (recipes.find(name_line) == recipes.end()) {
        cout<<"NO\n";
        return;
    }
    bool possible = true;
    forn(i, recipes[name_line].size()) {
        string req = recipes[name_line][i];
        if (stock.find(req) == stock.end()) {
            possible = false;
            break;
        }
    }
    if (possible) cout<<"YES\n";
    else cout<<"NO\n";
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
