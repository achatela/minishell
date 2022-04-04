#include "minishell.h"

static int	parsed_length(char *str, int i, int j, int k)
{
	char	*tmp;
	char	*tmp2;
	int		length;

	length = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			k = -1;
			j = i + 1;
			while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
				|| str[j] == '_'))
				j++;
			tmp = malloc(sizeof(char) * 100);
			if (!tmp)
				return (0);
			i++;
			while (str[i] && i != j && ++k > -1)
			{
				tmp[k] = str[i];
				i++;
			}
			tmp[k + 1] = '=';
			tmp[k + 2] = '\0';
			tmp2 = get_env_var(g_env, tmp, 0);
			if (tmp2 != NULL)
			{
				length += ft_strlen(tmp2);
				free(tmp2);
			}
			free(tmp);
	}
		else
		{
			i++;
			length++;
		}
	}
	printf("%d\n", length);
	return (length + 1);
}

static char	*fill_ret(char *ret, char *str, int i, int j)
{
	char	*tmp;
	char	*tmp2;
	int		k;
	int		l;

	l = 0;
	while (str[l])
	{
		if (str[l] == '$')
		{
			k = 0;
			i = l;
			j = i + 1;
			while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
				|| str[j] == '_'))
				j++;
			tmp = malloc(sizeof(char) * 100);
			i++;
//			while (str[i] && i != j && ++k > -1)
			while (str[i] && (ft_isalpha(str[i]) == 1 || ft_isalnum(str[i]) == 1
				|| str[i] == '_'))
			{
				tmp[k] = str[i];
				i++;
				k++;
			}
			tmp[k] = '=';
			tmp[k + 1] = '\0';
			tmp2 = get_env_var(g_env, tmp, 0);
			j = 0;
			i = l;
			while (tmp2[j])
			{
				ret[i] = tmp2[j];
				i++;
				j++;
			}
			l += ft_strlen(tmp);
			free(tmp);
			free(tmp2);
		}
		else
		{
			ret[i] = str[l];
			i++;
			l++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

char	*parse_arg(char *str, int i)
{
	char	*ret;

	if (str == NULL)
		return (NULL);
	(void)i;
	ret = malloc(sizeof(char) * parsed_length(str, 0, 0, 0));
	if (!ret)
		return (NULL);
	ret = fill_ret(ret, str, 0, 0);
	return (ret);
}
