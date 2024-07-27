// ***************************************************************************************
//    Project: Prime Number and Palindrome String Checker
//    File: utils.h
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

#ifndef UTILS__H__
#define UTILS__H__

#include <stdbool.h>
#include <stdio.h>

typedef enum
{
    PRIME,
    NOT_PRIME,
    NOT_A_NUMBER,
} PRIME_RESULT;

/**
 * @brief palindrome checker algorithm
 *
 * @param string
 * @return true or false based on the result
 */
bool is_palindrome(const char* string);

/**
 * @brief prime number checker algorithm
 *
 * @param num an integer number
 */
bool is_prime_number(int num);

/**
 * @brief checks if the string is not a number or a prime number
 *
 * @param str the input string
 * @return int 0 -> prime, 1 -> not prime, 2 -> not a number
 */
int is_prime(const char* str);

/**
 * @brief check the input string if it is palindrome then checks if it's a number and then checks if the number is prime
 *
 * @param string
 * @file if NULL the results will be printed on the stdout
 *
 * @return void
 */
void check_prpal_and_get_output(const char* string, FILE* file);

/**
 * @brief helper function to generate a proper output file name
 *
 * @param filepath
 * @return char*
 *
 * `NOTE: allocates memory`
 */
char* generate_output_filename(const char* filepath);

#endif // UTILS__H__