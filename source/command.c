/**
 * command.c
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This file provides an implementation of interface defined in command.h
 *
 * Version: 0.1
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string_utils.h"
#include "command.h"


command_t *command_create()
{
    // Allocate space for command_t.
    command_t *comm = (command_t *) malloc(sizeof(command_t));
    if (!comm) {
        printf("command_create: Failed to allocate memory.\n");
        return NULL;
    }

    // Init the object without any name and arguments.
    comm->name = NULL;
    comm->argv = NULL;
    comm->argc = 0;

    // Set default execution policy.
    comm->exec_policy = COMMAND_ALWAYS;

    return comm;
}

void command_destroy(command_t *comm)
{
    if (comm->name) free(comm->name);
    if (comm->argv) {
        for (int i = 0; i < comm->argc; i++) free(comm->argv[i]);
        free(comm->argv);
    }
}

command_t *command_create_from_str(char *str)
{
    command_t *comm = command_create();
    assert(comm);

    // Create a copy of given string, to work on it using strtok().
    char *str_cpy = (char *) malloc(sizeof(char) * strlen(str) + 1);
    strcpy(str_cpy, str);

    char *saveptr = str_cpy;  // Create a reference copy, so its value can
                              // be altered by strtok_multi_solid() calls.

    // First token on given string is command's name.
    char *comm_name = strtok_multi_solid(&saveptr, " ", "\"");
    if (comm_name) command_set_name(comm, comm_name);
    else command_set_name(comm, "");  // If no name, set to an empty string.

    char *comm_arg;

    // All remaining ones are arguments.
    while((comm_arg = strtok_multi_solid(&saveptr, " ", "\"")) != NULL) {
        char *trimmed = str_trim(comm_arg, '\"');
        command_add_arg(comm, trimmed);
        free(trimmed);
    }

    free(str_cpy);

    return comm;
}

void command_set_name(command_t *comm, char *name)
{
    assert(comm);
    assert(name);

    // Discard any previous name.
    if (comm->name) free(comm->name);

    // Allocate space and copy new name.
    size_t length = strlen(name);
    comm->name = malloc(length * sizeof(char) + 1);
    assert(comm->name);

    strcpy(comm->name, name);
}

void command_add_arg(command_t *comm, char *arg)
{
    assert(comm);
    assert(arg);

    // Increase the size of array that holds references to arguments.
    comm->argc++;
    comm->argv = (char **) realloc(comm->argv, sizeof(command_t *) * comm->argc);
    assert(comm->argv);

    // Allocate space and copy the actual argument.
    comm->argv[comm->argc-1] = (char *) malloc(strlen(arg) * sizeof(char) + 1);
    assert(comm->argv[comm->argc-1]);

    strcpy(comm->argv[comm->argc-1], arg);
}
