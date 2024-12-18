
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
    cout << "  ";
    for (c = 0; c < numCols; c++)
        cout << c % 10 << " ";
    cout << endl;
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

    
    fillMapUsingRecursion(realMap, 0, 0, numRows - 1, numCols - 1, CELL_EMPTY);
    fillMapUsingRecursion(currentMap, 0, 0, numRows - 1, numCols - 1, CELL_EMPTY);

    fin.ignore(); 

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
  
    int countMines = countCharFromMapUsingRecursion(realMap, 0, 0, numRows-1, numCols-1, CELL_MINE);

    
    int countEmpty = countCharFromMapUsingRecursion(currentMap, 0, 0, numRows-1, numCols-1, CELL_EMPTY);

    cout << "The total number of mines in the real map is: " << countMines << endl;
    cout << "The total number of empty cells in the current map is: " << countEmpty << endl;

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