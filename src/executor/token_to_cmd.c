#include "minishell.h"

void add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
    t_cmd *temp;
    if (!new_cmd)
        return ;
    if (*head == NULL)
        *head = new_cmd;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_cmd;
    }
}

t_cmd   *create_cmd_node(void)
{
    t_cmd *node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->arg = NULL;
    node->fdin = -1;
    node->fdout = -1;
    node->n_args = 0;
    node->next = NULL;
    return (node);
}

void    add_argument(t_cmd *cmd, char *token_content)
{
    char **new_arg;
    int i;

    i = 0;
    new_arg = (char **)malloc(sizeof(char *) * (cmd->n_args + 2));
    if (!new_arg)
        perror("Error: allocating memory");
    while (i < cmd->n_args)
    {
        new_arg[i] = cmd->arg[i];
        i++;
    }
    new_arg[cmd->n_args] = ft_strdup(token_content);
    new_arg[cmd->n_args + 1] = NULL;
    cmd->arg = new_arg;
    cmd->n_args++;
}

int handle_redirection(t_cmd *cmd, t_token **token)
{
    int status;

    status = 0;
    if (cmd == NULL || token == NULL || *token == NULL)
    {
        perror("Error: invalid pointer");
        return (1);
    }
    if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
    {
        status = ft_innout(cmd, token);
        if (status != 0)
            return (status);
    }
    return (0);
}

int fill_cmd_args(t_cmd *cmd, t_token **token)
{
    int status;
    
    status = 0;
    while (*token && (*token)->type != PIPE)
    {
        if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
        {
            status = handle_redirection(cmd, token);
            if (status != 0)
                break ;
        }
        else if ((*token)->type == WORD || (*token)->type == QUOTE || (*token)->type == DQUOTE)
        {
            add_argument(cmd, (*token)->content);
            *token = (*token)->next;
        }
        else
            *token = (*token)->next;
    }
    return (status);
}

int add_cmd_to_shell(t_cmd **cmd_list, t_token **token)
{
    t_cmd *new_cmd;
    int status;
    
    new_cmd = create_cmd_node();
    status = 0;
    if (!new_cmd)
        return (1);
    status = fill_cmd_args(new_cmd, token);
    if (status == 0)
        add_cmd_to_list(cmd_list, new_cmd);
    else
        free_cmd(&new_cmd);
    return (status);
}

void token_to_cmd(t_shell *data)
{
    int status; 

    status = 0;
    while (data->token)
    {
        if (data->token->type != PIPE)
        {
            status = add_cmd_to_shell(&data->cmd, &data->token);
            if (status != 0)
            {
                clear_structs(&data->token, &data->cmd);
                break ;
            }
        }
        else if (data->token->type == PIPE)
            data->token = data->token->next;
    }
}
