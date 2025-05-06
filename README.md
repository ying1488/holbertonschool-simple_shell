# Simple Shell (hsh)

## Description

**hsh** is a simple UNIX command-line interpreter (shell) written in C.  
It mimics basic functionalities of standard shells like `sh` or `bash`.

This project was created as part of the Holberton School curriculum.

## Features

- Execute commands located in the system PATH.
- Handle built-in commands:
  - `exit [status]`
- Command execution even when environment variables are removed.
- Graceful error handling for not found commands.
- Interactive and non-interactive mode support.

## Built-in Commands

| Command | Description             |
|---------|-------------------------|
| `exit`  | Exit the shell with status |

## Files

main.c - Entry point for the shell

execute_command.c - Execute user commands

split_line.c - Tokenize input

handle_exit.c - Handle exit built-in

utils.c - Helper functions (_strlen, _strdup, etc.)

shell.h - Header file with function prototypes and struct definitions

## How to Compile

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

## Usage

- Interactive mode:
```bash
./hsh
($) ls -l
($) exit


- Non-interactive mode:
```bash
echo "ls" | ./hsh


## Example

($) /bin/ls
hsh main.c shell.c README.md
($) exit


## Authors
Chutaphat Niampoung
Ying Tai
