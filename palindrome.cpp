#include <iostream>
#include <cstring>
#include <cctype>

int main()
{
  // Variables
  char input_string[80];
  char final_string[80];
  char flipped_string[80];
  char punctuation[] = ".,;:!`'\"()";
  unsigned int punc_count = sizeof(punctuation) / sizeof(punctuation[0]);

  // Read in the input
  std::cout << "Enter some text > ";
  std::cin.getline(input_string, 80);

  // Remove spaces and punctuation
  unsigned int index = 0;
  bool null_terminator = false;
  for (int i = 0; i < 80; ++i) {

    // First, check if the string is terminated
    if (not null_terminator and input_string[i] == '\0') {
      null_terminator = true;
    }

    // If the string is not over
    if (not null_terminator) {
      bool invalid_char = false;

      // Check if there is any punctuation.
      for (int j = 0; j < punc_count; ++j) {
	if (input_string[i] == punctuation[j]) {
	  invalid_char = true;
	}
      }

      // Check if there is a space
      if (not invalid_char and input_string[i] == ' ') {
	invalid_char = true;
      }

      // If the character is not excluded, add it to the finished string
      if (not invalid_char) {
	// Set the current char to a lower
	final_string[index] = std::tolower(input_string[i]);
	++index;
      }
    }
  }

  // Now, check to see if the string is a palindrome
  // First, we need to reverse the array
  for (int i = 0; i < index; ++i) {
    flipped_string[(index - i - 1)] = final_string[i];
  }

  // Second, read through both arrays and determine if the characters match
  bool matched = true;
  for (int i = 0; i < index; ++i) {
    if (matched and final_string[i] != flipped_string[i]) { matched = false; }
  }

  if (matched) {
    std::cout << "\nPalindrome.";
  }
  else {
    std::cout << "\nNot a palindrome.";
  }
  
  return 0;
}
