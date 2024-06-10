#include "minishell.h"

static void init_stack(t_cmd *cmd, t_shell *data, int argc, char **argv)
{
    // Inicializar t_cmd
    cmd->arg = argv;
    cmd->n_args = argc;
    cmd->next = NULL;

    // Inicializar t_shell
    data->cmd = cmd;
    data->env = NULL;  // Inicializar a NULL para la lista de entorno
    data->line = NULL;
    data->pid = 0;
    data->fdin = -1;
    data->fdout = -1;
    data->path = NULL;
    data->export = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_cmd cmd;
    t_shell data;

    init_stack(&cmd, &data, argc - 1, &argv[1]);
    init_env(&data, envp);
    //printf("\n\n---------------\n\n");
    //print_key(data.env);
    execute_builtin(&data);  // Pasa el puntero al comando
    //get_path(&data);
    // Liberar la memoria asignada
    //free(cmd.arg);  // Liberar la lista de argumentos tras el parseo
    free_env_list(data.env);  // Liberar la lista de entorno
    free_env_list(data.export);
    return (0);
}
