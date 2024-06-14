#include "minishell.h"

void	init_struct(t_shell *com)
{
	com->token = NULL;
	com->cmd = NULL;
	com->fdin = -1;
	com->fdout = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	com;

	(void)argc;
	(void)argv;
	(void)envp;
	init_struct(&com);
	com.str_cmd = readline(M "Mini" W "shell" RED "--> " RST);
	while (com.str_cmd)
	{
		add_history(com.str_cmd);
		lexer(com.str_cmd, com.token);
		free(com.str_cmd);
		com.str_cmd = readline(M "Mini" W "shell" RED "--> " RST);
	}
}
