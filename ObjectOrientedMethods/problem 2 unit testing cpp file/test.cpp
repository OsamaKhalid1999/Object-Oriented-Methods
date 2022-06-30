#include "pch.h"
#include <memory>
#include <iostream>
#include <set>
#include <string>
using namespace std;


template<class Type>
class HStack
{
	virtual void push(Type v) = 0;
	virtual void pop() = 0;
	virtual bool empty() = 0;
	virtual Type top() = 0;
};

template<class Type>
class CStack :public HStack<Type> {
private:
	int stackTop;
	int maxSize;
	Type* list;

public:
	CStack();

	CStack(int sz);

	void push(Type in);

	void pop();

	Type top();

	bool empty();

	bool full();

	int length();

	void clear();

	void toString();

	~CStack();

	//~stack();
};



template<class Type>

CStack<Type>::CStack() {
	maxSize = 10000;
	stackTop = -1;
	list = new Type[10000];
}

template<class Type>
CStack<Type>::CStack(int sz) {
	if (sz <= 0) {
		std::cout << "Size must be positive" << std::endl;
		exit(0);
	}
	maxSize = 10 * sz;
	stackTop = -1;
	list = new Type[maxSize];

}

template<class Type>
void CStack<Type>::push(Type in) {
	if (full()) {
		std::cout << "Stack is full" << std::endl;
		return;
	}
	stackTop++;
	list[stackTop] = in;
}

template<class Type>
void CStack<Type>::pop() {
	if (empty()) {
		std::cout << "Stack is empty" << std::endl;
	}
	stackTop--;
}

template<class Type>
Type CStack<Type>::top() {
	if (stackTop == -1) {
		std::cout << "Stack is empty" << std::endl;
		exit(0);
	}
	return list[stackTop];
}

template<class Type>
bool CStack<Type>::empty() {
	return (stackTop == -1);
}

template<class Type>
bool CStack<Type>::full() {
	return (stackTop + 1 == maxSize);
}

template<class Type>
int CStack<Type>::length() {
	return stackTop + 1;
}

template<class Type>
void CStack<Type>::clear() {
	stackTop = -1;
}

template<class Type>
void CStack<Type>::toString() {
	if (stackTop == -1) {
		std::cout << "Stack is empty" << std::endl;
		return;
	}
	for (int i = stackTop; i >= 0; i--) {
		std::cout << list[i] << " ";
	}
	std::cout << std::endl;

}

template<class Type>
CStack<Type>::~CStack() {
	delete[] list;
}


class HOperations
{
	virtual int precedence(char c) = 0;
	virtual std::string infixToPostfix(std::string infix) = 0;
	virtual double evaluatePostfix(std::string postfix) = 0;
	virtual bool IsOperator(char C) = 0;
	virtual std::string infixToPrefix(std::string infix) = 0;
	virtual double evaluatePrefix(std::string postfix) = 0;
};

class COperations : private HOperations
{
private:
	std::string postfix;
	std::string prefix;

public:
	std::set<char> numbers;
	int precedence(char c);
	std::string infixToPostfix(std::string infix);
	double evaluatePostfix(std::string postfix);
	bool IsOperator(char C);
	std::string infixToPrefix(std::string infix);
	double evaluatePrefix(std::string postfix);
};

