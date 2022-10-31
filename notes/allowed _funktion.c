
/**
 * @brief	readline will read a line from the terminal and return it, using prompt as a prompt
 * 			it will allocat the string using malloc.
 * 			for more information GNU READLINE
 * @param	prompt a string that will be printed at at the beginning of the terminal line
 * @return	return  a allocated string
 */
char *   readline (const char *prompt);
/**
 * @brief 
 * 
 */
rl_clear_history():
rl_on_new_line();
rl_replace_line();
rl_redisplay();
add_history();
////printf();
////malloc();
////free();
////write();
access();
////open();
////read();
////close();
fork();
wait();
waitpid();
wait3();
wait4();
signal();
sigaction();
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