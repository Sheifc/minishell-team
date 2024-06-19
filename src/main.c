#include "minishell.h"

void clear_token(t_token **token)
{
    t_token *current = *token;
    t_token *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *token = NULL;
}

void	init_struct(t_shell *com)
{
	com->token = NULL;
	com->cmd = NULL;
	com->fdin = -1;
	com->fdout = -1;
    com->env = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	com;

	(void)argc;
	(void)argv;
	init_struct(&com);
	com.str_cmd = readline(M "Mini" W "shell" RED "--> " RST);
	while (com.str_cmd)
    {
        add_history(com.str_cmd);
        lexer(com.str_cmd, &com.token);
        if(com.token)
            parser(com.token);
        if(com.token)
            expand_variables(&com.token, envp, com.env);
        free(com.str_cmd);
        clear_token(&com.token);
        com.str_cmd = readline(M "Mini" W "shell" RED "--> " RST);
    }
}
