#include "minishell.h"

t_env   *env_lst_search(t_env *env, const char *key)
{
    while (env)
    {
        if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
            return (env);
        env = env->next;
    }
    return (NULL);
}

static int update_pwd_oldpwd(t_env *env, const char *key, char *value)
{
    t_env   *temp_env;

    temp_env = env_lst_search(env, key);
    if (temp_env)
    {
        free(temp_env->value);
        temp_env->value = ft_strdup(value);
        if (!temp_env->value)
            return (0);
    }
    return (1);
}

static char    *get_pwd(t_shell *data, char *path, char *old_pwd)
{
    if (data->cmd->n_args == 1 || !ft_strncmp(data->cmd->arg[1], "~", 1))
    {
        path = get_cd_value(data->env, "HOME");
        if (!path)
        {
            free(old_pwd);
            ft_error("Error: HOME not found", 0);
        }
    }
    else if (!ft_strncmp(data->cmd->arg[1], "-", 1))
    {
        path = get_cd_value(data->env, "OLDPWD");
        if (!path)
        {
            free(old_pwd);
            ft_error("Error: path not found", 0);
        }
    }
    else
        path = data->cmd->arg[1];
    return (path);
}

static void    update_variables(char *new_pwd, char *old_pwd, t_shell *data)
{
    if (!new_pwd)
    {
        free(old_pwd);
        ft_error("Error obteniendo el nuevo directorio", 0);
    }
    if (!update_pwd_oldpwd(data->env, "OLDPWD", old_pwd) || 
        !update_pwd_oldpwd(data->export, "OLDPWD", old_pwd))
    {
        free(old_pwd);
        free(new_pwd);
        ft_error("Error actualizando OLDPWD", 0);
    }
    if (!update_pwd_oldpwd(data->env, "PWD", new_pwd) || 
        !update_pwd_oldpwd(data->export, "PWD", new_pwd))
    {
        free(old_pwd);
        free(new_pwd);
        ft_error("Error actualizando PWD", 0);
    }
}

void    ft_cd(t_shell *data)
{
    char    *pwd;
    char    *old_pwd;
    char    *new_pwd;

    pwd = NULL;
    old_pwd = get_current_directory();
    if (!old_pwd)
        ft_error("Error: getting pwd", 0);
    pwd = get_pwd(data, pwd, old_pwd);
    if (chdir(pwd) < 0)
    {
        free(old_pwd);
        ft_error("Error: chdir failed", 0);
    }
    new_pwd = get_current_directory();
    update_variables(new_pwd, old_pwd, data);
    free(old_pwd);
    free(new_pwd);   
}