int COperations::precedence(char c)
{
	if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

std::string COperations::infixToPostfix(std::string infix)
{
	std::unique_ptr<CStack<int>>conversion(new CStack<int>);
	for (int i = 0; i < infix.length(); i++)
	{

		//char c = s[i];
		if (infix[i] == ' ')
			continue;

		else if (infix[i] == '(')
		{
			conversion->push(infix[i]);
		}


		// If the scanned character is
		// an operand, add it to output string.
		else if (isdigit(infix[i]))
		{
			int operand = 0;
			while (i < infix.length() && isdigit(infix[i]))
			{
				operand = (operand * 10) + (infix[i] - '0');
				i++;
			}
			std::string str;
			std::stringstream ss;
			ss << operand;
			ss >> str;
			i--;

			postfix += str;
			postfix += " ";

		}



		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (infix[i] == '(')
			conversion->push(infix[i]);

		// If the scanned character is an ‘)’,
		// pop and to output string from the stack
		// until an ‘(‘ is encountered.
		else if (infix[i] == ')') {


			while (!conversion->empty() && conversion->top() != '(')
			{

				postfix += conversion->top();
				conversion->pop();
				postfix += " ";
			}
			conversion->pop();
		}

		//If an operator is scanned
		else {
			while (!conversion->empty() && precedence(infix[i]) <= precedence(conversion->top())) {


				postfix += conversion->top();
				conversion->pop();
				postfix += " ";
			}
			conversion->push(infix[i]);
		}
	}

	// Pop all the remaining elements from the stack		
	while (!conversion->empty()) {
		postfix += conversion->top();
		conversion->pop();
		postfix += " ";
	}



	//CStack<int>* conversion = new CStack<int>;
	conversion.reset();
	return postfix;
	postfix.clear();
}

double COperations::evaluatePostfix(std::string postfix)
{
	//CStack<double>* evaluation = new CStack<double>;
	std::unique_ptr<CStack<double>>evaluation(new CStack<double>);
	for (int i = 0; i < postfix.length(); i++)
	{

		// Scanning each character from left.
		// If character is a delimiter, move on.
		if (postfix[i] == ' ' || postfix[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if (IsOperator(postfix[i]))
		{
			// Pop two operands.
			double operand2 = evaluation->top(); evaluation->pop();
			double operand1 = evaluation->top(); evaluation->pop();

			//operand1 and operand2 are reversed in case of Prefix Expression

			// Perform operation
			switch (postfix[i]) {
			case '+':
				evaluation->push(operand1 + operand2);
				break;
			case '-':
				evaluation->push(operand1 - operand2);
				break;
			case '*':
				evaluation->push(operand1 * operand2);
				break;
			case '/':
				evaluation->push(operand1 / operand2);
				break;
			}


		}
		else if (isdigit(postfix[i]))
		{
			// Extract the numeric operand from the string
			// Keep incrementing i as long as you are getting a numeric digit.
			int operand = 0;
			while (i < postfix.length() && isdigit(postfix[i]))
			{
				// For a number with more than one digits, as we are scanning from left to right.
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10
				// and add the new digit.
				operand = (operand * 10) + (postfix[i] - '0');
				i++;
			}
			// Finally, you will come out of while loop with i set to a non-numeric character or end of string
			// decrement i because it will be incremented in increment section of loop once again.
			// We do not want to skip the non-numeric character by incrementing i twice.
			i--;

			// Push operand on stack.
			evaluation->push(operand);
		}
	}
	// If expression is in correct format, Stack will finally have one element. This will be the output.
	return evaluation->top();
	evaluation.reset();
	//delete(evaluation);
}


bool COperations::IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}

std::string COperations::infixToPrefix(std::string infix)
{
	//CStack<int>* conversion = new CStack<int>;

	std::unique_ptr<CStack<int>>conversion(new CStack<int>);
	//stack<int> operations;
	//final expression
	//string prefix;

	//reverse the string
	reverse(infix.begin(), infix.end());

	//considering opening and close brackets reversed
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] == '(') {
			infix[i] = ')';
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
		}
	}

	infix = "(" + infix + ")";

	// iterate through infix string
	for (int i = 0; i < infix.size(); i++)
	{
		// cerr << i << ":" << postfix << "\n" << operations.to_string() << endl;
		if (numbers.find(infix[i]) != numbers.end())
		{
			// delete last space to continue number
			if (numbers.find(infix[i - 1]) != numbers.end())
			{
				prefix.pop_back();
			}
			// add number to expression
			prefix += infix[i];
			prefix += " ";
		}
		else if (infix[i] == '(')
		{
			conversion->push('(');
		}
		else if (infix[i] == ')')
		{
			// remove everithing within the brackets
			while (conversion->top() != '(')
			{
				prefix += conversion->top();
				conversion->pop();
				prefix += " ";
			}
			// ignore open bracket
			conversion->pop();
		}
		else if (IsOperator(infix[i]))
		{
			// add lower priority operators to string
			while (precedence(infix[i]) < precedence(conversion->top()))
			{
				prefix += conversion->top();
				conversion->pop();
				prefix += " ";
			}
			conversion->push(infix[i]);
		}
	}
	// delete last space
	prefix.pop_back();
	reverse(prefix.begin(), prefix.end());
	return prefix;
	prefix.clear();


}

double COperations::evaluatePrefix(std::string prefix)
{
	//CStack<double>* evaluation = new CStack<double>;
	std::unique_ptr<CStack<double>>evaluation(new CStack<double>);
	for (int j = prefix.size() - 1; j >= 0; j--) {

		// if jth character is the delimiter ( which is
		// space in this case) then skip it
		if (prefix[j] == ' ')
			continue;

		// Push operand to Stack
		// To convert exprsn[j] to digit subtract
		// '0' from exprsn[j].
		if (isdigit(prefix[j])) {

			// there may be more than
			// one digits in a number
			int num = 0, i = j;
			while (j < prefix.size() && isdigit(prefix[j]))
				j--;
			j++;

			// from [j, i] exprsn contains a number
			for (int k = j; k <= i; k++)
				num = num * 10 + int(prefix[k] - '0');

			evaluation->push(num);
		}
		else {

			// Operator encountered
			// Pop two elements from Stack
			double o1 = evaluation->top();
			evaluation->pop();
			double o2 = evaluation->top();
			evaluation->pop();

			// Use switch case to operate on o1
			// and o2 and perform o1 O o2.
			switch (prefix[j]) {
			case '+':
				evaluation->push(o1 + o2);
				break;
			case '-':
				evaluation->push(o1 - o2);
				break;
			case '*':
				evaluation->push(o1 * o2);
				break;
			case '/':
				evaluation->push(o1 / o2);
				break;
			}
		}
	}

	return evaluation->top();
	//delete(evaluation);
	evaluation.reset();
}



