/**
 * engine.h
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This header file provides a simple and straightforward way to execute
 * shell commands described by command_t objects.
 *
 * Variables declared in engine.h:
 *  -char *engine_builtins[]
 *
 * Routines declared in engine.h:
 *  -int exec_commands(command_t **commands, int commandc)
 *  -int find_built_in(command_t *command)
 *  -int is_local_bin(command_t *command)
 *  -int exec_binary(command_t *command)
 *
 * Version: 0.1
 */

#ifndef __engine_h__
#define __engine_h__


#include "command.h"


/**
 * A NULL terminated array of strings, that contains the names of all
 * built-in commands contained in current engine implementation.
 */
extern char *engine_builtins[];


/**
 * Executes the given commands.
 *
 * This is the main entry point of the engine. The only thing it requires is
 * properly formed command objects. It maps given command representations
 * to actual binary files in filesystem or to built-in commands and invokes
 * them with the arguments also described in provided command objects.
 *
 * Locations searched for matching binary files are all the locations contained
 * in PATH environment variable and current working directory of the process
 * that invokes exec_commands().
 *
 * Parameters:
 *  -commands : An array of references to commands, to be executed.
 *  -commandc : Size of commands array.
 *
 * Returns:
 *  0 if execution of all commands succeeded, else the number of commands
 *  whose execution failed.
 */
int exec_commands(command_t **commands, int commandc);

/**
 * Searches the implemented built-in commands for matching with the given
 * command.
 *
 * engine_builtins array is used for the lookup.
 *
 * Parameters:
 *  -command : The command to be looked up on builtins.
 *
 * Returns:
 *  If given command is found to be a built-in, returns its index in
 *  engine_builtins array. If look up failes, it returns -1.
 */
int find_built_in(command_t *command);

/**
 * Checks if the given command requests a binary only to be found under
 * current working directory of the process invoking this routine.
 *
 * Parameters:
 *  -command : Command to use for the query.
 *
 * Returns:
 *  1 in case of command requesting a local binary file, else 0.
 */
int is_local_bin(command_t *command);

/**
 * Executes a command that requests a binary in the file system.
 *
 * Built-in commands are ignored.
 *
 * Parameters:
 *  -command : Command to be executed.
 *
 * Returns:
 *  If command executed, the status code of the invoked command. Else,
 *  a non-zero value is guaranteed.
 */
int exec_binary(command_t *command);

#endif
