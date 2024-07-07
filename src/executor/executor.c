#include "minishell.h"

void    wait_for_last_process(t_shell *data)
{
    int status;

    while ((data->pid = wait(&status)) > 0) //$?
    {
        if (WIFEXITED(status))
            data->status = WEXITSTATUS(status);
    }
}

void executor(t_shell *data)
{
    int tmpin;
    int tmpout;
    int fdpipe[2];
    int i;

    printf("llega a executor\n");
    i = -1;
    count_commands(data);
    printf("data->cmd_count: %d\n", data->cmd_count);
    if (!data->cmd)
        return ;
    tmpin = dup(0);
    tmpout = dup(1);
    printf("tmpin: %d, tmpout: %d\n", tmpin, tmpout);
    printf("data->cmd->fdin: %d\n", data->cmd->fdin);
    if (data->cmd->fdin == -1)
        data->cmd->fdin = dup(tmpin);
    while (++i < data->cmd_count)
    {
        printf("llega al while\n");
        printf("command: %s\n", data->cmd->arg[0]); //esto no lo imprime, hay un error con los argumentos
        dup2(data->cmd->fdin, 0);
        printf("fdin: %d\n", data->cmd->fdin);
        close(data->cmd->fdin);
        printf("data->cmd_count: %d, i: %d\n", data->cmd_count, i);
        if (data->cmd_count == i)
        {
            printf("llega al if\n");
            if (data->cmd->fdout == -1)
                data->cmd->fdout = dup(tmpout);
            printf("fdout: %d\n", data->cmd->fdout);
        }
        else
        {
            pipe(fdpipe);
            data->cmd->next->fdin = fdpipe[0];
            if (data->cmd->fdout == -1)
                data->cmd->fdout = fdpipe[1];
            else
                close(fdpipe[1]);
        }
        dup2(data->cmd->fdout, 1);
        close(data->cmd->fdout);
        if (!execute_builtin(data))
        {
            data->pid = fork();
            if (data->pid == 0)
            {
                get_path(data);
                if (!data->path)
                {
                    perror("Error: command not found");
                    exit(127);
                }
                execve(data->path, data->cmd->arg, data->envp);
                ft_error(data, "Error; execve failed", 127);
            }
            else if (data->pid < 0)
                ft_error(data, "Error: fork failed", 127);
            else
                if (data->cmd != NULL)
                    close(fdpipe[1]);
        }
        data->cmd = data->cmd->next;
    }
    //waitpid(data->pid, NULL, 0); // funciona para el cat /dev/random | head
    wait_for_last_process(data); // funciona para el cat | cat | ls haciendo cat inv imprimiendo ls inicial, cierra los cats, pero peta el random 
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);
}
