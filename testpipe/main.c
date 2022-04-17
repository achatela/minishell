#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int	pid;
	int p[2];
	int	ret = 0;
	char	tmp;

	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		write(p[1], "eeee", 5);
		ret = 1;
	}
	else if (pid != 0)
	{
		close(p[1]);
		close(0);
		dup2(p[0], 0);
		read(p[0], &tmp, 1);
	/*	while (tmp != '\0')
		{
			write(1, &tmp, 1);
			read(p[0], &tmp, 1);
		}*/
	}
//	printf("sorti\n");
	return (ret);
}
