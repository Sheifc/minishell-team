#include "minishell.h"

static void	exit_child_process(t_shell *data)
{
	if (!ft_check_built_in(data))
		ft_execute_command(data);
	else
		exit (1);
}

void	ft_pipex(t_shell *data)
{
	pid_t	pid;
	int		tube[2];

	pipe(tube);
	pid = fork();
	if (pid == 0)
	{
		close(tube[0]);
		if (data->cmd->fdin != STDIN_FILENO)
			dup2(data->cmd->fdin, STDIN_FILENO);
		if (data->cmd->fdout != STDOUT_FILENO && data->cmd->fdout != 0)
			dup2(data->cmd->fdout, STDOUT_FILENO);
		else
			dup2(tube[1], STDOUT_FILENO);
		close(tube[1]);
		exit_child_process(data);
	}
	else
	{
		wait(NULL);
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
	}
}

int	ft_start_pipex(t_shell *data)
{
	pid_t	pid;
	int		num;

	data->pid = fork();
	if (pid != 0)
		data->pid = pid;
	if (pid == 0)
	{
		while (data->cmd->next)
		{
			ft_pipex(data);
			data = data->cmd->next;
		}
		if (data->cmd->fdin != STDIN_FILENO)
			dup2(data->cmd->fdin, STDIN_FILENO);
		if (data->cmd->fdout != STDOUT_FILENO && data->cmd->fdout != 0)
			dup2(data->cmd->fdout, STDOUT_FILENO);
		exit_child_process(data);
	}
	wait(&num);
	if (WIFEXITED(num))
		data->status = WEXITSTATUS(num);
	return (0);
}

static char	*ft_get_cmd(char *str, char *path)
{
	char		**cases;
	char		*new;
	char		*tmp;
	int			i;

	if (!str)
		return (NULL);
	if (access(str, X_OK) == 0)
		return (ft_strdup(str));
	cases = ft_split(path, ':');
	i = 0;
	new = ft_strjoin("/", str);
	while (cases[i])
	{
		tmp = ft_strjoin(cases[i], new);
		if (access(tmp, X_OK) == 0)
			return (free(new), tmp);
		free(tmp);
		i++;
	}
	perror(str);
	return (free(new), ft_free_matrix(cases), NULL);
}

void	ft_execute_command(t_cmd *list, t_env *env)
{
	char	*path;
	char	*cmd_path;

	path = ft_get_env_key(env, "PATH");
	if (!path)
	{
		ft_putstr_fd("No existe PATH\n", 2);
		exit (127);
	}
	cmd_path = ft_get_cmd(list->flags[0], path);
	if (!cmd_path)
	{
		free(path);
		exit (127);
	}
	free(path);
	if (execve(cmd_path, list->flags, ft_get_envp(env)) == -1)
	{
		perror(cmd_path);
		exit(-1);
	}
}

int	ft_execute_line(t_shell *data)
{
	t_cmd	*list;

	list = data->list[0];
	ft_get_here_doc(list);
	if (!list->next)
	{
		ft_built_in_cd(list);
		if (ft_check_built_in_cd(list))
			list = list->next;
		else
			return (ft_start_pipex(list));
	}
	else
		return (ft_start_pipex(list));
	return (0);
}
