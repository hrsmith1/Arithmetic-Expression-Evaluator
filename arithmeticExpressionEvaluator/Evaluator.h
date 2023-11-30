/*
    PROGRAM: Evaluator Class
    AUTHORS: Hannah Smith, Teja Nimmagadda, Magaly Camacho
    DESCRIPTION: Class to evaluate a given expression
*/
#ifndef EVALUATOR_H
#define EVALUATOR_H
/*
    DIRECTIVES
*/
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

/*
    BASIC CLASS DEFINITION
*/
class Evaluator {
public:
  // evaluate the given expression
  string calculate(string exp);
  //returns history queue
  queue<string> getQueue();


private:
  // stacks used to evaluate expressions
  stack<string> opStack, numStack;
  //queue used to track user hisotry
  queue<string> history;
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
  // returns if operator 1 has equal or greater precedence compared to operator
  // 2
  bool hasPrecedence(string op1, string op2);
  // returns if parenthesis are matched
  void checkParenthesis(string exp);
};

#endif