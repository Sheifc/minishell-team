# include "minishell.h"

void    set_pipe(int type, char *str_cmd, t_token **tok, int *i)
{
    if(str_cmd[*i])
    {
        create_list(type, tok, ft_strdup("|"));
        *i += 1;
    }
}