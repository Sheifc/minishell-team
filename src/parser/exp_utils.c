#include "minishell.h"

int	is_there_a_dollar(char *str)
{
	int	i;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' || str[i] == '-' || str[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_utils2(char *line, char *temp, int *i, int *temp_len)
{
	char	*aux;
	int		j;
	char	*new_temp;
	char	*env_value;
	aux = (char *)malloc(sizeof(ft_strlen(line) + 1));
	j = 0;
	(*i)++;
	while (line[*i] && ft_isalnum(line[*i]))
		aux[j++] = line[(*i)++];
	aux[j] = '\0';
	env_value = getenv(aux);
	if (!env_value)
		env_value = "";
	new_temp = ft_strjoin(temp, env_value);
	*temp_len += ft_strlen(env_value);
	free(aux);
	free(temp);
	return (new_temp);
}

char *replace_dollar(char *line, t_env *env)
{
    char *temp;
    int i = 0;
    int temp_len = 0;
    char *home;
	temp = ft_strdup("");
    while (line[i])
	{
		if (line[i] == '$')
            temp = expand_utils(line, temp, &i, &temp_len);
        else if ((line[i] == '~' && line[i + 1] == '\0') || line[i] == '-')
		{
            home = get_value(env, "HOME");
            temp = malloc(sizeof(ft_strlen(home)));
            temp = ft_strdup(home);
            temp_len += ft_strlen(home);
            i++;
        }
		else
            temp[temp_len++] = line[i++];
        temp[temp_len] = '\0';
    }
    return temp;
}
