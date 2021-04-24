#include <iostream>
#include <vector>
using namespace std;


void printBoard(int arr[9][9]) {
	cout << "-------------------------" << endl;
	for (int y = 0; y < 9; y++) {
		if (y % 3 == 0 && y != 0){
            printf("-------------------------\n");
        }
		for(int j = 0; j < 9; j++){
            if (j % 3 == 0 && j != 0){
                printf(" | ");
            }
            if(j == 8 ){
                printf("%d", arr[y][j]);
            }
            else{
                printf("%d ", arr[y][j]);
            }
         }
		 printf("\n");
	}
	cout << "-------------------------" << endl;

}

bool valid(int arr[9][9], int row, int col, int n)
{
	if (arr[row][col] != 0) return false;
	bool status = true;
	int gridx = (col / 3) * 3;
	int gridy = (row / 3) * 3;
	for (int i = 0; i < 9; i++) {
		if (arr[row][i] == n) { status = false; break; }
		if (arr[i][col] == n) { status = false; break; }
		if (arr[gridy + i / 3][gridx + i % 3] == n) { status = false; break; }
	}
	return status;
}

void find_empty(int arr[9][9], int row, int col, int& rowNext, int& colNext)
{

	int indexNext = 9 * 9 + 1;
	for (int i = row * 9 + col + 1; i < 9 * 9; i++) {
		if (arr[i / 9][i % 9] == 0) {

			indexNext = i;
			break;
		}
	}
	rowNext = indexNext / 9;
	colNext = indexNext % 9;
}

void copySudoku(int arr[9][9], int arrCpy[9][9]) {
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			arrCpy[y][x] = arr[y][x];
}
std::vector<int> emptyLocations(int arr[9][9], int row, int col) {
	vector<int> locations;
	for (int n = 1; n <= 9; n++)
		if (valid(arr, row, col, n)) locations.push_back(n);
	return locations;
}


bool solve(int arr[9][9], int row, int col)
{

	if (row > 8) return true;
	if (arr[row][col] != 0) {
		int rowNext, colNext;
		find_empty(arr, row, col, rowNext, colNext);
		return solve(arr, rowNext, colNext);
	}

	std::vector<int> locations = emptyLocations(arr, row, col);

	if (locations.size() == 0) {
		
		return false; 
	
	};

	bool status = false;
	for (int i = 0; i < locations.size(); i++) {
		int n = locations[i];
		int arrCpy[9][9];
		copySudoku(arr, arrCpy);
		arrCpy[row][col] = n;
		int rowNext = row;
		int colNext = col;
		find_empty(arrCpy, row, col, rowNext, colNext);
		if (solve(arrCpy, rowNext, colNext)) {
			copySudoku(arrCpy, arr);
			status = true;
			break;
		}
	}
	return status;
}


int main(int argc, char** argv)
{
	int board[9][9] = {
		{7,8,0,4,0,0,1,2,0},
    	{6,0,0,0,7,5,0,0,9},
    	{0,0,0,6,0,1,0,7,8},
    	{0,0,7,0,4,0,2,6,0},
    	{0,0,1,0,5,0,9,3,0},
    	{9,0,4,0,6,0,0,0,5},
    	{0,7,0,3,0,0,0,1,2},
    	{1,2,0,0,0,7,4,0,0},
    	{0,4,9,2,0,6,0,0,7}
	};
	
	printBoard(board);
	solve(board, 0, 0);
	cout << "successfully solved board!" << std::endl;
	printBoard(board);

	return 0;
}