// Problem: G. Grid Reset
// Judge: Codeforces
// URL: https://codeforces.com/gym/668106/problem/G
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
template<class T> istream& operator>>(istream& i, vector<T>& v) { for(auto& x : v) i >> x; return i; }
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
#define MULTITEST true
#define pb push_back

// Optimization pragmas
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

void solve(){
    // Static initialization for Zobrist hashing keys
    static uint64_t zobrist[105][105];
    static bool z_init = false;
    if(!z_init){
        forn(i, 105) forn(j, 105) zobrist[i][j] = PIDRNG();
        z_init = true;
    }

    int n, m, k, q;
    in(n, m, k, q);
    string s;
    in(s);

    const int BEAM_WIDTH = 35;
    const int LOCAL_CANDS_LIMIT = 6;
    const int MAX_DIM = 105;

    using Bits = bitset<MAX_DIM>;

    struct State {
        vector<Bits> rows;
        vector<Bits> cols;
        vector<int> r_cnt;
        vector<int> c_cnt;
        ll score;
        int parent_idx;
        uint64_t hash;
    };

    struct Step {
        int r, c;
        int parent_idx;
    };
    
    // Static buffer for history to minimize allocation overhead
    static vector<Step> history;
    history.clear();
    history.reserve(q * BEAM_WIDTH + 1000);

    State start_node;
    start_node.rows.resize(n);
    start_node.cols.resize(m);
    start_node.r_cnt.assign(n, 0);
    start_node.c_cnt.assign(m, 0);
    start_node.score = 0;
    start_node.parent_idx = -1;
    start_node.hash = 0;

    vector<State> beam;
    beam.reserve(BEAM_WIDTH);
    beam.pb(start_node);

    // Compute row/col XOR sums for fast hash updates on reset
    vector<uint64_t> row_xor(n, 0), col_xor(m, 0);
    forn(i, n) forn(j, m) row_xor[i] ^= zobrist[i][j];
    forn(j, m) forn(i, n) col_xor[j] ^= zobrist[i][j];

    // Precompute validity masks
    // k_masks[i] has 1s at positions [i, i+k-1]
    vector<Bits> k_masks(MAX_DIM);
    Bits base_mask;
    forn(i, k) base_mask[i] = 1;
    forn(i, 102) k_masks[i] = (base_mask << i); 

    static vector<ll> gain_prefix; 
    if(gain_prefix.size() < 105) gain_prefix.resize(105);

    struct Cand {
        ll val;
        int r, c;
        int p_idx;
    };
    static vector<Cand> candidates; 
    static vector<Cand> local_cands;

    forn(op_idx, q){
        char type = s[op_idx];
        
        candidates.clear();
        
        forn(p_i, beam.size()){
            const auto& st = beam[p_i];
            
            // 1. Prefix Sums for O(1) Density Calculation
            // Density Gain = (new_count^2 - old_count^2) = 2*count + 1
            if(type == 'H'){
                gain_prefix[0] = 0;
                forn(j, m) gain_prefix[j+1] = gain_prefix[j] + (2 * st.c_cnt[j] + 1);
            } else {
                gain_prefix[0] = 0;
                forn(i, n) gain_prefix[i+1] = gain_prefix[i] + (2 * st.r_cnt[i] + 1);
            }

            // 2. Identify Critical Lines ("Zombies")
            // A line is critical if it has space < k.
            // Range: [m-k, m-2] (since m-1 -> m is a reset, not a zombie)
            Bits crit_rows, crit_cols;
            int lower_bound_row = m - k, upper_bound_row = m - 2;
            int lower_bound_col = n - k, upper_bound_col = n - 2;
            
            if(type == 'V'){
                forn(i, n) if(st.r_cnt[i] >= lower_bound_row && st.r_cnt[i] <= upper_bound_row) crit_rows[i] = 1;
            } else {
                forn(j, m) if(st.c_cnt[j] >= lower_bound_col && st.c_cnt[j] <= upper_bound_col) crit_cols[j] = 1;
            }

            local_cands.clear();

            if(type == 'H'){
                forn(r, n){
                    // Prune rows that physically cannot hold k segments
                    if(st.r_cnt[r] > m - k) continue; 
                    
                    for(int c = 0; c <= m - k; ++c){
                        if((st.rows[r] & k_masks[c]).none()){
                             ll current_score = st.score;
                             
                             // A. Resets (Priority 1)
                             int resets = 0;
                             if(st.r_cnt[r] + k == m) resets++;
                             for(int x = 0; x < k; ++x) if(st.c_cnt[c+x] + 1 == n) resets++;
                             
                             if(resets > 0){
                                 current_score += (ll)resets * 10000000000LL;
                             } else {
                                 // B. Zombie Penalty (Priority 2)
                                 // If not resetting, penalize creating "unusable" lines
                                 bool zombie = false;
                                 if(st.r_cnt[r] + k > m - k) zombie = true; 
                                 else if((crit_cols & k_masks[c]).any()) zombie = true;
                                 
                                 if(zombie) current_score -= 5000000LL;
                             }

                             // C. Density (Priority 3)
                             ll r_gain = (ll)(st.r_cnt[r] + k) * (st.r_cnt[r] + k) - (ll)st.r_cnt[r] * st.r_cnt[r];
                             current_score += r_gain + (gain_prefix[c+k] - gain_prefix[c]);

                             local_cands.pb({current_score, r, c, p_i});
                        }
                    }
                }
            } else { // V
                 forn(c, m){
                    if(st.c_cnt[c] > n - k) continue;

                    for(int r = 0; r <= n - k; ++r){
                        if((st.cols[c] & k_masks[r]).none()){
                            ll current_score = st.score;

                            int resets = 0;
                            if(st.c_cnt[c] + k == n) resets++;
                            for(int x = 0; x < k; ++x) if(st.r_cnt[r+x] + 1 == m) resets++;

                            if(resets > 0){
                                current_score += (ll)resets * 10000000000LL;
                            } else {
                                bool zombie = false;
                                if(st.c_cnt[c] + k > n - k) zombie = true;
                                else if((crit_rows & k_masks[r]).any()) zombie = true;
                                
                                if(zombie) current_score -= 5000000LL;
                            }

                            ll c_gain = (ll)(st.c_cnt[c] + k) * (st.c_cnt[c] + k) - (ll)st.c_cnt[c] * st.c_cnt[c];
                            current_score += c_gain + (gain_prefix[r+k] - gain_prefix[r]);

                            local_cands.pb({current_score, r, c, p_i});
                        }
                    }
                 }
            }

            // Keep only best local candidates to ensure beam diversity
            if(local_cands.size() > LOCAL_CANDS_LIMIT){
                partial_sort(local_cands.begin(), local_cands.begin() + LOCAL_CANDS_LIMIT, local_cands.end(),
                    [](const Cand& a, const Cand& b){ return a.val > b.val; });
                local_cands.resize(LOCAL_CANDS_LIMIT);
            }
            candidates.insert(candidates.end(), local_cands.begin(), local_cands.end());
        }

        if(candidates.empty()){
            out(-1);
            return;
        }

        // Global Selection of best candidates across all parents
        // Using nth_element is faster than full sort for selection
        if(candidates.size() > BEAM_WIDTH){
             nth_element(candidates.begin(), candidates.begin() + BEAM_WIDTH, candidates.end(), 
                 [](const Cand& a, const Cand& b){ return a.val > b.val; });
             candidates.resize(BEAM_WIDTH);
        }
        sort(all(candidates), [](const Cand& a, const Cand& b){ return a.val > b.val; });

        vector<State> next_beam;
        next_beam.reserve(BEAM_WIDTH);
        
        for(const auto& cand : candidates){
            State next_st = beam[cand.p_idx]; 
            
            // Apply Move & Update Hash
            if(type == 'H'){
                forn(x, k){
                    next_st.rows[cand.r][cand.c + x] = 1;
                    next_st.cols[cand.c + x][cand.r] = 1;
                    next_st.c_cnt[cand.c + x]++;
                    next_st.hash ^= zobrist[cand.r][cand.c + x];
                }
                next_st.r_cnt[cand.r] += k;
            } else {
                forn(x, k){
                    next_st.rows[cand.r + x][cand.c] = 1;
                    next_st.cols[cand.c][cand.r + x] = 1;
                    next_st.r_cnt[cand.r + x]++;
                    next_st.hash ^= zobrist[cand.r + x][cand.c];
                }
                next_st.c_cnt[cand.c] += k;
            }

            // Handle Simultaneous Resets
            static vector<int> full_r, full_c; 
            full_r.clear(); full_c.clear();
            
            forn(i, n) if(next_st.r_cnt[i] == m) full_r.pb(i);
            forn(j, m) if(next_st.c_cnt[j] == n) full_c.pb(j);

            if(!full_r.empty() || !full_c.empty()){
                // Optimized Hash Update:
                // 1. XOR full rows (removes set bits in those rows)
                // 2. XOR full cols (removes set bits in those cols)
                // 3. XOR intersections again (because they were removed twice, effectively putting them back. We need them gone.)
                for(int r : full_r) next_st.hash ^= row_xor[r];
                for(int c : full_c) next_st.hash ^= col_xor[c];
                for(int r : full_r) for(int c : full_c) next_st.hash ^= zobrist[r][c];

                Bits fr_mask, fc_mask;
                for(int r : full_r) { fr_mask[r] = 1; next_st.rows[r].reset(); }
                for(int c : full_c) { fc_mask[c] = 1; next_st.cols[c].reset(); }
                
                // Clear intersections in orthogonal lines
                forn(r, n) if(!fr_mask[r]) next_st.rows[r] &= ~fc_mask;
                forn(c, m) if(!fc_mask[c]) next_st.cols[c] &= ~fr_mask;
                
                // Recompute counts
                forn(r, n) next_st.r_cnt[r] = (int)next_st.rows[r].count();
                forn(c, m) next_st.c_cnt[c] = (int)next_st.cols[c].count();
            }

            // Deduplication Check
            bool dup = false;
            for(const auto& existing : next_beam){
                if(existing.hash == next_st.hash && existing.score == cand.val){ 
                    dup = true; break;
                }
            }
            if(dup) continue;

            history.pb({cand.r + 1, cand.c + 1, beam[cand.p_idx].parent_idx});
            next_st.parent_idx = (int)history.size() - 1;
            next_st.score = cand.val;

            next_beam.pb(move(next_st));
        }
        
        beam = move(next_beam);
    }
    
    if(beam.empty()){
        out(-1); 
        return;
    }

    // Reconstruct Path
    vector<pair<int, int>> ans;
    int curr = beam[0].parent_idx;
    while(curr != -1){
        ans.pb({history[curr].r, history[curr].c});
        curr = history[curr].parent_idx;
    }
    reverse(all(ans));
    for(auto& p : ans) out(p);
}
int main(){
    if(!INTERACTIVE)cin.tie(0)->sync_with_stdio(0);
    #ifndef LOCAL_JUDGE
    #if FILEMODE
    freopen(FILENAME".in","r",stdin);
    freopen(FILENAME".out","w",stdout);
    #endif
    #endif
    int t=1;
    if (MULTITEST) cin>>t;
    forn(i,t)solve();
}
