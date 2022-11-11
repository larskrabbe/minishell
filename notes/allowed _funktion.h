
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

/**
 * @brief set the sigmaks to 0 so every signal will get through it
*/
int sigemptyset(sigset_t *set);

/**
 * @brief Add a signalnumber to the signalmask
*/
 int sigaddset(sigset_t *set, int signum);

/**
 * @brief send a  process a signal
*/
int kill(pid_t pid, int sig);

/**
 * @brief cause normal process termination
*/
noreturn void exit(int status);

/**
 * @brief The getcwd() function copies an absolute pathname of the current
	   working directory to the array pointed to by buf, which is of
	   length size.
*/
char *getcwd(char *buf, size_t size);

/**
 * @brief changes the current working directory of the calling
	   process to the directory specified in path.
*/
int chdir(const char *path);

/**
 * @brief  These functions return information about a file, in the buffer
	   pointed to by statbuf.  No permissions are required on the file
	   itself, but—in the case of stat(), fstatat(), and lstat()—execute
	   (search) permission is required on all of the directories in
	   pathname that lead to the file.
*/
int stat(const char *restrict pathname,struct stat *restrict statbuf);
struct stat {
	dev_t     st_dev;         /* ID of device containing file */
	ino_t     st_ino;         /* Inode number */
	mode_t    st_mode;        /* File type and mode */
	nlink_t   st_nlink;       /* Number of hard links */
	uid_t     st_uid;         /* User ID of owner */
	gid_t     st_gid;         /* Group ID of owner */
	dev_t     st_rdev;        /* Device ID (if special file) */
	off_t     st_size;        /* Total size, in bytes */
	blksize_t st_blksize;     /* Block size for filesystem I/O */
	blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

	/* Since Linux 2.6, the kernel supports nanosecond
		precision for the following timestamp fields.
		For the details before Linux 2.6, see NOTES. */

