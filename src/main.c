#include "minishell.h"

int	main(int argc, char **argv, char **envp)
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
            fill_struct(&data);
        }
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
    }
    if (!execute_builtin(&data))
        executor(&data);
    free_all(data);
    return (0);
}
