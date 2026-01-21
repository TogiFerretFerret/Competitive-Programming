/**
 * Problem: A. Binary Literature
 * Solution approach:
 * 1.  We are given three binary strings of length 2n.
 * 2.  A valid answer is a string of length at most 3n containing at least two of the input strings as subsequences.
 * 3.  According to the Pigeonhole Principle, among the three strings, at least two must have the same "majority" character.
 *     - If count('0') >= n, '0' is the majority.
 *     - If count('1') >= n, '1' is the majority.
 *     - With only two possible majority types ('0' or '1') and three strings, at least two collide.
 * 4.  Let the two chosen strings be S1 and S2, and their common majority character be 'C'.
 *     Both S1 and S2 contain at least n occurrences of 'C'.
 * 5.  We can construct a common supersequence by greedily traversing S1 and S2.
 *     - If the current character of S1 is NOT 'C', add it to result.
 *     - Else if the current character of S2 is NOT 'C', add it to result.
 *     - If both are 'C', add 'C' and advance both pointers.
 *     - If one string finishes, append the remainder of the other.
 * 6.  Proof of validity:
 *     - This algorithm constructs a valid supersequence for S1 and S2.
 *     - Every time we match 'C' in both strings, we "save" 1 character of length compared to simple concatenation.
 *     - Since both have >= n occurrences of 'C', we will have at least n matches.
 *     - Maximum length = length(S1) + length(S2) - matches = 2n + 2n - matches <= 4n - n = 3n.
 *     - This fits the constraints.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    // Read the three strings
    string s[3];
    int majType[3]; // 0 represents majority '0', 1 represents majority '1'
    
    for (int i = 0; i < 3; ++i) {
        cin >> s[i];
        int count0 = 0;
        for (char c : s[i]) {
            if (c == '0') count0++;
        }
        // If '0' appears n or more times, majority is '0'
        if (count0 >= n) majType[i] = 0;
        // Otherwise, '1' must appear n or more times (since total len is 2n)
        else majType[i] = 1;
    }
    
    int id1 = -1, id2 = -1;
    char val = ' ';
    
    // Find any two strings with the same majority type (Pigeonhole principle guarantees existence)
    if (majType[0] == majType[1]) {
        id1 = 0; id2 = 1;
    } else if (majType[0] == majType[2]) {
        id1 = 0; id2 = 2;
    } else {
        id1 = 1; id2 = 2;
    }
    
    // Set the matching character
    val = (majType[id1] == 0 ? '0' : '1');
    
    const string& S1 = s[id1];
    const string& S2 = s[id2];
    
    string ans;
    // We expect length roughly around 3n
    ans.reserve(3 * n);
    
    int p1 = 0, p2 = 0;
    while (p1 < 2 * n && p2 < 2 * n) {
        // Greedy strategy:
        // Prioritize characters that differ from the common majority value 'val'.
        // If we see a character != val, it means it's the "minority" chunks 
        // between the 'val' markers. We output them to preserve subsequence order.
        
        if (S1[p1] != val) {
            ans.push_back(S1[p1++]);
        } else if (S2[p2] != val) {
            ans.push_back(S2[p2++]);
        } else {
            // Both pointers are at the common majority character 'val'.
            // We consume 'val' from both strings simultaneously (merge).
            ans.push_back(val);
            p1++;
            p2++;
        }
    }
    
    // Append any remaining suffixes
    while (p1 < 2 * n) ans.push_back(S1[p1++]);
    while (p2 < 2 * n) ans.push_back(S2[p2++]);
    
    cout << ans << "\n";
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
