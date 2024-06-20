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

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
    data->env = NULL;
	data->fdin = 0;
	data->fdout = 0;
    data->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	(void)argc;
	(void)argv;
	init_struct(&data, envp);
	data.str_cmd = readline(M "Mini" W "shell" RED "--> " RST);
	while (data.str_cmd)
    {
        add_history(data.str_cmd);
        lexer(data.str_cmd, &data.token);
        if(data.token)
            parser(&data.token, envp, data.env);
        if(data.token)
            print_lists(data.token);
        free(data.str_cmd);
        clear_token(&data.token);
        data.str_cmd = readline(M "Mini" W "shell" RED "--> " RST);
    }
}
