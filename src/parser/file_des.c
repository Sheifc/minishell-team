#include "minishell.h"

void	save_heredoc(t_cmd *cmd, t_token **tok, t_env *env)
{
	char	*line;
	char	*expanded_line;
	int		i;

	i = 1;
	cmd->fdin = open("hdoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (cmd->fdin == -1)
		printf("Error making HEREDOC\n");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("bash: warning: here-document at line %d delimited by (wanted «%s»)\n", i, (*tok)->content);
			break ;
		}
		i++;
		add_history(line);
		expanded_line = expand_heredoc(line, env);
		if (ft_strncmp(line, (*tok)->content, ft_strlen((*tok)->content)
				+ 1) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc(expanded_line, cmd);
		free(line);
	}
}

void	save_append(t_cmd *cmd, t_token **tok)
{
	(*tok) = (*tok)->next;
	cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fdout == -1)
		printf("Error appending fd\n");
	*tok = (*tok)->next;
}

void	save_infile(t_cmd *cmd, t_token **tok)
{
	(*tok) = (*tok)->next;
	cmd->fdin = open((*tok)->content, O_RDONLY);
	if (cmd->fdin == -1)
		printf("Error reading fd\n");
	(*tok) = (*tok)->next;
}

void	save_outfile(t_cmd *cmd, t_token **tok)
{
	(*tok) = (*tok)->next;
	if (cmd->fdout > 2)
		close(cmd->fdout);
	cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fdout == -1)
		printf("Error opening fd\n");
	*tok = (*tok)->next;
}

void	heredoc_handler(int signum)
{
	(void)signum;
	printf("> ^C\n");
	exit(130);
}

void	ft_innout(t_cmd *cmd, t_token **tok, t_env *env)
{
	int	pid;

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
	{
		pid = fork();
		*tok = (*tok)->next;
		if (pid == 0)
		{
			signal(SIGINT, heredoc_handler);
			save_heredoc(cmd, tok, env);
			exit(0);
		}
		*tok = (*tok)->next;
		signal(SIGINT, SIG_IGN);
		waitpid(pid, NULL, 0);
		cmd->fdin = open("hdoc.tmp", O_RDONLY);
		unlink("hdoc.tmp");
		signal(SIGINT, sigint_handler);
	}
}