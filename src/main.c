#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_shell data;

    (void)argc;
    (void)argv;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    init_struct(&data, envp);
    init_env(&data, envp);
    while (1)
    {
        data.str_cmd = readline(M "Mini" W "shell🐚" G "--> " RST);
        if(data.str_cmd == NULL)
            ft_exit_signal();
        add_history(data.str_cmd);
        lexer(data.str_cmd, &data.token);
        if (data.token != NULL && syntaxis_is_ok(&data.token) == 1 && ft_strlen(data.str_cmd) && only_spaces(data.str_cmd) == 0)
        {
            expand_variables(&data.token);
            fill_struct(&data);
            executor(&data);
        }
        clear_structs(&data.token, &data.cmd);
    }
    free_all(data);
    return (0);
}
