#include "minishell.h"

//home < pwd home > pwd home == pwd


char	*get_prompt(char **env)
{
	char	**ret;

	ret = malloc(sizeof(char *) * 4);
	ret[0] = get_env_var(env, "USER", 0);
	ret[1] = get_session(env, 0);
	return (tmp);
}
