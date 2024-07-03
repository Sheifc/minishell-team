#include "minishell.h"

int save_heredoc(t_cmd *cmd, t_token **tok)
{
    char *line;

    // Avanzar al siguiente token (el delimitador heredoc)
    *tok = (*tok)->next;

    // Crear y abrir el archivo temporal heredoc para escritura
    cmd->fdin = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdin == -1)
    {
        ft_error("Error making Heredoc\n", 1);
        return 1; // Indicar error
    }

    // Leer líneas del input y escribirlas en el archivo hasta que se encuentre la línea delimitadora
    line = readline("> ");
    while (line)
    {
        if (ft_strncmp(line, (*tok)->content, ft_strlen((*tok)->content) + 1) == 0)
        {
            free(line);
            break;
        }
        write(cmd->fdin, line, ft_strlen(line));
        write(cmd->fdin, "\n", 1);
        free(line);
        line = readline("> ");
    }
    close(cmd->fdin); // Cerrar el archivo temporal

    // Reabrir el archivo temporal heredoc para lectura
    cmd->fdin = open("heredoc_tmp", O_RDONLY);
    if (cmd->fdin == -1)
    {
        ft_error("Error opening Heredoc for reading\n", 1);
        return 1; // Indicar error
    }

    // Avanzar al siguiente token después del delimitador heredoc
    *tok = (*tok)->next;
    return 0; // Indicar éxito
}

int    save_append(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (cmd->fdin == -1)
    {
        ft_error("Error appending fd\n", 1);
        return 1; // Indicar error
    }
    (*tok) = (*tok)->next;
    return 0; // Indicar éxito
}

int save_infile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdin = open((*tok)->content, O_RDONLY);
    if (cmd->fdin == -1)
    {
        ft_error("Error reading fd\n", 1);
        return 1; // Indicar error
    }
    (*tok) = (*tok)->next;
    return 0; // Indicar éxito
}


int save_outfile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    if (cmd->fdout > 2)
        close(cmd->fdout);
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdout == -1)
    {
        ft_error("Error opening fd\n", 1);
        return 1; // Indicar error
    }
    *tok = (*tok)->next;
    return 0; // Indicar éxito
}

int ft_innout(t_cmd *cmd, t_token **tok)
{
    if (cmd == NULL || tok == NULL || *tok == NULL)
        return ft_error("Invalid pointer\n", 1);
    int flag = 0;
    if ((*tok)->type == IN)
        flag = save_infile(cmd, tok);
    else if ((*tok)->type == OUT)
        flag = save_outfile(cmd, tok);
    else if ((*tok)->type == APPEND)
        flag = save_append(cmd, tok);
    else if ((*tok)->type == HEREDOC)
        flag = save_heredoc(cmd, tok);
    else
        return 0; // Indicar éxito
    return flag; // Retornar el estado del flag
}
