// ***************************************************************************************
//    Project: Prime Number and Palindrome String Checker
//    File: command_defs.c
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

#include "command_defs.h"
#include "colors.h"
#include "command.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

def_invoke_fn_as(version_fn)
{
    (void)cmd;
    (void)argc;
    (void)argv;

    puts(FG_LRED "Version: 1.0.0" COLOR_RESET);
    puts(FG_LGREEN "Programmed by Navid Dezashibi" COLOR_RESET);
    puts(FG_LGREEN "Built on: "__DATE__
                   " - "__TIME__ COLOR_RESET);
}

bool is_palindrome(char* string)
{
    size_t len = strlen(string);

    if (len == 0)
        return false;

    if (len == 1)
        return true;

    for (int i = 0; i <= len / 2; ++i)
    {
        if (string[i] != string[len - i - 1])
            return false;
    }

    return true;
}

def_invoke_fn_as(check_fn)
{
    (void)cmd;

    do_arg_check(3);

    for (int i = arg_starts_at; i < argc; ++i)
    {
        printf("'%s' -> ", argv[i]);

        char* palindrome = is_palindrome(argv[i]) ? "palindrome" : "Not palindrome";

        printf(FG_LBLUE "%s", palindrome);

        puts(COLOR_RESET);
    }
}

def_invoke_fn_as(file_fn)
{
    do_arg_check(3);

    FILE* file = fopen(argv[arg_starts_at], "r");

    if (file == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "cannot open the file '%s', '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, argv[arg_starts_at], cmd->name, cmd->help);
        exit(-1);
    }

    printf("Processing calculations from '" FG_LGREEN "%s" COLOR_RESET "':\n", argv[arg_starts_at]);

    bool must_fail = false;
    char buffer[MAX_LINE_SIZE];
    // temporary argument holder including 1 executable name, 1 command name, and the rest command arguments
    // and each token has a fixed preserved size
    line_token_t temp_argv;
    int temp_argc;
    double curr_result = 0;
    int curr_line = 1;
    char* curr_tok;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // ./prpal_tool.exe <cmd> args
        // 0           1    2 3 ...
        // we always have 2 args available
        temp_argc = arg_starts_at;

        // Tokenize buffer based on ' ' (whitespace) and get each word separately
        curr_tok = strtok(buffer, WHITE_SPACE);

        if (curr_tok == NULL)
            continue;

        check_argc_size(temp_argc, true);
        check_token_size(curr_tok, true);

        // Allocate memory and copy command to temp_argv[1]
        // temp_argv[0] is supposed to be the executable name
        // and as it's not being used it won't be filled with any data
        strcpy(temp_argv[1], curr_tok);

        // Copy the results for the lines after the first line it will
        // copy the previous result at the top of the arguments
        if (curr_line > 1)
        {
            sprintf(temp_argv[arg_starts_at], "%.2f", curr_result);

            // we've already got an argument from the previous line
            ++temp_argc;
        }

        // Continue tokenization and add the rest of the tokens as arguments
        while (curr_tok != NULL)
        {
            curr_tok = strtok(NULL, WHITE_SPACE);
            if (curr_tok != NULL)
            {
                check_argc_size(temp_argc, true);
                check_token_size(curr_tok, true);

                strcpy(temp_argv[temp_argc], curr_tok);
                ++temp_argc;
            }
        }

        printf("line %d) ", curr_line);

        Command* cmd = get_command(temp_argv[1]);
        if (cmd == NULL)
        {
            printf(FG_RED "error: " COLOR_RESET "command '%s' not found\n", temp_argv[1]);
            show_help();
            must_fail = true;
            goto cleanup;
        }

        cmd->invoke(cmd, temp_argc, temp_argv);

        ++curr_line;
    }

cleanup:
    if (file)
        fclose(file);

    if (must_fail)
        exit(-1);
}