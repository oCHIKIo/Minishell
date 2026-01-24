# 

```
██╗  ██╗███████╗██████╗  ██████╗ 
╚██╗██╔╝██╔════╝██╔══██╗██╔═══██╗
 ╚███╔╝ █████╗  ██████╔╝██║   ██║
 ██╔██╗ ██╔══╝  ██╔══██╗██║   ██║
██╔╝ ██╗███████╗██║  ██║╚██████╔╝
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝ 
```

<div align="center">

### ⚔ *As Beautiful as a Shell* ⚔

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norminette-Passing-success?style=for-the-badge)](https://github.com/42School/norminette)
[![License](https://img.shields.io/badge/License-42-blue?style=for-the-badge)](LICENSE)

---

**A fully-featured Unix shell implementation built from scratch**

*Created by **CHIKI Badreddine** & **Alae Ben Dris Alami** @ 42 School*

</div>

---

## Table of Contents

<details>
<summary>Click to expand</summary>

1. [Overview](#-overview)
2. [Features](#-features)
3. [Architecture](#️-architecture)
4. [How It Works](#-how-it-works)
5. [Installation](#-installation)
6. [Usage](#-usage)
7. [Built-in Commands](#-built-in-commands)
8. [Operators & Redirections](#-operators--redirections)
9. [Data Flow Diagram](#-data-flow-diagram)
10. [Testing](#-testing)
11. [Authors](#-authors)
12. [License](#-license)

</details>

---

## Overview

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                                                                              ║
║  XERO is a custom Unix shell implementation, built as part of the 42         ║
║  School curriculum. It replicates the core functionality of Bash,            ║
║  providing an interactive command-line interface for executing programs,     ║
║  managing processes, and handling I/O redirections.                          ║
║                                                                              ║
║  This project demonstrates deep understanding of:                            ║
║  • Process management (fork, execve, wait)                                   ║
║  • File descriptors and I/O redirection                                      ║
║  • Signal handling                                                           ║
║  • Memory management                                                         ║
║  • Lexical analysis and parsing                                              ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
```

---

## Features

<table>
<tr>
<td width="50%">

### Core Features

```
┌─────────────────────────────────┐
│  ✅ Interactive prompt          │
│  ✅ Command history             │
│  ✅ PATH-based command search   │
│  ✅ Environment variables       │
│  ✅ Exit status handling ($?)   │
│  ✅ Quote handling (' and ")    │
│  ✅ Signal handling             │
└─────────────────────────────────┘
```

</td>
<td width="50%">

### Built-in Commands

```
┌─────────────────────────────────┐
│  📁 echo    - Print arguments   │
│  📁 cd      - Change directory  │
│  📁 pwd     - Print working dir │
│  📁 export  - Set env variable  │
│  📁 unset   - Remove env var    │
│  📁 env     - Show environment  │
│  📁 exit    - Exit the shell    │
└─────────────────────────────────┘
```

</td>
</tr>
<tr>
<td width="50%">

### Redirections

```
┌─────────────────────────────────┐
│  < file   - Input redirection   │
│  > file   - Output redirection  │
│  >> file  - Append redirection  │
│  << EOF   - Heredoc             │
└─────────────────────────────────┘
```

</td>
<td width="50%">

### Operators

```
┌─────────────────────────────────┐
│  - Pipe (connect stdout to      │
│       stdin of next command)    │
│                                 │
│  Piping allows chaining         │
│  multiple commands together     │
└─────────────────────────────────┘
```

</td>
</tr>
</table>

---

## Architecture

```
╔════════════════════════════════════════════════════════════════════════════════════╗
║                           XERO SHELL ARCHITECTURE                                  ║
╠════════════════════════════════════════════════════════════════════════════════════╣
║                                                                                    ║
║    ┌──────────────────────────────────────────────────────────────────────────┐    ║
║    │                           📁 PROJECT STRUCTURE                           │    ║
║    └──────────────────────────────────────────────────────────────────────────┘    ║
║                                                                                    ║
║    Minishell/                                                                      ║
║    ├── 📄 main.c                 # Entry point & main shell loop                   ║
║    ├── 📄 minishell.h            # Main header with all declarations               ║
║    ├── 📄 Makefile               # Build configuration                             ║
║    │                                                                               ║
║    ├── 📁 parsing/               # Input processing & tokenization                 ║
║    │   ├── 📁 tokenize/          # Lexical analysis (tokenizer)                    ║
║    │   ├── 📁 expand_tokens/     # Variable expansion & quote handling             ║
║    │   ├── 📁 create_cmd/        # Command structure creation                      ║
║    │   ├── 📁 validate_cmd/      # Syntax validation                               ║
║    │   ├── 📁 signals/           # Signal handlers                                 ║
║    │   ├── 📁 read_input/        # Input reading with readline                     ║
║    │   ├── 📁 input_processing/  # Input line processing                           ║
║    │   └── 📁 free/              # Memory cleanup functions                        ║
║    │                                                                               ║
║    ├── 📁 execution/             # Command execution                               ║
║    │   ├── 📁 builtins/          # Built-in command implementations                ║
║    │   │   ├── 📄 echo.c         # echo command                                    ║
║    │   │   ├── 📄 pwd.c          # pwd command                                     ║
║    │   │   ├── 📄 env.c          # env command                                     ║
║    │   │   ├── 📄 exit.c         # exit command                                    ║
║    │   │   ├── 📁 cd/            # cd command                                      ║
║    │   │   ├── 📁 export/        # export command                                  ║
║    │   │   └── 📁 unset/         # unset command                                   ║
║    │   ├── 📁 operators/         # Shell operators                                 ║
║    │   │   ├── 📁 pipe/          # Pipe handling                                   ║
║    │   │   ├── 📁 heredoc/       # Here-document handling                          ║
║    │   │   ├── 📁 in_out_redir/  # Input/output redirections                       ║
║    │   │   ├── 📄 append.c       # Append redirection                              ║
║    │   │   └── 📁 operators_utils/ # Utility functions                             ║
║    │   └── 📁 execute_cmd_utils/ # Command execution utilities                     ║
║    │                                                                               ║
║    ├── 📁 libft/                 # Custom C library                                ║
║    │                                                                               ║
║    ├── 📁 tools/                 # Additional utilities                            ║
║    │                                                                               ║
║    └── 📁 xero/                  # XERO branding & info                            ║
║                                                                                    ║
╚════════════════════════════════════════════════════════════════════════════════════╝
```

---

## How It Works

### The Shell Loop

Every shell follows a simple yet powerful loop called **REPL** (Read-Eval-Print Loop):

```
                    ┌─────────────────────────────────────────────┐
                    │              🔄 XERO SHELL LOOP             │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         1️⃣  DISPLAY PROMPT                  │
                    │              @xero⚔                         │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         2️⃣  READ INPUT                      │
                    │     Using readline() for line editing       │
                    │     and command history support             │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         3️⃣  TOKENIZE                        │
                    │     Break input into tokens:                │
                    │     WORD, PIPE, REDIR_IN, REDIR_OUT, etc.   │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         4️⃣  VALIDATE SYNTAX                 │
                    │     Check for proper quote closure,         │
                    │     valid operator usage, etc.              │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         5️⃣  EXPAND VARIABLES                │
                    │     $HOME → /home/user                      │
                    │     $? → last exit status                   │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         6️⃣  CREATE COMMAND STRUCTURE        │
                    │     Parse tokens into command nodes         │
                    │     with args, redirections, heredocs       │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         7️⃣  EXECUTE COMMANDS                │
                    │     Handle builtins, fork for externals,    │
                    │     setup pipes and redirections            │
                    └─────────────────────────────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────────┐
                    │         8️⃣  CLEANUP & LOOP                  │
                    │     Free memory, update exit status,        │
                    │     return to step 1                        │
                    └─────────────────────────────────────────────┘
                                         │
                                         └──────────────┐
                                                        │
                                         ┌──────────────┘
                                         │
                                         ▼
                                    [LOOP BACK]
```

---

### Step-by-Step Breakdown

#### 1️⃣ Input Reading

```c
/*
 * The shell uses GNU Readline library for:
 * - Line editing (arrow keys, backspace)
 * - Command history (up/down arrows)
 * - Tab completion capability
 */

char *input = readline("@xero⚔ ");
if (input && *input)
    add_history(input);  // Add to history
```

#### 2️⃣ Tokenization (Lexical Analysis)

The tokenizer breaks the input string into meaningful tokens:

```
┌────────────────────────────────────────────────────────────────────────────────┐
│                           TOKENIZATION EXAMPLE                                 │
├────────────────────────────────────────────────────────────────────────────────┤
│                                                                                │
│  INPUT: echo "Hello World" | cat -e > output.txt                               │
│                                                                                │
│  ┌──────────────────────────────────────────────────────────────────────────┐  │
│  │                              TOKENS                                      │  │
│  ├──────────────────────────────────────────────────────────────────────────┤  │
│  │                                                                          │  │
│  │   [WORD]          [WORD]           [PIPE]    [WORD]  [WORD]              │  │
│  │     │               │                 │         │       │                │  │
│  │   "echo"    "Hello World"            "|"      "cat"   "-e"               │  │
│  │                                                                          │  │
│  │         [REDIR_OUT]    [WORD]                                            │  │
│  │              │            │                                              │  │
│  │             ">"     "output.txt"                                         │  │
│  │                                                                          │  │
│  └──────────────────────────────────────────────────────────────────────────┘  │
│                                                                                │
└────────────────────────────────────────────────────────────────────────────────┘
```

**Token Types:**

-------------------------------------------------------------
| Token Type     | Symbol | Description                     |
|----------------|--------|---------------------------------|
| `WORD`         | -      | Commands, arguments, filenames  |
| `PIPE`         | `\|`   | Pipe operator                   |
| `REDIR_IN`     | `<`    | Input redirection               |
| `REDIR_OUT`    | `>`    | Output redirection              |
| `REDIR_APPEND` | `>>`   | Append redirection              |
| `HEREDOC`      | `<<`   | Here-document                   |
-------------------------------------------------------------

#### 3️⃣ Variable Expansion

```
┌────────────────────────────────────────────────────────────────────────────────┐
│                          VARIABLE EXPANSION                                    │
├────────────────────────────────────────────────────────────────────────────────┤
│                                                                                │
│   ┌──────────────────┐                      ┌──────────────────┐               │
│   │ echo $USER $HOME │  ═══════════════▶    │ echo john /home  │               │
│   └──────────────────┘                      └──────────────────┘               │
│          BEFORE                                    AFTER                       │
│                                                                                │
│   ┌───────────────────────────────────────────────────────────────────────┐    │
│   │  EXPANSION RULES:                                                     │    │
│   │                                                                       │    │
│   │  • $VAR        → Value of environment variable VAR                    │    │
│   │  • $?          → Exit status of last command                          │    │
│   │  • ${VAR}      → Same as $VAR (brace expansion)                       │    │
│   │  • 'text'      → Single quotes: NO expansion                          │    │
│   │  • "text"      → Double quotes: $VAR expanded, literals preserved     │    │
│   │  • ~           → Expands to $HOME                                     │    │
│   │                                                                       │    │
│   └───────────────────────────────────────────────────────────────────────┘    │
│                                                                                │
└────────────────────────────────────────────────────────────────────────────────┘
```

#### 4️⃣ Command Structure Creation

```
                    ┌─────────────────────────────────────────────┐
                    │           COMMAND DATA STRUCTURE            │
                    └─────────────────────────────────────────────┘

                              ┌──────────────┐
                              │   t_cmd      │
                              ├──────────────┤
                              │ args         │──▶ ["ls", "-la", NULL]
                              │ input_redirs │──▶ [< input.txt]
                              │ output_redirs│──▶ [> output.txt]
                              │ heredocs     │──▶ [<< EOF]
                              │ next         │──▶ [next command]
                              └──────────────┘

    ╔═══════════════════════════════════════════════════════════════════════════╗
    ║  EXAMPLE: ls -la | grep "hello" > results.txt                             ║
    ╠═══════════════════════════════════════════════════════════════════════════╣
    ║                                                                           ║
    ║   ┌─────────────┐          ┌─────────────────────────────────────────┐    ║
    ║   │  Command 1  │          │              Command 2                  │    ║
    ║   ├─────────────┤          ├─────────────────────────────────────────┤    ║
    ║   │ args: [ls,  │──next──▶ │ args: [grep, "hello"]                   │    ║
    ║   │       -la]  │          │ output_redirs: [> results.txt]          │    ║
    ║   └─────────────┘          └─────────────────────────────────────────┘    ║
    ║                                                                           ║
    ╚═══════════════════════════════════════════════════════════════════════════╝
```

#### 5️⃣ Execution Engine

```
┌────────────────────────────────────────────────────────────────────────────────┐
│                            EXECUTION FLOW                                      │
├────────────────────────────────────────────────────────────────────────────────┤
│                                                                                │
│                           ┌─────────────────┐                                  │
│                           │  Is it a        │                                  │
│                           │  builtin cmd?   │                                  │
│                           └────────┬────────┘                                  │
│                                    │                                           │
│                      ┌─────────────┴─────────────┐                             │
│                      │                           │                             │
│                     YES                          NO                            │
│                      │                           │                             │
│                      ▼                           ▼                             │
│         ┌────────────────────┐      ┌────────────────────────────────┐         │
│         │  Execute directly  │      │  fork() + execve()             │         │
│         │  in shell process  │      │                                │         │
│         │                    │      │  ┌──────────────────────────┐  │         │
│         │  Example:          │      │  │  Parent Process          │  │         │
│         │  - cd changes PWD  │      │  │  • Waits for child       │  │         │
│         │  - export modifies │      │  │  • Collects exit status  │  │         │
│         │    environment     │      │  └──────────────────────────┘  │         │
│         │  - exit terminates │      │                                │         │
│         │                    │      │  ┌──────────────────────────┐  │         │
│         └────────────────────┘      │  │  Child Process           │  │         │
│                                     │  │  • Setup redirections    │  │         │
│                                     │  │  • Execute program       │  │         │
│                                     │  │  • Replace process image │  │         │
│                                     │  └──────────────────────────┘  │         │
│                                     └────────────────────────────────┘         │
│                                                                                │
└────────────────────────────────────────────────────────────────────────────────┘
```

#### 6️⃣ Pipe Execution

```
╔════════════════════════════════════════════════════════════════════════════════╗
║                             PIPE MECHANISM                                     ║
╠════════════════════════════════════════════════════════════════════════════════╣
║                                                                                ║
║    Example: cat file.txt | grep "pattern" | wc -l                              ║
║                                                                                ║
║    ┌─────────────┐    PIPE     ┌─────────────┐    PIPE     ┌─────────────┐     ║
║    │             │   ┌───┐     │             │   ┌───┐     │             │     ║ 
║    │  cat        │──▶│   │────▶│  grep       │──▶│   │────▶│  wc -l      │     ║
║    │  file.txt   │   │   │     │  "pattern"  │   │   │     │             │     ║
║    │             │   └───┘     │             │   └───┘     │             │     ║
║    └─────────────┘  fd[0|1]    └─────────────┘  fd[0|1]    └─────────────┘     ║
║                                                                                ║
║    ┌───────────────────────────────────────────────────────────────────────┐   ║
║    │                        PIPE INTERNALS                                 │   ║
║    ├───────────────────────────────────────────────────────────────────────┤   ║
║    │                                                                       │   ║
║    │   1. Create pipe: pipe(fd)  →  fd[0] = read end, fd[1] = write end    │   ║
║    │   2. fork() to create child process                                   │   ║
║    │   3. Child: dup2(fd[1], STDOUT) - redirect stdout to pipe             │   ║
║    │   4. Next child: dup2(fd[0], STDIN) - read from pipe                  │   ║
║    │   5. Close unused file descriptors                                    │   ║
║    │   6. Execute command                                                  │   ║
║    │                                                                       │   ║
║    └───────────────────────────────────────────────────────────────────────┘   ║
║                                                                                ║
╚════════════════════════════════════════════════════════════════════════════════╝
```

---

## Installation

### Prerequisites

```bash
# Required libraries
- GNU Readline library
- GCC compiler
- Make utility
```

### Build Instructions

```bash
# Clone the repository
git clone <repository-url>
cd Minishell

# Compile the project
make

# Clean object files
make clean

# Full clean (including executable)
make fclean

# Rebuild everything
make re
```

### Compilation Process

```
                ┌────────────────────────────────────────────────────────────┐
                │                   COMPILATION FLOW                         │
                └────────────────────────────────────────────────────────────┘
                                           │
                                           ▼
                ┌────────────────────────────────────────────────────────────┐
                │                    make all                                │
                └────────────────────────────────────────────────────────────┘
                                           │
                    ┌──────────────────────┴──────────────────────┐
                    │                                             │
                    ▼                                             ▼
        ┌───────────────────────┐                    ┌───────────────────────┐
        │   Compile libft       │                    │   Compile source      │
        │   (libft/libft.a)     │                    │   files (.c → .o)     │
        └───────────────────────┘                    └───────────────────────┘
                    │                                             │
                    └──────────────────────┬──────────────────────┘
                                           │
                                           ▼
                ┌────────────────────────────────────────────────────────────┐
                │               Link all objects                             │
                │   cc -Wall -Wextra -Werror *.o -o minishell -lft -lreadline│
                └────────────────────────────────────────────────────────────┘
                                           │
                                           ▼
                ┌────────────────────────────────────────────────────────────┐
                │                    ./minishell ✓                           │
                └────────────────────────────────────────────────────────────┘
```

---

##  Usage

### Starting the Shell

```bash
./minishell
```

### Example Session

```
╭─────────────────────────────────────────────────────────────────╮
│                     XERO SHELL SESSION                          │
╰─────────────────────────────────────────────────────────────────╯

@xero⚔ echo "Welcome to XERO Shell!"
Welcome to XERO Shell!

@xero⚔ pwd
/home/user/Minishell

@xero⚔ export GREETING="Hello, World!"

@xero⚔ echo $GREETING
Hello, World!

@xero⚔ ls -la | wc -l
42

@xero⚔ cat << EOF
> This is a heredoc
> Multiple lines supported
> EOF
This is a heredoc
Multiple lines supported

@xero⚔ echo "Last exit status: $?"
Last exit status: 0

@xero⚔ xero --version
╭─────────────────────────────────────────────────────────╮
│                                                         │
│    ⚡ XERO v1.0.0 ⚡                                    │
│    (Stay tuned for exciting updates ahead!)             │
│    © 2025 CHIKI Badreddine & Alae Ben Dris Alami        │
│                                                         │
╰─────────────────────────────────────────────────────────╯

@xero⚔ exit
```

---

## Built-in Commands

<table>
<tr>
<th>Command</th>
<th>Syntax</th>
<th>Description</th>
</tr>
<tr>
<td><code>echo</code></td>
<td><code>echo [-n] [args...]</code></td>
<td>

```
Print arguments to stdout
-n: suppress trailing newline

Examples:
  echo Hello World     → "Hello World\n"
  echo -n No newline   → "No newline"
  echo -nnn Test       → "Test"
```

</td>
</tr>
<tr>
<td><code>cd</code></td>
<td><code>cd [path]</code></td>
<td>

```
Change current directory

Examples:
  cd /home/user    → absolute path
  cd ..            → parent directory
  cd ~             → home directory
  cd              → home directory
```

</td>
</tr>
<tr>
<td><code>pwd</code></td>
<td><code>pwd</code></td>
<td>

```
Print current working directory

Example:
  @xero⚔ pwd
  /home/user/projects
```

</td>
</tr>
<tr>
<td><code>export</code></td>
<td><code>export [name[=value]]</code></td>
<td>

```
Set environment variable

Examples:
  export              → list all vars
  export VAR=value    → set variable
  export VAR+=more    → append to var
```

</td>
</tr>
<tr>
<td><code>unset</code></td>
<td><code>unset [name...]</code></td>
<td>

```
Remove environment variable

Example:
  unset PATH HOME TERM
```

</td>
</tr>
<tr>
<td><code>env</code></td>
<td><code>env</code></td>
<td>

```
Display environment variables

Output format:
  KEY1=value1
  KEY2=value2
  ...
```

</td>
</tr>
<tr>
<td><code>exit</code></td>
<td><code>exit [status]</code></td>
<td>

```
Exit the shell

Examples:
  exit      → exit with status 0
  exit 42   → exit with status 42
  exit 256  → exit with status 0 (256 % 256)
```

</td>
</tr>
</table>

---

## 🔄 Operators & Redirections

### Input/Output Redirections

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║                           REDIRECTION OPERATORS                               ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║   < file     INPUT REDIRECTION                                                ║
║   ──────────────────────────────────────────────────────────────────────────  ║
║   Redirects the content of 'file' to the command's standard input             ║
║                                                                               ║
║   ┌─────────────┐         ┌─────────────┐         ┌─────────────┐             ║
║   │  input.txt  │ ──────▶ │   STDIN     │ ──────▶ │   command   │             ║
║   └─────────────┘         └─────────────┘         └─────────────┘             ║
║                                                                               ║
║   Example: cat < input.txt                                                    ║
║                                                                               ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║   > file     OUTPUT REDIRECTION (Overwrite)                                   ║
║   ──────────────────────────────────────────────────────────────────────────  ║
║   Redirects command's stdout to 'file', overwriting existing content          ║
║                                                                               ║
║   ┌─────────────┐         ┌─────────────┐         ┌─────────────┐             ║
║   │   command   │ ──────▶ │   STDOUT    │ ──────▶ │  output.txt │             ║
║   └─────────────┘         └─────────────┘         └─────────────┘             ║
║                                                                               ║
║   Example: echo "Hello" > output.txt                                          ║
║                                                                               ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║   >> file    OUTPUT REDIRECTION (Append)                                      ║
║   ──────────────────────────────────────────────────────────────────────────  ║
║   Appends command's stdout to 'file' without overwriting                      ║
║                                                                               ║
║   ┌─────────────┐         ┌─────────────────────────────────────┐             ║
║   │   command   │ ──────▶ │  output.txt (existing + new data)   │             ║
║   └─────────────┘         └─────────────────────────────────────┘             ║
║                                                                               ║
║   Example: echo "Line 2" >> output.txt                                        ║
║                                                                               ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║   << DELIMITER    HEREDOC                                                     ║
║   ──────────────────────────────────────────────────────────────────────────  ║
║   Read input until DELIMITER is encountered                                   ║
║                                                                               ║
║   ┌─────────────────────────────────────────────────────────────┐             ║
║   │  cat << END                                                 │             ║
║   │  This is line 1                                             │             ║
║   │  This is line 2                                             │             ║
║   │  END                                                        │             ║
║   └─────────────────────────────────────────────────────────────┘             ║
║                                                                               ║
║   • Without quotes: variables are expanded ($VAR → value)                     ║
║   • With quotes ('END' or "END"): literal, no expansion                       ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
```

### Pipe Operator

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║                              PIPE OPERATOR                                    ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║   cmd1 | cmd2 | cmd3                                                          ║
║   ──────────────────────────────────────────────────────────────────────────  ║
║   Connects stdout of one command to stdin of the next                         ║
║                                                                               ║
║   ┌────────┐      ┌────────┐      ┌────────┐      ┌────────┐                  ║
║   │  cmd1  │─────▶│  PIPE  │─────▶│  cmd2  │─────▶│  PIPE  │───▶...           ║
║   │ stdout │      │        │      │ stdin  │      │        │                  ║
║   └────────┘      └────────┘      └────────┘      └────────┘                  ║
║                                                                               ║
║   Examples:                                                                   ║
║                                                                               ║
║   ls -la | grep ".c"           # List only C files                            ║
║   cat file | sort | uniq       # Sort and remove duplicates                   ║
║   ps aux | grep minishell      # Find minishell process                       ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
```

---

## Data Flow Diagram

```
╔════════════════════════════════════════════════════════════════════════════════════╗
║                         COMPLETE DATA FLOW DIAGRAM                                 ║
╠════════════════════════════════════════════════════════════════════════════════════╣
║                                                                                    ║
║   USER INPUT                                                                       ║
║       │                                                                            ║
║       ▼                                                                            ║
║   ┌──────────────┐                                                                 ║
║   │  readline()  │  ◀── Interactive line editing, history                          ║
║   └──────┬───────┘                                                                 ║
║          │                                                                         ║
║          ▼                                                                         ║
║   ┌──────────────────────────────────────────────────────────────────────────┐     ║
║   │                         PARSING PHASE                                    │     ║
║   ├──────────────────────────────────────────────────────────────────────────┤     ║
║   │                                                                          │     ║
║   │   "echo $HOME | cat -e > file.txt"                                       │     ║
║   │       │                                                                  │     ║
║   │       ▼                                                                  │     ║
║   │   ┌────────────────┐                                                     │     ║
║   │   │   TOKENIZER    │──▶  [WORD] [WORD] [PIPE] [WORD] [WORD] [>] [WORD]   │     ║
║   │   └────────────────┘                                                     │     ║
║   │       │                                                                  │     ║
║   │       ▼                                                                  │     ║
║   │   ┌────────────────┐                                                     │     ║
║   │   │   VALIDATOR    │──▶  Check syntax, quotes, operators                 │     ║
║   │   └────────────────┘                                                     │     ║
║   │       │                                                                  │     ║
║   │       ▼                                                                  │     ║
║   │   ┌────────────────┐                                                     │     ║
║   │   │   EXPANDER     │──▶  $HOME → /home/user                              │     ║
║   │   └────────────────┘                                                     │     ║
║   │       │                                                                  │     ║
║   │       ▼                                                                  │     ║
║   │   ┌────────────────┐                                                     │     ║
║   │   │  CMD BUILDER   │──▶  t_cmd linked list                               │     ║
║   │   └────────────────┘                                                     │     ║
║   │                                                                          │     ║
║   └──────────────────────────────────────────────────────────────────────────┘     ║
║          │                                                                         ║
║          ▼                                                                         ║
║   ┌──────────────────────────────────────────────────────────────────────────┐     ║
║   │                        EXECUTION PHASE                                   │     ║
║   ├──────────────────────────────────────────────────────────────────────────┤     ║
║   │                                                                          │     ║
║   │   ┌─────────────────┐    ┌─────────────────┐                             │     ║
║   │   │ Check if pipe?  │───▶│ Setup pipeline  │                             │     ║
║   │   └─────────────────┘    └────────┬────────┘                             │     ║ 
║   │                                   │                                      │     ║ 
║   │         ┌─────────────────────────┼─────────────────────────┐            │     ║
║   │         │                         │                         │            │     ║
║   │         ▼                         ▼                         ▼            │     ║
║   │   ┌───────────┐           ┌───────────────┐         ┌───────────────┐    │     ║
║   │   │  BUILTIN  │           │    FORK       │         │   PIPE fd     │    │     ║
║   │   │  Execute  │           │   Create      │         │   Setup       │    │     ║
║   │   │  in shell │           │   child       │         │   dup2()      │    │     ║
║   │   └───────────┘           └───────┬───────┘         └───────────────┘    │     ║
║   │                                   │                                      │     ║
║   │                    ┌──────────────┴──────────────┐                       │     ║
║   │                    │                             │                       │     ║
║   │              ┌─────┴─────┐                ┌──────┴──────┐                │     ║
║   │              │   CHILD   │                │   PARENT    │                │     ║
║   │              │  Process  │                │   Process   │                │     ║ 
║   │              ├───────────┤                ├─────────────┤                │     ║
║   │              │ Setup     │                │ wait()      │                │     ║
║   │              │ redirect  │                │ Collect     │                │     ║
║   │              │ execve()  │                │ exit status │                │     ║
║   │              └───────────┘                └─────────────┘                │     ║
║   │                                                                          │     ║
║   └──────────────────────────────────────────────────────────────────────────┘     ║
║          │                                                                         ║
║          ▼                                                                         ║
║   ┌──────────────────────────────────────────────────────────────────────────┐     ║
║   │                        CLEANUP PHASE                                     │     ║
║   ├──────────────────────────────────────────────────────────────────────────┤     ║
║   │  • Free command structures                                               │     ║
║   │  • Free token list                                                       │     ║
║   │  • Update exit status ($?)                                               │     ║
║   │  • Remove heredoc temp files                                             │     ║
║   │  • Loop back to readline                                                 │     ║
║   └──────────────────────────────────────────────────────────────────────────┘     ║
║                                                                                    ║
╚════════════════════════════════════════════════════════════════════════════════════╝
```

---

## Signal Handling

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║                           SIGNAL HANDLING                                     ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║   ┌───────────────────────────────────────────────────────────────────────┐   ║
║   │                    INTERACTIVE MODE                                   │   ║
║   ├───────────────────────────────────────────────────────────────────────┤   ║
║   │                                                                       │   ║
║   │   SIGNAL      KEYSTROKE      BEHAVIOR                                 │   ║
║   │   ──────      ─────────      ────────                                 │   ║
║   │   SIGINT      Ctrl+C         Display new prompt                       │   ║
║   │   SIGQUIT     Ctrl+\         Do nothing (ignored)                     │   ║
║   │   EOF         Ctrl+D         Exit the shell                           │   ║
║   │                                                                       │   ║
║   └───────────────────────────────────────────────────────────────────────┘   ║
║                                                                               ║
║   ┌───────────────────────────────────────────────────────────────────────┐   ║
║   │                    DURING COMMAND EXECUTION                           │   ║
║   ├───────────────────────────────────────────────────────────────────────┤   ║
║   │                                                                       │   ║
║   │   SIGNAL      KEYSTROKE      BEHAVIOR                                 │   ║
║   │   ──────      ─────────      ────────                                 │   ║
║   │   SIGINT      Ctrl+C         Terminate running command                │   ║
║   │   SIGQUIT     Ctrl+\         Terminate with core dump message         │   ║
║   │                                                                       │   ║
║   └───────────────────────────────────────────────────────────────────────┘   ║
║                                                                               ║
║   ┌───────────────────────────────────────────────────────────────────────┐   ║
║   │                        IN HEREDOC                                     │   ║
║   ├───────────────────────────────────────────────────────────────────────┤   ║
║   │                                                                       │   ║
║   │   SIGNAL      KEYSTROKE      BEHAVIOR                                 │   ║
║   │   ──────      ─────────      ────────                                 │   ║
║   │   SIGINT      Ctrl+C         Cancel heredoc, return to prompt         │   ║
║   │   EOF         Ctrl+D         End heredoc input                        │   ║
║   │                                                                       │   ║
║   └───────────────────────────────────────────────────────────────────────┘   ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
```

---

## Concepts

> This section explains the fundamental concepts behind shell implementation. Understanding these will help you build your own shell from scratch.

---

### Process Management

A shell's primary job is to create and manage processes. Here's how it works at the system level:

#### The `fork()` System Call

```c
#include <unistd.h>

pid_t fork(void);
```

**What it does:**
- Creates an **exact copy** of the current process (parent)
- The copy is called the **child process**
- Both processes continue executing from the point of `fork()`

**Return values:**
| In Parent Process | In Child Process |
|-------------------|------------------|
| Child's PID (> 0) | 0                |
| -1 on error       | Never returns -1 |

**Example:**
```c
pid_t pid = fork();

if (pid == -1)
{
    perror("fork failed");
    exit(1);
}
else if (pid == 0)
{
    // Child process code
    printf("I am the child! PID: %d\n", getpid());
}
else
{
    // Parent process code
    printf("I am the parent! Child PID: %d\n", pid);
}
```

**Visual representation:**
```
    ┌─────────────────────┐
    │   Parent Process    │
    │      (shell)        │
    └──────────┬──────────┘
               │
          fork()
               │
    ┌──────────┴──────────┐
    │                     │
    ▼                     ▼
┌─────────┐         ┌─────────┐
│ Parent  │         │  Child  │
│ (shell) │         │ (copy)  │
│ pid > 0 │         │ pid = 0 │
└─────────┘         └─────────┘
    │                     │
    │                     ▼
    │              ┌─────────────┐
    │              │   execve()  │
    │              │ Replace with│
    │              │ new program │
    │              └─────────────┘
    │                     │
    ▼                     ▼
 wait()              Execute cmd
    │                     │
    └──────────┬──────────┘
               │
          Continue
```

---

#### The `execve()` System Call

```c
#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);
```

**What it does:**
- **Replaces** the current process with a new program
- The old program is completely overwritten
- If successful, `execve()` **never returns**

**Parameters:**
| Parameter  | Description                                    |
|------------|------------------------------------------------|
| `pathname` | Full path to the executable (e.g., "/bin/ls")  |
| `argv[]`   | Array of arguments, NULL-terminated            |
| `envp[]`   | Environment variables, NULL-terminated         |

**Example:**
```c
char *args[] = {"/bin/ls", "-la", NULL};
char *env[] = {"PATH=/bin:/usr/bin", "HOME=/home/user", NULL};

execve("/bin/ls", args, env);

// If we reach here, execve failed!
perror("execve failed");
exit(127);
```

**Important notes:**
- `argv[0]` should be the program name
- All arrays must be NULL-terminated
- On success, the calling process image is replaced
- On failure, returns -1 and sets `errno`

---

#### The `wait()` and `waitpid()` System Calls

```c
#include <sys/wait.h>

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```

**What they do:**
- Suspend the parent until a child process terminates
- Collect the child's exit status
- Prevent "zombie" processes

**Wait macros for status:**
| Macro                  | Description                              |
|------------------------|------------------------------------------|
| `WIFEXITED(status)`    | True if child exited normally            |
| `WEXITSTATUS(status)`  | Exit code (0-255) if exited normally     |
| `WIFSIGNALED(status)`  | True if child was killed by signal       |
| `WTERMSIG(status)`     | Signal number that killed the child      |

**Example:**
```c
pid_t pid = fork();

if (pid == 0)
{
    // Child: execute command
    execve("/bin/ls", args, envp);
    exit(127);  // execve failed
}
else
{
    // Parent: wait for child
    int status;
    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status))
        printf("Child exited with code: %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Child killed by signal: %d\n", WTERMSIG(status));
}
```

---

### File Descriptors

File descriptors (FDs) are integers that represent open files/streams in Unix.

#### Standard File Descriptors

| FD | Name   | Macro           | Default Device |
|----|--------|-----------------|----------------|
| 0  | stdin  | `STDIN_FILENO`  | Keyboard       |
| 1  | stdout | `STDOUT_FILENO` | Terminal       |
| 2  | stderr | `STDERR_FILENO` | Terminal       |

#### The `dup2()` System Call

```c
#include <unistd.h>

int dup2(int oldfd, int newfd);
```

**What it does:**
- Duplicates `oldfd` to `newfd`
- If `newfd` is open, it's closed first
- Both FDs now point to the same file/pipe

**This is how redirections work:**
```c
// Redirect stdout to a file
int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, STDOUT_FILENO);  // stdout now writes to file
close(fd);                 // Close original fd

printf("This goes to file!\n");  // Writes to output.txt
```

**Visual representation:**
```
BEFORE dup2(fd, 1):                 AFTER dup2(fd, 1):
┌─────────────────┐                 ┌─────────────────┐
│  FD Table       │                 │  FD Table       │
├─────────────────┤                 ├─────────────────┤
│ 0 → stdin       │                 │ 0 → stdin       │
│ 1 → terminal    │    ═══════▶     │ 1 → output.txt  │
│ 2 → terminal    │                 │ 2 → terminal    │
│ 3 → output.txt  │                 │ 3 → output.txt  │
└─────────────────┘                 └─────────────────┘
```

---

### 🔗 Pipes In-Depth

#### The `pipe()` System Call

```c
#include <unistd.h>

int pipe(int pipefd[2]);
```

**What it does:**
- Creates a unidirectional data channel
- `pipefd[0]` = read end (data comes OUT)
- `pipefd[1]` = write end (data goes IN)

**Visual representation:**
```
┌─────────────────────────────────────────────────────────────┐
│                         PIPE                                │
│                                                             │
│   ┌─────────┐                              ┌─────────┐      │
│   │ Writer  │   pipefd[1]      pipefd[0]   │ Reader  │      │
│   │ Process │ ───────────▶ ○ ─────────────▶│ Process │      │
│   └─────────┘     write      pipe buffer   └─────────┘      │
│                                   read                      │
│                                                             │
│   Data flows: Writer ──▶ pipe ──▶ Reader                    │
│   (unidirectional - one way only!)                          │
└─────────────────────────────────────────────────────────────┘
```

**Complete pipe example (cmd1 | cmd2):**
```c
int pipefd[2];
pipe(pipefd);  // Create pipe

pid_t pid1 = fork();
if (pid1 == 0)
{
    // Child 1: cmd1 (writer)
    close(pipefd[0]);           // Close unused read end
    dup2(pipefd[1], STDOUT_FILENO);  // stdout → pipe write end
    close(pipefd[1]);           // Close original write end
    
    execve("/bin/ls", args1, envp);  // ls output goes to pipe
    exit(127);
}

pid_t pid2 = fork();
if (pid2 == 0)
{
    // Child 2: cmd2 (reader)
    close(pipefd[1]);           // Close unused write end
    dup2(pipefd[0], STDIN_FILENO);   // stdin ← pipe read end
    close(pipefd[0]);           // Close original read end
    
    execve("/usr/bin/wc", args2, envp);  // wc reads from pipe
    exit(127);
}

// Parent: close both ends and wait
close(pipefd[0]);
close(pipefd[1]);
waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);
```

**Why close unused pipe ends?**
1. **For writer:** Close read end - not needed for writing
2. **For reader:** Close write end - so EOF is detected when writer finishes
3. **Rule:** Each process should close FDs it doesn't use

---

### Signals

#### What are Signals?

Signals are software interrupts sent to a process. They can be:
- Sent by the kernel (e.g., SIGSEGV for invalid memory access)
- Sent by user (e.g., Ctrl+C sends SIGINT)
- Sent by another process (using `kill()`)

#### Common Signals

| Signal  | Number | Default Action | Triggered By           |
|---------|--------|----------------|------------------------|
| SIGINT  | 2      | Terminate      | Ctrl+C                 |
| SIGQUIT | 3      | Core dump      | Ctrl+\                 |
| SIGKILL | 9      | Terminate      | Cannot be caught       |
| SIGSEGV | 11     | Core dump      | Invalid memory access  |
| SIGPIPE | 13     | Terminate      | Write to closed pipe   |
| SIGTERM | 15     | Terminate      | Polite termination     |
| SIGCHLD | 17     | Ignore         | Child process ended    |

#### The `signal()` Function

```c
#include <signal.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

**Handler options:**
| Handler      | Behavior                        |
|--------------|---------------------------------|
| `SIG_DFL`    | Default action for signal       |
| `SIG_IGN`    | Ignore the signal               |
| Custom func  | Call this function when signaled|

**Example:**
```c
void sigint_handler(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    // Don't use printf in signal handlers!
    // Use write() instead (async-signal-safe)
}

int main(void)
{
    signal(SIGINT, sigint_handler);   // Handle Ctrl+C
    signal(SIGQUIT, SIG_IGN);         // Ignore Ctrl+\
    
    while (1)
    {
        // Shell loop
    }
}
```

**Important rules for signal handlers:**
1. Keep them short and simple
2. Use only async-signal-safe functions (like `write()`, not `printf()`)
3. Use `volatile sig_atomic_t` for flags
4. Restore signal handlers if needed

---

### Environment Variables

Environment variables are key-value pairs passed to processes.

#### How they work:

```c
// Main receives environment
int main(int argc, char **argv, char **envp)
{
    // envp is a NULL-terminated array of strings
    // Format: "KEY=value"
    
    for (int i = 0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);
    
    return 0;
}
```

#### Getting/Setting Environment Variables

```c
#include <stdlib.h>

// Get a variable
char *getenv(const char *name);
// Example: char *home = getenv("HOME");

// Set a variable (in current process)
int setenv(const char *name, const char *value, int overwrite);

// Remove a variable
int unsetenv(const char *name);
```

#### How shell handles environment:

```
┌────────────────────────────────────────────────────────────────┐
│                    ENVIRONMENT FLOW                            │
├────────────────────────────────────────────────────────────────┤
│                                                                │
│   1. Shell starts with environment from parent                 │
│      $ ./minishell                                             │
│      └── Inherits: PATH, HOME, USER, etc.                      │
│                                                                │
│   2. User modifies with export/unset                           │
│      @xero⚔ export MY_VAR=hello                                │
│      └── Shell's internal envp is updated                      │
│                                                                │
│   3. Child processes inherit environment                       │
│      @xero⚔ /bin/echo $MY_VAR                                  │
│      └── fork() copies envp                                    │
│      └── execve() receives envp as 3rd argument                │
│                                                                │
└────────────────────────────────────────────────────────────────┘
```

---

### The PATH Variable

When you type a command without a full path, the shell searches for it in directories listed in `$PATH`.

#### How PATH lookup works:

```c
// PATH example: "/usr/local/bin:/usr/bin:/bin"
// Command: "ls"

// Shell tries in order:
// 1. /usr/local/bin/ls  → exists? no
// 2. /usr/bin/ls        → exists? no  
// 3. /bin/ls            → exists? YES! Execute this
```

**Implementation pseudocode:**
```c
char *find_command_path(char *cmd, char **envp)
{
    char *path = get_env_value("PATH", envp);
    char **dirs = split(path, ':');
    
    for (int i = 0; dirs[i] != NULL; i++)
    {
        char *full_path = join(dirs[i], "/", cmd);
        
        if (access(full_path, X_OK) == 0)  // Is executable?
            return full_path;
        
        free(full_path);
    }
    return NULL;  // Command not found
}
```

---

### Key System Calls Reference

| System Call | Header          | Purpose                                |
|-------------|-----------------|----------------------------------------|
| `fork()`    | `<unistd.h>`    | Create child process                   |
| `execve()`  | `<unistd.h>`    | Execute a program                      |
| `wait()`    | `<sys/wait.h>`  | Wait for child process                 |
| `waitpid()` | `<sys/wait.h>`  | Wait for specific child                |
| `pipe()`    | `<unistd.h>`    | Create pipe for IPC                    |
| `dup()`     | `<unistd.h>`    | Duplicate file descriptor              |
| `dup2()`    | `<unistd.h>`    | Duplicate FD to specific number        |
| `open()`    | `<fcntl.h>`     | Open file, get FD                      |
| `close()`   | `<unistd.h>`    | Close file descriptor                  |
| `read()`    | `<unistd.h>`    | Read from FD                           |
| `write()`   | `<unistd.h>`    | Write to FD                            |
| `access()`  | `<unistd.h>`    | Check file permissions                 |
| `getcwd()`  | `<unistd.h>`    | Get current working directory          |
| `chdir()`   | `<unistd.h>`    | Change directory                       |
| `signal()`  | `<signal.h>`    | Set signal handler                     |
| `kill()`    | `<signal.h>`    | Send signal to process                 |
| `exit()`    | `<stdlib.h>`    | Terminate process                      |

---

### Tips for Building Your Own Shell

1. **Start simple:** Parse and execute single commands first
2. **Add features incrementally:** Builtins → Redirections → Pipes
3. **Test frequently:** Each feature should work before adding the next
4. **Handle errors gracefully:** Check return values of all syscalls
5. **Manage memory carefully:** Free everything you allocate
6. **Use valgrind:** Detect memory leaks early
7. **Study bash behavior:** Test edge cases in bash first

```
┌─────────────────────────────────────────────────────────────────┐
│                  SHELL DEVELOPMENT ROADMAP                      │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│   Level 1: Basic Shell                                          │
│   ├── Read input with readline                                  │
│   ├── Parse simple commands                                     │
│   └── Execute with fork/execve/wait                             │
│                                                                 │
│   Level 2: Builtins                                             │
│   ├── echo, cd, pwd                                             │
│   ├── export, unset, env                                        │
│   └── exit                                                      │
│                                                                 │
│   Level 3: Redirections                                         │
│   ├── Input redirection (<)                                     │
│   ├── Output redirection (>)                                    │
│   ├── Append redirection (>>)                                   │
│   └── Heredoc (<<)                                              │
│                                                                 │
│   Level 4: Pipes                                                │
│   ├── Single pipe (cmd1 | cmd2)                                 │
│   └── Multiple pipes (cmd1 | cmd2 | cmd3)                       │
│                                                                 │
│   Level 5: Advanced Features                                    │
│   ├── Environment variable expansion                            │
│   ├── Quote handling (' and ")                                  │
│   ├── Signal handling                                           │
│   └── Exit status ($?)                                          │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## Testing

### Basic Tests

```bash
# Test echo
@xero⚔ echo Hello World
Hello World

# Test echo -n
@xero⚔ echo -n "No newline"
No newline@xero⚔ 

# Test pwd
@xero⚔ pwd
/current/directory

# Test cd
@xero⚔ cd /tmp && pwd
/tmp

# Test environment
@xero⚔ export TEST=hello
@xero⚔ echo $TEST
hello
@xero⚔ unset TEST
@xero⚔ echo $TEST

```

### Redirection Tests

```bash
# Output redirection
@xero⚔ echo "Hello" > test.txt
@xero⚔ cat test.txt
Hello

# Append redirection  
@xero⚔ echo "World" >> test.txt
@xero⚔ cat test.txt
Hello
World

# Input redirection
@xero⚔ cat < test.txt
Hello
World

# Heredoc
@xero⚔ cat << EOF
> Line 1
> Line 2
> EOF
Line 1
Line 2
```

### Pipe Tests

```bash
# Simple pipe
@xero⚔ ls | wc -l
42

# Multiple pipes
@xero⚔ cat /etc/passwd | grep root | wc -l
1

# Pipe with redirection
@xero⚔ ls -la | grep ".c" > cfiles.txt
```

### Edge Cases

```bash
# Empty command
@xero⚔ 
@xero⚔

# Quotes
@xero⚔ echo "hello 'world'"
hello 'world'

@xero⚔ echo 'hello "world"'
hello "world"

# Variable in double quotes
@xero⚔ echo "$HOME"
/home/user

# Variable in single quotes (no expansion)
@xero⚔ echo '$HOME'
$HOME

# Exit status
@xero⚔ ls nonexistent
ls: cannot access 'nonexistent': No such file or directory
@xero⚔ echo $?
2
```

---

## Technical Details

### Memory Management

```
┌────────────────────────────────────────────────────────────────────────────────┐
│                          MEMORY MANAGEMENT                                     │
├────────────────────────────────────────────────────────────────────────────────┤
│                                                                                │
│   XERO follows strict memory management rules:                                 │
│                                                                                │
│   ✓ All malloc'd memory is properly freed                                      │
│   ✓ No memory leaks in user code                                               │
│   ✓ Readline leaks are documented and acceptable                               │
│   ✓ Environment is properly duplicated and managed                             │
│                                                                                │
│   ┌─────────────────────────────────────────────────────────────────────────┐  │
│   │                      CLEANUP FUNCTIONS                                  │  │
│   ├─────────────────────────────────────────────────────────────────────────┤  │
│   │                                                                         │  │
│   │   free_tokens()    - Free token linked list                             │  │
│   │   free_cmd()       - Free command structure                             │  │
│   │   free_args()      - Free args array                                    │  │
│   │   free_envp()      - Free environment array                             │  │
│   │   free_arg_list()  - Free argument linked list                          │  │
│   │                                                                         │  │
│   └─────────────────────────────────────────────────────────────────────────┘  │
│                                                                                │
└────────────────────────────────────────────────────────────────────────────────┘
```

### Error Handling

```
┌────────────────────────────────────────────────────────────────────────────────┐
│                            ERROR HANDLING                                      │
├────────────────────────────────────────────────────────────────────────────────┤
│                                                                                │
│   XERO handles various error conditions gracefully:                            │
│                                                                                │
│   • Syntax errors           →  Display error, return to prompt                 │
│   • Command not found       →  Print error message, exit status 127            │
│   • Permission denied       →  Print error message, exit status 126            │
│   • Invalid redirections    →  Print error, don't execute                      │
│   • Unclosed quotes         →  Syntax error message                            │
│   • Invalid operators       →  Syntax error message                            │
│   • Memory allocation fail  →  Clean exit                                      │
│                                                                                │
│   Exit Status Codes:                                                           │
│   ┌─────────────────────────────────────────────────────────────────────────┐  │
│   │  0   - Success                                                          │  │
│   │  1   - General errors                                                   │  │ 
│   │  2   - Misuse of shell command                                          │  │
│   │  126 - Command not executable                                           │  │
│   │  127 - Command not found                                                │  │
│   │  130 - Terminated by Ctrl+C (SIGINT)                                    │  │
│   │  131 - Terminated by Ctrl+\ (SIGQUIT)                                   │  │
│   └─────────────────────────────────────────────────────────────────────────┘  │
│                                                                                │
└────────────────────────────────────────────────────────────────────────────────┘
```

---

## Authors

```
╔═══════════════════════════════════════════════════════════════════════════════════╗
║                                                                                   ║
║                              ⚔️  THE XERO TEAM  ⚔️                                  ║
║                                                                                   ║
╠═══════════════════════════════════════════════════════════════════════════════════╣
║                                                                                   ║
║   ┌─────────────────────────────────────────────────────────────────────────┐     ║
║   │                                                                         │     ║
║   │   👤 CHIKI Badreddine                                                   │     ║
║   │   ─────────────────────────────                                         │     ║
║   │   📧 bchiki@student.42.fr                                               │     ║
║   │   🛠️  Lead Parser & Core Architect                                      │     ║
║   │                                                                         │     ║
║   │   Responsibilities:                                                     │     ║
║   │   • Tokenization system                                                 │     ║
║   │   • Variable expansion                                                  │     ║
║   │   • Quote handling                                                      │     ║
║   │   • Syntax validation                                                   │     ║
║   │   • Signal handling                                                     │     ║
║   │   • Input processing                                                    │     ║
║   │                                                                         │     ║
║   └─────────────────────────────────────────────────────────────────────────┘     ║
║                                                                                   ║
║   ┌─────────────────────────────────────────────────────────────────────────┐     ║
║   │                                                                         │     ║
║   │   👤 Alae Ben Dris Alami                                                │     ║
║   │   ─────────────────────────────                                         │     ║
║   │   📧 aben-dri@student.42.fr                                             │     ║
║   │   🛠️  Execution Engine Specialist                                       │     ║
║   │                                                                         │     ║
║   │   Responsibilities:                                                     │     ║
║   │   • Command execution                                                   │     ║
║   │   • Pipe implementation                                                 │     ║
║   │   • Redirection handlers                                                │     ║
║   │   • Heredoc processing                                                  │     ║
║   │   • Built-in commands                                                   │     ║
║   │   • Process management                                                  │     ║
║   │                                                                         │     ║
║   └─────────────────────────────────────────────────────────────────────────┘     ║
║                                                                                   ║
╚═══════════════════════════════════════════════════════════════════════════════════╝
```

---

## License

This project was developed as part of the **42 School** curriculum.

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║                                                                               ║
║                          42 SCHOOL PROJECT                                    ║
║                                                                               ║
║   This project is part of the 42 cursus and is subject to 42 rules.           ║
║   It may not be redistributed or used for commercial purposes.                ║
║                                                                               ║
║   © 2025 CHIKI Badreddine & Alae Ben Dris Alami                               ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
```

---

<div align="center">

### Special Commands

```bash
# Check XERO version
@xero⚔ xero --version

# View developer credits  
@xero⚔ xero --devs
```

</div>


