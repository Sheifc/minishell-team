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

    if (!data->cmd)
        return ;
    tmpin = dup(0);
    tmpout = dup(1);
    if (data->cmd->fdin == -1)
        data->cmd->fdin = dup(tmpin); 
    while (data->cmd != NULL)
    {
        
        dup2(data->cmd->fdin, 0);
        close(data->cmd->fdin);
        if (data->cmd->next == NULL)
        {
            if (data->cmd->fdout == -1)
                data->cmd->fdout = dup(tmpout);
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
                    ft_error("Error: command not found", 127);
                execve(data->path, data->cmd->arg, data->envp);
                ft_error("Error; execve failed", 127);
            }
            else if (data->pid < 0)
                ft_error("Error: fork failed", 127);
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
