// === Region: Project Declaration ===
//
//  COMP2011 Fall 2024
//  PA2: Simpified MineSweeper Game Using Recursion
//
//  Your name: Saanvi Shukla
//  Your ITSC email: sshukla@connect.ust.hk
//
//  Note: Generative AI is NOT allowed in completing your lab exercises or programming assignments
//  Reference: https://course.cse.ust.hk/comp2011/web/code.html
//
//  Declaration:
//  I declare that I am not involved in plagiarism
//  I understand that both parties (i.e., students providing the codes and students copying the codes) will receive 0 marks.
//
//  Project TA:  BAI, Sikai (sbaiae@connect.ust.hk)
//
//  For code-level questions, please send a direct email to the above TA.
//  Asking questions with code blocks in a public discussion forum (e.g., Piazza) may cause plagiarism issues
//  Usually, you will get the quickest response via a direct email.
//
//  Possible usage of the program:
//
//  Method 1: You can display the output on the terminal
//
//  Mac/Linux: ./pa2 < testcase/inputX.txt
//  Windows  :  Get-Content testcase/inputX.txt | ./pa2
//
//  Method 2: You can redirect the output to a text file, and then open the text file for checking
//
//  Mac/Linux: ./pa2 < testcase/inputX.txt > myOutputX.txt
//  Winodws  :  Get-Content testcase/inputX.txt | ./pa2 > myOutputX.txt
//
// =====================================
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_ROWS = 20;
const int MAX_COLS = 30;

const char CELL_EMPTY = '.';
const char CELL_MINE = '*';
const char CELL_EMPTY_EXPLORED = ' ';

enum GameOptionType
{
    GAME_OPTION_EXIT = 0,
    GAME_OPTION_LOAD_INPUT,
    GAME_OPTION_MAKE_MOVE,
    MAX_GAME_OPTION
};
const char *GAME_OPITION_TEXT[] = {
    "Exit the Game",
    "Load mine map",
    "Make a move"};


bool isValidRowCol(int row, int col, int numRows, int numCols)
{
    return (row >= 0) && (row < numRows) && (col >= 0) && (col < numCols);
}


void displayGameOptionMenu()
{
    int maxGameOption = int(MAX_GAME_OPTION);
    cout << "== Game Menu ==" << endl;
    for (int i = 0; i < maxGameOption; i++)
    {
        cout << i << ": " << GAME_OPITION_TEXT[i] << endl;
    }
}

// === Start the recursion coding tasks for PA2 ===

// TODO: Implement fillMapUsingRecursion
// This function fills in a 2D array with the input character in a given range using recursion
// Note: You MUST USE recursion to implement this function
// 0 marks will be given if you use loops to implement this function 
//
// @param map: The 2D array storing the map information
// @param startRow: The start row index
// @param startCol: The start column index
// @param endRow: The end row index
// @param endCol: The end column index
// @param initChar: The character to fill the 2D array
void fillMapUsingRecursion(char map[MAX_ROWS][MAX_COLS], int startRow, int startCol, int endRow, int endCol, char initChar)
{
    if (startCol>endCol||startRow>endRow)
    {
    return;
    }
    map[startRow][startCol]=initChar;
    if (startCol<endCol) 
    {
    fillMapUsingRecursion(map,startRow,startCol+1,endRow,endCol,initChar);
    }
    else if (startRow<endRow)
    {
        fillMapUsingRecursion(map,startRow+1,0,endRow,endCol,initChar);
    }
    
}

// TODO: Implement countCharFromMapUsingRecursion
// This function counts the number of characters in a 2D array in a given range using recursion
// Note: You MUST USE recursion to implement this function
// 0 marks will be given if you use loops to implement this function 
//
// @param map: The 2D array storing the map information
// @param startRow: The start row index
// @param startCol: The start column index
// @param endRow: The end row index
// @param endCol: The end column index
// @param ch: The character to be counted from the 2D array
int countCharFromMapUsingRecursion(const char map[MAX_ROWS][MAX_COLS], int startRow, int startCol, int endRow, int endCol, char ch)
{
    if (startRow>endRow||startCol>endCol)
    {
        return 0;
    }
    int count;
    if (map[startRow][startCol]==ch)
    {
        count=1;
    }else
    {
        count=0;
    }
    if (startCol<endCol)
    {
        count+=countCharFromMapUsingRecursion(map,startRow,startCol+1,endRow,endCol,ch);
    } else if (startRow<endRow) 
    {
        count+=countCharFromMapUsingRecursion(map,startRow+1,0,endRow,endCol,ch);
    }
   return count;
}


// TODO: Implement countCharFromMapUsingRecursion
// This function explores (i.e., updates) the current map 
// Note: You MUST USE recursion to implement this function
// 0 marks will be given if you use loops to implement this function 
//
// @param realMap: The 2D array storing the real map information
// @param currentMap: The 2D array storing the current map (i.e., the exploring map) information
// @param numRows: The number of rows for the maps (both maps have the same size)
// @param numCols: The number of columns for the maps (both maps have the same size)
// @param row: The row index to explore
// @param col: The col index to explore

int adjacentcount(const char realMap[MAX_ROWS][MAX_COLS],int numRows,int numCols,int row,int col)
    {
    if (!isValidRowCol(row,col,numRows,numCols))
    {
        return 0;
    }

    if (realMap[row][col]==CELL_MINE)
    {
        return 1 ;
    }
    else {
        return 0;
    }
}

