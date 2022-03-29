#include "minishell.h"

static int	get_command(char *s)
{
	if (ft_strlen(s) == 4 && s[0] == 'e' && s[1] == 'c'
		&& s[2] == 'h' && s[3] == 'o' && s[4] == '\0')
		return (1);
	if (ft_strlen(s) == 3 && s[0] == 'c' && s[1] == 'd'
		&& s[2] == '\0')
		return (2);
	if (ft_strlen(s) == 4 && s[0] == 'p' && s[1] == 'w'
		&& s[2] == 'd' && s[3] == '\0')
		return (3);
	if (ft_strlen(s) == 7 && s[0] == 'e' && s[1] == 'x'
		&& s[2] == 'p' && s[3] == 'o' && s[4] == 'r'
		&& s[5] == 't' && s[6] == '\0')
		return (4);
	if (ft_strlen(s) == 6 && s[0] == 'u' && s[1] == 'n'
		&& s[2] == 's' && s[3] == 'e' && s[4] == 't'
		&& s[5] == '\0')
		return (5);
	if (ft_strlen(s) == 4 && s[0] == 'e' && s[1] == 'n'
		&& s[2] == 'v' && s[3] == '\0')
		return (6);
	if (ft_strlen(s) == 5 && s[0] == 'e' && s[1] == 'x'
		&& s[2] == 'i' && s[3] == 't' && s[4] == '\0')
		return (7);
	return (-1);
}

void	send_builtin(char **cmds)
{
	if (get_command(cmds[0]) == 1)
		builtin_echo(cmds, 1);
}
