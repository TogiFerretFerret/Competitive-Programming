#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

void solve() {
    int n;
    ll k;
    if (!(cin >> n >> k)) return;

    // Check if a k-th permutation exists. 
    // Total count is 2^(n-1). 
    // Only need to check if n is small enough that overflow matters.
    if (n < 62) {
        if (k > (1LL << (n - 1))) {
            cout << "-1\n";
            return;
        }
    }

    // Determine R: the size of the suffix where decisions matter.
    // For the prefix n - R, we will always choose block size 1 (i.e., just print sequentially)
    // because the count of permutations for any L=1 choice (2^(big)) is > k.
    // Minimal R such that 2^(R-1) >= k is sufficient.
    int R = 1;
    for (; R <= 61 && R <= n; ++R) {
        if ((1LL << (R - 1)) >= k) {
            break;
        }
    }
    // Just in case loop finishes without break (unlikely with k <= 10^18 but safe for boundary)
    // Or if loop broke, R is set correctly. 
    // Boundary constraint: R can't exceed n.
    if (R > n) R = n;

    // Print the deterministic prefix
    // For indices corresponding to these positions, we always pick L=1 block
    ll current_val = 1;
    for (int i = 0; i < n - R; ++i) {
        cout << current_val << " ";
        current_val++;
    }

    // Solve for the suffix of size m = R
    int m = R;
    while (m > 0) {
        // Try block sizes len = 1 to m
        for (int len = 1; len <= m; ++len) {
            int rem = m - len; // remaining size after this block
            ll count = 1;      // Default count for rem=0
            
            if (rem > 0) {
                // If rem is large enough, count exceeds k easily.
                // 60 is safe ceiling since k <= 10^18 < 2^60
                if (rem >= 60) {
                    count = k + 1; // Saturated, guaranteed to be > k
                } else {
                    count = (1LL << (rem - 1));
                }
            }

            // If k is within the range of this block size choice
            if (k <= count) {
                // Output the block: decreases from (current + len - 1) down to current
                for (int i = 0; i < len; ++i) {
                    cout << (current_val + len - 1 - i) << " ";
                }
                current_val += len;
                m -= len;
                // Break out of inner 'for' loop to process the next block in 'while' loop
                break; 
            } else {
                // Skip this block size choice and look for larger initial blocks
                k -= count;
            }
        }
    }
    cout << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
