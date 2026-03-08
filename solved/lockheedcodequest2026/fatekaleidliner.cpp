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
    typedef __int128_t int128;
    function<int128(ll, ll)> power = [&](ll base, ll exp) -> int128 {
        int128 res = 1;
        forn(i, exp) res *= base;
        return res;
    };
    struct UnitDef {
        int128 multiplier;
        string name;
    };
    vector<UnitDef> UNITS = {
        {power(10, 18), "GHz"},
        {power(10, 15), "MHz"},
        {power(10, 12), "kHz"},
        {power(10, 9),  "Hz"},
        {power(10, 6),  "mHz"},
        {power(10, 3),  "uHz"},
        {1,             "nHz"}
    };
    struct Operand {
        int128 value;
        bool isScalar;
    };
    function<string(int128)> int128ToString = [&](int128 n) -> string {
        if (n == 0) return "0";
        string prefix = "";
        if (n < 0) {
            prefix = "-";
            n = -n;
        }
        string s = "";
        while (n > 0) {
            s += (char)('0' + (int)(n % 10));
            n /= 10;
        }
        reverse(all(s));
        return prefix + s;
    };
    function<int128(string)> stringToInt128 = [&](string s) -> int128 {
        int128 res = 0;
        forn(i, s.length()) {
            char c = s[i];
            if (isdigit(c)) res = res * 10 + (c - '0');
        }
        return res;
    };
    function<Operand(string)> parseOperand = [&](string s) -> Operand {
        size_t first = s.find_first_not_of(' ');
        size_t last = s.find_last_not_of(' ');
        if (first == string::npos) return {0, true};
        s = s.substr(first, (last - first + 1));
        size_t spacePos = s.find_last_of(' ');
        if (spacePos == string::npos) {
            return {stringToInt128(s), true};
        } else {
            string numPart = s.substr(0, spacePos);
            string unitPart = s.substr(spacePos + 1);
            int128 val = stringToInt128(numPart);
            int128 multiplier = 1;
            forn(i, UNITS.size()) {
                if (UNITS[i].name == unitPart) {
                    multiplier = UNITS[i].multiplier;
                    break;
                }
            }
            return {val * multiplier, false};
        }
    };
    function<void(int128)> printResult = [&](int128 val) -> void {
        int128 absVal = (val < 0) ? -val : val;
        forn(i, UNITS.size()) {
            if (absVal % UNITS[i].multiplier == 0) {
                cout<<int128ToString(val / UNITS[i].multiplier)<<" "<<UNITS[i].name<<"\n";
                return;
            }
        }
        cout<<int128ToString(val)<<" nHz\n";
    };
    string line;
    getline(cin, line);
    if (line.empty()) getline(cin, line);
    vector<string> parts;
    stringstream ss(line);
    string seg;
    while(getline(ss, seg, ',')) {
        parts.pb(seg);
    }
    if (parts.size() != 3) return;
    Operand op1 = parseOperand(parts[0]);
    Operand op2 = parseOperand(parts[2]);
    string operStr = parts[1];
    operStr.erase(remove(all(operStr), ' '), operStr.end());
    char op = operStr[0];
    int128 resultVal = 0;
    if (op == '+') {
        if (op1.isScalar || op2.isScalar) {
            cout<<"INVALID\n";
            return;
        }
        resultVal = op1.value + op2.value;
    } else if (op == '-') {
        if (op1.isScalar || op2.isScalar) {
            cout<<"INVALID\n";
            return;
        }
        resultVal = op1.value - op2.value;
    } else if (op == '*') {
        if (op1.isScalar && op2.isScalar) {
            cout<<"INVALID\n";
            return;
        }
        if (!op1.isScalar && !op2.isScalar) {
            cout<<"INVALID\n";
            return;
        }
        resultVal = op1.value * op2.value;
    }
    printResult(resultVal);
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    if (MULTITEST) cin>>t;
    forn(i, t) solve();
}
