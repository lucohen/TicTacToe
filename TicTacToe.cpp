#include <iostream>
#include <tuple>

class TicTacToeGame {

public:
  TicTacToeGame();
  virtual ~TicTacToeGame();

  void play();

private:
  void initializeGrid();
  void displayGrid();
  std::tuple<int, int> findFirstUnoccupiedGridSquare();
  std::tuple<int, int> promptForGridCoord();
  bool checkForDraw();
  bool checkForWin();

private:
  char **pp_cGrid = nullptr;
};

TicTacToeGame::TicTacToeGame() {
  this->pp_cGrid = new char *[3];

  for (int iRow = 0; iRow < 3; ++iRow)
    pp_cGrid[iRow] = new char[3];

  initializeGrid();
}

TicTacToeGame::~TicTacToeGame() {
  for (int iRow = 0; iRow < 3; iRow++) {
    delete[] pp_cGrid[iRow];
  }
  delete[] pp_cGrid;
  pp_cGrid = nullptr;
}

void TicTacToeGame::initializeGrid() {
  for (int iRow = 0; iRow < 3; iRow++) {
    for (int iCol = 0; iCol < 3; iCol++) {
      this->pp_cGrid[iRow][iCol] = '~';
    }
  }
}

void TicTacToeGame::displayGrid() {
  for (int iRow = 0; iRow < 3; ++iRow) {
    for (int iCol = 0; iCol < 3; ++iCol) {
      std::cout << this->pp_cGrid[iRow][iCol] << " ";
    }
    std::cout << std::endl;
  }
}

void TicTacToeGame::play() {
  bool bWin = false;
  bool bDraw = false;
  bool filled = true;
  int iRow = 0;
  int iColumn = 0;

  std::cout << "Tic Tac Toe" << std::endl;
  std::cout << std::endl;

  displayGrid();
  while (!bWin && !bDraw) {
    while (filled) {
    std::tie(iRow, iColumn) = promptForGridCoord();
      if (this->pp_cGrid[iRow][iColumn] == '~')
      {this->pp_cGrid[iRow][iColumn] = 'X';
      filled = false;}
      else
        std::cout << "That grid square is already filled. Try again." << std::endl;
    }
    filled = true;

    displayGrid();
    std::cout << std::endl;
    bWin = checkForWin();
    bDraw = checkForDraw();

    if (!bWin and !bDraw) {
      std::tie(iRow, iColumn) = findFirstUnoccupiedGridSquare();
      this->pp_cGrid[iRow][iColumn] = 'O';

      displayGrid();
      std::cout << std::endl;
      bWin = checkForWin();
      bDraw = checkForDraw();
    }

    if (bDraw && !bWin) {
      std::cout << "Draw!" << std::endl;
    }
  }
  std::cout << "Game over." << std::endl;
}

bool TicTacToeGame::checkForDraw() {
  bool bContinue = false;
  for (int iRow = 0; iRow < 3; ++iRow) {
    for (int iColumn = 0; iColumn < 3; ++iColumn) {
      if (this->pp_cGrid[iRow][iColumn] != 'X' &&
          this->pp_cGrid[iRow][iColumn] != 'O') {
        bContinue = true;
      }
    }
  }
  return !bContinue;
}

std::tuple<int, int> TicTacToeGame::promptForGridCoord() {
  int iRow = 0;
  int iColumn = 0;
  bool goodRow = false;
  bool goodCol = false;

  while (goodRow == false) {
  std::cout << "Enter row: " << std::endl;
  std::cin >> iRow;
    if (iRow > 2 || iRow < 0) {
      std::cout << "Enter 0, 1, or 2." << std::endl;
    } 
    else {
      goodRow = true;
    }
  }
  while (goodCol == false) {
  std::cout << "Enter Column: " << std::endl;
  std::cin >> iColumn;
    if (iColumn > 2 || iColumn < 0) {
      std::cout << "Enter 0, 1, or 2." << std::endl;
    } 
    else {
      goodCol = true;
    }
  }

  std::tuple<int, int> tupleCoord = std::make_tuple(iRow, iColumn);

  return tupleCoord;
}

std::tuple<int, int> TicTacToeGame::findFirstUnoccupiedGridSquare() {
  int iRowUnoccupied = -1;
  int iColumnUnoccupied = -1;

  bool bFound = false;
  for (int iRow = 0; (iRow < 3) && !bFound; ++iRow) {
    for (int iColumn = 0; (iColumn < 3) && !bFound; ++iColumn) {
      if (this->pp_cGrid[iRow][iColumn] == '~') {
        iRowUnoccupied = iRow;
        iColumnUnoccupied = iColumn;
        bFound = true;
      }
    }
  }

  std::tuple<int, int> tupleUnoccupiedGridSquare(iRowUnoccupied,
                                                 iColumnUnoccupied);
  return tupleUnoccupiedGridSquare;
}

bool TicTacToeGame::checkForWin() {
  bool bWin = false;

  for (int iRow = 0; iRow < 3; ++iRow) {
    if (this->pp_cGrid[iRow][0] != '~') {
      if ((this->pp_cGrid[iRow][0] == this->pp_cGrid[iRow][1]) &&
          (this->pp_cGrid[iRow][0] == this->pp_cGrid[iRow][2])) {
        bWin = true;
        std::cout << "WINNER: " << this->pp_cGrid[iRow][0] << "!" << std::endl;
      }
    }
  }

  for (int iColumn = 0; iColumn < 3; ++iColumn) {
    if (this->pp_cGrid[0][iColumn] != '~') {
      if ((this->pp_cGrid[0][iColumn] == this->pp_cGrid[1][iColumn]) &&
          (this->pp_cGrid[0][iColumn] == this->pp_cGrid[2][iColumn])) {
        bWin = true;
        std::cout << "WINNER: " << this->pp_cGrid[0][iColumn] << "!"
                  << std::endl;
      }
    }
  }

  
    if (this->pp_cGrid[0][0] != '~') {
      if ((this->pp_cGrid[0][0] == this->pp_cGrid[1][1]) &&
          (this->pp_cGrid[0][0] == this->pp_cGrid[2][2])) {
        bWin = true;
        std::cout << "WINNER: " << this->pp_cGrid[0][0] << "!" << std::endl;
      }
    }
  

  
    if (this->pp_cGrid[0][2] != '~') {
      if ((this->pp_cGrid[0][2] == this->pp_cGrid[1][1]) &&
          (this->pp_cGrid[0][2] == this->pp_cGrid[2][0])) {
        bWin = true;
        std::cout << "WINNER: " << this->pp_cGrid[0][2] << "!" << std::endl;
      }
    }
  
  return bWin;
}

int main() {
  TicTacToeGame *p_game = new TicTacToeGame();

  p_game->play();

  delete p_game;
  p_game = nullptr;
}