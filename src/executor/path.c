#include "minishell.h"

/* static int    find_command_path(char **path_splitted, char *command, char **cmd_path)
{
    char    *path;
    char    *temp;
    int     i; 

    i = -1;
    while (path_splitted[++i] != NULL)
	{
        temp = ft_strjoin(path_splitted[i], "/");
        if (!temp)
            return (0);
        path = ft_strjoin(temp, command);
        free(temp);
        if (!path)
            return (0);
		if(access(path, X_OK) == 0)
        {
            *cmd_path = path;
            return (1);
        }
        free(path);
	}
    return (0);
} */

/* void	get_path(t_shell *data)
{
	char	**path_splitted;
	char	*value;

    if (data->cmd == NULL || data->cmd->arg == NULL || data->cmd->arg[0] == NULL)
        ft_error("Error: command not given", 0);
    if (access(data->cmd->arg[0], X_OK) == 0)
    {   
        data->path = data->cmd->arg[0];
        return ;
    }
    printf("llega\n");
    value = get_value(data->env, "PATH");
    printf("value: %s\n", value);
	if (!value){
        printf("deberia entrar\n");
		ft_error("Error: env variable PATH not found", 0);}
	path_splitted = ft_split(value, ':');
    if (!path_splitted)
        ft_error("Error: path was not possible to split", 0);
    if (!find_command_path(path_splitted, data->cmd->arg[0], &(data->path)))
    {
        ft_free_matrix(path_splitted);
        ft_error("Error: command not found", 0);
    }
    ft_free_matrix(path_splitted);
    //printf("path: %s", data->path);
} */
void	get_path(t_shell *data)
{
	char	**content_splited;
	int		i;
	char	*path;
	char	*content;

    if (data->cmd == NULL || data->cmd->arg == NULL || data->cmd->arg[0] == NULL)
        ft_error(data, "Error: command not given", 1);
	i = -1;
    if (access(data->cmd->arg[0], X_OK) == 0)
    {
        data->path = data->cmd->arg[0];
        return ;
    }
    content = get_value(data, data->env, "PATH");
	if (!content)
		return ;
	content_splited = ft_split(content, ':');
	while (content_splited[++i] != NULL)
	{
		path = ft_strjoin(content_splited[i], "/");
		path = ft_strjoin(path, data->cmd->arg[0]);
		if (access(path, X_OK) == 0)
        {
            data->path = path;
			return ;
        }
	}
	return ;
}
