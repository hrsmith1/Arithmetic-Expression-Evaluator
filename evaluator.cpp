/*
    PROGRAM: Evaluator Class
    AUTHORS: Hannah Smith, Teja Nimmagadda, Magaly Camacho 
    DESCRIPTION: Class to evaluate a given expression
*/

/*
    DIRECTIVES
*/ 
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <iostream>
using namespace std;

/*
    BASIC CLASS DEFINITION
*/
class Evaluator {
    public: 
        // evaluate the given expression
        string calculate(string exp);

    private:
        stack<string> opStack, numStack;
        // splits the given expression into tokens
        queue<string> tokenize(string exp);
        // returns if character is an operator
        bool isOperator(string c);
        // returns result (as a string) of operator applied on a and b
        string applyOperator(string a, string b, string op);
        // applies top operator of opStack to top 2 operands in numStack
        void operate();
        // returns precedence of given operator
        int getPrecedence(string op);
        // returns if operator 1 has equal or greater precedence compared to operator 2 
        bool hasPrecedence(string op1, string op2);
        // returns if parenthesis are matched
        void checkParenthesis(string exp);

        void printStack(stack<string> q) {
            cout << "Printing stack : ";
            while (!q.empty()) {
                cout << q.top();
                q.pop();
            }
        };
        void printQueue(queue<string> q) {
            cout << "\nPrinting Queue:";
            q.push("end");
            while (q.front() != "end") {
                cout << "\n\t " << q.front();
                q.push(q.front());
                q.pop();
            }
            q.pop();
        }
};

/*
    METHOD IMPLEMENTATIONS
*/
// public method to evaluate the given expression
string Evaluator::calculate(string exp) {
    // reset stacks and initialize queue of tokens
    stack<string>().swap(opStack);
    stack<string>().swap(numStack);
    queue<string> tokens = tokenize(exp);

    // go through tokens and proceed accordingly
    while (!tokens.empty()) {
        // get front token
        string token = tokens.front();
        tokens.pop();

        // if token is a number, push it to numStack
        if (token.length() > 1 || isdigit(token[0])) {
            numStack.push(token);
        }
        
        // if token is an opening parenthesis, push it to opStack
        else if (token == "(") {
            opStack.push(token);
        }

        // if token is a closing parenthesis, evaluate until reaching opening parenthesis
        else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                operate();
            }

            // check if unmatched parenthesis
            if (opStack.empty()) throw 1; 

            // pop opening parenthesis from opStack
            opStack.pop(); 
        }

        // if token is an operator, proceed based on precedence
        else {
            // if top of stack has equal or greater precedence, calculate 
            while ((!opStack.empty()) && hasPrecedence(opStack.top(), token)) {
                operate();
            }

            // push operator to opStack
            opStack.push(token);
        }
    }

    // operate on remaining operators
    while (!opStack.empty()) {
        operate();
    }

    // return result
    return numStack.top();
};

// private method that splits the given expression into tokens
queue<string> Evaluator::tokenize(string exp) {
    queue<string> tokens;
    string number = "";
    string c;
    string next;

    // check if parenthesis are matched
    checkParenthesis(exp);

    // iterate through expression
    for (int i = 0; i < exp.length(); i++) {
        c = exp[i];

        // if c is an operator
        if (isOperator(c) || c == "(" || c == ")") {
            // handle leading positive or negative
            if (i == 0 && (c == "+" || c == "-")) {
                tokens.push("0");
            }

            // append previous operand, if any
            if (number != "") {
                tokens.push(number);
                number = "";
            }

            // append operator c
            tokens.push(string(c));

            // check next character (handle positive, negative)
            next = exp[i+1];
            if (c == "(") {
                next = exp[i+1];
                if (next == "+" || next == "-") {
                    tokens.push("0");
                }
            }
        }

        // concatenate digits/periods to number
        else if (isdigit(c[0]) || c == ".") {
            number += c;
        }

        // ignore whitespace, but throw error for other characters (invalid ones)
        else if (c != " ") throw 51;
    }

    // append operand if leftover
    if (number != "") {
        tokens.push(number);
    }

    // return tokens
    return tokens;
};

// private method that returns if a given character is an operator
bool Evaluator::isOperator(string c) {
    // return if c is in [+, -, *, /, ^, %]
    switch (c[0]) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
            return true;

        default: return false;
    }
};

// private method that returns result (as a string) of operator applied on a and b
string Evaluator::applyOperator(string str_a, string str_b, string op) {
    // cast a and b from string to float
    float a = stof(str_a);
    float b = stof(str_b);
    float res;

    // calculate result based on operator
    switch (op[0]) {
        case '+': 
            res = a + b;
            break;

        case '-': 
            res = a - b;
            break;

        case '*': 
            res = a * b;
            break;

        case '/':
            if (b == 0) throw 3;
            res = a / b;
            break;

        case '^': 
            res = pow(a, b);
            break;

        case '%':
            if (b == 0) throw 3;
            res = fmod(a, b);
            break;

        default: throw 52;
    }

    // return result as a string
    return to_string(res);
};

// private method that applies top operator of opStack to top 2 operands in numStack
void Evaluator::operate() {
    // get operator from top of stack
    string op = opStack.top();
    opStack.pop();

    // get operands, throw error if not enough operands
    if (numStack.empty()) throw 21;
    string b = numStack.top();
    numStack.pop();

    if (numStack.empty()) throw 22;
    string a = numStack.top();
    numStack.pop();

    // calculate and push result to numStack
    string res = applyOperator(a, b, op);
    numStack.push(res);
};

// private method that returns precedence of given operator
int Evaluator::getPrecedence(string op) {
    // returns precedence of given operator
    switch (op[0]) {
        case '^': 
            return 3;

        case '*': 
        case '/':
        case '%':
            return 2;

        case '+': 
        case '-': 
            return 1;

        case '(':
        case ')':
            return 0;

        default: throw 53;
    }
};

// private method that returns if operator 1 has equal or greater precedence compared to operator 2
bool Evaluator::hasPrecedence(string op1, string op2) {
    // returns if op1 has precedence over op2 (or equal precedence)
    return getPrecedence(op1) >= getPrecedence(op2);
};

// returns if parenthesis are matched
void Evaluator::checkParenthesis(string exp) {
    stack<char> checker;

    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];
        if (c == '(') {
            checker.push(c);
        } else if (c == ')') {
            if (checker.empty()) throw 6;
            checker.pop();
        }
    }

    if (!checker.empty()) throw 6;
}