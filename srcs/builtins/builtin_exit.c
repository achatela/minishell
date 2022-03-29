#include "minishell.h"

int    builtin_exit(char **cmds)
{
    int i;
    int arg;
    int chr;
    // int ret;

    i = 1;
    chr = 0;
    arg = 0;
    // ret = 0;
    while (cmds[arg] != NULL)
        arg++;
    printf("arg: %d\n", arg);
    while (arg)
    {
        if (arg == 1)
            exit (0);
        i++;
        if (arg > 2 && ft_isalnum(cmds[i][chr]) == 0)
        {
            printf("minishell: exit: too many arguments\n");
            return (1);
        }
        if (ft_isalpha(cmds[i][chr]) == 0)
        {
            printf("minishell: exit: %s: numeric argument required\n", cmds[1]);
            exit(2);
        }
        i++;
        chr++;
        arg--;
    }
    return (0);
}