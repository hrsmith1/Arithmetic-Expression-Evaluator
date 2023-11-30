/*
  PROGRAM: Expression Handler Class
  AUTHORS: Maddie Watson, Christina Sorenson, Hannah Smith
  DESCRIPTION: Handle the frontend/user interactions for the Evaluator class
*/

/*
  DIRECTIVES
*/
#include "Evaluator.h"
#include <iostream>
using namespace std;

/*
  MAIN METHOD
*/
void printQueue(queue<string> hisqueue);
int main() {
  queue<string> copyHistory;
  Evaluator calculator;
  cout << "Welcome! Below you'll be able to insert a function to calculate. Here are the available operators:\n( ) - Parenthesis\n^ - Exponent\n* - Multiplication\n/ - Division\n% - Modulus\n+ - Addition\n- Subtraction\n\nPlease enter your expression, type \'history\' to print history, or type \'exit\' to end the program.\n";
  // loop to continuously prompt user for input
  while (true) {
    string input;
    cout << "Enter expression: ";
    getline(cin, input);

    for(unsigned long int i=0; i<input.size(); i++){
        input[i]=tolower(input[i]);
    }

    // if input given is "exit", exit the program
    if (input == "exit") {
      break;
    } 
    // if input given is "history", display history
    else if (input == "history"){
        copyHistory = calculator.getQueue();
        cout<<"User History:"<<endl;
        printQueue(copyHistory);

    }
    // otherwise, try to evaluate the input
    else {
      try {
        cout << "Result: " << calculator.calculate(input) << endl;
      } 
      // if the input is invalid, print the respective error message given the error code
      catch (int errNum) {
        switch (errNum) {
        case 2:
          cout << "Operator Without Operands" << endl;
          break;
        case 3:
          cout << "Division by Zero" << endl;
          break;
        case 4:
          cout << "Missing Operator" << endl;
          break;
        case 5:
          cout << "Invalid Character" << endl;
          break;
        case 6:
          cout << "Mismatched Parenthesis" << endl;
          break;
        }
      }
    }
  }
  return 0;
}
void printQueue(queue<string> hisqueue){
    for(unsigned long int i=0; i<hisqueue.size(); i++){
      string front = hisqueue.front();
      hisqueue.pop();
      hisqueue.push(front);
      cout<<front<<endl;
    }
}