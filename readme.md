# C shell
A shell written in C to perform various tasks like echo,pipelining ,redirection ,job handlind,signalling etc
## FILES
### .sh.c
contains the main shell loop and takes input from commandline to 
direct it to functions in other files.
Handles signals for child process termination
also performs cd and pwd
Contains other functions to generate the shell location that is outputed

### execute.c
contains forking and creating of background/foreground child process and replacing child processes with commands

### echo.c
performs echo

### readline.c
parses the input

### relative.c
handles the relative location to generate the output the current directory

### pinfo.c
performs the pinfo functionality.
Cannot generate executable path for all pid
Parses the /proc/pid/status and /proc/pid/exe
Assumes the status page is similar on all systems;

### test.c
handles ls

History functionality is incomplete hence commented out
also history.txt remains in the folder but please ignore

###  bg.c
handles bg command.Checks the whether the correct job number is given and sends
SIGCONT to the corresponding PID

### jobs.c
handles jobs functionionality.The function is passed a array of structure which contains 
information regarding jobs.The function extracts the running status by parsing the /proc/%pid/status folder and prints the info corresponding to all valid active job number
NOTE : important Assumption-My system can assign a max pid of roughly 32000 hence I use an array of 40000 instread of linked list of structure to store the relevant info.Other computer may encounter seg fault if pid exceeds 40000-1;

### fg.c
handles fg command
verifies the arguments corresponds to valid job number and brings it to the foreground by giving it terminal access and making the parent wait on it.returns it to background when stopped.

### kjob.c
send signals to process using job_id using the kill command

### overkill.c
sends sigint to all background process.

### signals
control + Z is handled by handle1.Sends SIGSTOP to foreground process pid.
A global variable stores -1 if shell is in foreground else the pid of foreground process

Control + C sends signal SIGINT using kill to the foreground process tracked by the aforementioned global variable

Control + D is handled by checking the return value of gets() while taking commandline input

### Parse.c
handles parsing for redirection purposes.
redirection is handled by duplication fd's corresponding to STDIN/STDOUT

### Pipelining
Handled in the main loop by separating the commands by | symbol and running them in loops(sequentially) and using pipes to read and write

Quit is done using exit

## NOTES
lines.txt is text file for testing different commands

history.txt is for history command.That is incomplete so please ignore

shell is the executable for the shell

There is a small chance that there may be some stray uncommented print statements
somewhere that I should have commented out but missed somehow.

## Compilation Instruction

To compile:

gcc -c -O echo.c pinfo.c relative.c readline.c test.c execute.c sh.c -w

To link

gcc  -O echo.o pinfo.o relative.o readline.o test.o execute.o sh.o

then run ./a.out

Or you can directly run ./shell as it is in the folder

Also makefile is available
