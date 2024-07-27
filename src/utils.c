// ***************************************************************************************
//    Project: Prime Number and Palindrome String Checker
//    File: utils.c
//    Date: 2024-07-27
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

#include "utils.h"
#include "colors.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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

void check_prpal_and_get_output(const char* string, FILE* file)
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
        exit(-1);
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