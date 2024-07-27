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
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    PRIME,
    NOT_PRIME,
    NOT_A_NUMBER,
} PRIME_RESULT;

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

bool is_palindrome(const char* string)
{
    int len = (int)strlen(string);

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

bool is_prime_number(int num)
{
    if (num <= 1)
        return false;
    if (num <= 3)
        return true; // 2 and 3 are prime numbers

    if (num % 2 == 0 || num % 3 == 0)
        return false;

    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

int is_prime(const char* str)
{
    char* endptr;
    errno = 0; // Reset errno before conversion

    long value = strtol(str, &endptr, 10);

    if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
    {
        return NOT_A_NUMBER; // Out of range or not an integer
    }

    // Check if no characters were converted
    if (endptr == str)
    {
        return NOT_A_NUMBER; // Not a number
    }

    // Check for trailing non-digit characters
    while (*endptr)
    {
        if (!isspace(*endptr))
        {
            return NOT_A_NUMBER; // Not a number due to trailing characters
        }
        endptr++;
    }

    // Convert long to int safely
    int num = (int)value;

    if (is_prime_number(num))
    {
        return PRIME;
    }

    return NOT_PRIME;
}

void check_prpl(const char* string, FILE* file)
{
    FILE* output = (file == NULL) ? stdout : file; // print to stdout if there is no file provided

    fprintf(output, "'%s' -> ", string);

    char* palindrome = is_palindrome(string) ? "palindrome" : "Not palindrome";

    if (!file)
        printf(FG_LBLUE);

    fprintf(output, "%s", palindrome);

    char* prime;

    switch (is_prime(string))
    {
    case PRIME:
        prime = "prime";
        break;

    case NOT_PRIME:
        prime = "Not prime";
        break;

    default:
        prime = "Not a number";
        break;
    };

    fprintf(output, ", %s\n", prime);

    if (!file)
        printf(COLOR_RESET);
}

def_invoke_fn_as(check_fn)
{
    (void)cmd;

    do_arg_check(3);

    for (int i = arg_starts_at; i < argc; ++i)
    {
        check_prpl(argv[i], NULL);
    }
}

char* generate_output_filename(const char* filepath)
{
    // Find the last occurrence of '/' or '\\' for UNIX or Windows paths respectively
    const char* filename = strrchr(filepath, '/');
    if (!filename)
    {
        filename = strrchr(filepath, '\\');
    }

    // If no path separator is found, the input_file is in the current directory
    if (!filename)
    {
        filename = filepath;
    }
    else
    {
        filename++; // Move past the path separator
    }

    // Find the last occurrence of '.'
    const char* dot = strrchr(filename, '.');

    // Calculate the length of the new filename
    size_t base_length = dot ? (size_t)(dot - filename) : strlen(filename);
    size_t extension_length = dot ? strlen(dot) : 0;
    size_t path_length = filename - filepath;
    size_t new_filename_length = path_length + base_length + strlen("_output") + extension_length;

    // Allocate memory for the new filename
    char* new_filename = (char*)malloc(new_filename_length + 1);
    if (!new_filename)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Copy the path part of the filename
    strncpy(new_filename, filepath, path_length);

    // Copy the base part of the filename
    strncpy(new_filename + path_length, filename, base_length);
    new_filename[path_length + base_length] = '\0';

    // Append "_output"
    strcat(new_filename, "_output");

    // Append the extension
    if (dot)
    {
        strcat(new_filename, dot);
    }

    return new_filename;
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
                check_prpl(curr_tok, output_file);
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