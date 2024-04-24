//Guided by https://www.geeksforgeeks.org/sudoku-backtracking-7/
#include <iostream>
#include <fstream>

//Puzzle read from file
void readPuzzle(int grid[9][9])
{
	//Tested on NYT Hard puzzle for 4/5/24,
	//giving me a record time of 3:34
    std::ifstream fileIn("sudoku.txt");
    for(int i = 0; i < 9; i++)
    {
        for (int j = 0; j< 9; j++)
        {
            fileIn >> grid[i][j];
        }
    }
    fileIn.close();
}

//Puzzle soln print to file
void printGrid(int grid[9][9])
{
    std::ofstream fileOut("sudokuSolution.txt");
	for (int i = 0; i < 9; i++) 
	{
		for (int j = 0; j < 9; j++)
			{
                std::cout << grid[i][j] << " ";
                fileOut << grid[i][j] << " ";
            }
		std::cout << std::endl;
        fileOut << std::endl;
	}
    fileOut.close();
}

//Reject()
bool isSafe(int grid[9][9], const int row, const int col, const int num)
{
	//Check the row to see if number is valid
	for(int i = 0; i < 9; i++)
	{
		if (grid[row][i] == num)
			return false;
	}

	//Check the column
	for(int i = 0; i < 9; i++)
	{
		if (grid[i][col] == num)
			return false;
	}

	//Check the subgrid
	//Will always begin on 0, 3, or 6
	//Candidate position will be >=,  so subtract the pos mod 3 to get start of subgrid
	int subGridRowBegin = row - row % 3, subGridColBegin = col - col % 3;

	//Iterate through subgrid to check for num
	for(int i = subGridRowBegin; i < subGridRowBegin + 3; i++)
	{	for(int j = subGridColBegin; j < subGridColBegin + 3; j++)
		{
			if(grid[i][j] == num)
				return false;
		}
	}

	//If we made it here, we're safe
	return true;
}

//Backtrack
bool solveSudoku(int grid[9][9], int row, int col)
{
	//End of Grid
	if (row == 8 && col == 9)
		return true;

	//If end of row, reset column, move to next row
	if (col == 9) 
	{
		row++;
		col = 0;
	}

	//If current tile isn't blank/0, move to next in row
	if (grid[row][col] > 0)
		return solveSudoku(grid, row, col + 1);

	//Check 1 - 9 for current tile
	for (int num = 1; num <= 9; num++) 
	{
		
		
		if (isSafe(grid, row, col, num)) 
		{
			//if it's safe, then save it
			//First()
			grid[row][col] = num;
		
			//Next
			if (solveSudoku(grid, row, col + 1))
				return true;	//Accept
		}
		//if unsafe or all next steps failed after this point, reset tile
		grid[row][col] = 0;
	}

	//Sudoku can't be solved.
	return false;
}

int main()
{
	int grid[9][9];
    readPuzzle(grid);

	//Serves as "accept" func
	if (solveSudoku(grid, 0, 0))
		printGrid(grid);	//Output
	else
		std::cout << "Sudoku can't be solved.\n";

	return 0;
}
