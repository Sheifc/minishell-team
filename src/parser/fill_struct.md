# include "minishell.h"
```c
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
    node->n_args = 0;
    i = 0;
    while(*token && (*token)->type != PIPE)
    {
        if((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
            ft_innout(node, token);
        if((*token) && (((*token)->type == WORD) || ((*token)->type == QUOTE) || ((*token)->type == DQUOTE)))
        {
            if (i >= argcs) // Asegurarse de no escribir fuera de los límites
            {
                fprintf(stderr, "Error: too many arguments\n");
                break;
            }
            node->arg[i] = ft_strdup((*token)->content);
            *token = (*token)->next;
            i++;
            node->n_args = i;
        }
    }
    node->arg[i] = NULL;
    node->next = NULL;
    return (node);
}

void	create_fill_list(t_cmd **cmd, t_token **token, int argcs)
{
    t_cmd	*aux;
    
    if (!*cmd)
        *cmd = list_empty_fill(token, argcs);
    else
    {
        aux = list_empty_fill(token, argcs);
        add_back_fill(cmd, aux);
    }
}

int count_args(t_token *token)
{
    int argc;
    int red;

    red = 0;
    argc = 0;
    while(token)
    {
        if(token->type == WORD)
            argc++;
        if(token->type == IN || token->type == OUT || token->type == APPEND || token->type == HEREDOC)
            red++;
        token = token->next;
    }
    return (argc - red);
}


void print_cmd_list(t_cmd *cmd)
{
    int count;
    if (cmd == NULL)
        return;
    while(cmd)
    {
        count = 0;
        while(cmd->arg[count])
        {
            printf("Arg[%d]: %s\n", count, cmd->arg[count]);
            count++;
        }
        printf("N_args: %d\n", cmd->n_args);
        printf("FD_IN: %d\n", cmd->fdin);
        printf("FD_OUT: %d\n", cmd->fdout);
        cmd = cmd->next;
    }
}

void fill_struct(t_shell *data)
{
    int argcs;

    argcs = count_args(data->token);
    while(data->token)
    {
        if(data->token->type != PIPE)
            create_fill_list(&data->cmd, &data->token, argcs);
        else if(data->token->type == PIPE)
            data->token = data->token->next;
    }
}
