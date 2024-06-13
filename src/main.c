# include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *str_cmd;

    (void)argc;
    (void)argv;
    (void)envp;
    
    str_cmd = readline(M"Mini"W"shell"RED"--> "RST);
    while(str_cmd)
    {
        add_history(str_cmd);
        lexer(str_cmd);
        free(str_cmd);
        str_cmd = readline(M"Mini"W"shell"RED"--> "RST);
    }
}
