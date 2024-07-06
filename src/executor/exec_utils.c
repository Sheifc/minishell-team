#include "minishell.h"

void ft_swap(char **a, char **b)
{
    char *aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void    count_commands(t_shell *data)
{
    t_cmd *current_cmd; 

    current_cmd = data->cmd;
    while (current_cmd != NULL)
    {
        data->cmd_count++;
        current_cmd = current_cmd->next;
    }
}

/* void    init_pid(t_shell *data)
{
    data->pid = malloc(sizeof(int) * data->cmd_count);
    if (!data->pid)
        ft_error(data, "Error: malloc failed", 127);
} */

void	kill_processess(int *pids, int len)
{
	while (len)
		kill(pids[--len], SIGKILL);
	free(pids);
}
