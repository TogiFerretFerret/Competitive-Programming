// Problem: Message Route
// Judge: CSES
// URL: https://cses.fi/problemset/task/1667
// Memory Limit: 512 MB
// Time Limit: 1000 ms
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static const uint64_t CHRONO_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
static const uint64_t PIDRNDP = (uint64_t)(getpid())*0xbffbffbffULL;
static mt19937_64 PIDRNG(PIDRNDP);
static const uint64_t PIDRND = PIDRNG();
static const uint64_t FIXED_RANDOM = CHRONO_RANDOM ^ PIDRND;
struct CHASH {
    template <typename T> size_t operator()(const T& x) const {
        return hash<T>{}(x) ^ FIXED_RANDOM;
    }
    template <typename T1, typename T2> size_t operator()(const pair<T1, T2>& x) const {
        return (*this)(x.first) ^ ((*this)(x.second) + 0x9e3779b9 + (x.first << 6) + (x.first >> 2));
    }
};
template<class T, class U> istream& operator>>(istream& i, pair<T, U>& p) { return i >> p.first >> p.second; }
template<class T, class U> ostream& operator<<(ostream& o, const pair<T, U>& p) { return o << p.first << " " << p.second; }
template<class T> istream& operator>>(istream& i, vector<T>& v) { for(auto& x : v) i >> x; return i; }
template<class T> ostream& operator<<(ostream& o, const vector<T>& v) { for(int i=0; i<v.size(); ++i) o << v[i] << (i==v.size()-1?"":" "); return o; }
#define m1(x) template<class T, class... U> void x(T&& a, U&&... b)
#define m2(x) (int[]){(x forward<U>(b),0)...}
m1(out) { cout << forward<T>(a);  m2(cout << " " <<); cout << "\n"; }
m1(debug) { cerr << forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> forward<T>(a); m2(cin >>); }
template<typename T1,typename T2> using hashmap=unordered_map<T1,T2,CHASH>;
template<typename TM> using matrix=vector<vector<TM>>;
template<typename TM> using tensor=vector<matrix<TM>>;
template<typename TM> using hypermatrix=vector<tensor<TM>>;
template<typename TM,typename... Args> auto make(size_t first,Args... args){
	if constexpr(sizeof...(args)==0){
		return vector<TM>(first);
	} else {
		return vector<decltype(make<TM>(args...))>(first,make<TM>(args...));
	}
}	
#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define pb push_back
#define MULTITEST false
void solve(){
	int n,m;in(n,m);
	vector<int> dist(n+1,INT_MAX),parent(n+1);
	matrix<int> adj(n+1);
	while(m--){int a,b;in(a,b);adj[a].push_back(b);adj[b].push_back(a);}
	queue<int> q;dist[1]=0;
	q.push(1);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int t:adj[x])
			if(dist[t]==INT_MAX){
				dist[t]=dist[x]+1;
				parent[t]=x;
				q.push(t);
			}
	}
	if(dist[n]==INT_MAX){
		out("IMPOSSIBLE");
		return;
	}
	out(dist[n]+1);
	vector<int> v{n};
	while(v.back()!=1)v.push_back(parent[v.back()]);
	reverse(all(v));
	out(v);
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int t=1;
	if (MULTITEST) cin>>t;
	forn(i,t)solve();
}