struct CTests :public::testing::Test
{
public:

	COperations Tests;

	void SetUp()
	{

	}
	void TearDown()
	{

	}



};


TEST_F(CTests, POSTFIX_CONVERSION_1)
{


	string infix = "(220+220)/((11+11)*(1000-990)/(1998-1996))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	//Assert
	ASSERT_STREQ(postfix.c_str(), "220 220 + 11 11 + 1000 990 - * 1998 1996 - / / ");
}

TEST_F(CTests, POSTFIX_CONVERSION_2)
{


	string infix = "(3333+2222)/((100-99)*(7777-2222)/(1000+111))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	//Assert
	ASSERT_STREQ(postfix.c_str(), "3333 2222 + 100 99 - 7777 2222 - * 1000 111 + / / ");
}

TEST_F(CTests, POSTFIX_CONVERSION_3)
{


	string infix = "74*((100-99)*(932-800)*(678-676))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	//Assert
	ASSERT_STREQ(postfix.c_str(), "74 100 99 - 932 800 - * 678 676 - * * ");
}

TEST_F(CTests, POSTFIX_CONVERSION_4)
{


	string infix = "20+40*(60-20)/20*2";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	//Assert
	ASSERT_STREQ(postfix.c_str(), "20 40 60 20 - * 20 / 2 * + ");
}

TEST_F(CTests, POSTFIX_CONVERSION_5)
{


	string infix = "20+20*(600/((10+5)*(777-773)*(100/25)+60))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	//Assert
	ASSERT_STREQ(postfix.c_str(), "20 20 600 10 5 + 777 773 - * 100 25 / * 60 + / * + ");
}

TEST_F(CTests, POSTFIX_CONVERSION_6)
{


	string infix = "(3000+3000)/(1000+1000)*((15000+1000)/(160-120))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	//Assert
	ASSERT_STREQ(postfix.c_str(), "3000 3000 + 1000 1000 + / 15000 1000 + 160 120 - / * ");
}

TEST_F(CTests, POSTFIX_CONVERSION_7)
{


	string infix = "(768+576)/(689-657)*(25-23)*(2000-1800)";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	//Assert
	ASSERT_STREQ(postfix.c_str(), "768 576 + 689 657 - / 25 23 - * 2000 1800 - * ");
}

TEST_F(CTests, POSTFIX_EVALUATION_1)
{


	string infix = "(220+220)/((11+11)*(1000-990)/(1998-1996))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	result = Tests.evaluatePostfix(postfix);

	//Assert
	ASSERT_EQ(result, 4);


}

TEST_F(CTests, POSTFIX_EVALUATION_2)
{


	string infix = "(3333+2222)/((100-99)*(7777-2222)/(1000+111))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	result = Tests.evaluatePostfix(postfix);

	//Assert

	ASSERT_EQ(result, 1111);

}

TEST_F(CTests, POSTFIX_EVALUATION_3)
{


	string infix = "74*((100-99)*(932-800)*(678-676))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	result = Tests.evaluatePostfix(postfix);

	//Assert
	ASSERT_EQ(result, 19536);

}


TEST_F(CTests, POSTFIX_EVALUATION_4)
{


	string infix = "20+40*(60-20)/20*2";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	result = Tests.evaluatePostfix(postfix);

	//Assert
	ASSERT_EQ(result, 180);

}

TEST_F(CTests, POSTFIX_EVALUATION_5)
{


	string infix = "20+20*(600/((10+5)*(777-773)*(100/25)+60))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	result = Tests.evaluatePostfix(postfix);

	//Assert
	ASSERT_EQ(result, 60);

}

TEST_F(CTests, POSTFIX_EVALUATION_6)
{


	string infix = "(3000+3000)/(1000+1000)*((15000+1000)/(160-120))";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	result = Tests.evaluatePostfix(postfix);

	//Assert
	ASSERT_EQ(result, 1200);

}

TEST_F(CTests, POSTFIX_EVALUATION_7)
{


	string infix = "(768+576)/(689-657)*(25-23)*(2000-1800)";
	string postfix;
	double result;
	//Act

	postfix = Tests.infixToPostfix(infix);
	result = Tests.evaluatePostfix(postfix);

	//Assert
	ASSERT_EQ(result, 16800);

}

