// ***************************************************************************************
//    Project: Prime Number and Palindrome String Checker
//    File: command_defs.c
//    Date: 2024-07-26
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE input_file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: refer to readme input_file.
// ***************************************************************************************

#include "command_defs.h"
#include "colors.h"
#include "command.h"
#include "utils.h"
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

def_invoke_fn_as(check_fn)
{
    (void)cmd;

    do_arg_check(3);

    for (int i = arg_starts_at; i < argc; ++i)
    {
        check_prpal_and_get_output(argv[i], NULL);
    }
}

def_invoke_fn_as(file_fn)
{
    do_arg_check(3);

    FILE* input_file = fopen(argv[arg_starts_at], "r");

    if (input_file == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "cannot open the input file '%s', '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, argv[arg_starts_at], cmd->name, cmd->help);
        exit(-1);
    }

    char* output_file_name = generate_output_filename(argv[arg_starts_at]);
    FILE* output_file = fopen(output_file_name, "w");

    if (output_file == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "cannot open the output file '%s', '%s'\nHelp: " FG_GREEN "%s\n" COLOR_RESET, output_file_name, cmd->name, cmd->help);
        free(output_file_name);
        exit(-1);
    }

    printf("Processing calculations from '" FG_LGREEN "%s" COLOR_RESET "':\n", argv[arg_starts_at]);

    bool must_fail = false;
    char buffer[MAX_LINE_SIZE];
    char* curr_tok;

    while (fgets(buffer, sizeof(buffer), input_file) != NULL)
    {
        // Tokenize buffer based on ' ' (whitespace) and get each word separately
        curr_tok = strtok(buffer, WHITE_SPACE);

        // Continue tokenization and add the rest of the tokens as arguments
        while (curr_tok != NULL)
        {
            check_token_size(curr_tok, true);

            if (curr_tok != NULL)
            {
                check_prpal_and_get_output(curr_tok, output_file);
            }
            curr_tok = strtok(NULL, WHITE_SPACE);
        }
    }

cleanup:
    if (input_file)
        fclose(input_file);

    if (output_file)
        fclose(output_file);

    if (output_file_name)
        free(output_file_name);

    if (must_fail)
        exit(-1);
}