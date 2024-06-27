#include "minishell.h"

int	execute_builtin(t_shell *data)
{
	if (data->cmd->n_args == 0)
		ft_error("Error: No arguments given");
	if (ft_strncmp(data->cmd->arg[0], "echo", 4) == 0){
        printf("entra en echo\n");
		return (ft_echo(data->cmd), 1);}
    else if(ft_strncmp(data->cmd->arg[0], "pwd", 3) == 0)
		return (ft_pwd(), 1);
	else if(ft_strncmp(data->cmd->arg[0], "cd", 2) == 0)
		return (ft_cd(data), 1);
	else if(ft_strncmp(data->cmd->arg[0], "export", 6) == 0)
		return (ft_export(data), 1);
	else if(ft_strncmp(data->cmd->arg[0], "unset", 5) == 0)
		return (ft_unset(data), 1);
	else if(ft_strncmp(data->cmd->arg[0], "env", 3) == 0)
		return (ft_env(data->env), 1);
	else if(ft_strncmp(data->cmd->arg[0], "exit", 4) == 0)
		return (ft_exit(data->cmd), 1);
	else{
        printf("da cero\n");
		return (0);}
}
