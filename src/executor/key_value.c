#include "minishell.h"

void    get_key_value(char *str, char **key, char **value)
{
    char *equal;

    if (str == NULL || key == NULL || value == NULL)
        perror("Error: null arguments");
    *key = ft_substr(str, 0, ft_strchr(str, '=') - str);
    equal = ft_strchr(str, '=');
    if (equal)
        *value = ft_strdup(equal + 1);
    else
        *value = NULL;
}

char    *get_value(t_env *env, const char *key)
{
    if (env == NULL || key == NULL)
        perror("Error: null arguments");
    while (env != NULL && env->next != NULL)
    {
        if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

char    *get_cd_value(t_env *env, const char *key)
{
    t_env   *node;
 
    node = env_lst_search(env, key);
    if (node)
        return (node->value);
    return (NULL);
}
