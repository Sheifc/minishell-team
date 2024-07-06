#include "minishell.h"

/* void    wait_for_last_process(t_shell *data)
{
    int status; 

    while ((data->pid = wait(&status)) > 0) //$?
    {
        if (WIFEXITED(status))
            data->status = WEXITSTATUS(status);
    }
} */

void    wait_for_last_process(t_shell *data)
{
    int status;

    while (1)
    {
        pid_t pid = wait(&status);
        if (pid > 0)
        {
            printf("Process with PID: %d exited\n", pid);
            if (WIFEXITED(status))
                data->status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                data->status = 128 + WTERMSIG(status); // Estándar para señales
                // Opcional: manejar señales específicas, como imprimir un mensaje
        }
        else if (data->pid == -1 && errno == EINTR)
            // La llamada a wait fue interrumpida por una señal. Decide si quieres reintentar.
            continue; // Esto reanuda la espera si fue interrumpida por una señal.
        else
            // No hay más procesos hijos o se encontró otro error.
            break;
        }
}

void executor(t_shell *data)
{
    int tmpin;
    int tmpout;
    int fdin;
    int fdout;
    int fdpipe[2];

    tmpin = dup(STDIN_FILENO);
    tmpout = dup(STDOUT_FILENO);
    fdin = dup(tmpin);
    printf("Initial tmpin: %d, tmpout: %d, fdin: %d\n", tmpin, tmpout, fdin);

    while (data->cmd != NULL)
    {
        if (data->cmd->fdin != -1)
            fdin = data->cmd->fdin;
        if (data->cmd->next != NULL)
        {
            pipe(fdpipe);
            fdout = fdpipe[1];
            data->cmd->next->fdin = fdpipe[0];
            printf("Pipe created: fdpipe[0]: %d, fdpipe[1]: %d\n", fdpipe[0], fdpipe[1]);
        }
        else if (data->cmd->fdout != -1)
            fdout = data->cmd->fdout;
        else
            fdout = dup(tmpout);

        dup2(fdin, STDIN_FILENO);
        dup2(fdout, STDOUT_FILENO);
    
        printf("dup2: fdin: %d, fdout: %d\n", fdin, fdout);
    
        if (fdin != tmpin){
            close(fdin);
            printf("Closed fdin: %d\n", fdin);}
        if (fdout != tmpout){
            close(fdout);
            printf("Closed fdout: %d\n", fdout);}

        if (!execute_builtin(data))
        {
            data->pid = fork();
            if (data->pid == 0)
            {
                if (data->cmd->next != NULL) {
                    close(fdpipe[0]); // Cierre del extremo de lectura en el hijo
                }
                if (fdin != STDIN_FILENO)
                    close(fdin); // Cerrar el descriptor de entrada duplicado
                if (fdout != STDOUT_FILENO)
                    close(fdout); // Cerrar el descriptor de salida duplicado
                get_path(data);
                if (!data->path)
                {
                    perror("path");
                    exit(1);
                }
                printf("Executing command: %s\n", data->path);
                execve(data->path, data->cmd->arg, data->envp);
                perror("exec");
                exit(1);
            }
            else if (data->pid > 0)
            {
                printf("Forked process with PID: %d\n", data->pid);
                if (data->cmd->next != NULL)
                {
                    close(fdpipe[1]); // Cerramos el extremo de escritura del pipe en el padre
                    printf("Closed fdpipe[1]: %d\n", fdpipe[1]);
                    fdin = fdpipe[0];
                }
                else
                {
                    if (fdin != tmpin)
                    {
                        close(fdin); // Cerramos fdin en el padre
                        printf("Closed fdin: %d\n", fdin);
                    }
                    fdin = tmpin;
                }
            }
            else
            {
                perror("fork");
            }
        }
        else
        {
            // Manejo de built-ins
            if (fdout != STDOUT_FILENO)
            {
                close(fdout);
                printf("Closed fdout: %d (builtin)\n", fdout);
            }
            if (fdin != STDIN_FILENO)
            {
                close(fdin);
                printf("Closed fdin: %d (builtin)\n", fdin);
            }
            fdin = dup(tmpin);
        }
        data->cmd = data->cmd->next;
    }
    if (data->cmd != NULL)
    {
        close(fdpipe[1]);
        printf("Closed fdpipe[1]: %d\n", fdpipe[1]);
    }
    //waitpid(data->pid, NULL, 0); // funciona para el cat /dev/random | head
    wait_for_last_process(data); // funciona para el cat | cat | ls haciendo cat inv imprimiendo ls inicial, cierra los cats, pero peta el random 
    dup2(tmpin, STDIN_FILENO);
    dup2(tmpout, STDOUT_FILENO);
    close(tmpin);
    close(tmpout);
    printf("Closed tmpin: %d, tmpout: %d\n", tmpin, tmpout);
}
