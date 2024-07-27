// ***************************************************************************************
//    Project: Prime Number and Palindrome String Checker
//    File: command_defs.h
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

#ifndef COMMAND_DEFS__H__
#define COMMAND_DEFS__H__

#include "command.h"

/**
 * @brief invoke function for `version` command
 *
 * This function prints build information
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0
 */
def_invoke_fn_as(version_fn);

/**
 * @brief invoke function for `check` command
 *
 * checks if a given string is a palindrome and
 * if the given string is also an integer number
 * then checks if the given number is a prime number, too.
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return the result of the operation.
 */
def_invoke_fn_as(check_fn);

/**
 * @brief invoke function for `file` command - loads file
 *
 * opens the given file, runs checks on each line,
 * creates a report file from the name of the input file
 * and writes the result in it
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return the result of the operation.
 */
def_invoke_fn_as(file_fn);

#endif // COMMAND_DEFS__H__
