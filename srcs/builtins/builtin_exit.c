
#include "minishell.h"

int    builtin_exit(char **cmds)
{
    int i;

    i = 0;
    if (cmds[0] && !cmds[1])
    {
        free_cmds(cmds, 0);
        free_env(g_env, 0);
        exit(0);
    }
    else if (ft_strisnum(cmds[1]) == 1 && cmds[2])
        printf("minishell: exit: too many arguments\n");
    else if (cmds[1] && ft_strisnum(cmds[1]) == 0)
    {
        printf("minishell: exit: %s: numeric argument required\n", cmds[1]);
        free_cmds(cmds, 0);
        exit(2);
    }
    else if (cmds[1] && cmds[2])
    {
        printf("minishell: exit: too many arguments\n");
        free_cmds(cmds, 0);
        exit(2);
    }
    else if (cmds[1])
    {
        i = ft_atoi(cmds[1]) % 256;
        free_cmds(cmds, 0);
        free_env(g_env, 0);
        exit(i);
    }
    return (0);
}
