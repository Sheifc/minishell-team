#include "minishell.h"
void print_tokens(t_token *token)
{
    while (token)
    {
        printf("Token: %s, Type: %d\n", token->content, token->type);
        token = token->next;
    }
}

/* int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	(void)argc;
	(void)argv;
	init_struct(&data, envp);
    init_env(&data, envp);
	data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	while (data.str_cmd)
    {
        add_history(data.str_cmd);
        if(!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
            data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
        lexer(data.str_cmd, &data.token);
        if(data.token != NULL && syntaxis_is_ok(&data.token) == 1)
        {
            //expand_variables(&data.token, envp, data.env);
            //print_tokens(data.token); // Imprimir tokens para depuración
            fill_struct(&data);
            print_cmd_list(data.cmd);
            executor(&data);
            clear_structs(&data.token, &data.cmd);
        }
        free(data.str_cmd);
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);  
    }
    free_all(data);
    return (0);
} */

int main(int argc, char **argv, char **envp)
{
    t_shell data;

    (void)argc;
    (void)argv;
    init_struct(&data, envp);
    init_env(&data, envp);
    data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
    while (data.str_cmd)
    {
        add_history(data.str_cmd);
        if (!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
        {
            free(data.str_cmd);
            data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
            continue;
        }
        lexer(data.str_cmd, &data.token);
        if (data.token != NULL && syntaxis_is_ok(&data.token) == 1)
        {
            fill_struct(&data);
            print_cmd_list(data.cmd);
            executor(&data);
            clear_structs(&data.token, &data.cmd);  // Liberar estructuras después de ejecutar los comandos
        }
        free(data.str_cmd);
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
    }
    free_all(data);
    return (0);
}
