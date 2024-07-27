// ***************************************************************************************
//    Project: Prime Number and Palindrome String Checker
//    File: command.c
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

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "global.h"

#include "command.h"

#include "colors.h"

Command* get_command(char* name)
{
    assert(commands_size > 0 && "There is no command defined");

    Command* cmd = NULL;

    for (size_t i = 0; i < commands_size; ++i)
    {
        if (strcmp(name, commands[i].name) == 0)
        {
            cmd = &commands[i];
            break;
        }
    }

    return cmd;
}

void show_help()
{
    assert(commands_size > 0 && "There is no command defined");

    puts(FG_GREEN "available commands:" COLOR_RESET);

    for (size_t i = 0; i < commands_size; ++i)
    {
        printf("\t" FG_LGREEN "%s" COLOR_RESET " -> " FG_LBLUE "%s\n" COLOR_RESET, commands[i].name, commands[i].help);
    }
}