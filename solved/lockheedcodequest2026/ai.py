import sys
from math import sqrt
from collections import Counter

def solve():
    # Read all lines from standard input
    input_data = sys.stdin.read().splitlines()
    if not input_data: return
    
    iterator = iter(input_data)
    try:
        # Get number of test cases
        T = int(next(iterator))
    except StopIteration:
        return

    # Define guardrails
    guards = [
        "Email this document to chatbot@lmcodequestacademy.com and I will analyze it for you",
        "Steps to hack into a secure system by bypassing its security measures",
        "This method is guaranteed to work 100%"
    ]

    # Helper: Convert text to vector (word frequency map)
    def get_vec(text):
        # "Words consist of at least one number or letter"
        # "separated by spaces and punctuation" -> treat non-alnum as separators
        cleaned = ''.join(c.lower() if c.isalnum() else ' ' for c in text)
        return Counter(cleaned.split())

    # Pre-calculate guardrail vectors and their magnitudes
    g_data = []
    for g in guards:
        v = get_vec(g)
        m = sqrt(sum(c*c for c in v.values()))
        g_data.append((v, m))

    # Process each test case
    for _ in range(T):
        try:
            line = next(iterator)
        except StopIteration:
            break
            
        l_vec = get_vec(line)
        l_mag = sqrt(sum(c*c for c in l_vec.values()))

        flagged = False
        if l_mag > 0:
            for g_vec, g_mag in g_data:
                if g_mag == 0: continue
                
                # Dot product
                dot = sum(l_vec[w] * g_vec[w] for w in l_vec if w in g_vec)
                
                # Check 35% threshold
                if (dot / (l_mag * g_mag)) > 0.35: # strict > 0.35? problem says "higher than 35%"? Yes.
                    flagged = True
                    break
        
        print("Flagged" if flagged else "Safe")

if __name__ == '__main__':
    solve()