void exploreMapUsingRecursion(const char realMap[MAX_ROWS][MAX_COLS],char currentMap[MAX_ROWS][MAX_COLS],
                              int numRows,int numCols,int row,int col) {
    if(!isValidRowCol(row,col,numRows,numCols))
    {
        return;
    }
    if (currentMap[row][col]!=CELL_EMPTY)
    {
        return; 
    }
    if (realMap[row][col]==CELL_MINE)
    {
        return; 
    }

    

    int count=adjacentcount(realMap,numRows,numCols,row-1,col)+adjacentcount(realMap,numRows,numCols,row+1,col)+adjacentcount(realMap,numRows,numCols,row,col-1)+adjacentcount(realMap,numRows,numCols,row,col+1)+adjacentcount(realMap,numRows,numCols,row-1,col-1)+adjacentcount(realMap,numRows,numCols,row-1,col+1)+adjacentcount(realMap,numRows,numCols,row+1,col-1)+adjacentcount(realMap,numRows,numCols,row+1,col+1);   

    if(count>0)
    {
        currentMap[row][col]=count+'0';
    }
    else
    {
        currentMap[row][col]=CELL_EMPTY_EXPLORED; 
        
        
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row-1,col-1); 
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row-1,col);     
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row-1,col+1);
        
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row,col-1);     
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row,col+1);   
        
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row+1,col-1);
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row+1,col);     
        exploreMapUsingRecursion(realMap,currentMap,numRows,numCols,row+1,col+1); 
    }

                              }




void displayMap(char map[MAX_ROWS][MAX_COLS], int numRows, int numCols)
{
    int r, c;

    // display column numbers
    cout << "  ";
    for (c = 0; c < numCols; c++)
        cout << c % 10 << " ";
    cout << endl;

    // display map and row numbers (on the left)
    for (r = 0; r < numRows; r++)
    {
        cout << r % 10 << " ";
        for (c = 0; c < numCols; c++)
            cout << map[r][c] << " ";
        cout << endl;
    }
}

void handleLoadMap(char realMap[MAX_ROWS][MAX_COLS], char currentMap[MAX_ROWS][MAX_COLS],
                   int &numRows, int &numCols)
{

    char filename[100];
    int r, c;

    cout << "Enter the map file name: ";
    cin >> filename;
    fstream fin(filename);
    fin >> numRows >> numCols;

    // Fill both the realMap and currentMap as CELL_EMPTY
    fillMapUsingRecursion(realMap, 0, 0, numRows - 1, numCols - 1, CELL_EMPTY);
    fillMapUsingRecursion(currentMap, 0, 0, numRows - 1, numCols - 1, CELL_EMPTY);

    fin.ignore(); // ignore and move to the next line, start to read the map characters

    for (r = 0; r < numRows; r++)
    {
        for (c = 0; c < numCols; c++)
        {
            fin >> realMap[r][c];
        }
    }
    fin.close();
}



bool handleMakeMove(char realMap[MAX_ROWS][MAX_COLS], char currentMap[MAX_ROWS][MAX_COLS],
                    int numRows, int numCols)
{
    int row, col;

    cout << "Enter your move (row column): ";
    cin >> row >> col;

    if (!isValidRowCol(row, col, numRows, numCols))
    {
        cout << "Error: Invalid row/column: " << row << " " << col << endl;
        return false;
    }

    if (realMap[row][col] == CELL_MINE)
    {
        cout << "Game over: hit a mine at row/column: " << row << " " << col << endl;
        return true;
    }

    if (currentMap[row][col] != CELL_EMPTY)
    {
        cout << "Error: The cell row/column is explored: " << row << " " << col << endl;
        return false;
    }

    exploreMapUsingRecursion(realMap, currentMap, numRows, numCols, row, col);
    cout << "Success: Explore the current map at row/column: " << row << " " << col << endl;
    cout << "The current map: " << endl;
    displayMap(currentMap, numRows, numCols);
    return false;
}

bool checkGameWin(char realMap[MAX_ROWS][MAX_COLS], char currentMap[MAX_ROWS][MAX_COLS],
                  int numRows, int numCols)
{
    // count the number of mines from the real map
    int countMines = countCharFromMapUsingRecursion(realMap, 0, 0, numRows-1, numCols-1, CELL_MINE);

    // count the number of empty cells in the current map
    int countEmpty = countCharFromMapUsingRecursion(currentMap, 0, 0, numRows-1, numCols-1, CELL_EMPTY);

    cout << "The total number of mines in the real map is: " << countMines << endl;
    cout << "The total number of empty cells in the current map is: " << countEmpty << endl;

    // End the game if both numbers are equal
    return countMines == countEmpty;
}

int main()
{

    int inputOption;
    GameOptionType gameOption;
    bool gameFinish = false;
    char realMap[MAX_ROWS][MAX_COLS];
    char currentMap[MAX_ROWS][MAX_COLS];
    int numRows, numCols;

    numRows = numCols = 0;

    while (!gameFinish)
    {
        displayGameOptionMenu();
        cout << "Enter your option: ";
        cin >> inputOption;
        gameOption = GameOptionType(inputOption);
        switch (gameOption)
        {
        case GAME_OPTION_EXIT:
            gameFinish = true;
            break;
        case GAME_OPTION_LOAD_INPUT:
            handleLoadMap(realMap, currentMap, numRows, numCols);
            cout << "The real map: " << endl;
            displayMap(realMap,numRows, numCols);
            cout << "The current map: " << endl;
            displayMap(currentMap, numRows, numCols);
            break;
        case GAME_OPTION_MAKE_MOVE:
            gameFinish = handleMakeMove(realMap, currentMap, numRows, numCols);
            if (!gameFinish)
            {
                if (checkGameWin(realMap, currentMap, numRows, numCols))
                {
                    cout << "Game finished! All non-mine cells are explored!" << endl;
                    gameFinish = true;
                }
            }
            break;
        default:
            cout << "Unsupported option: " << inputOption << endl;
        }
    }

    return 0;
}