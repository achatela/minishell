#include "minishell.h"

char	*parse_arg(char *str, int i)
{
	char	*ret;

	ret = str_no_quotes(str, i, 0, 0);
	return (ret);
}
