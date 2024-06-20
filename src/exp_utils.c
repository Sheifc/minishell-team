# include "minishell.h"

int is_there_a_dollar(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

char *replace_dollar(char *str, t_env *env)
{
    int i;
    int j;
    char *aux;
    char *final;
    t_env *aux_env;

    final = ft_strdup("");
    aux = ft_strdup("");
    i = 0;
    while(str[i])
    {
        aux_env = env;
        if(str[i] != '$')
            final[i] = str[i];
        if(str[i] == '$')
        {
            i++;
            j = 0;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) 
            {
                aux[j] = str[i];
                j++;
                i++;
            }
            aux[j] = '\0';
            while(aux_env)
            {
                if(ft_strncmp(aux_env->key, aux, ft_strlen(aux)) == 0)
                {
                    final = ft_strjoin(final, aux_env->value);
                    break;
                }
                aux_env = aux_env->next;
            }
        }
        else
            i++;
    }
    free(aux);
    return(final);
}
