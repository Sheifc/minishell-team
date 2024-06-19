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
    (void)env;

    final = ft_strdup("");
    aux = ft_strdup("");
    i = 0;
    while(str[i])
    {
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
            printf("%s\n", aux);
        }
        else
            i++;
        while(env)
        {
            if(ft_strncmp(aux, env->key, ft_strlen(env->key)) == 0)
                ft_strjoin(final, aux);
            env = env->next;
        }
    }
    return(final);
}
