#include "CStack.cpp"

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
