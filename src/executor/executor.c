#include "minishell.h"

void    wait_for_last_process(t_shell *data)
{
    int status; 

    while ((data->pid = wait(&status)) > 0)
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
            data->cmd->fdout = fdpipe[1];
            data->cmd->next->fdin = fdpipe[0];
        }
        dup2(data->cmd->fdout, 1);
        close(data->cmd->fdout); //
        if (!execute_builtin(data))
        {
            data->pid = fork();
            if (data->pid == 0)
            {
                get_path(data);
                if (!data->path)
                    return (void)perror("path");
                execve(data->path, data->cmd->arg, data->envp);
                perror("exec");
                exit(1);
            }
        }
        data->cmd = data->cmd->next;
    }
    //wait_for_last_process(data);
    waitpid(data->pid, NULL, 0);
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);
}
