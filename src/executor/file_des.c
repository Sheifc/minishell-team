#include "minishell.h"

int save_infile(t_shell *data, t_cmd *cmd, t_token **tok)
{
    t_cmd *last;
    printf("\n\n\nInfile function: ");
    last = get_last_cmd(cmd);
    printf("al entrar tok->content: %s\n", (*tok)->content);
    (*tok) = (*tok)->next;
    printf("sig tok->content: %s\n", (*tok)->content);
    if (last->fdin > 2)
        close(last->fdin);
    printf("save infile fdin: %d\n", cmd->fdin);
    if (cmd->fdin == -1)
        cmd->fdin = open((*tok)->content, O_RDONLY);
    printf("fdin after open: %d\n", cmd->fdin);
    if (cmd->fdin == -1)
    {
        ft_error(data, "Error reading fd\n", 1);
        return (1);
    }
    (*tok) = (*tok)->next;
    printf("al final de la funcion infile tok->content: %s\n", (*tok)->content);
    printf("\n\n\n");
    return (0);
}

int save_append(t_shell *data, t_cmd *cmd, t_token **tok)
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
        ft_error(data, "Error appending fd\n", 1);
        return (1);
    }
    if ((*tok)->next != NULL)
        (*tok) = (*tok)->next;
    return (0);
}

int save_outfile(t_shell *data, t_cmd *cmd, t_token **tok)
{
    t_cmd *last;

    last = get_last_cmd(cmd);
    (*tok) = (*tok)->next;
    printf("en outfile tok->content: %s\n", (*tok)->content);
    if (last->fdout > 2)
        close(last->fdout);
    printf("save outfile fdout: %d\n", last->fdout);
    if (last->fdout == -1)
        last->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("despues de open fdout: %d\n", last->fdout);
    if (cmd->fdout == -1)
    {
        ft_error(data, "Error opening fd\n", 1);
        return (1);
    }
    if ((*tok)->next != NULL)
        *tok = (*tok)->next;
    printf("al final de la funcion outfile tok->content: %s\n", (*tok)->content);
    return (0);
}

int ft_innout(t_shell *data, t_cmd *cmd, t_token **tok)
{
    if (cmd == NULL || tok == NULL || *tok == NULL)
    {
        ft_error(data, "Error: invalid pointer\n", 1);
        return (1);
    }
    int flag = 0;
    if ((*tok)->type == IN)
        flag = save_infile(data, cmd, tok);
    else if ((*tok)->type == OUT)
        flag = save_outfile(data, cmd, tok);
    else if ((*tok)->type == APPEND)
        flag = save_append(data, cmd, tok);
    //else if ((*tok)->type == HEREDOC)
        //flag = save_heredoc(data, cmd, tok);
    else
        return (0);
    return (flag);
}

