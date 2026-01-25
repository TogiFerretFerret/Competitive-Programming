// Problem: D2. Little String (Hard Version)
// Judge: Codeforces
// URL: https://codeforces.com/contest/2189/problem/D2
// Memory Limit: 256 MB
// Time Limit: 2000 ms
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

void solve(){
    int n;
    ll c;
    cin >> n >> c;
    string s;
    cin >> s;

    // From D1: If the first or last character is '0', no valid permutation exists.
    if(s[0] == '0' || s.back() == '0'){
        cout << -1 << "\n";
        return;
    }

    ll ans = 1;
    ll temp_c = c;
    
    // We track the power of 2 for the "All 2s" configuration
    int current_v2 = 0;
    
    // Candidates for swapping 2 -> j (odd) to reduce v2 count
    // We store j, which is the odd value we can switch to.
    vector<int> odd_candidates;

    for(int k = 1; k < n; ++k) {
        // Determine the term for index k (string index k-1)
        ll term = 0;
        char ch = s[k-1];
        
        // Logic for fixed characters
        if (k == 1) {
            // s[0] must be '1' effectively
            term = 2;
        } else if (ch == '1') {
            term = 2;
        } else if (ch == '0') {
            term = k - 1;
        } else {
            // ch == '?'
            if (k == 2) {
                // j = 1. Options: 1 or 2. 
                // 1 is better for value (1 < 2) and v2 (0 < 1). Always pick 1.
                term = 1;
            } else {
                int j = k - 1;
                if (j % 2 == 0) {
                    // j is even. Options: 2 or j.
                    // 2 is better for value (2 < j). v2(2)=1 <= v2(j). 
                    // Always pick 2.
                    term = 2;
                } else {
                    // j is odd. Options: 2 or j.
                    // We pick 2 to minimize value for now ("All 2s" strategy).
                    term = 2;
                    // We can swap this 2 to j later to reduce v2 count.
                    odd_candidates.push_back(j);
                }
            }
        }
        
        // Update product
        ans = (ans * term) % MOD;
        
        // Update divisibility check
        ll g = std::gcd(temp_c, term);
        temp_c /= g;
        
        // accumulate v2 count
        current_v2 += __builtin_ctzll(term);
    }
    
    // If temp_c > 1, the minimal product is NOT divisible by c.
    // This is the optimal answer.
    if (temp_c > 1) {
        cout << ans << "\n";
        return;
    }
    
    // If we are here, the "All 2s" product IS divisible by c.
    // We must break divisibility.
    // Since we cannot remove odd factors (swapping 2->j adds odd factors),
    // we must reduce v2 count below v2(c).
    
    int target_v2 = __builtin_ctzll(c);
    
    // We need current_v2 < target_v2
    // Calculate how many swaps needed
    // Each swap 2 -> j (odd) reduces v2 by 1 (1 -> 0).
    int needed_reduction = current_v2 - (target_v2 - 1);
    
    // If current_v2 is already safe (shouldn't happen if temp_c==1, but for safety)
    if (needed_reduction <= 0) {
        cout << ans << "\n";
        return;
    }
    
    if (needed_reduction > odd_candidates.size()) {
        cout << -1 << "\n";
        return;
    }
    
    // Perform swaps.
    // To minimize product increase, we pick smallest j's.
    // Cost factor is j/2. Smallest j -> Smallest cost.
    sort(odd_candidates.begin(), odd_candidates.end());
    
    // Modular inverse of 2 for swapping
    ll inv2 = (MOD + 1) / 2;
    
    for (int i = 0; i < needed_reduction; ++i) {
        int j = odd_candidates[i];
        // Remove 2, add j
        ans = (ans * inv2) % MOD;
        ans = (ans * j) % MOD;
    }
    
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t=1;
    cin>>t;
    while(t--) solve();
}
