# Minishell

# Funciones de la biblioteca readline

1. readline
   - Descripción: Lee una línea de entrada desde el usuario.
   - Prototipo: `char *readline(const char *prompt);`

2. rl_clear_history
   - Descripción: Borra el historial de comandos.
   - Prototipo: `void rl_clear_history(void);`

3. rl_on_new_line
   - Descripción: Indica que el cursor se ha movido a una nueva línea.
   - Prototipo: `int rl_on_new_line(void);`

4. rl_replace_line
   - Descripción: Reemplaza el contenido actual de la línea con una nueva línea.
   - Prototipo: `int rl_replace_line(const char *text, int clear_undo);`

5. rl_redisplay
   - Descripción: Redisplay the current input line.
   - Prototipo: `void rl_redisplay(void);`

6. add_history
   - Descripción: Agrega una línea al historial de comandos.
   - Prototipo: `void add_history(const char *string);`

# Funciones de la biblioteca estándar de C

7. printf
   - Descripción: Imprime un formato específico a la salida estándar.
   - Prototipo: `int printf(const char *format, ...);`

8. malloc
   - Descripción: Asigna memoria en el heap.
   - Prototipo: `void *malloc(size_t size);`

9. free
   - Descripción: Libera la memoria previamente asignada con malloc.
   - Prototipo: `void free(void *ptr);`

10. write
    - Descripción: Escribe datos en un archivo descriptor.
    - Prototipo: `ssize_t write(int fd, const void *buf, size_t count);`

11. access
    - Descripción: Comprueba si el proceso tiene acceso a un archivo.
    - Prototipo: `int access(const char *pathname, int mode);`

12. open
    - Descripción: Abre un archivo.
    - Prototipo: `int open(const char *pathname, int flags, ...);`

13. read
    - Descripción: Lee datos de un archivo descriptor.
    - Prototipo: `ssize_t read(int fd, void *buf, size_t count);`

14. close
    - Descripción: Cierra un archivo descriptor.
    - Prototipo: `int close(int fd);`

# Funciones de procesos

15. fork
    - Descripción: Crea un nuevo proceso duplicando el proceso actual.
    - Prototipo: `pid_t fork(void);`

16. wait
    - Descripción: Espera a que cualquier hijo termine.
    - Prototipo: `pid_t wait(int *wstatus);`

17. waitpid
    - Descripción: Espera a que un hijo específico termine.
    - Prototipo: `pid_t waitpid(pid_t pid, int *wstatus, int options);`

18. wait3
    - Descripción: Espera a que un hijo termine y devuelve información de uso del recurso.
    - Prototipo: `pid_t wait3(int *wstatus, int options, struct rusage *rusage);`

19. wait4
    - Descripción: Espera a que un hijo específico termine y devuelve información de uso del recurso.
    - Prototipo: `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);`

# Señales y manejo de señales

20. signal
    - Descripción: Define una función de manejo de señales.
    - Prototipo: `void (*signal(int signum, void (*handler)(int)))(int);`

21. sigaction
    - Descripción: Examina y cambia la acción de una señal.
    - Prototipo: `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

22. kill
    - Descripción: Envía una señal a un proceso o grupo de procesos.
    - Prototipo: `int kill(pid_t pid, int sig);`

23. exit
    - Descripción: Termina el proceso actual.
    - Prototipo: `void exit(int status);`

# Funciones del sistema de archivos

24. getcwd
    - Descripción: Obtiene el directorio de trabajo actual.
    - Prototipo: `char *getcwd(char *buf, size_t size);`

25. chdir
    - Descripción: Cambia el directorio de trabajo actual.
    - Prototipo: `int chdir(const char *path);`

26. stat
    - Descripción: Obtiene información sobre un archivo.
    - Prototipo: `int stat(const char *pathname, struct stat *statbuf);`

27. lstat
    - Descripción: Igual que stat pero para enlaces simbólicos.
    - Prototipo: `int lstat(const char *pathname, struct stat *statbuf);`

28. fstat
    - Descripción: Obtiene información sobre un archivo basado en su descriptor.
    - Prototipo: `int fstat(int fd, struct stat *statbuf);`

29. unlink
    - Descripción: Borra un nombre de archivo.
    - Prototipo: `int unlink(const char *pathname);`

30. execve
    - Descripción: Ejecuta un programa.
    - Prototipo: `int execve(const char *pathname, char *const argv[], char *const envp[]);`

# Funciones de manejo de descriptores

31. dup
    - Descripción: Duplica un descriptor de archivo.
    - Prototipo: `int dup(int oldfd);`

32. dup2
    - Descripción: Duplica un descriptor de archivo en un descriptor específico.
    - Prototipo: `int dup2(int oldfd, int newfd);`

33. pipe
    - Descripción: Crea un par de descriptores de archivo para comunicación entre procesos.
    - Prototipo: `int pipe(int pipefd[2]);`

# Funciones de directorio

34. opendir
    - Descripción: Abre un directorio.
    - Prototipo: `DIR *opendir(const char *name);`

35. readdir
    - Descripción: Lee una entrada de directorio.
    - Prototipo: `struct dirent *readdir(DIR *dirp);`

36. closedir
    - Descripción: Cierra un directorio.
    - Prototipo: `int closedir(DIR *dirp);`

# Funciones de errores

37. strerror
    - Descripción: Devuelve una cadena que describe el código de error.
    - Prototipo: `char *strerror(int errnum);`

38. perror
    - Descripción: Imprime un mensaje de error en la salida estándar de errores.
    - Prototipo: `void perror(const char *s);`

# Funciones de terminal

39. isatty
    - Descripción: Comprueba si un descriptor de archivo se refiere a un terminal.
    - Prototipo: `int isatty(int fd);`

40. ttyname
    - Descripción: Devuelve el nombre de un terminal asociado a un descriptor de archivo.
    - Prototipo: `char *ttyname(int fd);`

41. ttyslot
    - Descripción: Devuelve el número de ranura del terminal.
    - Prototipo: `int ttyslot(void);`

42. ioctl
    - Descripción: Manipula los parámetros de dispositivos de archivos especiales.
    - Prototipo: `int ioctl(int fd, unsigned long request, ...);`

# Funciones de entorno

43. getenv
    - Descripción: Obtiene el valor de una variable de entorno.
    - Prototipo: `char *getenv(const char *name);`

44. tcsetattr
    - Descripción: Establece los parámetros de la terminal.
    - Prototipo: `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);`

45. tcgetattr
    - Descripción: Obtiene los parámetros de la terminal.
    - Prototipo: `int tcgetattr(int fd, struct termios *termios_p);`

# Funciones de la biblioteca termcap

46. tgetent
    - Descripción: Accede a la base de datos termcap.
    - Prototipo: `int tgetent(char *bp, const char *name);`

47. tgetflag
    - Descripción: Obtiene el valor de un booleano de la base de datos termcap.
    - Prototipo: `int tgetflag(const char *id);`

48. tgetnum
    - Descripción: Obtiene el valor de un número de la base de datos termcap.
    - Prototipo: `int tgetnum(const char *id);`

49. tgetstr
    - Descripción: Obtiene el valor de una cadena de la base de datos termcap.
    - Prototipo: `char *tgetstr(const char *id, char **area);`

50. tgoto
    - Descripción: Construye una secuencia de control termcap.
    - Prototipo: `char *tgoto(const char *cap, int col, int row);`

51. tputs
    - Descripción: Emite una secuencia de control termcap.
    - Prototipo: `int tputs(const char *str, int affcnt, int (*putc)(int));`
