/**
 * crush.c
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This file is the entry point for the implementation of CRuSh shell.
 *
 * CRuSh can be run into the following two modes:
 *  1. Interactive Mode : Shell is invoked for manual command input by user.
 *      --> Executed as ./crush_exec_path
 *  2. Batch Mode : Shell is invoked for the execution of a provided script.
 *      --> Executed as ./crush_exec_path <script_path>
 *              where:
 *                  -script path: Path to the script file.
 *
 * Version: 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "command.h"
#include "string_utils.h"
#include "engine.h"
#include "parser.h"


#define LINE_SIZE 512               // Maximum allowed length of each line.
const char *DEFAULT_PROMPT = ">";   // Prompt to be displayed on shell.


void start_shell(FILE *input_stream);
char *get_prompt(char *buffer, size_t size);
void print_welcome_message();


int main(int argc, char *argv[])
{
    FILE *input_stream;  // Input stream to read commands from.

    // If a script is provided, commands stream is redirected to this file.
    if (argc > 1) {
        input_stream = fopen(argv[1], "r");
        if (!input_stream) {
            printf("Failed to open %s script.\n", argv[1]);
            exit(-1);
        }
    }
    else {
        print_welcome_message();
        input_stream = stdin;
    }

    // Invoke the shell.
    start_shell(input_stream);

    // If a script file was used as source for commands, release it.
    if (input_stream != stdin) fclose(input_stream);

    return 0;
}

/**
 * Invokes the shell.
 *
 * Parameters:
 *  -input_stream : The file stream, from where commands will be read. If
 *          shell is invoked in interactive mode, that argument should be
 *          stdin. If shell is invoked in batch mode, in order to run a script,
 *          this argument should be the FILE object representing the script
 *          file.
 */
void start_shell(FILE *input_stream)
{
    char line[LINE_SIZE];  // Text of each line to be executed.
    char prompt[1024];     // Prompt to be displayed. Don't allocate for prompts
                           // larger than 1024 chars. They are useless anyway.
    command_t **commands;  // Commands parsed out of current line.
    int commandc;          // Number of parsed commands.
    int rc;

    // Initially print prompt.
    if (input_stream == stdin) printf("%s ", get_prompt(prompt, sizeof(prompt)));

    // Keep reading a line from input stream, whatever it is (script or stdin).
    while(fgets(line, LINE_SIZE, input_stream)) {

        // Parse the current line into commands that can be executed.
        rc = parse_line(line, &commands, &commandc);
        if (rc) printf("Could not parse line '%s'\n", line);

        // Execute the parsed commands, only if parsing succeeded.
        if (!rc) {
            rc = exec_commands(commands, commandc);
            // if (rc) {
            //     printf("Execution of line '%s' failed.\n",
            //            command_get_name(commands[rc-1]));
            // }
        }

        // Cleanup already executed commands.
        for (int i = 0; i < commandc; i++) command_destroy(commands[i]);

        // Print prompt for the next command.
        if (input_stream == stdin)
            printf("%s ", get_prompt(prompt, sizeof(prompt)));
    }
}

/**
 * Stores into buffer a prompt consisted of login name + working dir +
 * DEFAULT_PROMPT.
 *
 * If length of login name or working dir exceed the size of the buffer as
 * defined by size, they get replaced by warning " (too long text) > ". If
 * buffer cannot even hold this warning message, a new buffer is allocated
 * and returned, containing the ">" prompt.
 *
 * Parameters:
 *  -buffer : The buffer where returned prompt will be stored.
 *  -size : Size of given buffer.
 *
 * Returns:
 *  If at least the warning message fits into given buffer, returns given
 *  buffer. Else returns a newly allocated string, that should be followed by
 *  a call to free().
 */
char *get_prompt(char *buffer, size_t size)
{
    char *free_pos = buffer;  // Indicates the first position in buffer free
                              // for writing.
    size_t free_size = size;  // Free space remaining in buffer.
    char *fallback_text = " (too long text) >";
    int rc;

    // In case size is too small even for fallback_text, allocate space for
    // a very simple prompt.
    static int no_space = 0;
    static char *no_space_buffer = NULL;
    if (size < strlen(fallback_text)+1) {
        if (!no_space) {
            printf("Internal Error: Someone idiot,\n");
            printf("did not allocate memory even for a tiny prompt.\n");
            printf("No detailed prompt for you.\n");
            no_space = 1;  // Display this massage only one.
            no_space_buffer = (char *) malloc(sizeof(char) * 2);
            no_space_buffer[0] = '>';
            no_space_buffer[1] = '\0';
        }
        return no_space_buffer;
    }

    // Get the login name of the user into buffer.
    rc = getlogin_r(free_pos, free_size);
    if (!rc) {
        size_t occupied = strlen(free_pos) + 1;
        free_pos += occupied;
        free_size -= occupied;
    }
    else {
        strcpy(free_pos, fallback_text);
        return buffer;
    }

    // Get the current working directory into buffer.
    if (getcwd(free_pos, free_size)) {
        *(free_pos-1) = ' ';  // Replace previous terminating char with space.
        size_t occupied = strlen(free_pos) + 1;
        free_pos += occupied;
        free_size -= occupied;
    }
    else if (free_size > strlen(fallback_text)) {
        *(free_pos-1) = ' ';  // Replace previous terminating char with space.
        strcpy(free_pos, fallback_text);
        return buffer;
    }

    // Append DEFAULT_PROMPT to the end.
    if (free_size > strlen(DEFAULT_PROMPT)+1) {
        *(free_pos-1) = ' ';  // Replace previous terminating char with space.
        strcpy(free_pos, DEFAULT_PROMPT);
    }

    return buffer;
}

/**
 * Prints a welcome message that can be used on shell startup.
 */
void print_welcome_message()
{
    printf("Welcome to CRuSh (Completely Rubbish Shell)!\n");
    printf("The shell that won't let you sleep again...\n");
    printf("--Brought to you by Dimitrios Karageorgiou--\n");
    printf("--Official repo: https://github.com/dkarageo/crush --\n");
    printf("\n");
}
