# include "minishell.h"

void    setter(int type, char *str_cmd, t_token **tok, int *i)
{
    int start;

    start = *i;
    if(str_cmd[*i] && type == PIPE)
        create_list(type, tok, ft_strdup("|"));
    else if(str_cmd[*i] && type == IN)
        create_list(type, tok, ft_strdup("<"));
    else if(str_cmd[*i] && type == OUT)
        create_list(type, tok, ft_strdup(">"));
    else if(str_cmd[*i] && type == WORD)
    {
        while(str_cmd[*i] && str_cmd[*i] != '|' && str_cmd[*i] != '<' && str_cmd[*i] != '>' && str_cmd[*i] != ' ' && str_cmd[*i] != '\'' && str_cmd[*i] != '"')
            *i += 1;
        create_list(type, tok, ft_substr(str_cmd, start, *i - start));
    }
    *i += 1;
}
