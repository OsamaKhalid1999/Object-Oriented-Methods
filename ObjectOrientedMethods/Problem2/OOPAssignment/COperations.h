//#include "CStack.cpp"
#include <string>
#include "HOperations.h"
#include <set>



class COperations : private HOperations
{
private:
	std::string postfix;//store the result of an expression converted to POSTFIX
	std::string prefix;//store the result of an expression converted to POSTFIX
	
public:
	std::set<char> numbers;	//set of numbers used in a prefix conversion and evaluation
	int precedence(char c);//operator precedence during the operations
	std::string infixToPostfix(std::string infix);//function to convert infix to postfix
	double evaluatePostfix(std::string postfix);	//function to evaluate a postfix expression
	bool IsOperator(char C);//function to check if scanned character is an opertor
	std::string infixToPrefix(std::string infix);//function to convert infix to prefix
    double evaluatePrefix(std::string postfix);//function to convert infix to postfix
};

