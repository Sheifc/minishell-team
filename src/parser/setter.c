#include "minishell.h"

void	append_hdoc_tok(char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i] == '<')
		heredoc_in(str_cmd, tok, i);
	else if (str_cmd[*i] == '>')
		append_out(str_cmd, tok, i);
}

void	word_tok(char *str_cmd, t_token **tok, int *i)
{
	int	start;

	start = *i;
	while (str_cmd[*i] && str_cmd[*i] != '|' && str_cmd[*i] != '<'
		&& str_cmd[*i] != '>' && str_cmd[*i] != ' ' && str_cmd[*i] != '\''
		&& str_cmd[*i] != '"')
		*i += 1;
	create_list(WORD, tok, ft_substr(str_cmd, start, *i - start));
}

void	quote_tok(char *str_cmd, t_token **tok, int *i)
{
	int	start;
	int	qflag;

	start = *i;
	qflag = quote_stuff(i, str_cmd);
	if (qflag > 0)
		create_list(QUOTE, tok, ft_substr(str_cmd, start + 1, qflag));
	else if (qflag < 0)
	{
		printf("Error: unclosed quote\n");
		(*tok) = NULL;
	}
	*i += 1;
}

void	dquote_tok(char *str_cmd, t_token **tok, int *i)
{
	int	start;
	int	qflag;

	start = *i;
	qflag = dquote_stuff(i, str_cmd);
	if (qflag > 0)
		create_list(DQUOTE, tok, ft_substr(str_cmd, start + 1, qflag));
	else if (qflag < 0)
	{
		printf("Error: unclosed dquote\n");
		(*tok) = NULL;
	}
	*i += 1;
}

void	setter(int type, char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i] && type == PIPE)
	{
		create_list(type, tok, ft_strdup("|"));
		*i += 1;
	}
	else if (str_cmd[*i] && type == IN)
		append_hdoc_tok(str_cmd, tok, i);
	else if (str_cmd[*i] && type == OUT)
		append_hdoc_tok(str_cmd, tok, i);
	else if (str_cmd[*i] && type == WORD)
		word_tok(str_cmd, tok, i);
	else if (str_cmd[*i] && type == QUOTE)
		quote_tok(str_cmd, tok, i);
	else if (str_cmd[*i] && type == DQUOTE)
		dquote_tok(str_cmd, tok, i);
}
