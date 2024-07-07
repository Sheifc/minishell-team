#include "minishell.h"

int save_infile(t_cmd *cmd, t_token **tok)
{
    t_cmd *last;

    last = get_last_cmd(cmd);
    (*tok) = (*tok)->next;
    if (last->fdin > 2)
        close(last->fdin);
    if (cmd->fdin == -1)
        cmd->fdin = open((*tok)->content, O_RDONLY);
    if (cmd->fdin == -1)
    {
        perror("Error: reading fd");
        return (1);
    }
    (*tok) = (*tok)->next;
    return (0);
}

int save_append(t_cmd *cmd, t_token **tok)
{
    t_cmd *last;

    last = get_last_cmd(cmd);
    (*tok) = (*tok)->next;
    if (last->fdout > 2)
        close(last->fdout);
    if (last->fdout == -1)
        last->fdout = open((*tok)->content, O_RDWR | O_CREAT | O_APPEND, 0644);
    if (last->fdout == -1)
    {
        perror("Error: appending fd");
        return (1);
    }
    (*tok) = (*tok)->next;
    return (0);
}

int save_outfile(t_cmd *cmd, t_token **tok)
{
    t_cmd *last;

    last = get_last_cmd(cmd);
    (*tok) = (*tok)->next;
    if (last->fdout > 2)
        close(last->fdout);
    if (last->fdout == -1)
        last->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdout == -1)
    {
        perror("Error: opening fd");
        return (1);
    }
    *tok = (*tok)->next;
    return (0);
}

int ft_innout(t_cmd *cmd, t_token **tok)
{
    if (cmd == NULL || tok == NULL || *tok == NULL)
    {
        perror("Error: invalid pointer");
        return (1);
    }
    int flag = 0;
    if ((*tok)->type == IN)
        flag = save_infile(cmd, tok);
    else if ((*tok)->type == OUT)
        flag = save_outfile(cmd, tok);
    else if ((*tok)->type == APPEND)
        flag = save_append(cmd, tok);
    // else if ((*tok)->type == HEREDOC)
    //     flag = save_heredoc(data, cmd, tok);
    else
        return (0);
    return (flag);
}

