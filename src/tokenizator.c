# include "minishell.h"

void set_token(int type, char *str_cmd, t_token **tok, int *i)
{
    if(type == PIPE)
        set_pipe(type, str_cmd, tok, i);
}