TEST_F(CTests, PREFIX_EVALUATION_1)
{

	string infix = "(220+220)/((11+11)*(1000-990)/(1998-1996))";
	string prefix;
	double d;
	//Act

	prefix = Tests.infixToPrefix(infix);
	d = Tests.evaluatePrefix(prefix);
	//Assert
	EXPECT_EQ(d, 4);
	
}

TEST_F(CTests, PREFIX_EVALUATION_2)
{

	string infix = "(3333+2222)/((100-99)*(7777-2222)/(1000+111))";
	string prefix;
	double d;
	//Act

	prefix = Tests.infixToPrefix(infix);
	d = Tests.evaluatePrefix(prefix);
	//Assert
	ASSERT_EQ(d, 1111);

}

TEST_F(CTests, PREFIX_EVALUATION_3)
{

	string infix = "74*((100-99)*(932-800)*(678-676))";
	string prefix;
	double d;
	//Act

	prefix = Tests.infixToPrefix(infix);
	d = Tests.evaluatePrefix(prefix);
	//Assert
	ASSERT_EQ(d, 19536);

}

TEST_F(CTests, PREFIX_EVALUATION_4)
{

	string infix = "20+40*(60-20)/20*2";
	string prefix;
	double d;
	//Act

	prefix = Tests.infixToPrefix(infix);
	d = Tests.evaluatePrefix(prefix);
	//Assert
	ASSERT_EQ(d, 180);

}

TEST_F(CTests, PREFIX_EVALUATION_5)
{

	string infix = "20+20*(600/((10+5)*(777-773)*(100/25)+60))";
	string prefix;
	double d;
	//Act

	prefix = Tests.infixToPrefix(infix);
	d = Tests.evaluatePrefix(prefix);
	//Assert
	ASSERT_EQ(d, 60);

}

TEST_F(CTests, PREFIX_EVALUATION_6)
{

	string infix = "(3000+3000)/(1000+1000)*((15000+1000)/(160-120))";
	string prefix;
	double d;
	//Act

	prefix = Tests.infixToPrefix(infix);
	d = Tests.evaluatePrefix(prefix);
	//Assert
	ASSERT_EQ(d, 1200);

}

TEST_F(CTests, PREFIX_EVALUATION_7)
{

	string infix = "(768+576)/(689-657)*(25-23)*(2000-1800)";
	string prefix;
	double d;
	//Act

	prefix = Tests.infixToPrefix(infix);
	d = Tests.evaluatePrefix(prefix);
	//Assert
	ASSERT_EQ(d, 16800);

}

TEST_F(CTests, PREFIX_CONVERSION_2)
{


	string infix = "(3333+2222)/((100-99)*(7777-2222)/(1000+111))";
	string prefix;
	
	//Act

	prefix = Tests.infixToPrefix(infix);
	//Assert
	ASSERT_STREQ(prefix.c_str(), "/ + 3333 2222 / * - 100 99 - 7777 2222 + 1000 111 ");
}

TEST_F(CTests, PREFIX_CONVERSION_3)
{


	string infix = "74*((100-99)*(932-800)*(678-676))";
	string prefix;

	//Act

	prefix = Tests.infixToPrefix(infix);
	//Assert
	ASSERT_STREQ(prefix.c_str(), "* 74 * * - 100 99 - 932 800 - 678 676 ");
}

TEST_F(CTests, PREFIX_CONVERSION_4)
{


	string infix = "20+40*(60-20)/20*2";
	string prefix;
	
	//Act

	prefix = Tests.infixToPrefix(infix);
	//Assert
	ASSERT_STREQ(prefix.c_str(), "+ 20 * / * 40 - 60 20 20 2 ");
}

TEST_F(CTests, PREFIX_CONVERSION_5)
{


	string infix = "20+20*(600/((10+5)*(777-773)*(100/25)+60))";
	string prefix;
	
	//Act

	prefix = Tests.infixToPrefix(infix);
	//Assert
	ASSERT_STREQ(prefix.c_str(), "+ 20 * 20 / 600 + * * + 10 5 - 777 773 / 100 25 60 ");
}

TEST_F(CTests, PREFIX_CONVERSION_6)
{


	string infix = "(3000+3000)/(1000+1000)*((15000+1000)/(160-120))";
	string prefix;
	
	//Act

	prefix = Tests.infixToPrefix(infix);
	//Assert
	ASSERT_STREQ(prefix.c_str(), "* / + 3000 3000 + 1000 1000 / + 15000 1000 - 160 120 ");
}

TEST_F(CTests, PREFIX_CONVERSION_7)
{


	string infix = "(768+576)/(689-657)*(25-23)*(2000-1800)";
	string prefix;
	
	//Act

	prefix = Tests.infixToPrefix(infix);
	//Assert
	ASSERT_STREQ(prefix.c_str(), "* * / + 768 576 - 689 657 - 25 23 - 2000 1800 ");
}






int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}





