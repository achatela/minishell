#include "../includes/minishell.h"

int main(void)
{
	int	fd;

	dup2(1, fd);
	write(fd, "e", 1);
	return (0);
}
