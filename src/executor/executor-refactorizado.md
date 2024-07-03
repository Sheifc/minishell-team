#include "minishell.h"

void    setup_input(t_cmd *cmd)
{
    if (cmd->fdin != -1)
    {
        if (dup2(cmd->fdin, 0) == -1)
            perror("dup2 input");
        close(cmd->fdin);
    }
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
        if (pipe(fdpipe) == -1){
            ft_error("Error: Pipe failed", 0);
            exit(1);}
        fdout = fdpipe[1];
        cmd->next->fdin = fdpipe[0];
    }
    if (fdout != -1)
    {
        if (dup2(fdout, 1) == -1)
            perror("dup2 output");
        close(fdout);
    }
}

void print_args(char **args)
{
    int i = 0;
    while (args[i])
    {
        printf("arg[%d]: %s\n", i, args[i]);
        i++;
    }
}

void    child_process(t_shell *data)
{
    get_path(data);
    if (!data->path){
        ft_error("Error: path not found", 0);
        exit(1);}
    execve(data->path, data->cmd->arg, data->envp);
    perror("excve");
    exit(1);
}

void    execute_command(t_shell *data)
{
    if (!execute_builtin(data)) 
    {
        data->pid = fork();
        if (data->pid == -1){
            ft_error("Error: Fork failed", 0);
            exit(1);}
        else if (data->pid == 0)
            child_process(data);
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

    tmpin = dup(0);
    tmpout = dup(1);
    if (!data->cmd)
        ft_error("Error: not command has been given", 0);
    if (data->cmd->fdin == -1)
        data->cmd->fdin = dup(tmpin);
    while (data->cmd != NULL)
    {
        setup_input(data->cmd);
        setup_output(data->cmd, tmpout, fdpipe);
        execute_command(data);
        if (data->cmd->next != NULL)// Si no es el último comando, actualizar tmpin para la próxima iteración
        {
            close(fdpipe[1]);
            tmpin = fdpipe[0];
        }
        data->cmd = data->cmd->next;
    }
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);
    wait_for_last_process(data);
}
