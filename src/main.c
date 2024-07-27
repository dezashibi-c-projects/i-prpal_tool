// ***************************************************************************************
//    Project: Prime Number and Palindrome String Checker
//    File: main.c
//    Date: 2024-07-26
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: refer to readme file.
// ***************************************************************************************

#include "colors.h"
#include "command.h"
#include "command_defs.h"
#include "global.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

def_commands = {
    {"version", "shows version and build information", version_fn},
    {"check", "checks if a given string is a palindrome and if the given string is also an integer number then checks if the given number is a prime number, too.", check_fn},
    {"file", "opens the given file, runs checks on each line, creates a report file from the name of the input file and writes the result in it", file_fn},
};
def_commands_size = (sizeof(commands) / sizeof(commands[0]));

int main(int argc, char* argv[])
{
    puts("CLI Prime Number and Palindrome String Checker");

    if (argc < 2)
    {
        puts(FG_RED "error: " COLOR_RESET "not enough number of arguments\n\t" FG_GREEN "./prpal_tool.exe <op> <...args>\n" COLOR_RESET);

        show_help();

        return -1;
    }

    Command* cmd = get_command(argv[1]);

    if (cmd == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "command '%s' not found\n", argv[1]);

        show_help();

        return -1;
    }

    line_token_t temp_argv;
    bool must_fail = false;

    check_argc_size(argc, false);

    for (int i = 0; i < argc; ++i)
    {

        check_token_size(argv[i], false);

        strcpy(temp_argv[i], argv[i]);
    }

    if (must_fail)
        return -1;

    cmd->invoke(cmd, argc, temp_argv);

cleanup:
    return 0;
}
