#include "minishell.h"

t_cmd	*get_last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_cmd_to_list(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = get_last_cmd(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->arg = NULL;
	node->fdin = -1;
	node->fdout = -1;
	node->n_args = 0;
	node->next = NULL;
	return (node);
}

void	handle_redirection(t_cmd *cmd, t_token **token)
{
	ft_innout(cmd, token);
	if (*token && (*token)->type == WORD)
		*token = (*token)->next;
}

void	add_argument(t_cmd *cmd, char *arg)
{
	char	**new_arg;
	int		i;

	i = 0;
	new_arg = (char **)malloc(sizeof(char *) * (cmd->n_args + 2));
	if (!new_arg)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	while (i < cmd->n_args)
	{
		new_arg[i] = cmd->arg[i];
		i++;
	}
	new_arg[cmd->n_args] = ft_strdup(arg);
	new_arg[cmd->n_args + 1] = NULL;
	free(cmd->arg);
	cmd->arg = new_arg;
	cmd->n_args++;
}

void	fill_cmd_args(t_cmd *cmd, t_token **token)
{
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == IN || (*token)->type == OUT
			|| (*token)->type == APPEND || (*token)->type == HEREDOC)
			handle_redirection(cmd, token);
		else if ((*token)->type == WORD || (*token)->type == QUOTE
			|| (*token)->type == DQUOTE)
		{
			add_argument(cmd, (*token)->content);
			*token = (*token)->next;
		}
		else
			*token = (*token)->next;
	}
}

void	add_cmd_to_shell(t_cmd **cmd_list, t_token **token)
{
	t_cmd	*new_cmd;

	new_cmd = create_cmd_node();
	if (new_cmd)
	{
		fill_cmd_args(new_cmd, token);
		add_cmd_to_list(cmd_list, new_cmd);
	}
}

void	fill_struct(t_shell *data)
{
	while (data->token)
	{
		if (data->token->type != PIPE)
			add_cmd_to_shell(&data->cmd, &data->token);
		else if (data->token->type == PIPE)
			data->token = data->token->next;
	}
}
