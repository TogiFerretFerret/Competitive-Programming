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
    struct State {
        string id;
        ll pop;
        int seats;
        int index;
    };
    struct Candidate {
        int state_idx;
        long double priority;
        bool operator<(const Candidate& other) const {
            return priority < other.priority;
        }
    };
    function<long double(ll, int)> getPriority = [&](ll population, int n) -> long double {
        return (long double)population / sqrt((long double)n * (n - 1));
    };
    int num_states = 50;
    int total_target_seats = 435;
    vector<State> states(num_states);
    forn(i, num_states) {
        cin>>states[i].id>>states[i].pop;
        states[i].seats = 1;
        states[i].index = i;
    }
    int seats_remaining = total_target_seats - num_states;
    priority_queue<Candidate> pq;
    forn(i, num_states) {
        long double p = getPriority(states[i].pop, 2);
        pq.push({i, p});
    }
    while (seats_remaining > 0) {
        Candidate top = pq.top();
        pq.pop();
        int idx = top.state_idx;
        states[idx].seats++;
        seats_remaining--;
        int next_seat = states[idx].seats + 1;
        long double new_p = getPriority(states[idx].pop, next_seat);
        pq.push({idx, new_p});
    }
    sort(all(states), [&](const State& a, const State& b) -> bool {
        return a.id < b.id;
    });
    forn(i, num_states) {
        cout<<states[i].id<<" "<<states[i].seats<<"\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
