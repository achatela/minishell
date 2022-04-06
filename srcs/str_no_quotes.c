#include "minishell.h"

static int	length_no_quotes(char *str, int i, int j, int k)
{
	char	*tmp;
	char	*tmp2;
	int		length;

	length = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			i++;
			length++;
		}
		else
		{
			i++;
			j = i;
			while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
					|| str[j] == '_' || str[j] == '-' /*|| str[j] == '/')*/))
				j++;
			tmp = malloc(sizeof(char) * (j - i) + 2);
			k = -1;
			while (++k > -1 && i < j)
				tmp[k] = str[i++];
			tmp[k++] = '=';
			tmp[k] = '\0';
			tmp2 = get_env_var(g_env, tmp, 0);
			length += ft_strlen(tmp2);
			free(tmp);
			free(tmp2);
		}
	}
	return (length + 1);
}

char	*str_no_quotes(char *str, int i, int j, int k)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		l;

	l = 0;
	ret = malloc(sizeof(char) * (length_no_quotes(str, 0, 0, 0)));
	while (str[i])
	{
		if (str[i] && str[i] != '$')
			ret[l++] = str[i++];
		else
		{
			i++;
			j = i;
			while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1/*	Refaire la partie invalid identifiers
																					(ils sont dans le .h)
																					*/
					|| str[j] == '_' || str[j] == '-'/*|| str[j] == '/')*/))
				j++;
			tmp = malloc(sizeof(char) * (j - i) + 2);
			k = -1;
			while (++k > -1 && i < j)
				tmp[k] = str[i++];
			tmp[k++] = '=';
			tmp[k] = '\0';
			k = -1;
			tmp2 = get_env_var(g_env, tmp, 0);
			free(tmp);
			while (tmp2[++k])
				ret[l++] = tmp2[k];
			free(tmp2);
		}
	}
	ret[l] = '\0';
	return (ret);
}
