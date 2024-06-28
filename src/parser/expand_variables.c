# include "minishell.h"

void expand_variables(t_token **token, t_env *env)
{
    t_token *aux;

    aux = *token;
    while(aux)
    {
        if(is_there_a_dollar(aux->content) == 1 && (aux->type == DQUOTE || aux->type == WORD))
        {
            aux->content = ft_strdup(replace_dollar(aux->content, env));
        }
        aux = aux->next;
    }
}
