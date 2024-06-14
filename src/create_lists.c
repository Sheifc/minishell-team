# include "minishell.h"

t_token *ft_last(t_token *lst)
{
    if(!lst)
        return(NULL);
    while(lst->next != NULL)
        lst = lst->next;
    return (lst);
}

void add_back(t_token **lst, t_token *new)
{
    t_token *last;

    last = ft_last(*lst);
    if(!last)
        *lst = new;
    else
        last->next = new;
}

t_token *list_empty(int type, char *content)
{
    t_token *node;

    node = (t_token *)malloc(sizeof(t_token));
    if(!node)
        return(NULL);
    node->content = ft_strdup(content);
    node->type = type;
    node->next = NULL;
    return(node);
}

void create_list(int type, t_token **tok, char *content)
{
    t_token *aux;
    if(!*tok)
    {
        *tok = list_empty(type, content);
    }
    else
    {
        aux = list_empty(type, content);
        add_back(tok, aux);
    }
    free(content);
}