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

// Estructura para el nodo de la lista enlazada de las variables de entorno
// misma estructura para la lista env y la lista export que no es mas que la lista env ordenada
typedef struct s_env
{
	char			*key;
	char			*value;
    struct s_env	*next;
}	t_env;

// esta estructura es un nodo para una lista enlazada de comandos: 
// cada nodo debe contener un comando con sus flags en formato array **arg: ejemplo: echo -n
typedef struct s_cmd
{
	char	**arg; // comando con sus flags
	int		n_args; // numero de argumentos en el nodo: ej: echo -n sería 2
    struct s_command *next; // puntero al siguiente nodo (comando)
}	t_cmd;

// En esta estructura durante el parseo se debe guardar los fd de apertura o creación de archivos
// Este fd debe ir actualizandose de modo que el ejecutor acceda al último fd para plasmar la salida del comando, en caso de haber mas de uno
typedef struct s_shell
{
	t_env	*env; // puntero a la cabeza de la lista de variables de entorno
	t_cmd	*cmd; // puntero a la cabeza de la lista de comandos
    t_env   *export;
    char    *str_cmd; //Prompt comando
	int		fdin; // fd creado tras abrir el infile. Inicializado a -1 en caso de no haber infile
	int 	fdout; // fd creado tras crear el outfile. Inicializado a -1 en caso de no haber outfile
    char	*path; // ruta del comando para el executor
    char **envp;
    t_token *token;
    pid_t	pid;
}	t_shell;


typedef struct s_signal
{
	int		exit_status;
	pid_t	pid;
}	t_signal;

#endif