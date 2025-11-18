# C-Shell

A custom Unix-like shell implementation in C that provides essential shell functionalities including built-in commands, process management, I/O redirection, and signal handling.

## Features

### 1. Interactive Display
- Dynamic shell prompt showing: `<username@system_name:curr_dir>`
- Home directory represented as `~`
- Real-time directory updates in the prompt
- No hard-coded system information

### 2. Built-in Commands

#### `echo`
Displays text arguments with proper spacing handling.
```bash
echo all the best
# Output: all the best
```

#### `pwd`
Prints the absolute path of the current working directory.
```bash
pwd
# Output: /home/user/logs
```

#### `cd`
Changes the current directory with multiple options:
- `cd` or `cd ~` - Navigate to home directory
- `cd ..` - Move one level up
- `cd -` - Switch to previous directory (prints the path)
- `cd [path]` - Change to specified directory

#### `history`
Manages command history with persistence:
- Stores last 20 commands
- Displays last 10 commands when invoked
- Persistent across sessions (saved to file)
- Automatically overwrites oldest commands
- Ignores duplicate consecutive commands

### 3. Process Management

#### Foreground Processes
Execute external commands and wait for completion:
```bash
ls -l
gcc program.c -o program
grep "pattern" file.txt
```

#### Background Processes
Run commands asynchronously using `&`:
```bash
sleep 10 &
./long_running_task &
```

### 4. I/O Redirection
Support for input and output redirection:
```bash
# Input redirection
command < input.txt

# Output redirection
command > output.txt

# Both
grep "hello" < input.txt > output.txt
```

### 5. Signal Handling
- **Ctrl+C**: Terminates foreground process only, shell continues running
- **Ctrl+D**: Exits the shell cleanly
- **Background Process Cleanup**: Automatic zombie process prevention

## Building and Running

### Prerequisites
- GCC compiler
- Linux/Unix environment
- Standard C library

### Compilation
```bash
make all
```

### Running the Shell
```bash
./shell
```

### Cleaning Build Files
```bash
make clean
```

## Project Structure
```
C-Shell/
├── commands.c
├── commands.h
├── defines.h
├── history.c
├── history.h
├── includes.h
├── log.c
├── log.h
├── main.c
├── makefile
├── process.c
├── process.h
├── README.md
├── utils.c
└── utils.h
```

## Implementation Details

### Built-in Commands
Implemented without using `exec` family system calls. Custom logic handles all built-in command functionality.

### Process Execution
- Fork-exec model for external commands
- Parent process management for foreground/background execution
- Proper signal handling and process cleanup

### History Persistence
Command history is stored in a file within the shell's home directory, maintaining state across different shell sessions.

## Error Handling
- System call errors handled using `perror`
- Invalid command arguments produce appropriate error messages
- Graceful handling of file I/O errors
- Proper validation for directory changes