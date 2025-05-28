#include <cctype>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        case '%':
            if (b == 0) throw runtime_error("Modulo by zero");
            return a % b;
    }
    throw runtime_error("Invalid operator");
}

int evaluate(const string& tokens) {
    stack<int> values;
    stack<char> ops;

    for (size_t i = 0; i < tokens.length(); i++) {
        if (isspace(tokens[i])) continue;

        if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }

        else if (isdigit(tokens[i]) || (tokens[i] == '-' && (i == 0 || tokens[i - 1] == '('))) {
            int val = 0;
            bool negative = false;
            if (tokens[i] == '-') {
                negative = true;
                i++;
            }
            while (i < tokens.length() && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            i--;
            if (negative) val = -val;
            values.push(val);
        }

        else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();

                int res = applyOp(val1, val2, op);
                values.push(res);
            }
            if (!ops.empty())
                ops.pop();
            else
                throw runtime_error("Mismatched parentheses");
        }

        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();

                int res = applyOp(val1, val2, op);
                values.push(res);
            }
            ops.push(tokens[i]);
        }
    }

    while (!ops.empty()) {
        if (ops.top() == '(' || ops.top() == ')') throw runtime_error("Mismatched parentheses");
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();

        int res = applyOp(val1, val2, op);
        values.push(res);
    }

    if (values.size() != 1) throw runtime_error("Invalid expression");
    return values.top();
}

int main() {
    cout << "Enter an algebraic expression with integers and operators (+, -, *, /, %, "
            "parentheses):\n";
    string expression;
    getline(cin, expression);

    try {
        int result = evaluate(expression);
        cout << "Result: " << result << endl;
        cout << "Asymptotic complexity: O(n), where n is the length of the expression." << endl;
    } catch (const exception& e) {
        cerr << "Error evaluating expression: " << e.what() << endl;
    }

    cin.ignore();
    cin.get();
    return 0;
}
