
/**
 * @brief	readline will read a line from the terminal and return it, using prompt as a prompt
 * 			it will allocat the string using malloc.
 * 			for more information GNU READLINE
 * @param	prompt a string that will be printed at at the beginning of the terminal line
 * @return	return  a allocated string
 */
char *   readline (const char *prompt);

/**
 * @brief Replace the contents of rl_line_buffer with text. 
 * The point and mark are preserved, if possible.
 * If clear_undo is non-zero, the undo list associated with the current line is cleared
 * 
 */
void	rl_replace_line(const char *text, int clear_undo);

/**
 * @brief Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.
 * 
 */
void	rl_redisplay(void);

/**
 * @brief import a string in th readline history buffer
 * 
 */
int		 add_history(const char *);

/**
 * @brief Clear the history list by deleting all of the entries,
 *  in the same manner as the History library’s clear_history() function.
 *  This differs from clear_history because it frees private data Readline saves in the history list
 * 
 */
void	rl_clear_history(void);

/**
 * @brief Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
 * 
 */
	int	rl_on_new_line(void);

/**
 * @brief Replace the contents of rl_line_buffer with text. The point and mark are preserved, 
 * if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
 * 
 */
void	rl_replace_line(const char *text, int clear_undo);

/**
 * @brief Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.
 * 
 */
void	rl_redisplay(void);

////printf();
////malloc();
////free();
////write();

/**
 * @brief access() checks whether the calling process can access the file pathname. 
 * If pathname is a symbolic link, it is dereferenced.
 * 
 */
int	access(const char *path, int mode);

////open();
////read();
////close()

/**
 * @brief Fork system call is used for creating a new process, 
 * which is called child process, which runs concurrently with the process that makes the fork()
 *  call (parent process). After a new child process is created,
 *  both processes will execute the next instruction following the fork() system call. 
 * A child process uses the same pc(program counter), same CPU registers,
 *  same open files which use in the parent process.
 * 
 * @note the big diffrence in comparision to prhread_create is 
 * that it create its own memory and dont use the shared own like with thread
 *  so no data races less data sharing
 */
pid_t	fork(void);

/**
 * @brief Fork system call is used for creating a new process, 
 * which is called child process,
 *  which runs concurrently with the process that makes the fork() call (parent process). 
 * After a new child process is created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), 
 * same CPU registers, same open files which use in the parent process.
 * 
 * @return returns the pid of the dead children
 */
pid_t wait(int *stat_loc);

/**
 * @brief wait for the pid of the childprocess to change
 * 
 * @param pid
 * Specifies the child processes the caller wants to wait for:
 * If pid is greater than 0, waitpid() waits for termination of the specific child whose process ID is equal to pid.
 * If pid is equal to zero, waitpid() waits for termination of any child whose process group ID is equal to that of the caller.
 * If pid is -1, waitpid() waits for any child process to end.
 * If pid is less than -1, waitpid() waits for the termination of any child whose process group ID is equal to the absolute value of pid.
 * @param status_tr Points to a location where waitpid() can store a status value. This status value is zero if the child process explicitly returns zero status. Otherwise, it is a value that can be analyzed with the status analysis macros described in “Status Analysis Macros”, below.
 * The status_ptr pointer may also be NULL, in which case waitpid() ignores the child's return status.
 * @param options
 * Specifies additional information for waitpid(). The options value is constructed from the bitwise inclusive-OR of zero or more of the following flags defined in the sys/wait.h header file:
 *? WCONTINUED
 * Special behavior for XPG4.2: Reports the status of any continued child processes as well as terminated ones. The WIFCONTINUED macro lets a process distinguish between a continued process and a terminated one.
 *? WNOHANG
 * Demands status information immediately. If status information is immediately available on an appropriate child process, waitpid() returns this information. Otherwise, waitpid() returns immediately with an error code indicating that the information was not available. In other words, WNOHANG checks child processes without causing the caller to be suspended.
 *? WUNTRACED
 * Reports on stopped child processes as well as terminated ones. The WIFSTOPPED macro lets a process distinguish between a stopped process and a terminated one.
 */
pid_t waitpid(pid_t pid, int *status_ptr, int options);

/**
 * @brief its wait for any child to return
 * its like waitpid but returns resource usage of the child process resource usage inside of rusage 
 * 
 */
pid_t wait3(int *status, int options, struct rusage *rusage);

/**
 * @brief like wait3 but waits only for a specifc child
 * 
 */

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);


/**
 * @brief old anitc version of sigaction only use it if u cant use sigaction
 * 
 */
void (*signal(int sig, void (*func)(int)))(int);

struct sigaction {
 union __sigaction_u __sigaction_u;  /* signal handler */
 sigset_t sa_mask;               /* signal mask to apply */
 int     sa_flags;               
};
// handler =  the function that will get executed when the linked signal get resieve
// with the mask we can say what signal we will resieve
// can give us acces to siginfo and maybe more

/**
 * @brief link signalnumber to a sigaction struct that contain the funktion adress 				
 * 
 */
int sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);

sigemptyset();
sigaddset();
kill();
exit();
getcwd();
chdir();
stat();
lstat();
fstat();
unlink();
execve();
dup();
dup2();
pipe();
opendir();
readdir();
closedir();
strerror();
perror();
isatty();
ttyname();
ttyslot();
ioctl();
getenv();
tcsetattr();
tcgetattr();
tgetent();
tgetflag();
tgetnum();
tgetstr();
tgoto();
tputs();