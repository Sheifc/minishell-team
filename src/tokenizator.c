# include "minishell.h"

void set_token(int type, char *str_cmd, t_token **tok, int *i)
{
    setter(type, str_cmd, tok, i);
}