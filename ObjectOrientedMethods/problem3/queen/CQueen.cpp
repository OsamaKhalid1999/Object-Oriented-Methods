#include "CQueen.h"
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
		std::cout << "Solution number : " << totalSolutions << std::endl << std::endl;//if the current row position is equal to the size of the board then output the firs solution

		outputMatrix(Queens);
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