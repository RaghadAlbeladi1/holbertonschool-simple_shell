<p align="center">
  <img src="https://github.com/user-attachments/assets/2527c745-4eda-4584-93ef-cf7e7863ea3f" 
       alt="Untitled design" width="1000"/>
</p>

# C - Simple Shell 🎓
## Description
**Simple Shell** is an implementation of our own simplified version of a UNIX command line interpreter written in C. The objective of this project is to build a shell from scratch that mimics basic behaviors of traditional UNIX shells. While limited in functionality, it applies the core concepts of process creation, command execution, environment variables, and input handling. In simple terms, a shell is a program that takes commands typed by the user and passes them to the operating system for execution. Our shell supports interactive and non-interactive modes, uses `execve` to execute commands found in the `PATH`, and includes basic built-ins like `exit` and `env`, excluding advanced features such as piping, redirection, or cursor movement.

This project was collaboratively developed by [**Raghad Albeladi**](https://github.com/RaghadAlbeladi1), [**Najwa Aljunaidel**](https://github.com/NajwaAljunaidel), [**Bushra Alotaibi**](https://github.com/Bushra2252), as part of the Holberton School curriculum.


## Requirements
- GCC version 9.4.0 or newer (currently using 11.4.0 on Ubuntu 22.04)  
- Operating System: **Ubuntu 22.04 LTS** (sandbox environment)  
- `make` utility (optional but recommended)
### 🔽 Clone the Repository
```bash
git clone https://github.com/RaghadAlbeladi1/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```
Compilation
All files are compiled on Ubuntu 22.04 LTS using:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```



