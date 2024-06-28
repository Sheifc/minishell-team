# include "minishell.h"

t_cmd	*ft_last_fill(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = (t_cmd *)lst->next;
	return (lst);
}

void	add_back_fill(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = ft_last_fill(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

void list_empty_utils(t_cmd *node, t_token **token, int *i) 
{
    if((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
        ft_innout(node, token);
    if((*token) && (((*token)->type == WORD) || ((*token)->type == QUOTE) || ((*token)->type == DQUOTE)))
    {
        node->arg[*i] = ft_strdup((*token)->content);
        *token = (*token)->next;
        (*i)++;
        node->n_args = *i;
    }
}

t_cmd	*list_empty_fill(t_token **token, int argcs)
{
    t_cmd	*node;
    int i;

    node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->arg = (char **)malloc(sizeof(char *) * (argcs + 1));
    if (!node->arg)
    {
        free(node);
        return (NULL);
    }
    node->fdin = -1;
    node->fdout = -1;
    i = 0;
    while(*token && (*token)->type != PIPE)
        list_empty_utils(node, token, &i);
    node->arg[i] = NULL;
    node->next = NULL;
    return (node);
}
