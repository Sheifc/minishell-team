#include "minishell.h"

void	heredoc_in(char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i + 1] == '<')
	{
		create_list(HEREDOC, tok, ft_strdup("<<"));
		*i += 2;
	}
	else
	{
		create_list(IN, tok, ft_strdup("<"));
		*i += 1;
	}
}

void	append_out(char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i + 1] == '>')
	{
		create_list(APPEND, tok, ft_strdup(">>"));
		*i += 2;
	}
	else
	{
		create_list(OUT, tok, ft_strdup(">"));
		*i += 1;
	}
}

void	sigint_handler(int signum)
{
	if(signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_exit_signal(void)
{
	printf("exit\n");
	exit(0);
}
