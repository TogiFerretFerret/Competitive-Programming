#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T, class U> istream& operator>>(istream& i, pair<T, U>& p) { return i >> p.first >> p.second; }
template<class T, class U> ostream& operator<<(ostream& o, const pair<T, U>& p) { return o << p.first << " " << p.second; }
template<class T> istream& operator>>(istream& i, vector<T>& v) { for(auto& x : v) i >> x; return i; }
template<class T> ostream& operator<<(ostream& o, const vector<T>& v) { for(int i=0; i<v.size(); ++i) o << v[i] << (i==v.size()-1?"":" "); return o; }
#define m1(x) template<class T, class... U> void x(T&& a, U&&... b)
#define m2(x) (int[]){(x forward<U>(b),0)...}
m1(out) { cout << forward<T>(a);  m2(cout << " " <<); cout << "\n"; }
m1(debug) { cerr << forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> forward<T>(a); m2(cin >>); }
template<typename T1,typename T2>
using hashmap=unordered_map<T1,T2>;
template<typename TM>
using matrix=vector<vector<TM>>;
template<typename TM>
using tensor=vector<matrix<TM>>;
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define MULTITEST false
// #define FILEIO
#define FILENAME "input"
void solve(){
	
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	#ifdef FILEIO
		freopen(FILENAME".in","r",stdin);
		freopen(FILENAME".out","w",stdout);
	#endif
	int t=1;
	if (MULTITEST) cin>>t;
	forn(i,t)solve();
}



