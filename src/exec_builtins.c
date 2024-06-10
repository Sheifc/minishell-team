#include "minishell.h"

void	execute_builtin(t_shell *data)
{
	if (data->cmd->n_args == 0) // puede gestionarse fuera de la función cd se llame
		return ;
	if (ft_strncmp(data->cmd->arg[0], "echo", 4) == 0)
		ft_echo(data->cmd);
    else if(ft_strncmp(data->cmd->arg[0], "pwd", 3) == 0)
		ft_pwd();
	else if(ft_strncmp(data->cmd->arg[0], "cd", 2) == 0)
		ft_cd(data);
	else if(ft_strncmp(data->cmd->arg[0], "export", 6) == 0)
		ft_export(data);
	else if(ft_strncmp(data->cmd->arg[0], "unset", 5) == 0)
		ft_unset(data);
	else if(ft_strncmp(data->cmd->arg[0], "env", 3) == 0)
		ft_env(data->env);
	else if(ft_strncmp(data->cmd->arg[0], "exit", 4) == 0)
		ft_exit(data->cmd);
	else
		ft_error("Error: Command not found");
}
