#include "minishell.h"

void is_new_line(t_token *tok)
{
	if (ft_strncmp(tok->content, "\\n", 2) == 0 && tok->next == NULL)
		tok = NULL;
	else if(ft_strncmp(tok->content, "!", 1) == 0 && tok->next == NULL)
		tok = NULL;
	else if(ft_strncmp(tok->content, ":", 1) == 0 && tok->next == NULL)
		tok = NULL;
}

void	pipe_parser(t_token *tok)
{
	t_token	*aux;

	aux = tok;
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		tok = NULL;
		return ;
	}
	while (aux->next)
	{
		if (aux->type == PIPE && aux->next->type == PIPE)
		{
			printf("Error: syntax error near unexpected token '||'\n");
			tok = NULL;
			return ;
		}
		aux = aux->next;
	}
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		tok = NULL;
		return ;
	}
}

void in_out_parser(t_token **tok)
{
	t_token *aux;

	aux = *tok;
	if(aux && (aux->type == IN || aux->type == OUT || aux->type == APPEND || aux->type == HEREDOC))
	{
		if(aux->next == NULL)
			printf("bash: syntax error near unexpected token 'newline'\n");
		else if(aux->type == IN)
			printf("bash: syntax error near unexpected token '<'");
		else if(aux->type == OUT)
			printf("bash: syntax error near unexpected token '>'");
		else if(aux->type == HEREDOC)
			printf("bash: syntax error near unexpected token '<<'");
		else if(aux->type == APPEND)
			printf("bash: syntax error near unexpected token '>>'");
		tok = NULL;
		return ;
	}
}

void	parser(t_token **tok, char **envp, t_env *env)
{
	pipe_parser(*tok);
	is_new_line(*tok);
	in_out_parser(tok);
	if(tok)
            expand_variables(tok, envp, env);
}
