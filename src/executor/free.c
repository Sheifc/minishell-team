#include "minishell.h"

void    free_env_list(t_env *head)
{
    t_env *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}

void    free_env_node(t_env **node)
{
    free((*node)->key);
    free((*node)->value);
    free(*node);
    *node = NULL;
}

void	free_token(t_token **token)
{
	t_token	*aux;

	if (!*token || !token)
		return ;
	while (*token)
	{
		aux = (*token)->next;
		free((*token)->content);
		free(*token);
		*token = aux;
	}
    *token = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	if (!*cmd || !cmd)
		return ;
	while (*cmd)
	{
		aux = (*cmd)->next;
		if ((*cmd)->fdin > 2)
			close((*cmd)->fdin);
		if ((*cmd)->fdout > 2)
			close((*cmd)->fdout);
		ft_free_matrix((*cmd)->arg);
		free(*cmd);
		*cmd = aux;
	}
}

void    free_all(t_shell *data)
{
    if (data->str_cmd)
        free(data->str_cmd);
    if (data->env)
        free_env_list(data->env);
    if (data->export)
        free_env_list(data->export);
    if (data->token)
        free_token(&data->token);
    if (data->cmd)
        free_cmd(&data->cmd);
}
