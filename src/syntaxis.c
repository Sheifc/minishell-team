# include "minishell.h"

int in_out_parser(t_token **tok)
{
	t_token *aux;

	aux = *tok;
	if(aux && (aux->type == IN || aux->type == OUT || aux->type == APPEND || aux->type == HEREDOC))
	{
		if(aux->next == NULL)
        {
			printf("bash: syntax error near unexpected token 'newline'\n");
            return(1);
        }
		else if(aux->type == IN && aux->next->type != WORD)
        {
			printf("bash: syntax error near unexpected token '<'\n");
            return(1);
        }
		else if(aux->type == OUT && aux->next->type != WORD)
        {
			printf("bash: syntax error near unexpected token '>'\n");
            return(1);
        }
		else if(aux->type == HEREDOC && aux->next->type != WORD)
        {
			printf("bash: syntax error near unexpected token '<<'\n");
            return(1);
        }
		else if(aux->type == APPEND && aux->next->type != WORD)
        {
			printf("bash: syntax error near unexpected token '>>'\n");
            return(1);
        }
	}
    return(0);
}

int	pipe_parser(t_token *tok)
{
	t_token	*aux;

	aux = tok;
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		return (1);
	}
	while (aux->next)
	{
		if (aux->type == PIPE && aux->next->type == PIPE)
		{
			printf("Error: syntax error near unexpected token '||'\n");
			return(1);
		}
		aux = aux->next;
	}
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		return(1);
	}
    return(0);
}

int is_new_line(t_token *tok)
{
	if (ft_strncmp(tok->content, "\\n", 2) == 0 && tok->next == NULL)
		return(1);
	else if(ft_strncmp(tok->content, "!", 1) == 0 && tok->next == NULL)
		return(1);
	else if(ft_strncmp(tok->content, ":", 1) == 0 && tok->next == NULL)
		return(1);
	else
		return(0);
}

int syntaxis_is_ok(t_token **token)
{
    if(is_new_line(*token))
        return(0);
    else if(pipe_parser(*token))
        return(0);
    else if(in_out_parser(token))
        return(0);
    return(1);
}