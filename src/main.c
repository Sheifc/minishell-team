#include "minishell.h"

void    handle_empty_or_whitespace_commands(char **str_cmd)
{
    if (!ft_strlen(*str_cmd) || only_spaces(*str_cmd) == 1)
    {
        free(*str_cmd);
        *str_cmd = readline(M "Mini" W "shell" G "--> " RST);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_shell data;

    init(&data, envp);
    while (1)
    {
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
        if (!data.str_cmd)
            break ;
        add_history(data.str_cmd);
        handle_empty_or_whitespace_commands(&data.str_cmd);
        lexer(data.str_cmd, &data.token);
        if (data.token != NULL && syntaxis_is_ok(&data.token) == 1)
        {
            //expand_variables(&data.token);
            token_to_cmd(&data);
            if (data.cmd != NULL)
            {
                executor(&data);
                clear_structs(&data.token, &data.cmd);
            }
        }
        free(data.str_cmd);
        data.cmd_count = 0;
        data.str_cmd = NULL;
    }
    free_all(&data);
    return ((void)argc, (void)argv, 0);
}
