/*
    PROGRAM: Evaluator Class
    AUTHORS: Hannah Smith, Teja Nimmagadda, Magaly Camacho
    DESCRIPTION: Class to evaluate a given expression
*/

/*
    DIRECTIVES
*/
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include "Evaluator.h"
using namespace std;

/*
    Class METHOD IMPLEMENTATIONS
*/
// public method to evaluate the given expression
string Evaluator::calculate(string exp) {
  // reset stacks to empty and initialize queue of tokens
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

    // if token is a closing parenthesis, evaluate until reaching opening
    // parenthesis
    else if (token == ")") {
      while (!opStack.empty() && opStack.top() != "(") {
        operate();
      }

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

  // check for missing operator
  string res = numStack.top();
  numStack.pop();
  if (!numStack.empty()){
    throw 4;
  }
  //push result to history queue
    history.push(exp+"="+res);

  // return result
  return res;
};

// private method that splits the given expression into tokens
queue<string> Evaluator::tokenize(string exp) {
  queue<string> tokens;
  string c, next, number = "";

  // check if parenthesis are matched (throws error if not)
  checkParenthesis(exp);

  // iterate through expression
  for (unsigned long int i = 0; i < exp.length(); i++) {
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
      next = exp[i + 1];
      if (c == "(") {
        next = exp[i + 1];
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
    else if (c != " ")
      throw 5;
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

  default:
    return false;
  }
};

// private method that returns result (as a string) of operator applied on a and
// b
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
    if (b == 0)
      throw 3; // can't divide by 0
    res = a / b;
    break;

  case '^':
    res = pow(a, b);
    break;

  case '%':
    if (b == 0)
      throw 3; // can't divide by 0
    res = fmod(a, b);
    break;

  default:
    throw 5;
  }

  // return result as a string
  return to_string(res);
};

// private method that applies top operator of opStack to top 2 operands in
// numStack
void Evaluator::operate() {
  // get operator from top of stack
  string op = opStack.top();
  opStack.pop();

  // get operands, throw error if not enough operands
  if (numStack.empty())
    throw 2;
  string b = numStack.top();
  numStack.pop();

  if (numStack.empty())
    throw 2;
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

  default:
    throw 5;
  }
};

// private method that returns if operator 1 has equal or greater precedence
// compared to operator 2
bool Evaluator::hasPrecedence(string op1, string op2) {
  // returns if op1 has precedence over op2 (or equal precedence)
  return getPrecedence(op1) >= getPrecedence(op2);
};

// private method that checks if parenthesis are matched, it throws an error if
// they aren't
void Evaluator::checkParenthesis(string exp) {
  stack<char> checker;

  // iterate through expression
  for (unsigned long int i = 0; i < exp.length(); i++) {
    char c = exp[i];

    // push ( to checker stack
    if (c == '(') {
      checker.push(c);
    }

    // if ), pop matching ( from checker, if checker is empty then parenthesis
    // are mismatched so throw error
    else if (c == ')') {
      if (checker.empty())
        throw 6;
      checker.pop();
    }
  }

  // if there are leftover (, mismatched parenthesis so throw error
  if (!checker.empty())
    throw 6;
}
queue<string> Evaluator::getQueue(){
    return history;
}