	struct timespec st_atim;  /* Time of last access */
	struct timespec st_mtim;  /* Time of last modification */
	struct timespec st_ctim;  /* Time of last status change */

#define st_atime st_atim.tv_sec      /* Backward compatibility */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};

/**
 * @brief lstat() is identical to stat(), except that if pathname is a
	 symbolic link, then it returns information about the link itself,
	 not the file that the link refers to.
*/
 int lstat(const char *restrict pathname,struct stat *restrict statbuf);

/**
 * @brief 
	 fstat() is identical to stat(), except that the file about which
	 information is to be retrieved is specified by the file
	 descriptor fd.
*/
int fstat(int fd, struct stat *statbuf);

/**
 * @brief    unlink() deletes a name from the filesystem.  If that name was
	 the last link to a file and no processes have the file open, the
	 file is deleted and the space it was using is made available for
	 reuse.
*/
int unlink(const char *pathname);

/**
 * @brief execve() executes the program referred to by pathname.  This
	 causes the program that is currently being run by the calling
	 process to be replaced with a new program, with newly initialized
	 stack, heap, and (initialized and uninitialized) data segments.
*/
int execve(const char *pathname, char *const argv[],char *const envp[]);

/**
 * @brief  The dup() system call allocates a new file descriptor that refers
	 to the same open file description as the descriptor oldfd.  (For
	 an explanation of open file descriptions, see open(2).)  The new
	 file descriptor number is guaranteed to be the lowest-numbered
	 file descriptor that was unused in the calling process.
*/
int dup(int oldfd);

/**
 * @brief  The dup2() system call performs the same task as dup(), but
	 instead of using the lowest-numbered unused file descriptor, it
	 uses the file descriptor number specified in newfd.  In other
	 words, the file descriptor newfd is adjusted so that it now
	 refers to the same open file description as oldfd.
*/
int dup2(int oldfd, int newfd);

/**
 * @brief   pipe() creates a pipe, a unidirectional data channel that can be
	 used for interprocess communication.  The array pipefd is used to
	 return two file descriptors referring to the ends of the pipe.
	 pipefd[0] refers to the read end of the pipe.  pipefd[1] refers
	 to the write end of the pipe.  Data written to the write end of
	 the pipe is buffered by the kernel until it is read from the read
	 end of the pipe.  For further details, see pipe(7).
*/
 int pipe(int pipefd[2]);

/**
 * @brief      The opendir() function opens a directory stream corresponding to
	 the directory name, and returns a pointer to the directory
	 stream.  The stream is positioned at the first entry in the
	 directory.
*/
DIR *opendir(const char *name);


struct dirent {
	ino_t          d_ino;       /* Inode number */
	off_t          d_off;       /* Not an offset; see below */
	unsigned short d_reclen;    /* Length of this record */
	unsigned char  d_type;      /* Type of file; not supported
						by all filesystem types */
	char           d_name[256]; /* Null-terminated filename */
};

/**
 * @brief The readdir() function returns a pointer to a dirent structure
       representing the next directory entry in the directory stream
       pointed to by dirp.  It returns NULL on reaching the end of the
       directory stream or if an error occurred.
*/
struct dirent *readdir(DIR *dirp);

/**
 * @brief   The closedir() function closes the directory stream associated
       with dirp.  A successful call to closedir() also closes the
       underlying file descriptor associated with dirp.  The directory
       stream descriptor dirp is not available after this call.
*/
int closedir(DIR *dirp);

/**
 * @brief The strerror() function returns a pointer to a string that
       describes the error code passed in the argument errnum, possibly
       using the LC_MESSAGES part of the current locale to select the
       appropriate language.  (For example, if errnum is EINVAL, the
       returned description will be "Invalid argument".)  This string
       must not be modified by the application, but may be modified by a
       subsequent call to strerror() or strerror_l().  No other library
       function, including perror(3), will modify this string.
*/
char *strerror(int errnum);

/**
 * @brief The perror() function produces a message on standard error
       describing the last error encountered during a call to a system
       or library function
*/
void perror(const char *s);

/**
 * @brief The isatty() function tests whether fd is an open file descriptor
       referring to a terminal.
*/
int isatty(int fd);

/**
 * @brief  The function ttyname() returns a pointer to the null-terminated
       pathname of the terminal device that is open on the file
       descriptor fd, or NULL on error (for example, if fd is not
       connected to a terminal).  The return value may point to static
       data, possibly overwritten by the next call.  The function
       ttyname_r() stores this pathname in the buffer buf of length
       buflen.
*/
char *ttyname(int fd);

/**
 * @brief find the slot of the current user's terminal in some
       file
*/
int ttyslot(void);

/**
 * @brief The ioctl() system call manipulates the underlying device
       parameters of special files.  In particular, many operating
       characteristics of character special files (e.g., terminals) may
       be controlled with ioctl() requests.  The argument fd must be an
       open file descriptor.
*/
int ioctl(int fd, unsigned long request, ...);


/**
 * @brief The getenv() function searches the environment list to find the
       environment variable name, and returns a pointer to the
       corresponding value string.
*/
char *getenv(const char *name);

/**
 * @brief  set the parameters associated with the terminal
*/
int tcsetattr(int fildes, int optional_actions,const struct termios *termios_p);

/**
 * @brief get the parameters associated with the terminal
*/
int tcgetattr(int fildes, struct termios *termios_p);

/**
 * @brief 	The tgetent routine loads the entry for name. It returns 1 on success, 
 			0 if there is no such entry, and -1 if the terminfo database could not be found. 
 			The emulation ignores the buffer pointer bp. 
*/
 int tgetent(char *bp, const char *name);

/**
 * @brief The tgetflag routine gets the boolean entry for id, or zero if it is not available. 
*/
 int tgetflag(char *id);

/**
 * @brief The tgetflag routine gets the boolean entry for id, or zero if it is not available. 
*/
 int tgetnum(char *id);
 
/**
 * @brief 	The tgetstr routine returns the string entry for id, or zero if it is not available. 
 			Use tputs to output the returned string. 
 			The return value will also be copied to the buffer pointed to by area,
  			and the area value will be updated to point past the null ending this value. 
*/
 char *tgetstr(char *id, char **area);
 
/**
 * @brief The tgoto routine instantiates the parameters into the given capability.
 			 The output from this routine is to be passed to tputs. 
*/
 char *tgoto(const char *cap, int col, int row);
 
/**
 * @brief The tputs routine is described on the curs_terminfo(3X) manual page.
 			 It can retrieve capabilities by either termcap or terminfo name.
*/
 int tputs(const char *str, int affcnt, int (*putc)(int)); 