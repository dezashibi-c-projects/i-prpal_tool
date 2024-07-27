# Prime Number and Palindrome String Checker

Prime Number and Palindrome String Checker cli tool in C

- **User Story:** As an intermediate learner, I want to create a program that checks if a given string is a palindrome then checks if a given number is a prime number, too. It can load strings separated by space from a file, then checks for `palindrome` strings first and if the string is a number check for the `prime` number as well. and gives user proper report or save the report in a different file.
- **Expected Result:** The program outputs whether the string is palindrome or not and if the string is a number will add whether the number is prime or not as well.
- **Concepts:** Loops, conditional statements, functions, strings, read/write files.

## Implementation

I can use some codes from [this project of mine](https://github.com/dezashibi-c-projects/b-calculator) to bootstrap some codes in my project.

- I can use my `Makefile` it's pretty much good and handy
- I can use `command.h`, `command.c`, the `main.c` itself and `colors.h`

This is also another CLI tool, it tokenize the given string let it be a line from a file or direct input and will tell if the chunks from the input are palindrome first then if they can be converted into an integer number it will check also for prime numbers as well.

Output: `'<string>' -> [not] palindrome, [not] prime`

## Commands

- `check` check the input based on argument passed to the program and shows the result on screen
- `file` gets the file name and read and process line by line and saves the result in the `filename_output.ext`

## Memory Management

I would say this program just like the [previous one](https://github.com/dezashibi-c-projects/b-calculator) has limitations for sure, I might tweak limitations later on but for now I will leave the
limitation constants as they are.

So, the TL;DR; is that number of entries per line and number of character per each entry is limited. The lesson here again is not to be shy when introducing limitations and also don't be afraid
to use fixed amount of memory especially when the program is supposed to end in a short amount of time.

## External variables aka Globally accessible variables

I've made a change in the way command works, there is a fact here and that is the `commands` and `command_size` are almost needed for the entire program lifetime, so instead of passing them around which makes
functions always have to accept two extra arguments, this time I've defined them to be accessible globally first by removing `static` keyword from their definitions, then I've added the file `global.h` with the
following content which allows other `C` files to treat to these identifiers as they are already defined and initialized because **"we're sure"** that later on after compiler linked all the object files together, there will be such a symbol to be used.

```c
#ifndef GLOBAL__H__
#define GLOBAL__H__

#include "command.h"
#include <stddef.h>

extern def_commands;
extern def_commands_size;

#endif // GLOBAL__H__
```

**By the way** I've just played around with `def_commands` and `def_commands_size` definitions in `command.h` to tweak them for my needs, it's not a big change though.
