#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<string> st;                        // States
vector<string> finalSt;                   // Final States
string startSt;                           // Start State
vector<tuple<string, string, string>> transition; // NFA Transitions
vector<string> symbols;                   // Input Symbols
vector<tuple<string, string, string>> dfa;        // DFA Transitions

// Split a comma-separated string into a vector
vector<string> split(const string &str) {
    vector<string> result;
    stringstream ss(str);
    string temp;
    while (getline(ss, temp, ',')) {
        result.push_back(temp);
    }
    return result;
}

// Remove duplicates from a comma-separated string
string normalizeStateSet(const string &stateStr) {
    vector<string> states = split(stateStr);
    set<string> uniqueStates(states.begin(), states.end());
    vector<string> sortedStates(uniqueStates.begin(), uniqueStates.end());
    string result = "";
    for (size_t i = 0; i < sortedStates.size(); i++) {
        result += sortedStates[i];
        if (i != sortedStates.size() - 1)
            result += ",";
    }
    return result;
}

// Insert transitions from user input
void insertTransition() {
    cout << "\nInsert the Transition Table:\n";
    for (const string &s : st) {
        cout << "For state '" << s << "':\n";
        for (const string &sym : symbols) {
            cout << "  On symbol '" << sym << "' goes to (separate multiple states with space, end with '.'): ";
            string nextState, a;
            cin >> nextState;
            while (cin >> a && a != ".") {
                nextState += "," + a;
            }
            transition.push_back({s, sym, normalizeStateSet(nextState)});
        }
    }
}

// Get transition states from NFA for given from-state and symbol
string getNextStateFromNFA(const string &from, const string &symbol) {
    for (auto &t : transition) {
        if (get<0>(t) == from && get<1>(t) == symbol) {
            return get<2>(t);
        }
    }
    return "";
}

// Convert NFA to DFA
void todfa() {
    queue<string> q;
    set<string> visited;
    q.push(startSt);
    visited.insert(startSt);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (const string &sym : symbols) {
            set<string> resultSet;
            vector<string> subStates = split(current);

            for (const string &sub : subStates) {
                string result = getNextStateFromNFA(sub, sym);
                if (!result.empty()) {
                    vector<string> resSplit = split(result);
                    resultSet.insert(resSplit.begin(), resSplit.end());
                }
            }

            if (!resultSet.empty()) {
                string nextCombined = "";
                for (const string &s : resultSet) {
                    nextCombined += s + ",";
                }
                nextCombined.pop_back(); // Remove last comma
                nextCombined = normalizeStateSet(nextCombined);

                dfa.push_back({current, sym, nextCombined});

                if (visited.find(nextCombined) == visited.end()) {
                    visited.insert(nextCombined);
                    q.push(nextCombined);
                }
            }
        }
    }
}

// Main function
int main() {
    cout << "Enter the states in the NFA (type -1 to stop):\n";
    while (true) {
        string s;
        cin >> s;
        if (s == "-1") break;
        st.push_back(s);
    }

    cout << "\nEnter the Start State: ";
    cin >> startSt;

    cout << "\nEnter the Final States (type -1 to stop):\n";
    while (true) {
        string f;
        cin >> f;
        if (f == "-1") break;
        finalSt.push_back(f);
    }

    cout << "\nEnter the transition symbols (type -1 to stop):\n";
    while (true) {
        string sym;
        cin >> sym;
        if (sym == "-1") break;
        symbols.push_back(sym);
    }

    insertTransition();
    todfa();

    cout << "\n========================================\n";
    cout << "             NFA TRANSITION TABLE        \n";
    cout << "========================================\n";
    cout << "STATE\t| SYMBOL\t| NEXT STATE\n";
    cout << "----------------------------------------\n";
    for (const auto &t : transition) {
        cout << get<0>(t) << "\t| " << get<1>(t) << "\t\t| " << get<2>(t) << endl;
    }


cout << "\n\n===============================================================\n";
cout << "                       DFA TRANSITION TABLE                    \n";
cout << "===============================================================\n";
cout << left << setw(25) << "STATE" << "| "
     << setw(20) << "SYMBOL" << "| "
     << setw(25) << "NEXT STATE" << endl;
cout << "---------------------------------------------------------------\n";

for (const auto &t : dfa) {
    cout << left << setw(25) << ("{" + get<0>(t) + "}") << "| "
         << setw(20) << get<1>(t) << "| "
         << setw(25) << ("{" + get<2>(t) + "}") << endl;
}


    return 0;
}
