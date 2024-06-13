# include "minishell.h"

void print_lists(t_token *tok)
{
    while(tok)
    {
        ft_printf("%s\n", tok->content);
        tok = tok->next;
    }
}