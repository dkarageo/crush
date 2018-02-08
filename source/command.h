/**
 * command.h
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This header provides an interface for proper representation of shell
 * commands and their arguments.
 *
 * Types defined in command.h:
 *  -command_t
 *
 * Constants defined in command.h:
 *  -COMMAND_ON_PREVIOUS_SUCCEED
 *  -COMMAND_ALWAYS
 *
 * Macros defined in command.h:
 *  -command_get_name(comm)
 *  -command_get_args(comm)
 *  -command_get_args_num(comm)
 *  -command_get_exec_policy(comm)
 *  -command_set_exec_policy(comm, policy)
 *
 * Functions defined in command.h:
 *  -command_t *command_create()
 *  -command_t *command_create_from_str(char *str)
 *  -void command_destroy(command_t *comm)
 *  -void command_set_name(command_t *comm, char *name)
 *  -void command_add_arg(command_t *comm, char *arg)
 *
 * Version: 0.1
 */

#ifndef __comand_h__
#define __comand_h__


typedef struct {
    char *name;       // Name of command.
    char **argv;      // An array consisting of all command's arguments.
    int argc;         // Number of arguments.
    int exec_policy;  // Execution policy of this command.
} command_t;


// Constants defining allowed execution policies.
#define COMMAND_ON_PREVIOUS_SUCCEED 1  // Execute if previous command succeeded.
#define COMMAND_ALWAYS 2               // Always execute this command.

/**
 * Returns the name of a command.
 */
#define command_get_name(comm) comm->name

/**
 * Returns an array of string references, containing the arguments for given
 * command.
 */
#define command_get_args(comm) comm->argv

/**
 * Returns the number of arguments currently associated with this command.
 */
#define command_get_args_num(comm) comm->argc

/**
 * Returns the execution policy of this command.
 */
#define command_get_exec_policy(comm) comm->exec_policy

/**
 * Sets the execution policy of this command.
 */
#define command_set_exec_policy(comm, policy) comm->exec_policy = policy

/**
 * Creates an empty command object.
 *
 * The created objects does not contain any name nor arguments. The default
 * execution policy is set to COMMAND_ALWAYS.
 *
 * Returns:
 *  The newly created command object.
 */
command_t *command_create();

/**
 * Creates a command object from its textual representation.
 *
 * The given textual representation is expected to contain the command's name
 * and its arguments, separated by an arbitrary number of whitespaces. If
 * other separators are used, or given string contains parts not belonging
 * to the command, the contents of returned object are undefined.
 *
 * Execution policy is set to COMMAND_ALWAYS.
 *
 * Parameters:
 *  str : A string to be parsed for finding command name and it's arguments.
 *
 * Returnes:
 *  A newly created command object with its fields set according to the given
 * string.
 */
command_t *command_create_from_str(char *str);

/**
 * Destroys a command object.
 *
 * Parameters:
 *  -comm : Command object to destroy.
 */
void command_destroy(command_t *comm);

/**
 * Sets a new name to the command.
 *
 * Previous name is discared.
 *
 * Parameters:
 *  -comm : Command object to alter its name.
 *  -name : A string representing the new name.
 */
void command_set_name(command_t *comm, char *name);

/**
 * Adds an argument to the end of argument list of given command.
 *
 * Parameters:
 *  -comm : Command object in which new argument will be added.
 *  -arg : A string with the name of the new argument.
 */
void command_add_arg(command_t *comm, char *arg);

#endif
