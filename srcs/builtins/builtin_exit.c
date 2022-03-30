
#include "minishell.h"

int    builtin_exit(char **cmds)
{
    if (ft_strisnum(cmds[1]) == 1 && cmds[2])
        printf("minishell: exit: too many arguments\n");
    else if (cmds[1] && ft_strisnum(cmds[1]) == 0)
    {
        printf("minishell: exit: %s: numeric argument required\n", cmds[1]);
        exit(2);
    }
    else if (cmds[1] && cmds[2])
    {
        printf("minishell: exit: too many arguments\n");
        exit(2);
    }
    else if (cmds[1])
        exit(ft_atoi(cmds[1]) % 256);
    return (0);
}
