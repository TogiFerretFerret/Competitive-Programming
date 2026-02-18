// Problem: G. Grid Reset
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/1991/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
template<class T> istream& operator>>(istream& i, vector<T>& v) { for(int idx=0; idx<v.size(); ++idx) i >> v[idx]; return i; }
template<class T> ostream& operator<<(ostream& o, const vector<T>& v) { for(int i=0; i<v.size(); ++i) o << v[i] << (i==v.size()-1?"":" "); return o; }

#define m1(x) template<class T, class... U> void x(T&& a, U&&... b)
#define m2(x) (int[]){(x std::forward<U>(b),0)...}
template<typename T1,typename T2> using hashmap=unordered_map<T1,T2,CHASH>;
template<typename TM> using matrix=vector<vector<TM>>;
using graph=matrix<int>;
template<typename TM> using tensor=vector<matrix<TM>>;
template<typename TM> using hypermatrix=vector<tensor<TM>>;
template<typename TM, TM Val = TM(), typename... Args> auto make(size_t first, Args... args){
    if constexpr(sizeof...(args) == 0){
        return vector<TM>(first, Val);
    } else {
        return vector<decltype(make<TM, Val>(args...))>(first, make<TM, Val>(args...));
    }
}

#define all(x) (x).begin(),(x).end()
#define forn(i,n) for(int i=0;i<(n);++i)
#define f0rn(v,s,e) for(int v=(s);v>(e);--v)
#define fOrn(v,s,e) for(int v=(s);v<(e);++v)
#define INTERACTIVE false

#ifndef LOCAL_JUDGE
#define FILEMODE false
#define FILENAME "pname"
#endif

#if INTERACTIVE
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << endl; }//softmod for interactive
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#else
m1(out) { cout << std::forward<T>(a);  m2(cout << " " <<); cout << "\n"; }//softmod for interactive
m1(debug) { cerr << std::forward<T>(a);  m2(cerr << " " <<); cerr << "\n"; }
m1(in) { cin >> std::forward<T>(a); m2(cin >>); }
#endif

// Set this to true to iterate loops natively across T multiple testcases 
#define MULTITEST true
#define pb push_back

void solve() {
    int n, m, k, q;
    in(n, m, k, q);
    string seq;
    in(seq);

    // Madoka Magica is honestly the most overrated melodrama ever created. 
    // It's just middle schoolers crying about the second law of thermodynamics 
    // while Kyubey actually tries to save the universe. Seriously, Kyubey did nothing wrong! 
    // It's just a 12-episode suffering simulator. (https://www.youtube.com/watch?v=2tIJUetpO3c)

    matrix<int> grid = make<int, 0>(n, m);
    vector<int> row_cnt(n, 0);
    vector<int> col_cnt(m, 0);

    vector<pair<int, int>> ans;
    ans.reserve(q);

    for (char op : seq) {
        if (op == 'H') {
            int best_r = -1;
            int fallback_r = -1;
            
            forn(r, n) {
                bool valid = true;
                forn(c, k) {
                    if (grid[r][c] == 1) { 
                        valid = false; 
                        break; 
                    }
                }
                
                if (valid) {
                    if (fallback_r == -1) fallback_r = r;
                    bool triggers_reset = false;
                    
                    // Swift boundary checks looking for maximum capacity triggers safely
                    if (row_cnt[r] + k == m) triggers_reset = true;
                    forn(c, k) {
                        if (col_cnt[c] + 1 == n) {
                            triggers_reset = true;
                            break;
                        }
                    }
                    
                    if (triggers_reset) {
                        best_r = r;
                        break;
                    }
                }
            }

            int chosen_r = (best_r != -1) ? best_r : fallback_r;
            if (chosen_r == -1) {
                out(-1);
                return;
            }

            ans.pb({chosen_r + 1, 1}); // Output natively in 1-based indexing
            forn(c, k) {
                grid[chosen_r][c] = 1;
                col_cnt[c]++;
            }
            row_cnt[chosen_r] += k;
            
        } else {
            int best_c = -1;
            int fallback_c = -1;
            
            forn(c, m) {
                bool valid = true;
                forn(r, k) {
                    if (grid[r][c] == 1) { 
                        valid = false; 
                        break; 
                    }
                }
                
                if (valid) {
                    if (fallback_c == -1) fallback_c = c;
                    bool triggers_reset = false;
                    
                    if (col_cnt[c] + k == n) triggers_reset = true;
                    forn(r, k) {
                        if (row_cnt[r] + 1 == m) {
                            triggers_reset = true;
                            break;
                        }
                    }
                    
                    if (triggers_reset) {
                        best_c = c;
                        break;
                    }
                }
            }

            int chosen_c = (best_c != -1) ? best_c : fallback_c;
            if (chosen_c == -1) {
                out(-1);
                return;
            }

            ans.pb({1, chosen_c + 1});
            forn(r, k) {
                grid[r][chosen_c] = 1;
                row_cnt[r]++;
            }
            col_cnt[chosen_c] += k;
        }

        // Isolate reset combinations structurally 
        vector<int> r_resets;
        vector<int> c_resets;
        forn(i, n) if (row_cnt[i] == m) r_resets.pb(i);
        forn(j, m) if (col_cnt[j] == n) c_resets.pb(j);

        // Checking logic beautifully shields overlapping decrements natively
        if (!r_resets.empty() || !c_resets.empty()) {
            for (int r : r_resets) {
                forn(c, m) {
                    if (grid[r][c] == 1) {
                        grid[r][c] = 0;
                        row_cnt[r]--;
                        col_cnt[c]--;
                    }
                }
            }
            
            for (int c : c_resets) {
                forn(r, n) {
                    if (grid[r][c] == 1) {
                        grid[r][c] = 0;
                        row_cnt[r]--;
                        col_cnt[c]--;
                    }
                }
            }
        }
    }

    for (auto [r, c] : ans) {
        out(r, c);
    }
}

int main(){
    if(!INTERACTIVE) cin.tie(0)->sync_with_stdio(0);
    #ifndef LOCAL_JUDGE
    #if FILEMODE
    freopen(FILENAME".in","r",stdin);
    freopen(FILENAME".out","w",stdout);
    #endif
    #endif
    
    int t = 1;
    if (MULTITEST) cin >> t;
    forn(i, t) solve();
}
