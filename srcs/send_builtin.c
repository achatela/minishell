#include "minishell.h"

static int	get_command(char *s)
{
	if (ft_strlen(s) == 4 && s[0] == 'e' && s[1] == 'c'		/* ECHO */
		&& s[2] == 'h' && s[3] == 'o' && s[4] == '\0')
		return (1);
	if (ft_strlen(s) == 2 && s[0] == 'c' && s[1] == 'd'		/* CD */
		&& s[2] == '\0')
		return (2);
	if (ft_strlen(s) == 3 && s[0] == 'p' && s[1] == 'w'		/* PWD */
		&& s[2] == 'd' && s[3] == '\0')
		return (3);
	if (ft_strlen(s) == 6 && s[0] == 'e' && s[1] == 'x'		/* EXPORT */
		&& s[2] == 'p' && s[3] == 'o' && s[4] == 'r'
		&& s[5] == 't' && s[6] == '\0')
		return (4);
	if (ft_strlen(s) == 5 && s[0] == 'u' && s[1] == 'n'		/* UNSET */
		&& s[2] == 's' && s[3] == 'e' && s[4] == 't'
		&& s[5] == '\0')
		return (5);
	if (ft_strlen(s) == 3 && s[0] == 'e' && s[1] == 'n'		/* ENV */
		&& s[2] == 'v' && s[3] == '\0')
		return (6);
	if (ft_strlen(s) == 4 && s[0] == 'e' && s[1] == 'x'		/* EXIT */
		&& s[2] == 'i' && s[3] == 't' && s[4] == '\0')
		return (7);
	return (-1);
}

int	send_builtin(char **cmds)
{
	if (get_command(cmds[0]) == 1)
		return(builtin_echo(cmds, 1));
	if (get_command(cmds[0]) == 2)
		return(builtin_cd(cmds, 0));
	if (get_command(cmds[0]) == 3)
		printf("%s\n", getcwd(NULL, 0));
	if (get_command(cmds[0]) == 7)
		return(builtin_exit(cmds));
	return (-1);
}
