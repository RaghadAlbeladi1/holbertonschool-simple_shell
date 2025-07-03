<p align="center">
  <img src="https://github.com/user-attachments/assets/2527c745-4eda-4584-93ef-cf7e7863ea3f" 
       alt="Untitled design" width="1000"/>
</p>

# C - Simple Shell 🎓
## Description
**Simple Shell** is a custom UNIX command line interpreter implemented in C, developed as part of the Holberton School curriculum. This collaborative project between [**Raghad Albeladi**](https://github.com/RaghadAlbeladi1), [**Najwa Aljunaidel**](https://github.com/NajwaAljunaidel), and [**Bushra Alotaibi**](https://github.com/Bushra2252) replicates core functionalities of traditional shells like `bash` or `sh`, with a focus on:

- **Process Management**: Handles command execution using `fork`, `execve`, and `wait`.
- **Environment Variables**: Supports `env` and custom `_getenv` for variable lookup.
- **Built-ins**: Implements essential commands like `exit` and `env`.
- **Modes**: Works in both **interactive** (user input) and **non-interactive** (script/file input) modes.

### Key Limitations (Scope):
❌ **No** piping (`|`) or redirection (`>`, `<`).  
❌ **No** advanced features like aliases, job control, or signal handling.  
❌ **No** wildcard expansion (e.g., `*.c`).  

### Technical Stack:
- **Language**: C (GNU89 standard).  
- **System Calls**: `execve`, `fork`, `waitpid`, `getline`, etc.  
- **Testing**: Valgrind for memory leaks, Betty for style compliance.

## Project Files

Below is a breakdown of the main files in this repository, displayed as badges with descriptions:

- [![shell.h](https://img.shields.io/badge/shell.h-blue?style=flat-square)](https://github.com/hedjouj/holbertonschool-simple_shell/blob/main/shell.h)  → Contains all function prototypes, macros and necessary header includes for our shell.

- [![shell.c](https://img.shields.io/badge/shell.c-green?style=flat-square)](https://github.com/hedjouj/holbertonschool-simple_shell/blob/main/shell.c) → Implements the REPL loop: reads user input, parses it, and dispatches commands.

- [![getenv.c](https://img.shields.io/badge/getenv.c-yellow?style=flat-square)](https://github.com/hedjouj/holbertonschool-simple_shell/blob/main/getenv.c) → Defines a custom `_getenv`‑style function to fetch environment variable values.

- [![builtins.c](https://img.shields.io/badge/builtins.c-orange?style=flat-square)](https://github.com/hedjouj/holbertonschool-simple_shell/blob/main/tools.c) → A collection of helper utilities for string handling, memory management and error reporting.

- [![execute.c](https://img.shields.io/badge/execute.c-red?style=flat-square)](https://github.com/hedjouj/holbertonschool-simple_shell/blob/main/command.c) → Locates executables on the `$PATH` and executes them with the provided arguments.

- [![man_1_simple_shell](https://img.shields.io/badge/man__1__simple__shell-lightgrey?style=flat-square)](https://github.com/hedjouj/holbertonschool-simple_shell/blob/main/man_1_simple_shell) → The formatted man‑page for your shell (section 1), describing usage, options and examples.

## Requirements
- GCC version 9.4.0 or newer (currently using 11.4.0 on Ubuntu 22.04)  
- Operating System: **Ubuntu 22.04 LTS** (sandbox environment)  
- `make` utility (optional but recommended)

## Compilation / Installation
**The code should be compiled this way:**
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c -o hsh
```
**What does it do?**
This command is used to strictly compile all C files in our project. It helps ensure the code is:

✅ Clean and free from common bugs

✅ Following C89 coding standards

✅ Compiled with any warning treated as an error

### 🔽 Clone the Repository
```bash
git clone https://github.com/RaghadAlbeladi1/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```

## Launch the shell
After compilation is complete, you're ready to start using the shell.Run
```bash
./hsh
```
```bash
ls
pwd
env
exit
You can also press Ctrl + D to exit the shell.
```
  ## Example
```bash
$ ./hsh
simple_shell$ echo "Hello, World!"
Hello, World!
simple_shell$ ls -1
AUTHORS
README.md
built-ins.c
execute.c
hbtn_ls
hsh
prompt.c
shell.c
shell.h
tools.c
user_input.c
simple_shell$ exit
$
```
**In this session:**
- Started the shell with `./hsh`
- Ran a simple `echo` command
- Listed directory contents with `ls -1`
- Exited cleanly with `exit`
  
## Testing

### Allowed Functions & System Calls

You may only use the following headers, functions and syscalls in your implementation:

```text
All functions from string.h
access       (man 2 access)
chdir        (man 2 chdir)
close        (man 2 close)
closedir     (man 3 closedir)
execve       (man 2 execve)
exit         (man 3 exit)
_exit        (man 2 _exit)
fflush       (man 3 fflush)
fork         (man 2 fork)
free         (man 3 free)
getcwd       (man 3 getcwd)
getline      (man 3 getline)
getpid       (man 2 getpid)
isatty       (man 3 isatty)
kill         (man 2 kill)
malloc       (man 3 malloc)
open         (man 2 open)
opendir      (man 3 opendir)
perror       (man 3 perror)
printf       (man 3 printf)
fprintf      (man 3 fprintf)
vfprintf     (man 3 vfprintf)
sprintf      (man 3 sprintf)
putchar      (man 3 putchar)
read         (man 2 read)
readdir      (man 3 readdir)
signal       (man 2 signal)
stat         (man 2 stat)    # __xstat
lstat        (man 2 lstat)   # __lxstat
fstat        (man 2 fstat)   # __fxstat
strtok       (man 3 strtok)
wait         (man 2 wait)
waitpid      (man 2 waitpid)
wait3        (man 2 wait3)
wait4        (man 2 wait4)
write        (man 2 write)
```
**Memory Safety** 
Use Valgrind to verify there are no leaks or invalid accesses:
```text
$ valgrind ./hsh
==12345== Memcheck, a memory error detector
==12345== Command: ./hsh
==12345==
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap usage: 14 allocs, 14 frees, 2600 bytes allocated
==12345==
==12345== All heap blocks were freed -- no leaks are possible
==12345== ERROR SUMMARY: 0 errors
```
**This confirms:**
- Every `malloc` has a matching `free`.  
- No invalid reads or writes occurred.  
- Your shell cleans up all resources before exiting.

## Authors 

- **Raghad Albeladi**  [![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github)](https://github.com/RaghadAlbeladi1)
- **Najwa Aljunaidel**  [![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github)](https://github.com/NajwaAljunaidel)
 - **Bushra Alotaibi**  [![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github)](https://github.com/Bushra2252)

 







