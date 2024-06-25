
#ifndef MINISHELL_H
# define MINISHELL_H

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

# include "structures.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

//*--------------------BUILTINS----------------------------
void	execute_builtin(t_shell *data);
void	ft_echo(t_cmd *args);
void	ft_cd(t_shell *data);
char	*get_current_directory(void);
int		ft_pwd(void);
void	ft_export(t_shell *data);
void	ft_unset(t_shell *data);
void	ft_env(t_env *env);
void	ft_exit(t_cmd *cmd);

//*--------------------ENV---------------------------------
void	fill_env_list(t_env **head, char **envp, int *i);
void	init_env(t_shell *data, char **envp);
void	add(t_env **head, char *key, char *value);
void	pop(t_env **head, char *key);
void	get_key_value(char *str, char **key, char **value);
char	*get_value(t_env *env, char *key);
void	update_list(t_env **env, char *key, char *value);

//*--------------------EXECUTOR----------------------------
void	get_path(t_shell *data);
void	executor(t_shell *data);

//*--------------------UTILS-------------------------------
void	ft_swap(char **a, char **b);
void	print_key(t_env *head);
char	*print_value(t_env *env, char *key);
void	print_list(t_env *head);
void	free_env_list(t_env *head);
void	free_env_node(t_env **node);
void	ft_error(char *msg);
void	print_error(char *msg);

//*--------------------LEXER-------------------------------
void	lexer(char *str_cmd, t_token **tok);
void	set_token(int type, char *str_cmd, t_token **tok, int *i);
void	setter(int type, char *str_cmd, t_token **tok, int *i);
void	create_list(int type, t_token **tok, char *content);
void	print_lists(t_token *tok);
int		quote_stuff(int *i, char *str_cmd);
int		dquote_stuff(int *i, char *str_cmd);
void	heredoc_in(char *str_cmd, t_token **tok, int *i);
void	append_out(char *str_cmd, t_token **tok, int *i);

//*--------------------PARSER-------------------------------
void	parser(t_token **tok, char **envp, t_env *env);

//*--------------------EXPAND_VARIABLES---------------------
void	expand_variables(t_token **token, char **envp, t_env *env);
void	create_env_list(char *value, t_env **env, char *key);
int is_there_a_dollar(char *str);
char *replace_dollar(char *str, t_env *env);

//*--------------------FILL_STRUCT--------------------------
void	fill_struct(t_shell *data);
int syntaxis_is_ok(t_token **token);

#endif