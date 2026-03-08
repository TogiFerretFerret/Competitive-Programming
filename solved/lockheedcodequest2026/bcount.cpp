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
    struct CharData {
        char c;
        int count;
        int firstAppearanceIndex;
    };
    function<bool(const CharData&, const CharData&)> compareCharData = [&](const CharData& a, const CharData& b) -> bool {
        if (a.count != b.count) {
            return a.count > b.count;
        }
        return a.firstAppearanceIndex < b.firstAppearanceIndex;
    };
    string line;
    getline(cin, line);
    cout<<line<<"\n";
    forn(i, line.length()) {
        cout<<"-";
    }
    cout<<"\n";
    stringstream ss(line);
    string word;
    int wordCount = 0;
    while (ss>>word) {
        wordCount++;
    }
    cout<<"CHARACTERS: "<<line.length()<<"\n";
    cout<<"WORDS: "<<wordCount<<"\n";
    map<char, int> frequency;
    map<char, int> firstIndex;
    forn(i, line.length()) {
        char c = line[i];
        if (frequency.find(c) == frequency.end()) {
            frequency[c] = 1;
            firstIndex[c] = i;
        } else {
            frequency[c]++;
        }
    }
    vector<CharData> stats;
    for (const auto& [key, val] : frequency) {
        stats.pb({key, val, firstIndex[key]});
    }
    sort(all(stats), compareCharData);
    for (const CharData& data : stats) {
        cout<<data.c<<": "<<data.count<<"\n";
    }
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
