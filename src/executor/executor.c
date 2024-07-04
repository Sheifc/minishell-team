#include "minishell.h"

void	wait_for_last_process(t_shell *data)
{
	int	status;

	while ((data->pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
	}
}

void	executor(t_shell *msh)
{
	int	tmpin;
	int	tmpout;
	int	fdpipe[2];

	tmpin = dup(0);
	tmpout = dup(1);
	if (msh->cmd->fdin == -1)
		msh->cmd->fdin = dup(tmpin);
	while (msh->cmd != NULL)
	{
		dup2(msh->cmd->fdin, 0);
		close(msh->cmd->fdin);
		if (msh->cmd->next == NULL)
		{
			if (msh->cmd->fdout == -1)
				msh->cmd->fdout = dup(tmpout);
		}
		else
		{
			pipe(fdpipe);
			msh->cmd->fdout = fdpipe[1];
			msh->cmd->next->fdin = fdpipe[0];
		}
		dup2(msh->cmd->fdout, 1);
		close(msh->cmd->fdout);
		if (!execute_builtin(msh))
		{
			msh->pid = fork();
			if (msh->pid == 0)
			{
				get_path(msh);
				if (!msh->path)
					return (void)perror("path");
				execve(msh->path, msh->cmd->arg, msh->envp);
				perror("exec");
				exit(1);
			}
		}
		msh->cmd = msh->cmd->next;
	}
	// wait_for_last_process(msh);
	waitpid(msh->pid, NULL, 0);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}
