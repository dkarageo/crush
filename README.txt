**
* README.txt
*
* Created by Dimitrios Karageorgiou, AEM: 8420
* for course: Operating Systems.
*
* Electrical and Computers Engineering Department,
* Aristotle University of Thessaloniki, Greeece,
* 2017-2018.
*
* Version: 0.1
**


0. Contents.
    -1. Introduction.
    -2. Licensing.
    -3. How to obtain code.
    -4. How to compile.
    -5. How to run.
        -5a. Interactive mode
        -5b. Batch mode
    -6. Features.
        -6a. Invoking commands
        -6b. Passing arguments to commands
        -6c. Defining arguments that contain whitespaces
        -6d. Built-in commands
        -6e. Defining multiple commands in a line
        -6f. Executing commands based on the return code of previous command


1. Introduction.

CRUSH, crush or CRuSh, is a shell developed for educational purposes by
Dimitrios Karageorgiou. It was developed during course "Operating Systems",
of Electrical and Computers Engineering department of Aristotle University of
Thessaloniki, Greece during 2017-2018 season.

CRuSh stands for "Completely Rubbish Shell", a funny title, though perfectly
describing the real world usages of this shell. After all, at least at this
stage, it is not intended as a project to create an everyday shell.

It is intended for providing a minimal implementation of core concepts used
in a shell, useful for everyone who wants to start implementing a shell from
scratch or who wants to understand some fundamental concepts.


2. Licensing.

This project is licensed under GNU GPL v3.0. If a copy of this license did not
come with this README, you can get a copy here:
https://www.gnu.org/licenses/gpl-3.0.en.html


3. How to obtain code.

Official repo of CRuSh is: https://github.com/dkarageo/crush

Git client can be used to retrieve the code.


4. How to compile.

In order to compile the project, a compiler supporting 'gnu11' C standard
should be present, like all version of GCC 4.x and above. Also a version
of 'make' should be present.

In order to compile, a Makefile is provided and can be used as:
    "make"


5. How to run.

The shell can be used in two different ways. It can be used both in interactive
mode and batch mode.

5a. Interactive mode:

Interactive mode is the normal, expected operation of a shell, where user
types in commands, command by command, line by line and the shell executes
them. In order to invoke the the shell in interactive mode, the only thing
needed is to execute its executable or use the makefile shorthand. These two
ways can be used as following:
    -Direct executable call: ./bin/crush
    -Makefile shorthand: make run

5b. Batch mode:

In batch mode, shell is given a shell script file and executes it. This mode
can be invoked, by providing as first argument to the shell's executable the
path to a shell script. Also, there is a shorthand in makefile. The exact
commands for utilizing these two ways are:
    -Direct executable call: ./bin/crush <path_to_shell_script>
    -Makefile shorthand: make run_batch script=<path_to_shell_script>

When the shell script terminates the shell automatically quits.

In both modes, invoking 'quit' or 'exit' commands manually by typing them or
by including them at any point in the given shell script respectively, causes
the shell to terminate.


6. Features.

The following features applies both to interactive and batch mode, unless
stated otherwise.

6a. Invoking commands:

Invoking commands is the most basic operation of the shell. Commands under
current working directory of the shell (the directory upon which shell's
executable called, unless changed with 'cd' built-in command) can be invoked
as:
    ./<command_name>
Also path navigation is supported, so commands can also be called by using
either their absolute or relative path:
    ./<path_to_command>/<command_name>

Apart from invoking commands based on their path, commands can also be
invoking if their path is contained in 'PATH' environment variable, as
following:
    <command_name>

6b. Passing arguments to commands:

Arguments to commands can be passed by including them right after the command's
name, separated by at least a whitespace from it. Multiple arguments can be
passed to a command, by separating each one from the previous, by an arbitrary
number of whitespaces, as following:
    <command_name> <arg1> <arg2> <arg3> ..... <argN>

6c. Defining arguments that contain whitespaces:

It is very common for an argument to contain one or more whitespaces. In order
shell to be able to distinguish between many arguments separated by whitespaces
and one argument that contains whitespaces, arguments of this kind should be
enclosed into double-quotes as following:
    <command_name> "arg with whitespaces 1" "arg with whitespaces 2" ....

6d. Built-in commands:

The shell implements a series of built-in commands (i.e. commands that doesn't
require any external executable). The names of these commands cannot be used
for calling real binaries whose path reside in 'PATH' environment variable.
For example calling:
    cd <new_path>
will always call 'cd' built-in command.
Though, executables named under the built-in names, can be called using their
absolute or relative paths.
For example:
    ./cd
that call won't call the built-in 'cd' command, but will look for an
executable named 'cd' under current working directory.

The list of supported built-in commands is the following:

    1. 'cd' command: This command changes the current working directory of the
            shell and can be invoked as following:
                cd <new_path>
            where new_path can be either an absolute or relative path.

    2. 'quit' command: This command terminates the shell and can be invoked as:
                quit

    3. 'exit' command: The same as 'quit' and invoked as:
                exit

    4. '' command: This is the empty (or "Do Nothing") command. This command
            while it does nothing, allows for an arbitrary number of blank
            lines, both in interactive and batch modes.

6e. Defining multiple commands in a line:

Multiple commands can be defined in a line, by separating them by ';', as
following:
    <command1>; <command2>; <command3>; .... ; <commandN>
All of these commands will be executed as if they had been defined in
different lines.

6f. Executing commands based on the return code of previous command:

In order to execute commands based on the return code of the execution of
the previous command, the '&&' operator is available. It can be used between
two commands, so that the second one is only executed if the first one has
returned normally (i.e. status code 0 returned). It can be used in order
to chain an arbitrary number of commands as following:
    <command1> && <command2> && .... <commandN>

Also, '&&' operator can be combined with ';' operator, so many chained blocks
are contained in a single line, like following:
    <chain1_com1> && <chain1_com2>; <chain2_com1>; <chain3_com1> && <chain3_com2> ....
