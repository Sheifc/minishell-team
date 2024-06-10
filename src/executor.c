#include "minishell.h"

/* void	ft_fork(pid_t   fd)
{
	pid_t	pid_first;
	pid_t	pid_last;
	int		i;

	i = 2;
	pid_first = fork();
	if (pid_first == -1)
		ft_error("Fork failed");
	else if (pid_first == 0)
		first_child_process(argv, envp, fd);
	else
	{
		close(fd[1]);
		waitpid(pid_first, NULL, 0);
		while (++i < argc - 2)
			middle_child_process(argv, envp, fd, i);
		pid_last = fork();
		if (pid_last == -1)
			ft_error("Last fork failed");
		else if (pid_last == 0)
			last_child_process(argv, envp, fd, argc);
		else if (close(fd[0]) == 0)
			waitpid(pid_last, NULL, 0);
	}
}

void    executor(t_shell *data)
{
    pid_t   fd;

    while (data->cmd)
    {
        if (pipe(fd) == -1)
            ft_error("Create pipe failed");
        else
            ft_fork(&fd);
    }
} */
