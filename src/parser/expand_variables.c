# include "minishell.h"

/* char *get_key_parser(char *str)
{
    int i;
    char *key;

    i = 0;
    while(str[i] != '=')
        i++;
    key = malloc(sizeof(char) * i + 1);
    if(!key)
        return (NULL);
    i = 0;
    while(str[i] != '=')
    {
        key[i] = str[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

char *get_value_parser(char *str)
{
    int i;
    int j;
    char *value;

    i = 0;
    while(str[i] != '=')
        i++;
    i++;
    j = i;
    while(str[j] != '\0')
        j++;
    value = malloc(sizeof(char) * j - i + 1);
    if(!value)
        return (NULL);
    j = 0;
    while(str[i] != '\0')
    {
        value[j] = str[i];
        i++;
        j++;
    }
    value[j] = '\0';
    return (value);
}

t_env *transform_env(char *envp[])
{
    t_env *env;
    t_env *aux;
    int i;
    char *key;
    char *value;

    env = NULL;
    aux = NULL;
    i = 0;
    while (envp[i])
    {
        key = get_key_parser(envp[i]);
        value = get_value_parser(envp[i]);
        create_env_list(value, &aux, key);
        if(env == NULL)
            env = aux;
        i++;
    }
    return (env);
}

void expand_variables(t_token **token, char **envp, t_env *env)
{
    t_token *aux;

    env = transform_env(envp);
    aux = *token;
    while(aux)
    {
        if(is_there_a_dollar(aux->content) == 1 && (aux->type == DQUOTE || aux->type == WORD))
        {
            aux->content = ft_strdup(replace_dollar(aux->content, env));
        }
        aux = aux->next;
    }
} */
