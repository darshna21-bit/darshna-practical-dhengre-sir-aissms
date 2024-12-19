#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix
string infixToPostfix(const string &infix) {
    stack<char> s;
    string postfix;

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        if (isalnum(ch)) {
            postfix += ch; // Add operands directly to postfix
        } else if (ch == '(') {
            s.push(ch); // Push '(' to stack
        } else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // Remove '('
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch); // Push current operator
        }
    }

    while (!s.empty()) {
        postfix += s.top(); // Append remaining operators
        s.pop();
    }

    return postfix;
}

// Function to evaluate postfix expression
int evaluatePostfix(const string &postfix) {
    stack<int> s;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            s.push(ch - '0'); // Convert char to int and push
        } else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.top();
}

int main() {
    string infix;

    cout << "Enter an infix expression: ";
    getline(cin, infix); // Use getline to handle spaces in input

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    // Check if expression is numeric (only contains digits and operators)
    bool isNumeric = true;
    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];
        if (!isdigit(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        int result = evaluatePostfix(postfix);
        cout << "Result of evaluation: " << result << endl;
    } else {
        cout << "Evaluation is only possible for numeric expressions." << endl;
    }

    return 0;
}

