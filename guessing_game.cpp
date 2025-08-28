/*
No global variables. (Global constants are all right.)
No strings. Not ever.
You should include <iostream>, not stdio.
Use new and delete instead of malloc and free.
Avoid using a mouse. Learn the shortcuts.
Only use break/continue if you must, like in switch statements.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
  srand(time(NULL));
  bool alive = true;
  
  while (alive) {
    int number = (rand() % 101);
    int guess;
    int guess_count = 0;
    int leave;
    bool solved = false;
    
    while (not solved) {
        // First, get the guess of the player and increment the count
	std::cout << "Guess a number! (between 0 - 100) > ";
	std::cin >> guess;
	std::cout << std::endl;
	++guess_count;

	// Second, compare the guess to the chosen number
	if (guess > number) { std::cout << "Your guess was too high! "; }
	else if (guess < number) { std::cout << "Your guess was too low! "; }
	else { std::cout << "Great work! You guessed the correct number in: " << guess_count << " guesses."; solved = true; }
    }

    // Ask player if they want to play again through numeric input
    std::cout << "If you want to continue playing, type '0'. If not, type literally any other number. > ";
    std::cin >> leave;
    if (leave != 0) { alive = false; }
  }
  
  return 0;
}
