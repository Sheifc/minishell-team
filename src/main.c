# include "../includes/minishell.h"
# include "../includes/structures.h"

int main(int argc, char **argv, char **envp)
{
    char *str_cmd;

    (void)argc;
    (void)argv;
    (void)envp;
    
    str_cmd = readline(M"Mini"W"shell"RED"--> "RST);
    while(str_cmd)
    {
        if(!ft_strncmp(str_cmd, "exit", 4))
        {
            ft_printf("exit");
            free(str_cmd);
            exit(0);
        }
        history(str_cmd);
        lexer(str_cmd);
        free(str_cmd);
        str_cmd = readline(M"Mini"W"shell"RED"--> "RST);
    }
}
