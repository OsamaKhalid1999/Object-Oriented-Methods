#include "pch.h"
#include <iostream>
#include <vector>


template<class Type>
class CStack 
{
private:
	int stackTop;
	int maxSize;
	Type* list;

public:
	CStack();//default stack constructor

	CStack(int sz);//constructor that allows to increase the size of the array if overflowed

	void push(Type in);//function to push elements on stack

	void pop();//removes the last add element into the stack

	Type top();//returns the top element of the stack

	bool empty();//checks if the stack is empty and underflows

	bool full();//checks if the stack is full and overflows

	int length();//return number of elements in stack

	void clear();//clear content of stack

	void toString();//print the concent of the stack

	~CStack();

	//~stack();
};


#include <iostream>
#include <vector>


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
	//delete[] list;
}




class CQueen
{
private:

	int xCoordinate = 0;
	int yCoordinate = 0;
public:
	int nQueens = 0;
	int totalSolutions = 0;
	bool isConflict(std::vector<std::vector<int>> Matrix, int xCoordinate, int yCoordinate);//function to check valid position
	void outputMatrix(CStack <CQueen> Queens);//function to print the board on screen
	void solution(std::vector<std::vector<int>> board, int yCoordinate, CStack <CQueen> Queens);//resolution of the problem
	void display();//function to display in main

};

bool CQueen::isConflict(std::vector<std::vector<int>> Matrix, int xCoordinate, int yCoordinate)
{
	int i, j;

	/* Check this row on left side */
	for (i = 0; i < xCoordinate; i++)
	{
		if (Matrix[i][yCoordinate])
		{
			return false;
		}

	}


	/* Check upper diagonal on left side */
	for (i = xCoordinate, j = yCoordinate; i >= 0 && j >= 0; i--, j--)
	{
		if (Matrix[i][j])
		{
			return false;
		}
	}



	/* Check lower diagonal on left side */
	for (i = xCoordinate, j = yCoordinate; i >= 0 && j < nQueens; j++, i--)
	{
		if (Matrix[i][j])
		{
			return false;
		}

	}



	return true;

}
void CQueen::outputMatrix(CStack <CQueen> Queens)
{
	CStack <CQueen> temporary = Queens;//copy of the stack for just doing operations
	std::vector<std::vector<int>> board(nQueens, std::vector<int>(nQueens, 0));

	CQueen pos;//queen object

	while (!temporary.empty())
	{
		pos = temporary.top();
		temporary.pop();
		board[pos.xCoordinate][pos.yCoordinate] = 1;
	}


	for (int i = 0; i < nQueens; i++)
	{
		for (int j = 0; j < nQueens; j++)
		{
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}

}
void CQueen::solution(std::vector<std::vector<int>> Matrix, int xCoordinate, CStack <CQueen> Queens)
{
	CQueen QueenPosition;
	if (xCoordinate == nQueens)
	{
		totalSolutions++;
		//std::cout << "Solution number : " << totalSolutions << std::endl << std::endl;//if the current row position is equal to the size of the board then output the firs solution

		//outputMatrix(Queens);
		std::cout << std::endl;

	}


	if (xCoordinate != nQueens)//if the queen row position is less than the size of the board then perform backtracking
	{
		for (int i = 0; i < nQueens; i++)
		{
			if (isConflict(Matrix, xCoordinate, i))
			{
				QueenPosition.xCoordinate = xCoordinate;
				QueenPosition.yCoordinate = i;
				Queens.push(QueenPosition);
				Matrix[xCoordinate][i] = 1;

				solution(Matrix, xCoordinate + 1, Queens);
				Queens.pop();
				Matrix[xCoordinate][i] = 0;

			}
		}

	}

}

void CQueen::display()
{
	std::cout << "please enter the board size";
	CQueen queenPosition;
	CStack <CQueen> Queens;
	std::cin >> queenPosition.nQueens;
	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	std::cout << std::endl;
	std::cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	if (queenPosition.totalSolutions == 0)
	{
		std::cout << "No solution found." << std::endl;
	}

}

struct CTests :public::testing::Test
{
public:

	CStack <CQueen> Queens;
	CQueen queenPosition;
	void SetUp()
	{

	}
	void TearDown()
	{

	}



};


TEST_F(CTests, BOARDSIZE_1)
{
	
	queenPosition.nQueens = 1;
	
	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));
	


	queenPosition.solution(Matrix, 0, Queens);
	
	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d,1);
	
}

TEST_F(CTests, BOARDSIZE_2)
{

	queenPosition.nQueens = 2;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 0);

}

TEST_F(CTests, BOARDSIZE_3)
{

	queenPosition.nQueens = 3;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 0);

}

TEST_F(CTests, BOARDSIZE_4)
{

	queenPosition.nQueens = 4;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 2);

}

TEST_F(CTests, BOARDSIZE_5)
{

	queenPosition.nQueens = 5;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 10);

}

TEST_F(CTests, BOARDSIZE_6)
{

	queenPosition.nQueens = 6;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 4);

}

TEST_F(CTests, BOARDSIZE_7)
{

	queenPosition.nQueens = 7;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 40);

}

TEST_F(CTests, BOARDSIZE_8)
{

	queenPosition.nQueens = 8;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 92);

}

TEST_F(CTests, BOARDSIZE_9)
{

	queenPosition.nQueens = 9;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 352);

}


TEST_F(CTests, BOARDSIZE_10)
{

	queenPosition.nQueens = 10;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 724);

}

TEST_F(CTests, BOARDSIZE_11)
{

	queenPosition.nQueens = 11;

	std::vector<std::vector<int>> Matrix(queenPosition.nQueens, std::vector<int>(queenPosition.nQueens, 0));



	queenPosition.solution(Matrix, 0, Queens);

	//cout << " there are " << queenPosition.totalSolutions << " solutions for the problem ";
	int d;
	d = queenPosition.totalSolutions;
	ASSERT_EQ(d, 2680);

}






int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}