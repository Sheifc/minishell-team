#include "minishell.h"

int    save_append(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (cmd->fdin == -1)
    {
        ft_error("Error appending fd\n", 1);
        return (1);
    }
    (*tok) = (*tok)->next;
    return (0);
}

int save_infile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdin = open((*tok)->content, O_RDONLY);
    if (cmd->fdin == -1)
    {
        ft_error("Error reading fd\n", 1);
        return (1);
    }
    (*tok) = (*tok)->next;
    return (0);
}

int save_outfile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    if (cmd->fdout > 2)
        close(cmd->fdout);
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdout == -1)
    {
        ft_error("Error opening fd\n", 1);
        return (1);
    }
    *tok = (*tok)->next;
    return (0);
}

int ft_innout(t_cmd *cmd, t_token **tok)
{
    if (cmd == NULL || tok == NULL || *tok == NULL)
        return (ft_error("Invalid pointer\n", 1));
    int flag = 0;
    if ((*tok)->type == IN)
        flag = save_infile(cmd, tok);
    else if ((*tok)->type == OUT)
        flag = save_outfile(cmd, tok);
    else if ((*tok)->type == APPEND)
        flag = save_append(cmd, tok);
    else if ((*tok)->type == HEREDOC)
        flag = heredoc(cmd, tok);
    else
        return (0);
    return (flag);
}
