// Problem: J. Convex Hull Sort
#include <bits/stdc++.h>
using namespace std;

// Geometry and Logic Structures
struct Point {
    int id;           // Original 1-based index (Target)
    long long x, y;
    int current_label;
    bool removed;
};

// Global Tracking
vector<Point> points;
vector<int> label_pos; // Map: label_val -> index in points vector
set<pair<int,int>> used_edges;

// Geometry Utils
long long cross_product(int o, int a, int b) {
    return (points[a].x - points[o].x) * (points[b].y - points[o].y) - 
           (points[a].y - points[o].y) * (points[b].x - points[o].x);
}

// Check segment usage
bool is_used(int u, int v) {
    if (u > v) swap(u, v);
    return used_edges.count({u, v});
}

void mark_used(int u, int v) {
    if (u > v) swap(u, v);
    used_edges.insert({u, v});
}

// Disjoint Set Union
struct DSU {
    vector<int> p;
    DSU(int n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }
    int find(int i) {
        if (p[i] == i) return i;
        return p[i] = find(p[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) p[root_i] = root_j;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    points.resize(n);
    label_pos.resize(n + 1);
    vector<int> active_indices;

    for (int i = 0; i < n; ++i) {
        points[i].removed = false;
        points[i].id = i + 1; // 1-based Target
        cin >> points[i].x >> points[i].y >> points[i].current_label;
        label_pos[points[i].current_label] = i; 
        active_indices.push_back(i);
    }

    vector<pair<int,int>> output_ops;

    // Iteratively resolve points
    while (!active_indices.empty()) {
        // 1. Identify Pivot O (Bottom-Leftmost)
        int best_idx = -1;
        for (int i : active_indices) {
            if (best_idx == -1) best_idx = i;
            else {
                if (points[i].x < points[best_idx].x || 
                   (points[i].x == points[best_idx].x && points[i].y < points[best_idx].y)) {
                    best_idx = i;
                }
            }
        }
        int o_idx = best_idx;

        // If correct, remove and continue
        if (points[o_idx].current_label == points[o_idx].id) {
            points[o_idx].removed = true;
            // Clean active list
            vector<int> next_active;
            for(int i : active_indices) if(!points[i].removed) next_active.push_back(i);
            active_indices = next_active;
            continue;
        }

        // 2. Prepare Others
        vector<int> others;
        for(int i : active_indices) {
            if(i != o_idx) others.push_back(i);
        }

        // Sort by angle around O
        // Since O is min-X (and min-Y), vectors point to right/up. Standard CP sort works.
        sort(others.begin(), others.end(), [&](int a, int b){
            long long cp = cross_product(o_idx, a, b);
            if (cp != 0) return cp > 0;
            // Closer points first? Or simple ID logic
            long long da = (points[a].x - points[o_idx].x)*(points[a].x - points[o_idx].x) + (points[a].y - points[o_idx].y)*(points[a].y - points[o_idx].y);
            long long db = (points[b].x - points[o_idx].x)*(points[b].x - points[o_idx].x) + (points[b].y - points[o_idx].y)*(points[b].y - points[o_idx].y);
            return da < db;
        });

        // 3. Build Permutation Cycle DSU
        // Re-index 'active' into 0..K for DSU
        // Mapping: point_index -> DSU_id
        // Wait, just use global point index for DSU (size N)
        DSU dsu(n);
        // Connect each active point to the location of its target
        // Arrow: point i holds val X. X should be at target(X) (aka location where val==points[i].id).
        // Standard permutation DSU: edge from i to j if points[i].label should go to j
        // i -> label_pos[ points[i].current_label? NO. 
        // Cycles are defined: Node `i` holds value `V`. This value `V` is the rightful owner of node `k` such that `points[k].id == V`.
        // So edge i -> label_pos[points[i].id] ? NO. 
        // Edge i -> k where points[k].id == points[i].current_label? 
        // Actually: We are permuting contents. The cycles exist in the mapping "Position -> Position".
        // Current content at `i` is `L`. `L` belongs to `Dest`. Next content comes from `Source` which has `id == L`.
        // Edge i -> Dest (where points[Dest].id == points[i].current_label).
        // Correct. Union i with label_pos_target.
        
        // Actually simplest: current label at i points to index 'label_pos[ points[i].id ]'?? No.
        // Node P has label V. Target for label V is the node Q where points[Q].id == V.
        // Link P and Q.
        
        // Let's create DSU on active nodes.
        // Target map: Value V -> Index where points[Index].id == V.
        // We can precompute inverse map `id_to_index`.
        vector<int> id_to_index(n + 1);
        for(int idx : active_indices) id_to_index[points[idx].id] = idx;

        for (int i : active_indices) {
            int val_held = points[i].current_label;
            // Check if valid value (might be removing nodes, values range 1..N)
            // But loop conditions ensure O is processed until O is correct. 
            // O is only removed when O holds O.
            // Values not belonging to active nodes? Should not happen if closed set.
            // Wait, previously removed nodes hold their correct values.
            // If active node i holds Value V belonging to Removed Node K:
            // This implies Node K was removed but V wasn't at K? 
            // Impossible logic if "Remove O iff O correct".
            // Thus, active set holds active values. Permutation is closed.
            if(val_held > 0 && val_held <= n) {
                // Find node owning val_held
                int owner_idx = id_to_index[val_held]; 
                // Since closure, owner must be active? Yes.
                dsu.unite(i, owner_idx);
            }
        }

        // 4. Merge Components using Border Edges
        for (size_t k = 0; k + 1 < others.size(); ++k) {
            int u = others[k];
            int v = others[k+1];
            if (dsu.find(u) != dsu.find(v)) {
                // Check if segment distinct
                if (!is_used(points[u].id, points[v].id)) {
                    // Perform Op
                    mark_used(points[u].id, points[v].id);
                    output_ops.push_back({points[u].id, points[v].id});
                    
                    int lu = points[u].current_label;
                    int lv = points[v].current_label;
                    swap(points[u].current_label, points[v].current_label);
                    label_pos[lu] = v;
                    label_pos[lv] = u;
                    
                    dsu.unite(u, v);
                }
            }
        }

        // 5. Solve O using Central Edges
        // All connected mislabeled nodes are now in one component (linked to O eventually?).
        // If disjoint components remained (due to Used Edges skips), loop repeats? 
        // No, 'while T!=O' loop fixes O's component. If stuff remains, it will be handled next iteration.
        // Loop: Bring label ID(O) to O.
        int needed = points[o_idx].id;
        int holder = label_pos[needed];

        while (holder != o_idx) {
            // Check safety? Fan logic + planarity ensures safety for star.
            // Reuse? Star edges used exactly once per clearance.
            if (is_used(points[o_idx].id, points[holder].id)) {
                // Should not happen in standard fan if merges didn't abuse center.
                // Merges used 'others', not 'O'. Star uses 'O'. Distinct.
                break;
            }
            
            mark_used(points[o_idx].id, points[holder].id);
            output_ops.push_back({points[o_idx].id, points[holder].id});

            int lo = points[o_idx].current_label; // garbage at O
            int lh = points[holder].current_label; // correct label for O
            swap(points[o_idx].current_label, points[holder].current_label);
            label_pos[lo] = holder;
            label_pos[lh] = o_idx;

            // Now O holds correct label.
            // The logic: Swap(O, Holder) puts CorrectLabel at O. 
            // BUT: O then effectively exits (conceptually correct). 
            // BUT BUT: 'holder' received O's old label.
            // Problem: If we simply 'fix' O, we break the cycle there.
            // Cycle solving usually: Swap (O, next in cycle). O is the pivot passing vals.
            // Observation 1 says "Repeatedly swap between i (Pivot) and a_i".
            // Here 'a_i' means "Location that Target(Value at O) belongs to".
            // Let L_at_O be Val. Owner(Val) is TargetNode.
            // Swap (O, TargetNode). Now TargetNode has Val (Correct).
            // O has new Val. Repeat.
            // Correct termination: O finally receives ID(O) from the node pointing to it.
            // This means we trace $O \to Target(L_0) \to Target(L_1) \dots \to O$.
            // Loop Condition must follow the labels OUT of O.
            
            // Re-calc after swap? No, O is now Correct if we swapped holder? 
            // My previous manual trace was: "Holder has Needed. Swap. O Correct. Loop End."
            // But we want to process the *entire component*.
            // To process component, we follow label AT O.
            // Only stop if Label at O is O.
            
            // Correction: Revert explicit "Fetch Needed" logic. Use "Dispatch Current".
            // This solves the whole cycle. O eventually gets satisfied last.
            // Fetch logic satisfies O immediately but leaves others. 
            // Dispatch logic satisfies others and leaves O for last.
            
            int val_at_o = points[o_idx].current_label;
            if(val_at_o == points[o_idx].id) break; // O satisfied, Done.

            int target_node = id_to_index[val_at_o];
            holder = target_node; // Use this variable to continue the structure
            
            // Logic is: swap(O, holder).
            // 'holder' gets 'val_at_o' which is 'points[holder].id'. 
            // So 'holder' becomes correct.
            // O gets whatever holder had.
            // Repeat.
        }

        // Remove O (it's correct or isolated correct)
        points[o_idx].removed = true;
        
        vector<int> next_active;
        for(int i : active_indices) if(!points[i].removed) next_active.push_back(i);
        active_indices = next_active;
    }

    cout << output_ops.size() << "\n";
    for(auto& p : output_ops) cout << p.first << " " << p.second << "\n";

    return 0;
}
