#include "minishell.h"

static int	ft_count(char const *s, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s[a] && s[a] == c)
		a++;
	while (s[a])
	{
		while (s[a] && s[a] != c)
			a++;
		b++;
		while (s[a] && s[a] == c)
			a++;
	}
	return (b);
}

static char	*strdup_modif(char const *s, char c, int a)
{
	int		d;
	char	*str;
	int		b;
	int		tmp;

	d = -1;
	b = 0;
	while (s[a] && s[a] == c)
		a++;
	tmp = a;
	while (s[tmp] && s[tmp] != c)
	{
		b++;
		tmp++;
	}
	str = malloc(sizeof(char) * (b + 1));
	if (!str)
		return (NULL);
	while (++d < b && s[a])
	{
		str[d] = s[a];
		a++;
	}
	str[d] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		a;
	int		b;
	char	**tab;

	a = 5;
	b = 0;
	while (s[a] && s[a] == c)
		a++;
	tab = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[a] && b < ft_count(s, c))
	{
		tab[b] = strdup_modif(s, c, a);
		while (s[a] && s[a] != c)
			a++;
		while (s[a] && s[a] == c)
			a++;
		b++;
	}
	tab[b] = 0;
	return (tab);
}

