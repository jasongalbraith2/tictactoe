#include <iostream>

// Global dimension variables
const unsigned int ROWS = 3;
const unsigned int COLS = 3;

// Function to print out the board
void printBoard(char** positions) {
  // Clear screen and print header
  //std::cout << "\033[H\033[J    A | B | C \n";

  // Print rows
  for (int i = 0; i < ROWS; ++i) {
    std::cout << "   ---|---|---\n";
    std::cout << " " << i << "  " << positions[i][0] << " | " << positions[i][1] << " | " << positions[i][2] << "\n";
  }
  
  // Add spacing for input text
  std::cout << "\n\n";
}

bool check_for_draw(char** positions) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      if (positions[i][j] == ' ') { return false; }
    }
  }
  return true;
}

bool check_for_win(char** positions) {
  // Check for a horizontal win
  char initialChar;
  bool match = true;

  // Scan across each row and check if the initial character matches the next two.
  for (int i = 0; i < ROWS; ++i) {
    initialChar = positions[i][0];
    if (initialChar != ' ') {
      for (int j = 1; j < COLS; ++j) {
	if (initialChar != positions[i][j]) {
	  match = false;
	}
      }
      if (match) { return true; }
    }
  }

  // Scan across each column and check if the initial character matches the next two.
  match = true;
  for (int i = 0; i < COLS; ++i) {
    initialChar = positions[0][i];
    if (initialChar != ' ') {
      for (int j = 0; j < ROWS; ++j) {
	if (initialChar != positions[j][i]) {
	  match = false;
	}
      }
      if (match) { return true; }
    }
  }

  // Scan across each diagonal..
  // Left up to right down (LU-RD)
  match = true;
  initialChar = positions[0][0];
  if (initialChar != ' ') {
    for (int i = 1; i < ROWS; ++i) {
      if (initialChar != positions[i][i]) {
	match = false;
      }
    }
    if (match) { return true; }
  }

  // Right up to left down (RU-LD)
  match = true;
  initialChar = positions[ROWS - 1][0];
  if (initialChar != ' ') {
    for (int i = ROWS - 2; i >= 0; --i) {
      if (initialChar != positions[i][i]) {
	match = false;
      }
    }
    if (match) { return true; }
  }

  return false;
}

int main() {
  char** positions = new char*[ROWS];
  char toPlace[3];

  // Loop variables that infer results
  bool running = true;
  bool hasWon = false;
  bool player1 = true;

  // Variables for converting input to position selection
  unsigned int columnChoice;
  unsigned int rowChoice;

  // Post game result
  unsigned int player1Wins = 0;
  unsigned int player2Wins = 0;
  char playAgain;

  // Allocate memory and assign white space
  for (int i = 0; i < ROWS; ++i) {
    positions[i] = new char[COLS];
    for (int j = 0; j < COLS; ++j) {
      positions[i][j] = ' ';
    }
  }

  while (running) {

    // Each game of tictactoe
    hasWon = false;
    player1 = true;
    while (not hasWon) {
      // Print the board to the user
      printBoard(positions);

      std::cout << "It is " << ((player1) ? "PLAYER 1" : "PLAYER 2") << "\'s turn.\nPlease input the column followed by the row (e.x. a1, b3) > "; 
      std::cin >> toPlace;

      // Lowercase the input, then use ascii conversion to check to see if it is within the range
      // Also, convert the row choice to an actual integer
      columnChoice = std::tolower(toPlace[0]) - 'a';
      rowChoice = toPlace[1] - '0';
      if (columnChoice > 2 or rowChoice > 2) {
	std::cout << "\nInvalid column or row choice. Please try again. (press any key to continue)\n";
	std::cin.ignore(10000, '\n');
	std::cin.get();
      }
      else {
	
	// Now, check to see if the space is already taken
	if (positions[rowChoice][columnChoice] != ' ') {
	  std::cout << "\nYour selection is already filled, try another spot. (press any key to continue)\n";
	  std::cin.ignore(10000, '\n');
	  std::cin.get();
	}
	else {

	  // The space is open!! Now, assign the player's piece to this spot.
	  positions[rowChoice][columnChoice] = (player1) ? 'X' : 'O';
	  
	  // Check for win or draw
	  if (check_for_win(positions)) {
	    hasWon = true;
	    printBoard(positions);

	    // Add wins to the player
	    if (player1) { ++player1Wins; }
	    else { ++player2Wins; }

	    std::cout << "CONGRATULATIONS TO " << ((player1) ? "PLAYER 1" : "PLAYER 2") << "!!!\n";
	    std::cout << "Player 1 has " << player1Wins << " wins and Player 2 has " << player2Wins << "!\n";
	  }
	  else {
	    player1 = not player1;
	  }
	}
      }
    }

    std::cout << "\nWould you like to play again (y/n) > ";
    std::cin >> playAgain;
    if (playAgain != 'y') {
      running = false;
    }
  }

  // Deallocate memory
  for (int i = 0; i < ROWS; ++i) {
    delete [] positions[i];
  }
  delete [] positions;
  
  return 0;
}
