# NFA-TO-DFA
# 🔁 NFA to DFA Converter (C++)

 > This is a C++ command-line tool to convert a **Non-Deterministic Finite Automaton (NFA)** into a **Deterministic Finite Automaton (DFA)**. It allows you to input custom NFA components and outputs both the original NFA transition table and the generated DFA transition table.

![States: NFA](https://img.shields.io/badge/States-yellow?style=flat-square&logo=appveyor&logoColor=black)
![Symbols: Input](https://img.shields.io/badge/Symbols-blue?style=flat-square&logo=typescript&logoColor=white)
![Conversion: NFA→DFA](https://img.shields.io/badge/Conversion-yellow?style=flat-square&logo=visual-studio-code&logoColor=black)
![Language: C++](https://img.shields.io/badge/Language-C++-blue?style=flat-square&logo=c%2B%2B&logoColor=white)
![Platform: CLI](https://img.shields.io/badge/Platform-CLI-yellow?style=flat-square&logo=gnu-bash&logoColor=black)


---

## 🚀 Features

- Accepts user-defined:
  - States
  - Start state
  - Final states
  - Input symbols
  - Transitions (with support for multiple next-states per symbol)
- Converts NFA to DFA by combining states
- Outputs clean and readable:
  - NFA Transition Table
  - DFA Transition Table
- Handles composite DFA states like `{q0,q1}`

---

## 🧠 Concepts Used

- Finite Automata
- Deterministic and Non-deterministic transitions
- Queue-based BFS for state exploration
- Set operations and string manipulation
- Transition table representation with tuples

---

## 🛠️ How to Use

### 1. 🔧 Compile the Program

Use any C++ compiler, such as `g++`:

```bash
g++ nfa_to_dfa.cpp -o nfa_to_dfa
```
### Run the program

```
./nfa_to_dfa
```
---

# 3. 🧾 Input Format
**States:** One per line (e.g., q0, q1, q2). End with -1.

**Start State:** Single input (e.g., q0)

**Final States:** One per line. End with -1.

**Symbols:** One per line (e.g., a, b). End with -1.

**Transitions:**

For each state-symbol pair, enter destination states separated by space.

End each input with a . (dot) to finish that line.

**Example:** ```q0 q1 .```

# 🧪 Sample Input
```
States:        q0, q1, q2
Start State:   q0
Final States:  q2
Symbols:       a, b

Transitions:
For q0:
  a → q0 q1
  b → q0
For q1:
  a → -
  b → q2
For q2:
  a → -
  b → -
```
---
# 🖨️ Sample Output
```
========================================
             NFA TRANSITION TABLE        
========================================
STATE   | SYMBOL        | NEXT STATE
----------------------------------------
q0      | a             | q0,q1
q0      | b             | q0
q1      | a             | 
q1      | b             | q2
q2      | a             | 
q2      | b             | 

========================================
           DFA TRANSITION TABLE          
========================================
STATE          | SYMBOL        | NEXT STATE
----------------------------------------
{q0}           | a             | {q0,q1}
{q0}           | b             | {q0}
{q0,q1}        | a             | {q0,q1}
{q0,q1}        | b             | {q0,q2}
...
```
---

# 📂 Project Structure
```
nfa_to_dfa/
│
├── nfa_to_dfa.cpp       # Main C++ source file
└── README.md            # Project documentation
```
---

# 🤝 Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss your ideas.

If you'd like to:

- Add epsilon (ε) transition support

- Minimize the DFA

- Add unit tests

Feel free to fork and contribute!

# 📄 License
This project is open source under the MIT License.

---
