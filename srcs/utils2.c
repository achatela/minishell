#include "minishell.h"

int	invalid_identifiers(char c)
{
	if ((c <= 13 && c >= 1) || c == '!' || c == '"' || c == '#'
		|| c == '$' || c == '%' || c == '&' || c == 39 || c == '('
		|| c == ')' || c == '*' || c == ';' || c == '<' || c == '>'
		|| c == '\\' || c == '`' || c == '{' || c == '}' || c == '|'
		|| c == 127 || c == '~')
		return (1);
	else
		return (0);
}
