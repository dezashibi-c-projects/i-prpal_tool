# Prime Number and Palindrome String Checker

Prime Number and Palindrome String Checker cli tool in C

- **User Story:** As an intermediate learner, I want to create a program that checks if a given string is a palindrome and if the given string is also an integer number then checks if the given number is a prime number, too. It can load strings separated by space from a file, then checks for `palindrome` strings first and if the string is a number check for the `prime` number as well. and gives user proper report or save the report in a different file.
- **Expected Result:** The program outputs whether the string is palindrome or not and if the string is a number will add whether the number is prime or not as well.
- **Concepts:** Loops, conditional statements, functions, strings, read/write files.

## Implementation

I can use some codes from [this project of mine](https://github.com/dezashibi-c/b-calculator) to bootstrap some codes in my project.

- I can use my `Makefile` it's pretty much good and handy
- I can use `command.h`, `command.c`, the `main.c` itself and `colors.h`

This is also another CLI tool, it tokenize the given string let it be a line from a file or direct input and will tell if the chunks from the input are palindrome first then if they can be converted into an integer number it will check also for prime numbers as well.

Output: `'<string>' -> [not] palindrome, [not] prime`

## Commands

- `check` check the input based on argument passed to the program and shows the result on screen
- `file` gets the file name and read and process line by line and saves the result in the `filename_output.ext`

## Memory Management

I would say this program just like the [previous one](https://github.com/dezashibi-c/b-calculator) has limitations for sure, I might tweak limitations later on but for now I will leave the
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

## `void` in parameter section of function definitions -> `void fn(void)`

Here is an interesting thing that happened and remind me that I can talk about it here, some may ask what's the difference between the following definitions?

```c
int fn();

int fn(void);

```

The answer is while they act the same but during the compilation they are not the same. I've changed the signature of `show_help` from `show_help(commands, commands_size)` to `show_help()`
and I've forgot to update their calls in `main.c`, the program compiled, ran with no problem, why? because in `C` there is something called variable argument list which means you can
pass any number of argument of a same type and then access them like an array inside the function body.

So the point is to tell compiler that **"Hey I'm sure there are no parameter anymore and don't accept any"** we can specify that by adding `void` keyword when defining the function.

And then if we try to compile again this is what we'll get:

```bash
src/main.c: In function ‘main’:
src/main.c:42:9: error: too many arguments to function ‘show_help’
   42 |         show_help(commands, commands_size);
      |         ^~~~~~~~~
In file included from src/main.c:17:
src/command.h:125:6: note: declared here
  125 | void show_help(void);
      |      ^~~~~~~~~
src/main.c:53:9: error: too many arguments to function ‘show_help’
   53 |         show_help(commands, commands_size);
      |         ^~~~~~~~~
src/command.h:125:6: note: declared here
  125 | void show_help(void);
      |      ^~~~~~~~~
make: *** [Makefile:54: obj/main.o] Error 1

```

## License

Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0) License.

Please refer to [LICENSE](/LICENSE) file.
