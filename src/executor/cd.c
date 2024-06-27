#include "minishell.h"

void    update_list(t_env **env, char *key, char *value)
{
    t_env   *aux;
    aux = *env;
    if (get_value(aux, key) == NULL)
    {
        add(&aux, key, value);
    }
    else
    {
        pop(&aux, key);
        add(&aux, key, value);
    }
}

void    ft_cd(t_shell *data)
{
    char    *path;
    char    *old_pwd;
    char    *new_pwd;

    printf("Directorio actual: ");
    ft_pwd();

    if (data->cmd->n_args == 1)
        path = get_value(data->env, "HOME");
    else if (ft_strncmp(data->cmd->arg[1], "-", 2) == 0)
    {
        path = get_value(data->env, "OLDPWD");
        if (path)
            printf("%s\n", path);
    }
    else
        path = data->cmd->arg[1];
    if (!path)
        ft_error("Error: path not found");
    old_pwd = get_value(data->env, "PWD");
    printf("old_pwd: %s\n", old_pwd);
    if (!old_pwd)
        old_pwd = get_current_directory();
    if (chdir(path) < 0)
		ft_error("error");
    new_pwd = get_current_directory();
    printf("new_pwd: %s\n", new_pwd);

    update_list(&data->env, "PWD", new_pwd);
    printf("%s\n",new_pwd);
    exit(0);
    update_list(&data->env, "OLDPWD", old_pwd);

    //update_list(&data->export, "PWD", new_pwd);
    //update_list(&data->export, "OLDPWD", old_pwd);

    printf("Nuevo directorio actual: ");
    ft_pwd();
    printf("Imprimimos env list: ");
    print_list(data->env);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");

    //free(new_pwd);
    //free(old_pwd);
    exit(0);
}
