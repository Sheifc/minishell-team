#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../libft/includes/libft.h"

typedef enum e_token_type
{
    WORD,
    PIPE,
    IN,
    OUT,
    HEREDOC,
    APPEND,
    QUOTE,
    DQUOTE
}   t_token_type;

typedef struct s_token
{
    char            *content;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
    struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char	**arg;
	int		n_args;
    int		fdin;
	int 	fdout;
    struct s_cmd *next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmd;
    t_env   *export;
    t_token *token;
    char    *str_cmd;
    char    **envp;
    char	*path;
    int     status;
    pid_t	pid;
    int flag_hdoc;
}	t_shell;


typedef struct s_signal
{
	int		exit_status;
	pid_t	pid;
}	t_signal;

#endif