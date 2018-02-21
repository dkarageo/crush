/**
 * parser.c
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This file provides an implementation for routines defined in parser.h
 *
 * Version: 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "command.h"
#include "string_utils.h"
#include "parser.h"


char *exclude_comment(char *line, const char *delim, const char *solid_delim);


int parse_line(char *line, command_t ***commands, int *commandc)
{
    char *main_delim = ";";    // Delimiter for independent command sequences.
    char *sub_delim = "&&";    // Delimiter for chained command sequences.
    char *solid_delim = "\"";  // Delimiter that defines a solid block.
    char *comment_delim = "#"; // Delimiter that defines a comment.

    command_t **comms = NULL;  // Pointer to the array containing found commands.
    int comms_c = 0;           // Number of found commands.
    int avail_space = 0;

    // Blocks defined as solid, should have both a starting and ending delim.
    if (str_str_occurencies(line, solid_delim) % 2 != 0) {
        printf("Syntax Error: starting %s expects an ending one.\n", solid_delim);
        return -1;
    }

    // Init array space for 1 command.
    comms = (command_t **) malloc(sizeof(command_t *) * 1);
    assert(comms);
    avail_space = 1;

    // Replace all newlines by spaces.
    str_char_replace(line, '\n', ' ');
    str_char_replace(line, '\r', ' ');

    // Clean comment part.
    exclude_comment(line, comment_delim, solid_delim);

    // Start searching for blocks delimited by main_delim from the beggining.
    char *cur_main = NULL;   // Pointer to current token found.
    char *next_main = line;  // Pointer after the end of cur_main token.

    // Separate the given line into blocks delimited by main_delim.
    while((cur_main = strtok_multi_solid(
                &next_main, main_delim, solid_delim)) != NULL) {

        // Start searching for commands delimited by sub_delim, into the token
        // returned by splitting based on main_delim.
        char *cur_sub = NULL;       // Pointer to the current subtoken found.
        char *next_sub = cur_main;  // Pointer after the end of cur_sub token.

        int sub_comms = 0;  // Counter for commands found in current block.

        // Separate each sub block, into commands separated by sub_delim.
        while((cur_sub = strtok_multi_solid(
                    &next_sub, sub_delim, solid_delim)) != NULL) {

            // If no available space left, double the size of array.
            if (avail_space == comms_c) {
                avail_space *= 2;
                comms = (command_t **) realloc(
                            comms, sizeof(command_t *) * avail_space);
                assert(comms);
            }

            // Create a new command object for each command found.
            comms[comms_c] = command_create_from_str(cur_sub);
            // Commands separated by sub_delim form a chain where each
            // subsequent one is executed only if the previous one succeeds.
            if (sub_comms != 0) {
                command_set_exec_policy(comms[comms_c],
                                        COMMAND_ON_PREVIOUS_SUCCEED);
            }
            comms_c++;
            sub_comms++;
        }
    }

    // Write results to given arguments.
    *commands = comms;
    *commandc = comms_c;

    return 0;
}

/**
 * Terminate a line at comment position by placing a NUL char.
 *
 * Parameters:
 *  -line : The line to search for comment occurence.
 *  -delim : The delimiter that defines the beggining of a comment.
 *  -solid_delim : The delimiter that defines a solid block.
 *
 * Returns:
 *  The position of the beggining of a comment if it was found, else NULL.
 */
char *exclude_comment(char *line, const char *delim, const char *solid_delim)
{
    strtok_multi_solid(&line, delim, solid_delim);

    return line;
}
