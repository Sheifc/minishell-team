
#ifndef MINISHELL_H
# define MINISHELL_H

# include "structures.h"
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

//*--------------------BUILTINS----------------------------
void	execute_builtin(t_shell *data);
void	ft_echo(t_cmd *args);
void	ft_cd(t_shell *data);
char    *get_current_directory(void);
int     ft_pwd(void);
void    ft_export(t_shell *data);
void	ft_unset(t_shell *data);
void	ft_env(t_env *env);
void	ft_exit(t_cmd *cmd);

//*--------------------ENV---------------------------------
void    fill_env_list(t_env **head, char **envp, int *i);
void    init_env(t_shell *data, char **envp);
void    add(t_env **head, char *key, char *value);
void    pop(t_env **head, char *key);
void    get_key_value(char *str, char **key, char **value);
char    *get_value(t_env *env, char *key);
void    update_list(t_env **env, char *key, char *value);

//*--------------------EXECUTOR----------------------------
void    get_path(t_shell *data);
void    executor(t_shell *data);

//*--------------------UTILS-------------------------------
void    ft_swap(char **a, char **b);
void    print_key(t_env *head);
char    *print_value(t_env *env, char *key);
void    print_list(t_env *head);
void    free_env_list(t_env *head);
void    free_env_node(t_env **node);
void    ft_error(char *msg);
void    print_error(char *msg);

#endif