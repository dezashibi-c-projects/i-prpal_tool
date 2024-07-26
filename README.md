# Prime Number and Palindrome String Checker

Prime Number and Palindrome String Checker cli tool in C

- **User Story:** As an intermediate learner, I want to create a program that checks if a given string is a palindrome then checks if a given number is a prime number, too. It can load strings separated by space from a file, then checks for `palindrome` strings first and if the string is a number check for the `prime` number as well. and gives user proper report or save the report in a different file.
- **Expected Result:** The program outputs whether the number is prime or not.
- **Concepts:** Loops, conditional statements, functions, strings, read/write files.

## Implementation

I can use some codes from [this project of mine](https://github.com/dezashibi-c-projects/b-calculator) to bootstrap some codes in my project.

- I can use my `Makefile` it's pretty much good and handy
- I can use `command.h`, `command.c`, the `main.c` itself and `colors.h`

This is also another CLI tool, it tokenize the given string let it be a line from a file or direct input and will tell if the chunks from the input are palindrome first then if they can be converted into an integer number it will check also for prime numbers as well.

Output: `'<string>' -> [not] palindrome`, `[not] prime`
