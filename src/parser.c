#include "minishell.h"

void	pipe_parser(t_token *tok)
{
	t_token	*aux;

	aux = tok;
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		return ;
	}
	while (aux->next)
	{
		if (aux->type == PIPE && aux->next->type == PIPE)
		{
			printf("Error: syntax error near unexpected token '|'\n");
			return ;
		}
		aux = aux->next;
	}
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		return ;
	}
}

void	parser(t_token *tok)
{
	pipe_parser(tok);
}
