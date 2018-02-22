# **Crush**

## A simple Linux shell developed from scratch, aimed for educational purposes.


Developed by *Dimitrios Karageorgiou*,\
during the course *Operating Systems*,\
*Aristotle University Of Thessaloniki, Greece,*\
*2017-2018.*

**Crush**, is a Linux shell that implements basic functionality expected of a shell.

Crush stands for "**C**ompletely **Ru**bbish **Sh**ell", a funny title, though perfectly describing the real world usages of this shell. After all, at least at this stage, it is not intended as a project to create an everyday shell.

It is intended for providing a minimal implementation of core concepts used in a shell, useful for everyone who wants to start implementing a shell from scratch or who wants to understand some fundamental concepts.


### **How to compile:**

The straightforward way to compile is the following:

```
make
```

In order to compile a compiler that supports gnu11 C standard is required.


### **How to invoke Crush:**

#### Interactive Mode:

**Crush** can be invoked in interactive mode, i.e. the mode where commands are
read one by one from the user, either by directly calling the executable or
utilizing a shorthand in Makefile as following:

Direct executable call: `./bin/crush` \
Makefile shorthand: `make run`

#### Batch Mode:

**Crush** can also be used to run shell scripts that utilize the functionality it implements. Like interactive mode, it can be done by either providing the script as first argument to the executable, or by using a Makefile shorthand as following:

Direct executable call: `./bin/crush <path_to_shell_script>` \
Makefile shorthand: `make run_batch script=<path_to_shell_script>`


### **Main functionality implemented by Crush:**

1. Invoking commands either by their absolute/relative path or by searching for appropriate executables in *PATH* environment variable.
2. Passing an arbitrary number of arguments to commands, separated by an arbitrary number of spaces.
3. Defining arguments that contain whitespaces.
4. Defining multiple commands in a line separated by `;`.
5. Creating chains of commands using `&&` operator.
6. Simple built-in commands such as *cd*, *quit*, etc.
7. Define comments right after '#' character.
8. Various error messages.

More detail about *Crush* features can be found in `README.txt`.


### **Licensing:**

This project is licensed under GNU GPL v3.0.
