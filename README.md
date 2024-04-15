# Minishell Project

## Introduction
The Minishell project is an educational endeavor designed to deepen understanding of how shells operate in computing. This project involves creating a simple shell, akin to a minimalist bash, where you can learn about processes, file descriptors, and command-line interaction.

## Features
- **Command Prompt:** Displays a prompt waiting for new commands.
- **Command History:** Maintains a history of commands that can be navigated through.
- **Executable Search:** Locates and launches executables based on the PATH environment variable or through specified paths.
- **Signal Handling:** Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` like bash.
- **Redirections and Pipes:** Implements input and output redirections (`<`, `>`, `<<`, `>>`) and pipes (`|`).
- **Environment Variables:** Supports expansion of environment variables (`$VAR`) and command exit status (`$?`).
- **Built-in Commands:** Includes builtins like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

## Technical Specifications
- **Programming Language:** The project is entirely written in C.
- **Memory Management:** Proper management of heap-allocated memory with no leaks allowed.
- **Error Handling:** Graceful handling of unexpected terminations (e.g., segmentation faults).

## Build Instructions
Use the provided `Makefile` with commands:
- `make all` to compile the shell
- `make clean` to remove object files
- `make fclean` to remove object files and executable
- `make re` to recompile the project

## Usage
To start the shell after building, execute the compiled output:
```bash
./minishell
