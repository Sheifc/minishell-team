#include "minishell.h"

static void	write_heredoc(char *expanded_line, t_cmd *cmd)
{
	write(cmd->fdin, expanded_line, ft_strlen(expanded_line));
	write(cmd->fdin, "\n", 1);
}

char	*expand_heredoc(char *line)
{
	char	*temp;
	int		i;
	int		temp_len;

	temp = ft_strdup("");
	i = 0;
	temp_len = 0;
	while (line[i])
	{
		if (line[i] == '$')
			temp = expand_utils(line, temp, &i, &temp_len);
		else
			temp[temp_len++] = line[i++];
	}
	temp[temp_len] = '\0';
	return (temp);
}

int	save_heredoc(t_shell *data, t_cmd *cmd, t_token **tok)
{
	char	*line;
	char	*expanded_line;
	int		i;

	i = 1;
	cmd->fdin = open("hdoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdin == -1)
    {
        ft_error(data, "Error making Heredoc\n", 1);
        return 1;
    }
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("Minishell: warning: here-document at line %d delimited by (wanted «%s»)\n", i, (*tok)->content);
			break ;
		}
		i++;
		add_history(line);
		expanded_line = expand_heredoc(line);
		if (ft_strncmp(line, (*tok)->content, ft_strlen((*tok)->content)
				+ 1) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc(expanded_line, cmd);
		free(line);
	}
    return (0);
}

void	heredoc_handler(int signum)
{
	(void)signum;
	printf("> ^C\n");
	exit(130);
}

int    heredoc(t_shell *data, t_cmd *cmd, t_token **tok)
{
    pid_t	pid;

    pid = fork();
    if (pid == -1)
    {
        ft_error(data, "Error forking\n", 1);
        return 1;
    }
    *tok = (*tok)->next;
    if (pid == 0)
    {
        signal(SIGINT, heredoc_handler);
        save_heredoc(data, cmd, tok);
        exit(0);
    }
    *tok = (*tok)->next;
    signal(SIGINT, SIG_IGN);
    waitpid(pid, NULL, 0);
    cmd->fdin = open("hdoc.tmp", O_RDONLY);
    unlink("hdoc.tmp");
    signal(SIGINT, sigint_handler);
    return (0);
}
