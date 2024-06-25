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

t_cmd	*list_empty_fill(t_token *token, int argcs)
{
	t_cmd	*node;
    int i;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
    
    node->arg = (char **)malloc(sizeof(char *) * argcs + 1);
    if (!node->arg)
        return (NULL);
    i = 0;
	while(token && token->type == WORD)
    {
        node->arg[i] = ft_strdup(token->content);
        token = token->next;
        i++;
    }
    node->arg[i] = NULL;
    node->next = NULL;
    return (node);
}

void	create_fill_list(t_cmd **cmd, t_token **token, int argcs)
{
    t_cmd	*aux;
    
    if (!*cmd)
        *cmd = list_empty_fill(*token, argcs);
    else
    {
        aux = list_empty_fill(*token, argcs);
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
        cmd = cmd->next;
    }
}

void fill_struct(t_shell *data)
{
    int argcs;

    argcs = count_args(data->token);
    while(data->token)
    {
        if(data->token->type == WORD)
            create_fill_list(&data->cmd, &data->token, argcs);
        else if(data->token->type == PIPE)
            data->token = data->token->next;
        else if(data->token->type == IN)
            printf("Save infile\n");
        else if(data->token->type == OUT)
            printf("Save outfile\n");
        else if(data->token->type == APPEND)
            printf("Save appendfile\n");
        else if(data->token->type == HEREDOC)
            printf("Save heredoc\n");
        data->token = data->token->next;
    }
    print_cmd_list(data->cmd);
    printf("sale\n");
}
