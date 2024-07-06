#include "minishell.h"

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
    data->env = NULL;
    data->export = NULL;
    data->str_cmd = NULL;
    data->envp = envp;
    data->path = NULL;
    data->status = 0;
    data->pid = 0;
    data->error_code = 0;
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void    init_signals()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void    init(t_shell *data, char **envp)
{
    init_signals();
    init_struct(data, envp);
    init_env(data, envp);
}
