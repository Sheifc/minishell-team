#include "minishell.h"

static void	write_heredoc(char *expanded_line, t_cmd *cmd)
{
	write(cmd->fdin, expanded_line, ft_strlen(expanded_line));
	write(cmd->fdin, "\n", 1);
}

/* int save_heredoc(t_cmd *cmd, t_token **tok)
{
    char *line;

    // Avanzar al siguiente token (el delimitador heredoc)
    *tok = (*tok)->next;

    // Crear y abrir el archivo temporal heredoc para escritura
    cmd->fdin = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdin == -1)
    {
        ft_error("Error making Heredoc\n", 1);
        return 1; // Indicar error
    }

    // Leer líneas del input y escribirlas en el archivo hasta que se encuentre la línea delimitadora
    line = readline("> ");
    while (line)
    {
        if (ft_strncmp(line, (*tok)->content, ft_strlen((*tok)->content) + 1) == 0)
        {
            free(line);
            break;
        }
        write(cmd->fdin, line, ft_strlen(line));
        write(cmd->fdin, "\n", 1);
        free(line);
        line = readline("> ");
    }
    close(cmd->fdin); // Cerrar el archivo temporal

    // Reabrir el archivo temporal heredoc para lectura
    cmd->fdin = open("heredoc_tmp", O_RDONLY);
    if (cmd->fdin == -1)
    {
        ft_error("Error opening Heredoc for reading\n", 1);
        return 1; // Indicar error
    }

    // Avanzar al siguiente token después del delimitador heredoc
    *tok = (*tok)->next;
    return 0; // Indicar éxito
} */

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

int	save_heredoc(t_cmd *cmd, t_token **tok)
{
	char	*line;
	char	*expanded_line;
	int		i;

	i = 1;
	cmd->fdin = open("hdoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdin == -1)
    {
        ft_error("Error making Heredoc\n", 1);
        return 1; // Indicar error
    }
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
	//printf("> ^C\n");
	exit(130);
}

int    heredoc(t_cmd *cmd, t_token **tok)
{
    pid_t	pid;

    pid = fork();
    if (pid == -1)
    {
        ft_error("Error forking\n", 1);
        return 1; // Indicar error
    }
    *tok = (*tok)->next;
    if (pid == 0)
    {
        signal(SIGINT, heredoc_handler);
        save_heredoc(cmd, tok);
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
