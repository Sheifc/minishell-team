#include "minishell.h"

int only_spaces(char *str_cmd)
{
    int i;

    i = 0;
    while(str_cmd[i])
    {
        if(str_cmd[i] != ' ')
            return(0);
        i++;
    }
    return(1);
}

void clear_structs(t_token **token, t_cmd **cmd)
{
    t_token *current = *token;
    t_cmd *current_cmd = *cmd;
    t_cmd *next_cmd;
    t_token *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    while (current_cmd != NULL)
    {
        if(current_cmd->fdin != -1)
            close(current_cmd->fdin);
        if(current_cmd->fdout != -1)
            close(current_cmd->fdout);
        next_cmd = current_cmd->next;
        free(current_cmd);
        current_cmd = next_cmd;
    }
    *cmd = NULL;
    *token = NULL;
}

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
    data->env = NULL;
    data->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	(void)argc;
	(void)argv;
	init_struct(&data, envp);
	data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	while (data.str_cmd)
    {
        add_history(data.str_cmd);
        if(!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
            data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
        lexer(data.str_cmd, &data.token);
        if(data.token != NULL && syntaxis_is_ok(&data.token) == 1)
        {
            expand_variables(&data.token, envp, data.env);
            fill_struct(&data);
        }
        free(data.str_cmd);
        clear_structs(&data.token, &data.cmd);
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
    }
}
