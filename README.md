# suii-shell

This project is an implementation of a shell for linux and other unix like operating systems.
The shell provides a command line interface where users can enter commands.

## Supported Commands

The shell handles two types of commands. They are:
<ul>
<li>Internal Commands: These commands are handled directly by the shell.</li>
<li>External Commands: These commands are executed by external programs.</li>
</ul>

The supported internal commands are: ``` "cd" , "echo" , "pwd" ```
The supported external commands are: ``` "ls" , "cat" , "date" , "rm" , "mkdir" ```
Thread-based execution occurs if the command is followed by the characters "&t". The rest of the functionality remains the same.

## How are the commands handled?

External commands are executed by creating a new process using the fork() system call and running the individual program using the execl() family of system calls. The parent program waits for the child program to terminate using the wait() family of system calls.
The same functionality is achieved using threads by using pthread_create() instead of fork() and system() instead of execl().

Internal commands are implemented directly and do not require forking.

## Running the shell

Simply clone the repo. Open the folder suishell and make. Run the program.
