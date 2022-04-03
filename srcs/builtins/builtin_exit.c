
#include "minishell.h"

/* /!\ /!\ /!\ FIX LES "" /!\ /!\ /!\ */
/* /!\ /!\ /!\ FIX LES "" /!\ /!\ /!\ */
/* /!\ /!\ /!\ FIX LES "" /!\ /!\ /!\ */
/* C FIX TKT MEME PAS */

int    builtin_exit(t_args *args)
{
    int i;

    i = 0;
	args = args->next;
    if (args == NULL)
    {
    //    free_cmds(cmds, 0);
        free_env(g_env, 0);
        exit(0);
    }
    else if (ft_strisnum(args->parsed_arg) == 1
			&& args->next != NULL)
        printf("minishell: exit: too many arguments\n");
    else if (ft_strisnum(args->parsed_arg) == 1)
    {
        printf("minishell: exit: %s: numeric argument required\n", args->parsed_arg);
        printf("[%s]\n", args->parsed_arg);
       // free_cmds(cmds, 0);
        exit(2);
    }
    else if (args && args->next)
    {
        printf("minishell: exit: too many arguments\n");
      //  free_cmds(cmds, 0);
        exit(2);
    }
    else if (args && ft_strisnum(args->parsed_arg) == 0)
    {
        i = ft_atoi(args->parsed_arg) % 256;
       // free_cmds(cmds, 0);
        free_env(g_env, 0);
        exit(i);
    }
    return (0);
}
