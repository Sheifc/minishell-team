#include "minishell.h"

void    setup_input(t_cmd *cmd, int tmpin)
{
    if (cmd->fdin == -1)
        cmd->fdin = dup(tmpin);
    dup2(cmd->fdin, 0);
    close(cmd->fdin);
}

void    setup_output(t_cmd *cmd, int tmpout, int fdpipe[2])
{
    int fdout;

    if (cmd->next == NULL)
    {
        if (cmd->fdout == -1)
            cmd->fdout = dup(tmpout);
        fdout = cmd->fdout;
    }
    else
    {
        if (pipe(fdpipe) == -1)
            ft_error("Error: Pipe failed");
        fdout = fdpipe[1];
        cmd->next->fdin = fdpipe[0];
    }
    dup2(fdout, 1);
    close(fdout);
}

void    child_process(t_shell *data, t_cmd *cmd)
{
    get_path(data);
    if (!data->path)
        return (ft_error("Error: path not found"));
    printf("obtiene el path\n");
    execve(data->path, cmd->arg, data->envp);
    ft_error("Error: execve failed");
    exit(1);
}

void    execute_command(t_shell *data, t_cmd *cmd)
{
    if (!execute_builtin(data)) 
    {
        data->pid = fork();
        if (data->pid == -1)
            ft_error("Error: Fork failed");
        else if (data->pid == 0)
            child_process(data, cmd);
    }
}
void    wait_for_last_process(t_shell *data)
{
    int status; 

    while ((data->pid = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
            data->status = WEXITSTATUS(status);
    }
}

void    executor(t_shell *data)
{
    int tmpin;
    int tmpout;
    int fdpipe[2];
    t_cmd   *current; 

    tmpin = dup(0);
    tmpout = dup(1);
    if (!data->cmd)
        ft_error("Error: not command has been given");
    current = data->cmd;
    while (current != NULL)
    {
        setup_input(current, tmpin);
        setup_output(current, tmpout, fdpipe);
        execute_command(data, current);
        current = current->next;
    }// Restaurar stdin y stdout a sus valores por defecto
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);// Esperar al último comando
    wait_for_last_process(data);
}
