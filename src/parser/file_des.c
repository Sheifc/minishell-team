#include "minishell.h"

void    save_heredoc(t_cmd *cmd, t_token **tok)
{
    char    *line;
    char    *expanded_line;
    *tok = (*tok)->next;
    cmd->fdin = open("heredoc", O_WRONLY | O_CREAT, 0644);
    if (cmd->fdin == -1)
        printf("Error making HEREDOC\n");
    line = readline("> ");
    while (line)
    {
        add_history(line);
        expanded_line = expand_heredoc(line);
        if (ft_strncmp(line, (*tok)->content, ft_strlen((*tok)->content)
                + 1) == 0)
            break ;
        write(cmd->fdin, expanded_line, ft_strlen(expanded_line));
        write(cmd->fdin, "\n", 1);
        free(line);
        line = readline("> ");
    }
    *tok = (*tok)->next;
    unlink("heredoc");
}

void    save_append(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (cmd->fdout == -1)
        printf("Error appending fd\n");
    *tok = (*tok)->next;
}

void    save_infile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdin = open((*tok)->content, O_RDONLY);
    if (cmd->fdin == -1)
        printf("Error reading fd\n");
    (*tok) = (*tok)->next;
}

void    save_outfile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    if (cmd->fdout > 2)
        close(cmd->fdout);
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdout == -1)
        printf("Error opening fd\n");
    *tok = (*tok)->next;
}

void    ft_innout(t_cmd *cmd, t_token **tok)
{
    if (cmd == NULL || tok == NULL)
    {
        printf("Invalid pointer\n");
        return ;
    }
    if ((*tok)->type == IN)
        save_infile(cmd, tok);
    else if ((*tok)->type == OUT)
        save_outfile(cmd, tok);
    else if ((*tok)->type == APPEND)
        save_append(cmd, tok);
    else if ((*tok)->type == HEREDOC)
        save_heredoc(cmd, tok);
}
