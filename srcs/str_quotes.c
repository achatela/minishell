#include "minishell.h"

static int	var_length(char *str, int i, int j, int k)
{
	char	*tmp;
	char	*tmp2;
	int		length;

	length = 0;
	while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
			|| str[j] == '_'))
		j++;
	tmp = malloc(sizeof(char) * (j - i) + 2);
	i++;
	while (++k > -1 && i < j)
		tmp[k] = str[i++];
	tmp[k++] = '=';
	tmp[k] = '\0';
	tmp2 = get_env_var(g_env, tmp, 0);
	length += ft_strlen(tmp2);
	free(tmp);
	free(tmp2);
	return (length);
}

static int	length_quotes(char *str, int i, int length)
{
	while (str[i] && str[i] != '"' && str[i] != 39)
	{
		length++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '"'/*&& i == 0*/)
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] == '$')
				{
					length += var_length(str, i, i + 1, -1);
					while (str[i] && (ft_isalpha(str[i]) == 1 || ft_isalnum(str[i]) == 1
							|| str[i] == '_'))
						i++;
					i++;
				}
				else
				{
					i++;
					length++;
				}
			}
			i++;
		}
		else if (str[i] == 39/* && i == 0*/)
		{
			i++;
			while (str[i] && str[i] != 39)
			{
				length++;
				i++;
			}
			i++;
		}
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}

static char	*var_str(char *str, int i, int j, int k)
{
	char	*tmp;
	char	*ret;

	while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
			|| str[j] == '_'))
		j++;
	tmp = malloc(sizeof(char) * ((j - i) + 2));
	i++;
	while (++k > -1 && i < j)
		tmp[k] = str[i++];
	tmp[k++] = '=';
	tmp[k] = '\0';
	ret = get_env_var(g_env, tmp, 0);
	free(tmp);
	return (ret);
}

static char	*fill_quotes_ret(char *str, int i, int j, int k)
{
	char	*tmp;
	char	*tmp2;

	tmp = malloc(sizeof(char) * (length_quotes(str, 0, 0) + 1));
	while (str[i] && str[i] != '"' && str[i] != 39)
		tmp[j++] = str[i++];
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] == '$')
				{
					tmp2 = var_str(str, i, i + 1, -1);
					if (tmp2 != NULL)
					{
						k = -1;
						while (tmp2[++k])
							tmp[j++] = tmp2[k];
					}
					i++;
					while (str[i] && (ft_isalpha(str[i]) == 1 || ft_isalnum(str[i]) == 1
							|| str[i] == '_'))
						i++;
					free(tmp2);
				}
				else
					tmp[j++] = str[i++];
			}
			i++;
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				tmp[j++] = str[i++];
			i++;
		}
		/* else if str[i] == '$'
		 * en dehors des quotes*/
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*str_quotes(char *str)
{
	char	*ret;

	ret = fill_quotes_ret(str, 0, 0, -1);
	//printf("length = %d\n", length_quotes(str, 0, 0));
	return (ret);
}
