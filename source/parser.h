/**
 * parser.h
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This header contains routines usefull for parsing contiguous string
 * representations of shell commands, into actual command objects.
 *
 * Functions defined in parser.h:
 *  -int parse_line(char *line, command_t ***commands, int *commandc)
 *
 * Version: 0.1
 */

#ifndef __parser_h__
#define __parser_h__

/**
 * Parses the given text line into a sequence of commands.
 *
 * Parameters:
 *  -line : A null terminated string to parse.
 *  -commands : A reference to an array of references to command_t objects.
 *          In this parameter, such an array will be returned upon successful
 *          parsing.
 *  -commandc : A reference to an integer, where the number of elements returned
 *          in commands will be stored.
 *
 * Returns:
 *  Upon successful parsing returns 0. Also, in commands and
 *  commandc arguments, the array of commands found in given line and its size
 *  are returned respectively. Upon failure, returns a non-zero value and
 *  commands and commandc arguments are set to NULL and 0 respectively.
 */
int parse_line(char *line, command_t ***commands, int *commandc);

#endif
