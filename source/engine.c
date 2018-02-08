/**
 * engine.c
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This file provides an implementation for routines and variables declared
 * in engine.h header.
 *
 * Version: 0.1
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "string_utils.h"
#include "engine.h"


// ------ Built-In Commands Declaration ------
int quit(command_t *command);
int change_dir(command_t *command);
int do_nothing(command_t *command);

// ------ Declaration of arbitrary util functions ------
char **convert_2d_array_to_null_term(char **array, int n);
char **create_null_term_array_reference(char **array, int n);
char **array_push_at_beggining(char **array, char *new_obj);


// Human readable names of built-in commands.
char *engine_builtins[] = {
        "quit",
        "exit",
        "cd",
        "",
        NULL
};

// Functions mapping for each built-in name defined in engine_builtins.
int (*engine_builtins_map[]) (command_t *) = {
        quit,
        quit,
        change_dir,
        do_nothing,
        NULL
};


int exec_commands(command_t **commands, int commandc)
{
    int previous_rc = 0;  // First command is always executed.
    int failures = 0;     // Count the total number of commands failed.

    for (int i = 0; i < commandc; i++) {

        command_t *comm = commands[i];

        // Execute commands that require previous command to have succeed, only
        // if such is the case. Otherwise, continue to next one.
        int policy = command_get_exec_policy(comm);
        if (policy == COMMAND_ON_PREVIOUS_SUCCEED && previous_rc) {
            printf("Did not execute '%s', since previous command failed.\n",
                   command_get_name(comm));
            previous_rc = -1;  // Update return code to a failure one.
            continue;  // Go to next one.
        }

        // Check if current command is a built-in and if it is execute the
        // corresponding built-in.
        int builtin_id;
        if ((builtin_id = find_built_in(comm)) > -1) {
            previous_rc = engine_builtins_map[builtin_id](comm);
        }

        // Check if a command refers to a local binary (starts with "./").
        else if (is_local_bin(comm)) {
            // Trim "./" at beggining.
            char *trimmed = str_trim(command_get_name(comm), '.');
            char *trimmed2 = str_trim(trimmed, '/');
            command_set_name(comm, trimmed2);
            free(trimmed);
            free(trimmed2);

            previous_rc = exec_binary(comm);
        }

        else {
            previous_rc = exec_binary(comm);
        }

        if (previous_rc) failures++;  // Count the commands failed.
    }

    return failures;
}

int exec_binary(command_t *command)
{
    char **args = create_null_term_array_reference(
        command_get_args(command), command_get_args_num(command));
    char *name = command_get_name(command);

    // Place name of the command to the first argument.
    args = array_push_at_beggining(args, name);
    assert(args);

    pid_t pid;   // Process ID of the child to execute binary.
    int status;  // Status code returned from child process.

    if ((pid = fork()) == -1) {
        perror("Internal error: Cthulhu came up and your lovely CRUSH, crashed...!");
        exit(-1);
    }
    else if (pid == 0) {  // Child code.
        execvp(name, args);

        // If child reached here, then execvp() failed.
        printf("No command '%s' found.\n", name);
        exit(errno);  // Return errno to parent process.
    }
    else {  // Parent code.
        waitpid(pid, &status, 0);
    }

    // Cleanup resourcess.
    free(args);

    return status;
}

int is_local_bin(command_t *command) {
    char *name = command_get_name(command);
    if (name[0] == '.' && name[1] == '/') return 1;
    else return 0;
}

int find_built_in(command_t *command) {
    int i = 0;
    char *builtin_name;
    while ((builtin_name = engine_builtins[i]) != NULL) {
        if (!strcmp(engine_builtins[i], command_get_name(command))) {
            return i;
        }
        i++;
    }

    return -1;
}

int quit(command_t *command)
{
    exit(0);
    return 0;
}

int change_dir(command_t *command)
{
    int rc = chdir(command_get_args(command)[0]);

    if (rc)
        printf("No such directory exists.\n");

    return rc;
}

int do_nothing(command_t *command) { return 0; }

char **create_null_term_array_reference(char **array, int n)
{
    // Allocate space for given array, plus one more for NULL pointer.
    char **term_array = (char **) malloc(sizeof(char *) * (n + 1));
    // Copy the previous references.
    memcpy(term_array, array, sizeof(char *) * n);
    // Set final reference to NULL, to indicate the final position.
    term_array[n] = NULL;

    return term_array;
}

char **array_push_at_beggining(char **array, char *new_obj)
{
    // Count the length of null terminated array.
    int length = 0;
    while(array[length] != NULL) length++;

    // Increase space for 1 more item.
    array = (char **) realloc(array, (length+2) * sizeof(char *));

    // Move all items by 1 to the right.
    memmove(array+1, array, (length+1) * sizeof(char *));

    // Store new item to first position.
    array[0] = new_obj;

    return array;
}
