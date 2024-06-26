# include "minishell.h"

void save_infile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdin = open((*tok)->content, O_RDONLY);
    if (cmd->fdin == -1)
        printf("Error reading fd\n");
    (*tok) = (*tok)->next;
}

void save_outfile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(cmd->fdout == -1)
        printf("Error opening fd\n");
    *tok = (*tok)->next;
}

void ft_innout(t_cmd *cmd, t_token **tok)
{
    if (cmd == NULL || tok == NULL) 
    {
        printf("Invalid pointer\n");
        return;
    }
    if((*tok)->type == IN)
        save_infile(cmd, tok);
    else if((*tok)->type == OUT)
        save_outfile(cmd, tok);
}
