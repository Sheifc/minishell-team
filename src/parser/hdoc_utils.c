# include "minishell.h"

void write_heredoc(char *expanded_line, t_cmd *cmd)
{
    write(cmd->fdin, expanded_line, ft_strlen(expanded_line));
    write(cmd->fdin, "\n", 1);
}
