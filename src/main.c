#include "minishell.h"

void is_line_empty(char *str)
{
    free(str);
    str = readline(M "Mini" W "shell" G "--> " RST);
}

void sigint_handler(int signum)
{
    (void)signum;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void ft_exit_signal(void)
{
    printf("exit\n");
    exit(0);
}

void sigquit_handler(int signum)
{
    (void)signum;
    printf("SIGQUIT caught cleaning and exiting\n");
    exit(0);
}

int main(int argc, char **argv, char **envp)
{
    t_shell data;

    (void)argc;
    (void)argv;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    init_struct(&data, envp);
    init_env(&data, envp);
    while (1)
    {
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
        if(data.str_cmd == NULL)
            ft_exit_signal();
        add_history(data.str_cmd);
        if (!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
            is_line_empty(data.str_cmd);
        lexer(data.str_cmd, &data.token);
        if (data.token != NULL && syntaxis_is_ok(&data.token, &data) == 1)
        {
            expand_variables(&data.token, data.env, &data);
            fill_struct(&data);
            executor(&data);
        }
        clear_structs(&data.token, &data.cmd);
    }
    free_all(data);
    return (0);
}
