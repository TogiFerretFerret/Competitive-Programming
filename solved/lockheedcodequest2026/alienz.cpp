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
    struct Rule {
        regex re;
        string msg;
        bool valid;
    };
    int d, s;
    cin>>d>>s;
    string dum;
    getline(cin, dum);
    function<string(const string&, int&)> parseItem;
    function<string(const string&, int&)> parseSequence;
    function<string(const string&, int&)> parseElement;
    parseSequence = [&](const string& str, int& idx) -> string {
        string seq = "";
        while (idx < (int)str.length()) {
            char c = str[idx];
            if (c == ')' || c == ']' || isspace(c)) break;
            seq += parseItem(str, idx);
        }
        return seq;
    };
    parseElement = [&](const string& str, int& idx) -> string {
        if (idx >= (int)str.length()) return "";
        string token = "";
        if (isdigit(str[idx])) {
            token += str[idx];
            idx++;
        } else if (str[idx] == '(') {
            idx++;
            token += "(?:";
            token += parseSequence(str, idx);
            if (idx < (int)str.length() && str[idx] == ')') idx++;
            token += ")";
        } else if (str[idx] == '[') {
            idx++;
            token += "(?:";
            bool first = true;
            while (idx < (int)str.length() && str[idx] != ']') {
                if (!first) token += "|";
                token += parseItem(str, idx);
                first = false;
            }
            if (idx < (int)str.length() && str[idx] == ']') idx++;
            token += ")";
        }
        return token;
    };
    parseItem = [&](const string& str, int& idx) -> string {
        string elem = parseElement(str, idx);
        if (idx < (int)str.length()) {
            if (str[idx] == '/') { idx++; elem += "?"; }
            else if (str[idx] == '.') { idx++; elem += "*"; }
            else if (str[idx] == '-') { idx++; elem += "+"; }
        }
        return elem;
    };
    function<string(const string&)> extractPattern = [&](const string& line) -> string {
        size_t q = line.find('"');
        if (q == string::npos) return line;
        size_t end = q - 1;
        while (end > 0 && isspace(line[end])) end--;
        return line.substr(0, end + 1);
    };
    function<string(const string&)> extractMsg = [&](const string& line) -> string {
        size_t start = line.find('"');
        size_t end = line.rfind('"');
        if (start == string::npos || end == string::npos || end <= start) return "";
        return line.substr(start + 1, end - start - 1);
    };
    vector<Rule> rules;
    forn(i, d) {
        string line;
        if (!getline(cin, line)) break;
        if (line.empty()) { i--; continue; }
        string patStr = extractPattern(line);
        string msgStr = extractMsg(line);
        int pos = 0;
        string regStr = parseSequence(patStr, pos);
        try {
            rules.pb({regex(regStr), msgStr, true});
        } catch (...) {
            rules.pb({regex(""), "", false});
        }
    }
    string stream = "";
    forn(i, s) {
        string line;
        getline(cin, line);
        stream += line;
    }
    int curr_pos = 0;
    ll msg_start = -1;
    ll last_match_end = -100;
    string current_buffer = "";
    bool any_msg = false;
    string::const_iterator bg = stream.begin();
    string::const_iterator ed = stream.end();
    while (curr_pos < (int)stream.length()) {
        int bestLen = 0;
        int bestIdx = -1;
        forn(k, rules.size()) {
            if(!rules[k].valid) continue;
            smatch m;
            if (regex_search(bg + curr_pos, ed, m, rules[k].re, regex_constants::match_continuous)) {
                if ((int)m.length() > bestLen) {
                    bestLen = m.length();
                    bestIdx = k;
                }
            }
        }
        if (bestLen > 0) {
            any_msg = true;
            ll gap = (ll)curr_pos - last_match_end;
            if (msg_start != -1) {
                if (gap >= 8) {
                    cout<<"MESSAGE AT "<<msg_start<<" "<<current_buffer<<"\n";
                    msg_start = curr_pos;
                    current_buffer = "";
                }
            } else {
                msg_start = curr_pos;
            }
            current_buffer += rules[bestIdx].msg;
            last_match_end = curr_pos + bestLen;
            curr_pos += bestLen;
        } else {
            curr_pos++;
            if (msg_start != -1) {
                ll gap = (ll)curr_pos - last_match_end;
                if (gap == 8) {
                    cout<<"MESSAGE AT "<<msg_start<<" "<<current_buffer<<"\n";
                    msg_start = -1;
                    current_buffer = "";
                }
            }
        }
    }
    if (msg_start != -1) {
        cout<<"MESSAGE AT "<<msg_start<<" "<<current_buffer<<"\n";
    }
    if (!any_msg) {
        cout<<"NO MESSAGES\n";
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
