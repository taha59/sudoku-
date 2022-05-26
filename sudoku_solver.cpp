/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
    returns true if the given value can be inserted in the given cell
    otherwise returns false
*/
bool valid_placement(vector < vector < int > > &board, int row, int col, int num){
    
    int i, j;
    for (i = 0; i < 9; i++){

        //check rows
        if (board[row][i] == num)
            return false;

        //check cols
        if (board[i][col] == num)
            return false;
    }
    
    //check subgrids
    int sq_row = int(row/3) * 3;
    int sq_col = int(col/3) * 3;

    for (i = sq_row; i < sq_row + 3; i++){
        for (j = sq_col; j < sq_col + 3; j++){
            if (board[i][j] == num)
                return false;
        }
    }
    
    //if number can be legally placed
    return true;
}

/*
    returns an index pair of a cell that is empty
    Example: 920
             001
             234
             
    In this case the row is 0 and col is 2 so (02) would be returned
    
    if there is no empty cell the string "END" is returned
*/

string find_empty_cell(vector < vector < int > > &board){
    int row = 0, col = 0;
    
    while(board[row][col]!= 0){
        col += 1;

        if (col == 9){
            row += 1;
            col = 0;
        }
            
        if (row == 9){
            return "END";
        }
    }
    
    return to_string(row) + to_string(col);
}

/*
    recursive function for solving the sudoku
*/
bool sudoku_solve(vector < vector < int > > &board){
    string s = find_empty_cell(board);
    if (s == "END")
        return true;
        
    int row = s[0] - '0';
    int col = s[1] - '0';
    
    int i;
    
    //insert in empty cells only
    for (i = 1; i < 10; i++){
           
        //if the number can be inserted
        if (valid_placement(board, row, col, i) == true){
            board[row][col] = i;

            if (sudoku_solve(board) == true)
                return true;
            else
                board[row][col] = 0;
        }
    }
    return false;
}

// pretty prints the sudoku board
void display_board(vector < vector < int > > &board){
    for (int i = 0; i < 9; i++){
        if (i % 3 == 0){
            cout << "|-----------------------|" << endl;
            cout << "| ";
        }
        else
            cout << "| ";
            
        for (int j =0; j < 9; j++){
            if (j % 3 == 0 && j != 0){
                cout << "| ";
            }
            cout << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "|-----------------------|" << endl;
}

int main(){
    
    ifstream file("input.txt");
    string line;
    
    vector < vector < int > > board;
    
    while(getline(file, line)){
        
        vector <int> temp(9, 0);
        
        for (int i = 0; i < 9; i++){
            temp[i] = int(line[i]) - '0';
        }
        
        board.push_back(temp);
    }
    
    if (sudoku_solve(board) == true)
        display_board(board);
    else
        cerr << "Not solvable";
    
    return 0;
}